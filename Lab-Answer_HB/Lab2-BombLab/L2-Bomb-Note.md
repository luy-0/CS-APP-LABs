# Lab2:BombLab Note

提示: 本文可能直接包含答案, 如果你想自己解决,不建议使用本文.

## Catalog

1. GDB	包括GDB基本使用法, 但不全面
2. Bombs  包括各炸弹的题解与答案
3. Functions    包括各函数及其受调用函数的反汇编,及解释

## GDB

### Breakpoints

```
 break sum					进入sum()时断点
 break *0x80483c3 			在地址 0x80483c3 设置断点(注意`\*号)
```



### Execution

```
stepi n						执行n条指令,缺省为1 会进入被调用函数
nexti n						执行n条指令,缺省为1 不会进入被调用函数
```



### Print

```
print (char *) 0xbfff890   	Examine a string stored at 0xbffff890

print  /x $rip         		十六进制打印rip寄存器 (/x可换为/d或/b)

print *(int *) 0xbffff890 	Print integer at address 0xbffff890

print *(int **) ($rsp+8)	Print address at address  ($rsp+8)

```

### Info



```
 info registers     	Print all registers and their contents 

info breakpoints  		Print status of user-settable breakpoints
```



## Bombs

### Bomb1

炸弹1涉及到以下函数:

1. Phase_1
2. strings_not_equal
3. string_length

输入一个字符串, 它将与位于地址`0x402400`的字符串比较, 相符即可拆除.

因此答案为:

> Border relations with Canada have never been better.


### Bomb2

炸弹2涉及到以下函数:

1. Phase_2
2. read_six_numbers

输入6个数字, 第一个是1, 剩下成公比为2的G.P. 即可拆除.

因此答案为:

> 1 2 4 8 16 32

 

### Bomb3

炸弹3涉及到以下函数:

1. phase_3
2. __isoc99_sscanf

输入两个数字, 这两个数字必须是以下8组之一:

- 0    207
- 1    311
- 2    707
- 3    256
- 4    389
- 5    206
- 6    682
- 7    327

例如,答案可以输入:

> 2   707

答案不唯一

### Bomb4

这个递归炸弹真把我整🤮了... 每一条汇编指令都能看懂在干什么, 合在一起就傻了, 连猜带蒙把答案鼓捣出来了...

我讨厌递归😭

PS: 后来用反汇编解决了

炸弹4涉及到以下函数:

1. phase_4
2. func4

输入两个数字, 数字1必须为 `{0,1,3,7}` 中任一个, 数字2必须为 `0`.

例如, 答案可以输入:

> 3  0

答案不唯一

## Functions

### Main()

```

```

---

### Phase_1

- 输入: 一个字符指针 input
- 功能: input 指向对象与 地址`$0x402400`指向对象相同,不同炸
- 调用: strings_not_equal();  explode_bomb();
- 返回: 0

```
Dump of assembler code for function phase_1:
//rdi = *input
    0x0000000000400ee0 <+0>:	sub    $0x8,%rsp        //栈下调8位
    0x0000000000400ee4 <+4>:	mov    $0x402400,%esi   //$0x402400 放入%esi(参数2)
    0x0000000000400ee9 <+9>:	callq  0x401338 <strings_not_equal> //调用strings_not_equal
    0x0000000000400eee <+14>:	test   %eax,%eax       //检测参1参2是否相同
    0x0000000000400ef0 <+16>:	je     0x400ef7 <phase_1+23>    //0相同 转+23
    0x0000000000400ef2 <+18>:	callq  0x40143a <explode_bomb>  //1不同,炸
    0x0000000000400ef7 <+23>:	add    $0x8,%rsp    //出栈
    0x0000000000400efb <+27>:	retq 

