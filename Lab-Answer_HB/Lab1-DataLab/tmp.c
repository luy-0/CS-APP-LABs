#include <stdio.h>
// #include <iostream>

// using namespace std;
int bitXor(int x, int y) {
  int re = ~x&y;
  return re;
}
int isTmax(int x) {
  /* 
  不能用条件语句
  构造映射: Tmax->1; others -> 0;
   */
  int tmin = 1 << 31;
  int tmp = tmin | x;   //全部是1
//   printf("%x",tmp);
  tmp = ~tmp;           //全部是0
  int re = !tmp;        //!逻辑非,~按位取反
  return re;
}
int isLessOrEqual(int x, int y) {
  int x_n = ~x + 1;
  int re = !((y + x_n)>>31);
  return re;
}
int isAsciiDigit(int x) {
  /*  */
  int min = 0x30;
  int max = 0x39;
  int min_n = ~min + 1;
  int x_n = ~x + 1;
  int if1 = !((x + min_n)>>31);
  int if2 = !((max + x_n)>>31);
  int re = if1 & if2;
  return re;
}
int conditional(int x, int y, int z) {
  /*  */
  int isZero = ((!x)<<31)>>31;  //x=0,isZ=11111111;x!=0,isZ=00000000
  int re = (y & (~isZero)) + (z & isZero);
  return re;
}
int negate(int x) {
  /* 取反加一 */
  int re = ~x + 1;
  return re;
}
int tmin(void) {
/*   已知32位intre
  求 1000 0000 0000 0000 0000 0000 0000 0000 
*/
  int re = 1;
  re = re << 31;
  return re;

}
int main(int argc, char const *argv[])
{
    for (int i = -9; i <11; i++)
    {
        int a = conditional(i,4,5);
        printf("%d\t%d\n",i,a);
    }
    
    int a = conditional(2,4,5);
    // a = a<<2;
    // a = !a;
    // printf("%d\n",a);
    // printf("%05x\n",a);
    // printf("%p\n",a);



    return 0;
}
