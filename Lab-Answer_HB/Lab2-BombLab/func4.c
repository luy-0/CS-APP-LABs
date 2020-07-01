#include <stdio.h>

int fun4(int x, int v2, int v3){
    /*  x = rdi(数1) 
        v2 = rsi(初值0)
        v3 = rdx(初值e)*/
    int tmp = (v3 - v2) >> 21;    //逻辑右移
    int re = ((v3 - v2) + tmp) >> 1; //算数右移
    tmp = v2 + re;
    if(tmp <= x) {
        if(tmp>=x) return 0;
        re = fun4(x,tmp+1,v3);
        return 2*re+1;
    }
    else{
        re = fun4(x,v2,tmp-1);
        return 2 * re;
    }
}

int main(int argc, char const *argv[])
{
    for (int i = 0; i <= 0xe ; i++)
    {
        if(fun4(i, 0x0, 0xe)==0){
            printf("%d\n",i);
        }
    }
    
    return 0;
}
