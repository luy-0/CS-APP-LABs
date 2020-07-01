# Lab1-DataLab-Note

可以在本md中记录学习心得, 经验, 总结, 以及走过的坑!

`Notes by Levick Cheng`

`Please read problems think thoroughly before you check this notes`

[reference](https://wdxtub.com/csapp/thick-csapp-lab-1/2016/04/16/)

首先弄复习一遍操作符含义

> !  逻辑取反
>
> ~ 按位取反
>
> & 按位与
>
> ^ 按位异或
>
> |  按位或
>
> << （算数）左移
>
> \>>    (算数)右移
>
> 优先级：`！`> `~`  > `-(负号` > `+` > `-` >`<<` >`>>`>`&` > `^` > `|` 

## 1.bitXor
要求：

```c++
 \* bitXor - x^y using only ~ and & 
 \*  Example: bitXor(4, 5) = 1
 \*  Legal ops: ~ &
 \*  Max ops: 14
 \*  Rating: 1
```

首先进行位异或，我们需要清楚`异或(^)等于什么`，根据定义，我们知道

​                                                                   $Z = X \oplus Y = X\overline Y  + \overline X Y$

但是我们没有或（or）操作符，所以我们需要通过~（not，非）和&（and，与）来得到，看到这张图，相信聪明的你会想到怎么做了。

<img src="C:\Users\Levick\source\github\CSAPP\CS-APP-LABs\Lab-Notes\img\image-20200621222306462.png" alt="image-20200621222306462" style="zoom:67%;" />

​							                                              $X + Y{ = }\sim(XY)$

故答案可以为：

```c
int bitXor(int x, int y) {
  int o1=x&(~y);
  int o1=(~x)&y;
  return ~(o1&o2);
}
```

## 2.Tmin

要求：

```C	
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
```

首先明确最小整型补码是`1000...00000`，而我们可以用移位操作，那就十分明了了，只需要`000...0001`左移31位即可得到（默认int为32位）,`return 1<<31`

## 3.isTmax

requirement:

```C	
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
```

Tmax:`0111...111`, Tmin:`1000...000`,  那么Tmin左移得全0，那么我们直接将x左移1位看他是不是全0，但是需要注意到特殊情况，x本身就是全0。

Answer：

```c
int isTmax(int x) {
  int tmp=~x;
  return !(2*tmp)&!(!tmp);
}
```

## 4.allOddBits

requirement:

```c	
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
```

稍微解释一下题目，奇数位全1则返回1，反之返回0

从结果出发，我们的结果需要为全0或者全1的一个数，然后进行操作返回。奇数位全为1,那我们将x右移一位然后和0xAAAAAAAA按位或就可以得到全1了。至于0xAAAAAAAA我们可以通过移位得到（因为赋值得到的int只能在0~255之间）

Answer:

```c
int allOddBits(int x) {
  int a= 0xAA;
  int b=(a<<8)+a;//0x AA AA
  int c=(b<<8)+b;//0X AA AA AA
  int d=(c<<8)+c;//0X AA AA AA AA
  return !(d | (x>>1))
}
```

## 5.negate

requirement:

```c
* negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
```

这题比较简单，计算机通过补码解释int，补码取反怎么操作？取反加一。

```c
int negate(int x) {
  return ~x+1;
}
```

## 6.isAsciiDigit

requirement:

```c
* isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
```

判断ascII值是不是0到9，首先我们明确，‘0’=48=0x30，‘9’=58=0x39，所输入x应该在此范围内，x-‘0’>=0,x-'9'<=0.

如何实现减法？补码减法直接取反加一，因此，x-'0'=x+(~48+1)，后同。

故，参考答案如下：

```c
int isAsciiDigit(int x) {
  return ( (x+(~48+1))>>31 )& ( (x+(~58+1))>>31 );
}
```

##7. conditional

requirement:

```c
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
```

​	我们通过逻辑取反可以得到x是否为0, 而为了实现x?y:z，我们可以化简为：

​	(a&y)|(b&z)，x为0时，a全0，b全1，返回z；x为1时，a全1，b全0，返回y。根据赋值，a=!x+\~1+1，b=\~!x+1

故，参考答案如下：

```c
int conditional(int x, int y, int z) {
  return ((!x+~1+1)&y)+(~!x+1)&z;
}
```

## 8.isLessOrEqual

requirement:

```c
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
```

判断x,y大小关系，那我们可以用y-x，若结果符号为正（0）则说明x<=y，返回1，若符号为负（1），则说明x>y返回0，结果可以通过符号位取反得到

故参考答案如下：

```c
1
```

## 9.logicalNeg

requirement:

```c
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
```

逻辑取反最后的结果是0和1，且只有全0是返回1，其他情况返回均返回0。那么问题来了，如果区别全0？

​	我们可以利用补码和其相反数的一个性质，0取反还是0，但是其他数取反为其相反数。0|0=0, x|(~x+1)<0, 将x和其相反数按位或则得到0或一个负数，右移31根据其符号位可以得到我们想要的结果。

故参考答案如下：

```c
1
```

## 10.howManyBits

requirement:

```c
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
```

根据观察我们发现，正数（或0）中符号位后第一串连续的0和负数中符号位后第一串连续的1去掉后不影响结果