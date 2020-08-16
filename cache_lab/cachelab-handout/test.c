#include <stdio.h>
#include <limits.h>
int main(){
    long int a = (long int)INT_MAX + 10;
    printf("%ld\n", a);
    printf("%ld\n", (unsigned long long int)-1);

    return 0;

}