#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

typedef struct{
    int valid_bit;
    int tag;
    int stamp;
}cache_line;

int S = 0, E = 0, b = 0, s = 0;
int hits = 0, misses = 0, evictions = 0;
void update_stamp(cache_line cache[S][E]);
void update(unsigned long int address, cache_line cache[S][E]){
    update_stamp(cache);
    // Address of word (tag set_index block_offset)
    // address >> b is (00..00 tag set_index) need to do & with (0000..000 111111)number of set_index 1
    // -1U is 1111...11111 with 32 of 1. need to right shift 32-s bits
    int set_index = (int)((address >> b) & (unsigned long int)(-1U >>(32 - s)));
    int tag = (int)(address >> (b + s));
    // printf("address: %lx...", address);
    // printf("set_index: %d,,,tag: %d\n", set_index, tag);
    // for(int i = 0; i < E; ++i){
    //     printf("tag::::::%d timestamp::::::%d valid::::::%d ",cache[set_index][i].tag,cache[set_index][i].stamp,cache[set_index][i].valid_bit);
    // }
    // printf("\n");
    
    for(int i = 0; i < E; ++i){
        if(cache[set_index][i].tag == tag){
            if(cache[set_index][i].valid_bit == 1){
                cache[set_index][i].stamp = 0;
                hits ++;
                return;
            }
        }
    }
    // if there is no hit, check if there is cold miss
    for(int i = 0; i < E; ++i){
        if(cache[set_index][i].valid_bit == 0){
            cache[set_index][i].stamp = 0;
            cache[set_index][i].tag = tag;
            cache[set_index][i].valid_bit = 1;
            misses ++;
            return;
        }
    }
    //if there is no cold miss, all the space in current set is occupied and since no hit, we need to evict one space with largest time stamp
    int latest_block_stamp = 0, latest_block_index = 0;
    for(int i = 0; i < E; ++i){
        if(cache[set_index][i].stamp > latest_block_stamp){
            latest_block_stamp = cache[set_index][i].stamp;
            latest_block_index = i;
        }
    }
    evictions ++;
    misses ++;
    cache[set_index][latest_block_index].stamp = 0;
    cache[set_index][latest_block_index].tag = tag;
    return;
}

void update_stamp(cache_line cache[S][E]){
    for(int i = 0; i<S; i++){
        for(int j = 0; j < E; ++j){
            if(cache[i][j].valid_bit == 1)  // be careful, only update the time stamp when there is a using cache.
                cache[i][j].stamp ++;
        }
    }
}


int main(int argc, char *argv[])
{   
    int help_flag = 0, verbose_flag = 0;
    char *file = NULL;   
    char oc;
    while((oc = getopt(argc, argv, "hvs:E:b:t:")) != -1){
        switch(oc)
        {
            case 'h':
                help_flag = 1;
                break;
            case 'v':
                verbose_flag = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                file = optarg;
                break;
        }
    }
    
    if(help_flag == 1){
        system("cat help.txt");
        exit(0);
    }

    if(s == 0){
        printf("need a positive sets value, use -h to check instruction\n");
        exit(1);
    }
    if(E == 0){
        printf("need a positive lines value, use -h to check instruction\n");
        exit(1);
    }

    if(b == 0){
        printf("need a positive blocks value, use -h to check instruction\n");
        exit(1);
    }

    if(!file){
        printf("need a file name, use -h to check instruction\n");
        exit(1);
    }

    FILE * fp = fopen(file, "r");
    if(!fp){//if file pointer is NULL throw error and exit
        printf("can not open the file %s\n", file);
        exit(1);
    }

    S = 1<<s; // 2^s is S, get the how many sets 

    cache_line cache[S][E];
    memset(cache, 0, sizeof(cache));  // array name,  0 or -1 , array size
    // for(int i = 0; i<S; i++){
    //     for(int j = 0; j < E; ++j){
    //         cache[i][j].tag = -1;
    //     }
    // }
    char buffer[1000];
    unsigned long int address;
    int offset;
    char opt;
    
    while(fgets(buffer, 1000, fp)){
        sscanf(buffer," %c %lx,%d", &opt, &address, &offset);
        // printf("%c %lxu,%d\n",opt, address, offset);
        int prev_hits = hits, prev_misses = misses, prev_evictions = evictions;    
        if (opt == 'I'){
            continue;
        }
        switch(opt)
        {
            case 'L':
                update(address, cache);
                break;
            case 'M':
                update(address, cache);    
            case 'S':
                update(address, cache);
                break;
        }
        if(verbose_flag){
            printf("%c %lx,%d", opt, address, offset);
            if(misses > prev_misses) printf(" miss");
            if(evictions > prev_evictions) printf(" eviction");
            while(hits > prev_hits){
                prev_hits++;
                printf(" hit");
            } 
            printf("\n");
            
        }
        
        
    }


    fclose(fp);//don't forget to close the file
    printSummary(hits, misses, evictions);
    
    return 0;
}
