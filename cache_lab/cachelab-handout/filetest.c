#include <stdio.h>

int main(){
    FILE * f = fopen("filetest.txt", "r");
    char * a;
    while(fgets(a, 100, f) != NULL){
        
        printf("%s", a);
    }
    
    fclose(f);
    return 0;
}