```



### strings_not_equal

- 输入: 参数12 均为字符地址
- 功能: 比较两个指向对象长度与内容是否相同
- 调用: string_length()
- 返回: 相同返回0, 不同返回1

```
Dump of assembler code for function strings_not_equal:
/* rdi = *input; esi = $0x402400
    0x0000000000401338 <+0>:	push   %r12
    0x000000000040133a <+2>:	push   %rbp
    0x000000000040133b <+3>:	push   %rbx     //以上保存环境
    0x000000000040133c <+4>:	mov    %rdi,%rbx    //rbx = *input
    0x000000000040133f <+7>:	mov    %rsi,%rbp    //rbp = $0x402400(地址)
    0x0000000000401342 <+10>:	callq  0x40131b <string_length> //调用string_length, 参数不变
    0x0000000000401347 <+15>:	mov    %eax,%r12d   //r12d(双字)保存字符串长度
    0x000000000040134a <+18>:	mov    %rbp,%rdi    //计算($0x402400)的长度
    0x000000000040134d <+21>:	callq  0x40131b <string_length> //($0x402400)长度保存在rax
    0x0000000000401352 <+26>:	mov    $0x1,%edx    //edx = 1
    0x0000000000401357 <+31>:	cmp    %eax,%r12d   //字符串与常数长度比较
    0x000000000040135a <+34>:	jne    0x40139b <strings_not_equal+99>  //长度不同转99
    0x000000000040135c <+36>:	movzbl (%rbx),%eax  //串1 -> rax
    0x000000000040135f <+39>:	test   %al,%al
    0x0000000000401361 <+41>:	je     0x401388 <strings_not_equal+80>//如果串1空,转80
    0x0000000000401363 <+43>:	cmp    0x0(%rbp),%al        //比较串1串2
    0x0000000000401366 <+46>:	je     0x401372 <strings_not_equal+58>  //相等,转58
    0x0000000000401368 <+48>:	jmp    0x40138f <strings_not_equal+87>  //不等,转87
    0x000000000040136a <+50>:	cmp    0x0(%rbp),%al    //比较(常数)与字符串
    0x000000000040136d <+53>:	nopl   (%rax)       //好像是对齐用的? 无操作
    0x0000000000401370 <+56>:	jne    0x401396 <strings_not_equal+94>  //不等转94
    0x0000000000401372 <+58>:	add    $0x1,%rbx    //字符串指针++
    0x0000000000401376 <+62>:	add    $0x1,%rbp    //常数地址指针++
    0x000000000040137a <+66>:	movzbl (%rbx),%eax  
    0x000000000040137d <+69>:	test   %al,%al      //如果字符串不空
    0x000000000040137f <+71>:	jne    0x40136a <strings_not_equal+50> //转+50
    0x0000000000401381 <+73>:	mov    $0x0,%edx	//如果串1空
    0x0000000000401386 <+78>:	jmp    0x40139b <strings_not_equal+99>
    0x0000000000401388 <+80>:	mov    $0x0,%edx	//上接41,串1空, 返回0
    0x000000000040138d <+85>:	jmp    0x40139b <strings_not_equal+99>
    0x000000000040138f <+87>:	mov    $0x1,%edx    //上接48,串12不等,返回1
    0x0000000000401394 <+92>:	jmp    0x40139b <strings_not_equal+99>
    0x0000000000401396 <+94>:	mov    $0x1,%edx    //上接94,串不等,返回1
    0x000000000040139b <+99>:	mov    %edx,%eax    //上接34,长度不等,返回1
    0x000000000040139d <+101>:	pop    %rbx 
    0x000000000040139e <+102>:	pop    %rbp
    0x000000000040139f <+103>:	pop    %r12 //恢复环境
    0x00000000004013a1 <+105>:	retq   

```

注:

1. 开头结尾有保存环境的push与pop操作

2. r12d 指12寄存器的双字部分, 依次是:r12, r12d, r12w, r12b. d疑似指double word

3. nopl 为无操作, 可参考[这里](https://exp.newsmth.net/topic/article/9a37ce02c405b2b7ae9558f161f38c38).

4. 过程:

   1. 先比较两串的长度,若不同直接返回1(+34); 
   2. 然后一个一个bit地比较, 每次比较完跳转回+50, 直到全部比较结束, 串为空,返回0
   3. 当比较中遇到串不等, 立刻退出,返回1

5. 疑惑:

   1. 为什么每次指针仅仅是自加? 每次是对al比较(1byte), 指针+4岂不美哉?

   2. 87,94,99都是出错, 返回1, 为什么不合并成1个? 

      (猜测:可能是优化级别不够, 照顾我们的智力水平😂)



### string_length

- 输入: 字符指针
- 功能: 返回指向的串的长度, 空返回0
- 无调用
- 返回: 返回指向的串的长度, 空返回0

```
rdi = *input; 
Dump of assembler code for function string_length:
    0x000000000040131b <+0>:	cmpb   $0x0,(%rdi)      
    0x000000000040131e <+3>:	je     0x401332 <string_length+23>  //如果input空, 转23(返回0)
    0x0000000000401320 <+5>:	mov    %rdi,%rdx        //rdx = *input
    0x0000000000401323 <+8>:	add    $0x1,%rdx        //rdx ++ 每轮将指针+1 
    0x0000000000401327 <+12>:	mov    %edx,%eax    //eax =rdx
    0x0000000000401329 <+14>:	sub    %edi,%eax    //eax -= edi, 当前指针与原指针差值
    0x000000000040132b <+16>:	cmpb   $0x0,(%rdx)  //指针指向与0比较
    0x000000000040132e <+19>:	jne    0x401323 <string_length+8>//当指向非零, 表示还未结束 递归调用
    0x0000000000401330 <+21>:	repz retq   //返还rax 即最后的差值, 为指针储存的数据的长度
    0x0000000000401332 <+23>:	mov    $0x0,%eax    //(上接+3) 返回0
    0x0000000000401337 <+28>:	retq  
```



---

### Phase_2

- 输入: *input
- 功能: 与六个数字比较, 不同炸
- 调用: read_six_numbers
- 返回: 无

```
Dump of assembler code for function phase_2:
//rdi *input
    0x0000000000400efc <+0>:	push   %rbp
    0x0000000000400efd <+1>:	push   %rbx			//保存环境
    0x0000000000400efe <+2>:	sub    $0x28,%rsp   //栈分28位
    0x0000000000400f02 <+6>:	mov    %rsp,%rsi    //栈指针作为第二个参数
    0x0000000000400f05 <+9>:	callq  0x40145c <read_six_numbers>	//读数在栈内
    0x0000000000400f0a <+14>:	cmpl   $0x1,(%rsp)  //栈顶元素与1比较
    0x0000000000400f0e <+18>:	je     0x400f30 <phase_2+52>    //不同炸, 相同转52
    0x0000000000400f10 <+20>:	callq  0x40143a <explode_bomb>
    0x0000000000400f15 <+25>:	jmp    0x400f30 <phase_2+52>
    0x0000000000400f17 <+27>:	mov    -0x4(%rbx),%eax      //eax = 栈元素前一个元素
    0x0000000000400f1a <+30>:	add    %eax,%eax            //eax *= 2
    0x0000000000400f1c <+32>:	cmp    %eax,(%rbx)              //rbx(下一个元素)与eax(两倍的上一个元素)比较
    0x0000000000400f1e <+34>:	je     0x400f25 <phase_2+41>    //不同炸,相同转41
    0x0000000000400f20 <+36>:	callq  0x40143a <explode_bomb>
    0x0000000000400f25 <+41>:	add    $0x4,%rbx            //rbx = 栈下一个元素
    0x0000000000400f29 <+45>:	cmp    %rbp,%rbx            //rbx 与 rbp比较
    0x0000000000400f2c <+48>:	jne    0x400f17 <phase_2+27>    //不同转27,继续轮回
    0x0000000000400f2e <+50>:	jmp    0x400f3c <phase_2+64>//相同,第六个元素 转64
    0x0000000000400f30 <+52>:	lea    0x4(%rsp),%rbx       //rbx = 下一个元素
    0x0000000000400f35 <+57>:	lea    0x18(%rsp),%rbp      //rbp = 栈顶+18(应该是第六个元素,存疑)
    0x0000000000400f3a <+62>:	jmp    0x400f17 <phase_2+27>   //转27
    0x0000000000400f3c <+64>:	add    $0x28,%rsp           //出栈28位
    0x0000000000400f40 <+68>:	pop    %rbx
    0x0000000000400f41 <+69>:	pop    %rbp             //恢复环境
    0x0000000000400f42 <+70>:	retq                    //结束
```

注: 

1. read_six_numbers 函数内其实没看懂, 由名字猜测了一波
2. lea S D指令, 将S(一个有效地址) 复制给D, 后续引用(D)用法类似指针
3. `add    $0x4,%rbx` 指针下一个元素, 注意栈是倒过来储存的
4. 存疑:
   1. 57 行, `%rbp`应该是被赋了第六个参数的值. 可是为什么是+18? 不应该是+ 20(4*5)吗?



### read_six_numbers

- 输入: *input, 栈指针
- 功能: 读取6个数据储存在栈中
- 调用: __isoc99_sscanf@plt (疑似库函数?)
- 返回: 无

```
Dump of assembler code for function read_six_numbers:
    //rdi *input    rsi 栈指针
    0x000000000040145c <+0>:	sub    $0x18,%rsp       //分配18
    0x0000000000401460 <+4>:	mov    %rsi,%rdx        //rdx = 原栈指针
    0x0000000000401463 <+7>:	lea    0x4(%rsi),%rcx   //rcx = (原栈2)
    0x0000000000401467 <+11>:	lea    0x14(%rsi),%rax  //rax = (原栈+14)
    0x000000000040146b <+15>:	mov    %rax,0x8(%rsp)   //(栈+8) = 原栈+14
    0x0000000000401470 <+20>:	lea    0x10(%rsi),%rax  //rax = (原栈+10)
    0x0000000000401474 <+24>:	mov    %rax,(%rsp)      //(rsp) = rax = (原栈+10)
    0x0000000000401478 <+28>:	lea    0xc(%rsi),%r9    //r9 = (rsi+c)
    0x000000000040147c <+32>:	lea    0x8(%rsi),%r8    //r8 = (rsi+8)
    0x0000000000401480 <+36>:	mov    $0x4025c3,%esi   //si = $0x4025c3
    0x0000000000401485 <+41>:	mov    $0x0,%eax        //ax = 0
    0x000000000040148a <+46>:	callq  0x400bf0 <__isoc99_sscanf@plt>
    0x000000000040148f <+51>:	cmp    $0x5,%eax        //结果与5比较
    0x0000000000401492 <+54>:	jg     0x401499 <read_six_numbers+61>//结果>5 不炸
    0x0000000000401494 <+56>:	callq  0x40143a <explode_bomb>
    0x0000000000401499 <+61>:	add    $0x18,%rsp       //收回18
    0x000000000040149d <+65>:	retq 
```

嗯...虽然我没懂他每一步在干什么, 不妨碍我猜出他是用来干啥的.

### Phase_3

- 输入: *input
- 功能: 与两个数字比较, 不同炸
- 调用: __isoc99_sscanf
- 返回: 无

```
rdi = &input
Dump of assembler code for function phase_3:
    0x0000000000400f43 <+0>:	    sub    $0x18,%rsp               //栈扩18
    0x0000000000400f47 <+4>:	    lea    0xc(%rsp),%rcx           //rcx = &(栈12)
    0x0000000000400f4c <+9>:	    lea    0x8(%rsp),%rdx           //rdx = &(栈8)
    0x0000000000400f51 <+14>:	mov    $0x4025cf,%esi           //si = $0x4025cf
    0x0000000000400f56 <+19>:	mov    $0x0,%eax                //ax = $0x0
    0x0000000000400f5b <+24>:	callq  0x400bf0 <__isoc99_sscanf@plt>   // 见注解p3_1,将2个数字装入栈8 和 栈12处
    0x0000000000400f60 <+29>:	cmp    $0x1,%eax                //ax与1比较 
    0x0000000000400f63 <+32>:	jg     0x400f6a <phase_3+39>    //ax>1 跳转39 否则炸
    0x0000000000400f65 <+34>:	callq  0x40143a <explode_bomb>
    0x0000000000400f6a <+39>:	cmpl   $0x7,0x8(%rsp)           //*(栈8)与7比较 (也就是数字1与7比较)
    0x0000000000400f6f <+44>:	ja     0x400fad <phase_3+106>   //*(栈8)>7(无符号) 转106,炸
    0x0000000000400f71 <+46>:	mov    0x8(%rsp),%eax           //ax = *(栈8) 数1
    0x0000000000400f75 <+50>:	jmpq   *0x402470(,%rax,8)       //跳转到(ax*8+0x402470) 见注解p3_2
    0x0000000000400f7c <+57>:	mov    $0xcf,%eax               //上接50 且ax=0 key = 0xcf = 207
    0x0000000000400f81 <+62>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400f83 <+64>:	mov    $0x2c3,%eax              //上接50 且ax=2 key = 0x2c3 = 707
    0x0000000000400f88 <+69>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400f8a <+71>:	mov    $0x100,%eax              //上接50 且ax=3 key = 0x100 = 256
    0x0000000000400f8f <+76>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400f91 <+78>:	mov    $0x185,%eax              //上接50 且ax=4 key = 0x185 = 389
    0x0000000000400f96 <+83>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400f98 <+85>:	mov    $0xce,%eax               //上接50 且ax=5 key = 0xce  = 206
    0x0000000000400f9d <+90>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400f9f <+92>:	mov    $0x2aa,%eax              //上接50 且ax=6 key = 0x2aa = 682
    0x0000000000400fa4 <+97>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400fa6 <+99>:	mov    $0x147,%eax              //上接50 且ax=7 key = 0x147 = 327
    0x0000000000400fab <+104>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400fad <+106>:	callq  0x40143a <explode_bomb>  //上接44,输入个数<2
    0x0000000000400fb2 <+111>:	mov    $0x0,%eax                //这里是什么情况?存疑
    0x0000000000400fb7 <+116>:	jmp    0x400fbe <phase_3+123>
    0x0000000000400fb9 <+118>:	mov    $0x137,%eax              //上接50 且ax=1 key = 0x137 = 311
    0x0000000000400fbe <+123>:	cmp    0xc(%rsp),%eax           //比较ax(即key)与数2
    0x0000000000400fc2 <+127>:	je     0x400fc9 <phase_3+134>   //不等炸
    0x0000000000400fc4 <+129>:	callq  0x40143a <explode_bomb>
    0x0000000000400fc9 <+134>:	add    $0x18,%rsp
    0x0000000000400fcd <+138>:	retq   
```

注: 

1. 输入两个数字,分别储存在栈8与栈12处, 多余输入不计

2. 如果输入1个,直接炸

3. 数1(栈8) 若>(unsigned )7, 直接炸

4. 根据数1的不同取值(0~7), 跳转到栈种储存的不同地址, 并根据地址拿到key(存储到ax中)

5. 数2(栈12) 与 key比较, 不同炸, 相同过

6. 疑惑:

   +111处是什么时候会运行到? 直接把ax赋0?

#### 注解p3_1    

**__isoc99_sscanf()**

​    c99标准库sscanf函数, [参考链接](http://www.cplusplus.com/reference/cstdio/sscanf/)

> ​    int sscanf ( const char * s, const char * format, ...);
>
> ​    Read formatted data from string
>
> ​    Reads data from s and stores them according to parameter format into the locations given by the additional arguments, as if scanf was used, but reading from s instead of the standard input (stdin).
>
> ​    The additional arguments should point to already allocated objects of the type specified by their corresponding format specifier within the format string.
>
> ​    Return Value
>
> ​    On success, the function returns the number of items in the argument list successfully filled. This count can match the expected number of items or be less (even zero) in the case of a matching failure.
>
> ​    In the case of an input failure before any data could be successfully interpreted, EOF is returned. 

​    返回读取到的item的个数

#### 注解p3_2  

**每个(ax*8+0x402470)中储存的地址**

```
(gdb) print *(int**)  (0x402470+8*0)
$11 = (int *) 0x400f7c <phase_3+57>

(gdb) print *(int**)  (0x402470+8*1)
$12 = (int *) 0x400fb9 <phase_3+118>

(gdb) print *(int**)  (0x402470+8*2)
$13 = (int *) 0x400f83 <phase_3+64>

(gdb) print *(int**)  (0x402470+8*3)
$14 = (int *) 0x400f8a <phase_3+71>

(gdb) print *(int**)  (0x402470+8*4)
$15 = (int *) 0x400f91 <phase_3+78>

(gdb) print *(int**)  (0x402470+8*5)
$16 = (int *) 0x400f98 <phase_3+85>

(gdb) print *(int**)  (0x402470+8*6)
$17 = (int *) 0x400f9f <phase_3+92>

(gdb) print *(int**)  (0x402470+8*7)
$18 = (int *) 0x400fa6 <phase_3+99>
```



### Phase_4

- 输入: *input
- 功能: 与两个数字比较, 不同炸
- 调用: __isoc99_sscanf
- 返回: 无

```
%rdi &input
Dump of assembler code for function phase_4:
    0x000000000040100c <+0>:	sub    $0x18,%rsp               //扩栈18
    0x0000000000401010 <+4>:	lea    0xc(%rsp),%rcx           //cx 栈12   数2
    0x0000000000401015 <+9>:	lea    0x8(%rsp),%rdx           //dx 栈8    数1
    0x000000000040101a <+14>:	mov    $0x4025cf,%esi           //si = 0x4025cf
    0x000000000040101f <+19>:	mov    $0x0,%eax                //ax = 0
    0x0000000000401024 <+24>:	callq  0x400bf0 <__isoc99_sscanf@plt>   //读取
    0x0000000000401029 <+29>:	cmp    $0x2,%eax                //读入2个数字
    0x000000000040102c <+32>:	jne    0x401035 <phase_4+41>    //读入个数!=2,炸
    0x000000000040102e <+34>:	cmpl   $0xe,0x8(%rsp)           //数1 与 14比较
    0x0000000000401033 <+39>:	jbe    0x40103a <phase_4+46>    //数1 <=14 转46
    0x0000000000401035 <+41>:	callq  0x40143a <explode_bomb>  //数1 >14 炸
    0x000000000040103a <+46>:	mov    $0xe,%edx                //14赋给dx
    0x000000000040103f <+51>:	mov    $0x0,%esi                //si = 0
    0x0000000000401044 <+56>:	mov    0x8(%rsp),%edi           //di 栈8    数1
    0x0000000000401048 <+60>:	callq  0x400fce <func4>         
    0x000000000040104d <+65>:	test   %eax,%eax                //对于返回值ax
    0x000000000040104f <+67>:	jne    0x401058 <phase_4+76>    //ax!=0 转76 炸
    0x0000000000401051 <+69>:	cmpl   $0x0,0xc(%rsp)           //栈12(数2) == 0
    0x0000000000401056 <+74>:	je     0x40105d <phase_4+81>    //不等炸,等拆
    0x0000000000401058 <+76>:	callq  0x40143a <explode_bomb>
    0x000000000040105d <+81>:	add    $0x18,%rsp
    0x0000000000401061 <+85>:	retq  
```

注:

1. 这一块代码还是比较好懂的. 0~32从input中取两个数字放入栈8 栈12 处, 如果不是**两个**数字的话直接炸
2. 34~67 是对数1 检测, 首先数1必须<=14, 否则炸. 然后对数1调用func4函数, 如果返回值!=0直接炸
3. 69~85 是对数2 检测, 简单的令人发指. 不为0炸, 为0炸弹拆除.



### func4

- 输入: rdi = 数1 rsi = ?   rdx = 0xe
- 功能: 对参数进行某种神秘操作, 返回某个值
- 调用:  func4
- 返回: 某个int

```
第一轮: rdi = 数1 rsi = 0   rdx = 0xe 
Dump of assembler code for function func4:
   0x0000000000400fce <+0>:	    sub    $0x8,%rsp            //栈扩8
   0x0000000000400fd2 <+4>:	    mov    %edx,%eax            //ax = dx
   0x0000000000400fd4 <+6>:	    sub    %esi,%eax            //ax = dx-si
   0x0000000000400fd6 <+8>:	    mov    %eax,%ecx            //cx = dx-si
   0x0000000000400fd8 <+10>:	shr    $0x1f,%ecx           //逻辑右移 cx 31位 正0负1
   0x0000000000400fdb <+13>:	add    %ecx,%eax            //ax += cx
   0x0000000000400fdd <+15>:	sar    %eax                 //ax 算数右移1位
   0x0000000000400fdf <+17>:	lea    (%rax,%rsi,1),%ecx   //cx = si + ax
   0x0000000000400fe2 <+20>:	cmp    %edi,%ecx            //cx与数1比较 
   0x0000000000400fe4 <+22>:	jle    0x400ff2 <func4+36>  //cx<=数1, 转36
   0x0000000000400fe6 <+24>:	lea    -0x1(%rcx),%edx      //cx>数1 dx = cx-1
   0x0000000000400fe9 <+27>:	callq  0x400fce <func4>     //调用func4 di=数1,si=si,dx=cx-1
   0x0000000000400fee <+32>:	add    %eax,%eax            //返回值ax*=2
   0x0000000000400ff0 <+34>:	jmp    0x401007 <func4+57>  //返回
   0x0000000000400ff2 <+36>:	mov    $0x0,%eax            //上接22 ax = 0
   0x0000000000400ff7 <+41>:	cmp    %edi,%ecx            //比较cx 数1
   0x0000000000400ff9 <+43>:	jge    0x401007 <func4+57>  //cx>=数1(也就是cx=数1) 转57 返回 
   0x0000000000400ffb <+45>:	lea    0x1(%rcx),%esi       //cx<数1 si = cx+1
   0x0000000000400ffe <+48>:	callq  0x400fce <func4>     //调用func4 di=数1,si=si=cx+1,dx=dx
   0x0000000000401003 <+53>:	lea    0x1(%rax,%rax,1),%eax    //ax=2ax+1
   0x0000000000401007 <+57>:	add    $0x8,%rsp            
   0x000000000040100b <+61>:	retq 
```



这个函数折磨了我整整24h, 最终没忍住去搜了别人的题解. 下面这一段借鉴了[一位简书网友的这篇文章](https://www.jianshu.com/p/33eb51b2024e)

对func4函数进行反汇编:

```c
int fun4(int x, int v2, int v3){
    /*  x = rdi(数1) 
        v2 = rsi(初值0)
        v3 = rdx(初值e)*/
    int tmp = (v3 - v2) >> 21;    		//逻辑右移
    int re = ((v3 - v2) + tmp) >> 1; 	//算数右移
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
```

不妨再写个测试函数:

```c
#include <stdio.h>
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
```

得到:

```
0
1
3
7
```

当且仅当 x = 0,1,3,7 中某个值时,func会返回0.