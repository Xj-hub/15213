#include <iostream>
int fun(int x, int y, int rdi){
    int a = y - x;
    int c = a;
    c = 0;
    a = c + a;
    a = a>>1;
    c = a + x;
    if ( c<= rdi){
        a = 0;
        if(c >= rdi)
        return a;
        else{
            x = c + 1;
            a = fun(x, y, rdi);
            a = a + a + 1;
            return a;
        }
    }
    return -1;
}

int main(){
    int r =  fun(0, 14, 7);
    std::cout<<r<<'\n';
    return 0;
}