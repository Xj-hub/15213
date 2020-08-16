#include <stdio.h>
#include <stdlib.h>
// int main(){
//     char *a;
//     int n = 60;
//     sscanf(a, "%d", &n);
//     printf("%s", a);
// }


// int main() {
//     int* a = malloc(100*sizeof(int));
//     for (int i=0; i < 100; i++) {
//         a[i] = i;
//         printf("%d\n", a[i]);
//     }

//     free(a);
//     return 0;
// }

// #include <stdio.h>
// #include <unistd.h>

// int main (int argc, char **argv)
// {
//     int oc;                     /*选项字符 */
//     char ec;                             /*无效的选项字符*/
//     char *b_opt_arg;            /*选项参数字串 */

//     while((oc = getopt(argc, argv, ":ngl:")) != -1) ////////////////////////////here :hgl: is the differenece
//     {
//         switch(oc)
//         {
//             case 'n':
//                 printf("My name is Lyong.\n");
//                 break;
//              case 'g':
//                 printf("Her name is Xxiong.\n");
//                 break;
//             case 'l':
//                 b_opt_arg = optarg;
//                 printf("Our love is %s\n", optarg);
//                 break;
//             case '?':
//                 ec = (char)optopt;
//                 printf("无效的选项字符 \' %c \'!\n", ec);
//                 break;
//             case ':':
//                 printf("缺少选项参数！\n");
//                 break;
//         }
//     }
//     return 0;
// }

#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    int oc;                     /*选项字符 */
    char *b_opt_arg;            /*选项参数字串 */

    while((oc = getopt(argc, argv, "ngl:")) != -1)
    {
        switch(oc)
        {
            case 'n':
                printf("My name is Lyong.\n");
                break;
             case 'g':
                system("cat help.txt");
                break;
            case 'l':
                b_opt_arg = optarg;
                printf("Our love is %s\n", optarg);
                break;
            case '?':
                printf("arguments error!\n");
                break;
        }
    }
    return 0;
}