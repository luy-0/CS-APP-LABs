
#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "phases.h"

FILE *infile;

int main(int argc, char *argv[])
{
    char *input;

    /* 总而言之是输入部分, 忽视 */
    if (argc == 1) {  
	infile = stdin;     /* 如果执行时无参数, 采用终端标准输入 */    
    } 
    else if (argc == 2) {
        if (!(infile = fopen(argv[1], "r"))) {
            printf("%s: Error: Couldn't open %s\n", argv[0], argv[1]);
            exit(8);
        }
    }
    else {
	printf("Usage: %s [<input_file>]\n", argv[0]);
	exit(8);
    }

    /* Do all sorts of secret stuff that makes the bomb harder to defuse. */
    initialize_bomb();

    printf("Welcome to my fiendish little bomb. You have 6 phases with\n");
    printf("which to blow yourself up. Have a nice day!\n");

    /* Hmm...  Six phases must be more secure than one phase! */
    input = read_line();             /* Get input                   */
    phase_1(input);                  /* Run the phase               */
    phase_defused();                 /* 消除炸弹 */
    printf("Phase 1 defused. How about the next one?\n");

    /* The second phase is harder.  No one will ever figure out
     * how to defuse this... */
    input = read_line();
    phase_2(input);
    phase_defused();
    printf("That's number 2.  Keep going!\n");

    /* I guess this is too easy so far.  Some more complex code will
     * confuse people. */
    input = read_line();
    phase_3(input);
    phase_defused();
    printf("Halfway there!\n");

    /* Oh yeah?  Well, how good is your math?  Try on this saucy problem! */
    input = read_line();
    phase_4(input);
    phase_defused();
    printf("So you got that one.  Try this one.\n");
    
    /* Round and 'round in memory we go, where we stop, the bomb blows! */
    input = read_line();
    phase_5(input);
    phase_defused();
    printf("Good work!  On to the next...\n");

    /* This phase will never be used, since no one will get past the
     * earlier ones.  But just in case, make this one extra hard. */
    input = read_line();
    phase_6(input);
    phase_defused();

    /* Wow, they got it!  But isn't something... missing?  Perhaps
     * something they overlooked?  Mua ha ha ha ha! */
    
    return 0;
}

/* main函数的汇编 虽然没啥用
Dump of assembler code for function main:
   0x0000000000400da0 <+0>:	push   %rbx         
   0x0000000000400da1 <+1>:	cmp    $0x1,%edi   
   0x0000000000400da4 <+4>:	jne    0x400db6 <main+22>   
   0x0000000000400da6 <+6>:	mov    0x20299b(%rip),%rax        # 0x603748 <stdin@@GLIBC_2.2.5>
   0x0000000000400dad <+13>:	mov    %rax,0x2029b4(%rip)        # 0x603768 <infile>
   0x0000000000400db4 <+20>:	jmp    0x400e19 <main+121>
   0x0000000000400db6 <+22>:	mov    %rsi,%rbx
   0x0000000000400db9 <+25>:	cmp    $0x2,%edi
   0x0000000000400dbc <+28>:	jne    0x400df8 <main+88>
   0x0000000000400dbe <+30>:	mov    0x8(%rsi),%rdi
   0x0000000000400dc2 <+34>:	mov    $0x4022b4,%esi
   0x0000000000400dc7 <+39>:	callq  0x400c10 <fopen@plt>
   0x0000000000400dcc <+44>:	mov    %rax,0x202995(%rip)        # 0x603768 <infile>
   0x0000000000400dd3 <+51>:	test   %rax,%rax
   0x0000000000400dd6 <+54>:	jne    0x400e19 <main+121>
   0x0000000000400dd8 <+56>:	mov    0x8(%rbx),%rcx
   0x0000000000400ddc <+60>:	mov    (%rbx),%rdx
   0x0000000000400ddf <+63>:	mov    $0x4022b6,%esi
   0x0000000000400de4 <+68>:	mov    $0x1,%edi
   0x0000000000400de9 <+73>:	callq  0x400c00 <__printf_chk@plt>
   0x0000000000400dee <+78>:	mov    $0x8,%edi
   0x0000000000400df3 <+83>:	callq  0x400c20 <exit@plt>
   0x0000000000400df8 <+88>:	mov    (%rsi),%rdx
 */

/* 输入参数与 ($0x402400)是否相同,不同炸*/
phase_1(){
    /* 
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


     */





}

/* 参数12为地址, 比较两个指向是否相同,相同返回0不同返回1 */
strings_not_equal(){
/* rdi = *input; esi = $0x402400
Dump of assembler code for function strings_not_equal:
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

 */
}

/* 输入字符指针, 返回指向的字符串长度, 空返回0 */
string_length(){
/* rdi = *input; 
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
    */
}

/* 输入6个规律数字 */
phase_2(){
/* rdi *input
Dump of assembler code for function phase_2:
    0x0000000000400efc <0+>:	push   %rbp
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
     */
}

/* 将栈中数据写入内存 */
read_six_numbers(){
/* rdi *input    rsi 栈指针
Dump of assembler code for function read_six_numbers:
    0x000000000040145c <+0>:	sub    $0x18,%rsp       //分配18
    0x0000000000401460 <+4>:	mov    %rsi,%rdx        //rdx = 原栈指针
    0x0000000000401463 <+7>:	lea    0x4(%rsi),%rcx   //rcx = (栈4)
    0x0000000000401467 <+11>:	lea    0x14(%rsi),%rax  //rax = (栈20)
    0x000000000040146b <+15>:	mov    %rax,0x8(%rsp)   //(栈+8) = 栈20
    0x0000000000401470 <+20>:	lea    0x10(%rsi),%rax  //rax = (栈+16)
    0x0000000000401474 <+24>:	mov    %rax,(%rsp)      //(rsp) = rax = (原栈+16)
    0x0000000000401478 <+28>:	lea    0xc(%rsi),%r9    //r9 = (rsi+12)
    0x000000000040147c <+32>:	lea    0x8(%rsi),%r8    //r8 = (rsi+8)
    0x0000000000401480 <+36>:	mov    $0x4025c3,%esi   //si = $0x4025c3
    0x0000000000401485 <+41>:	mov    $0x0,%eax        //ax = 0
    0x000000000040148a <+46>:	callq  0x400bf0 <__isoc99_sscanf@plt>
    0x000000000040148f <+51>:	cmp    $0x5,%eax        //结果与5比较
    0x0000000000401492 <+54>:	jg     0x401499 <read_six_numbers+61>//结果>5 不炸
    0x0000000000401494 <+56>:	callq  0x40143a <explode_bomb>
    0x0000000000401499 <+61>:	add    $0x18,%rsp       //收回18
    0x000000000040149d <+65>:	retq  
     */
}

/* 输入2个数字,与8组数据比较,不同炸 */
phase_3(){
    /* 
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
   0x0000000000400fb2 <+111>:	mov    $0x0,%eax                //这里是什么情况?
   0x0000000000400fb7 <+116>:	jmp    0x400fbe <phase_3+123>
   0x0000000000400fb9 <+118>:	mov    $0x137,%eax              //上接50 且ax=1 key = 0x137 = 311
   0x0000000000400fbe <+123>:	cmp    0xc(%rsp),%eax           //比较ax(即key)与数2
   0x0000000000400fc2 <+127>:	je     0x400fc9 <phase_3+134>   //不等炸
   0x0000000000400fc4 <+129>:	callq  0x40143a <explode_bomb>
   0x0000000000400fc9 <+134>:	add    $0x18,%rsp
   0x0000000000400fcd <+138>:	retq   
 */



}

/* 注解p3_1 __isoc99_sscanf()
    c99标准库sscanf函数, (参考链接)[http://www.cplusplus.com/reference/cstdio/sscanf/]

    int sscanf ( const char * s, const char * format, ...);
    Read formatted data from string
    Reads data from s and stores them according to parameter format into the locations given by the additional arguments, as if scanf was used, but reading from s instead of the standard input (stdin).

    The additional arguments should point to already allocated objects of the type specified by their corresponding format specifier within the format string.

    Return Value
    On success, the function returns the number of items in the argument list successfully filled. This count can match the expected number of items or be less (even zero) in the case of a matching failure.
    In the case of an input failure before any data could be successfully interpreted, EOF is returned. 
    返回读取到的item的个数


*/

/* 注解p3_2  每个(ax*8+0x402470)中储存的地址
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
 */

/* 两个数字比较 数1{0 1 3 7},数2=0 否则炸 */
phase_4(){
    /* 
%rdi &input
Dump of assembler code for function phase_4:
   0x000000000040100c <+0>:	    sub    $0x18,%rsp               //扩栈18
   0x0000000000401010 <+4>:	    lea    0xc(%rsp),%rcx           //cx 栈12   数2
   0x0000000000401015 <+9>:	    lea    0x8(%rsp),%rdx           //dx 栈8    数1
   0x000000000040101a <+14>:	mov    $0x4025cf,%esi           //si = 0x4025cf
   0x000000000040101f <+19>:	mov    $0x0,%eax                //ax = 0
   0x0000000000401024 <+24>:	callq  0x400bf0 <__isoc99_sscanf@plt>   //读取
   0x0000000000401029 <+29>:	cmp    $0x2,%eax                //读入2个数字
   0x000000000040102c <+32>:	jne    0x401035 <phase_4+41>    //不为2个,炸
   0x000000000040102e <+34>:	cmpl   $0xe,0x8(%rsp)           //数1 与 14比较
   0x0000000000401033 <+39>:	jbe    0x40103a <phase_4+46>    //数1 <=14 转46
   0x0000000000401035 <+41>:	callq  0x40143a <explode_bomb>  //数1 >14 炸
   0x000000000040103a <+46>:	mov    $0xe,%edx                //14赋给dx
   0x000000000040103f <+51>:	mov    $0x0,%esi                //si = 0
   0x0000000000401044 <+56>:	mov    0x8(%rsp),%edi           //di 栈8    数1
   0x0000000000401048 <+60>:	callq  0x400fce <func4>         
   0x000000000040104d <+65>:	test   %eax,%eax                //对于返回值ax
   0x000000000040104f <+67>:	jne    0x401058 <phase_4+76>    //ax!=0 转76 炸
   0x0000000000401051 <+69>:	cmpl   $0x0,0xc(%rsp)           //栈12 == 0? 数2
   0x0000000000401056 <+74>:	je     0x40105d <phase_4+81>    //不等炸,等拆
   0x0000000000401058 <+76>:	callq  0x40143a <explode_bomb>
   0x000000000040105d <+81>:	add    $0x18,%rsp
   0x0000000000401061 <+85>:	retq  
    
    
     */

}

/* 对参数操作,返回int */
func4(){
    /* 
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
    */
}

/* 输入长度为6的字符串并比较 */
phase_5(){
    /* 
%rdi &input
Dump of assembler code for function phase_5:
    0x0000000000401062 <+0>:	push   %rbx
    0x0000000000401063 <+1>:	sub    $0x20,%rsp
    0x0000000000401067 <+5>:	mov    %rdi,%rbx            //rbx = &input
    0x000000000040106a <+8>:	mov    %fs:0x28,%rax        //rax = &fs+28      详见注解p5_1
    0x0000000000401073 <+17>:	mov    %rax,0x18(%rsp)      //栈18储存&fs+28
    0x0000000000401078 <+22>:	xor    %eax,%eax            //自我异或, 等价于ax置0
    0x000000000040107a <+24>:	callq  0x40131b <string_length> //检测rdi的长度
    0x000000000040107f <+29>:	cmp    $0x6,%eax            
    0x0000000000401082 <+32>:	je     0x4010d2 <phase_5+112>   //长度=6 转112
    0x0000000000401084 <+34>:	callq  0x40143a <explode_bomb>  //长度!=6,炸
    0x0000000000401089 <+39>:	jmp    0x4010d2 <phase_5+112>
    0x000000000040108b <+41>:	movzbl (%rbx,%rax,1),%ecx       //cx = (ax+bx) = input[ax]
    0x000000000040108f <+45>:	mov    %cl,(%rsp)               //栈0 = cl
    0x0000000000401092 <+48>:	mov    (%rsp),%rdx              //dx = 栈0
    0x0000000000401096 <+52>:	and    $0xf,%edx                //dx^f 取后4位
    0x0000000000401099 <+55>:	movzbl 0x4024b0(%rdx),%edx      //dx = (0x4024b0+dx) 这里比较复杂,详见注解p5_2,p5_3
    0x00000000004010a0 <+62>:	mov    %dl,0x10(%rsp,%rax,1)    //栈10+ax = dl 
    0x00000000004010a4 <+66>:	add    $0x1,%rax                //ax+=1
    0x00000000004010a8 <+70>:	cmp    $0x6,%rax                //ax与6比较
    0x00000000004010ac <+74>:	jne    0x40108b <phase_5+41>    //不为6 继续循环至41
    //对输入的每个字符依次运算,根据运算结果取出特定内存中的字符,依次存储在栈10~栈16处
    0x00000000004010ae <+76>:	movb   $0x0,0x16(%rsp)          //栈16=0
    0x00000000004010b3 <+81>:	mov    $0x40245e,%esi           //si=0x40245e
    0x00000000004010b8 <+86>:	lea    0x10(%rsp),%rdi          //di=栈10
    0x00000000004010bd <+91>:	callq  0x401338 <strings_not_equal> //栈10与0x40245e比较
    0x00000000004010c2 <+96>:	test   %eax,%eax                    //对于ax (strings_not_equal的返回值)
    0x00000000004010c4 <+98>:	je     0x4010d9 <phase_5+119>       //返回值1(不同) 炸 相同转119
    0x00000000004010c6 <+100>:	callq  0x40143a <explode_bomb>
    0x00000000004010cb <+105>:	nopl   0x0(%rax,%rax,1)
    0x00000000004010d0 <+110>:	jmp    0x4010d9 <phase_5+119>
    0x00000000004010d2 <+112>:	mov    $0x0,%eax                    //ax置0
    0x00000000004010d7 <+117>:	jmp    0x40108b <phase_5+41>        //转41
    0x00000000004010d9 <+119>:	mov    0x18(%rsp),%rax              //ax=栈18
    0x00000000004010de <+124>:	xor    %fs:0x28,%rax                //栈18 与fs+28异或
    0x00000000004010e7 <+133>:	je     0x4010ee <phase_5+140>       //相同 转140 解决
    0x00000000004010e9 <+135>:	callq  0x400b30 <__stack_chk_fail@plt>
    0x00000000004010ee <+140>:	add    $0x20,%rsp
    0x00000000004010f2 <+144>:	pop    %rbx
    0x00000000004010f3 <+145>:	retq   
    
     */


}

/* 注解p5_1 fs段寄存器
    8086CPU将内存分段，并设计了 4 个段寄存器，CS，DS，ES 和 SS，分别用于指令、数据、其它和堆栈。
    FS、GS 是从 80386 开始增加的两个辅助段寄存器，没有全称，取名就是按字母序排在 CS、DS、ES 之后的。 
    */

/* 注解p5_2 映射字符

char 类型占有1个字节(8bits)的空间, 代码中对于每个字符, 取后四位代码, 并加上0x4024b0得到映射字符的地址, 并将得到的映射字符存入栈中的对应位置.例如当字符串的第二个字符为O时, 会进行如下操作:

> 字符`O`对应的ASCAII码为 `0x4f`
>
> 取后四位代码 `0xf`
>
> 得到映射字符的地址 `0x4024bf`
>
> 访问该地址, 得到映射字符`l` , 并存入栈11处 (11是第二个字符对应栈中的位置)
 */

/* 注解p5_3 0x4024b0附近存储的字符
    (gdb) print (char) *(0x4024b0+0x0)
    $1 = 109 'm'

    (gdb) print (char) *(0x4024b0+0x1)
    $2 = 97 'a'
    
    (gdb) print (char) *(0x4024b0+0x2)
    $3 = 100 'd'
    
    (gdb) print (char) *(0x4024b0+0x3)
    $4 = 117 'u'
    
    (gdb) print (char) *(0x4024b0+0x4)
    $5 = 105 'i'
    
    (gdb) print (char) *(0x4024b0+0x5)
    $6 = 101 'e'
    
    (gdb) print (char) *(0x4024b0+0x6)
    $7 = 114 'r'
    
    (gdb) print (char) *(0x4024b0+0x7)
    $8 = 115 's'
    
    (gdb) print (char) *(0x4024b0+0x8)
    $9 = 110 'n'
    
    (gdb) print (char) *(0x4024b0+0x9)
    $10 = 102 'f'
    
    (gdb) print (char) *(0x4024b0+0xa)
    $11 = 111 'o'
    
    (gdb) print (char) *(0x4024b0+0xb)
    $12 = 116 't'
    
    (gdb) print (char) *(0x4024b0+0xc)
    $13 = 118 'v'
    
    (gdb) print (char) *(0x4024b0+0xd)
    $14 = 98 'b'
    
    (gdb) print (char) *(0x4024b0+0xe)
    $15 = 121 'y'
    
    (gdb) print (char) *(0x4024b0+0xf)
    $16 = 108 'l'
 */

/* 输入数字1-6,有顺序要求 */
phase_6(){
    /* 
%rdi &input
Dump of assembler code for function phase_6:
   0x00000000004010f4 <+0>:	push   %r14
   0x00000000004010f6 <+2>:	push   %r13
   0x00000000004010f8 <+4>:	push   %r12
   0x00000000004010fa <+6>:	push   %rbp
   0x00000000004010fb <+7>:	push   %rbx
   0x00000000004010fc <+8>:	sub    $0x50,%rsp
   0x0000000000401100 <+12>:	mov    %rsp,%r13
   0x0000000000401103 <+15>:	mov    %rsp,%rsi
   0x0000000000401106 <+18>:	callq  0x40145c <read_six_numbers>  //读入6个数字
   0x000000000040110b <+23>:	mov    %rsp,%r14
   0x000000000040110e <+26>:	mov    $0x0,%r12d   
   0x0000000000401114 <+32>:	mov    %r13,%rbp                //rbp=r13 外循环1起始
   0x0000000000401117 <+35>:	mov    0x0(%r13),%eax              
   0x000000000040111b <+39>:	sub    $0x1,%eax                //ax=(r13)-1
   0x000000000040111e <+42>:	cmp    $0x5,%eax                //ax与5比较
   0x0000000000401121 <+45>:	jbe    0x401128 <phase_6+52>    //ax>5 炸
   0x0000000000401123 <+47>:	callq  0x40143a <explode_bomb>
   0x0000000000401128 <+52>:	add    $0x1,%r12d               //r12++  r12为外循环索引
   0x000000000040112c <+56>:	cmp    $0x6,%r12d               //比较r12与6
   0x0000000000401130 <+60>:	je     0x401153 <phase_6+95>    //循环6次 结束转95(外循环 1)
   0x0000000000401132 <+62>:	mov    %r12d,%ebx
   0x0000000000401135 <+65>:	movslq %ebx,%rax                //里循环起始
   0x0000000000401138 <+68>:	mov    (%rsp,%rax,4),%eax       //ax = 栈[r12]
   0x000000000040113b <+71>:	cmp    %eax,0x0(%rbp)           //比较(r13)与ax
   0x000000000040113e <+74>:	jne    0x401145 <phase_6+81>    //不等于 转81 等于 炸
   0x0000000000401140 <+76>:	callq  0x40143a <explode_bomb>
   0x0000000000401145 <+81>:	add    $0x1,%ebx                //bx++ bx为里循环索引
   0x0000000000401148 <+84>:	cmp    $0x5,%ebx                
   0x000000000040114b <+87>:	jle    0x401135 <phase_6+65>    //若bx<=5, 即数2~数5 循环65 (里循环 2)
   0x000000000040114d <+89>:	add    $0x4,%r13                //现在数6,r13=下一个数字栈地址
   0x0000000000401151 <+93>:	jmp    0x401114 <phase_6+32>    //转32(外循环) 
   //循环12: 外循环保证每个数字均∈[1,6] , 里循环保证数字各不相同
   //方便起见, 称输入的6个数字为a[i],i∈[0,5]
   0x0000000000401153 <+95>:	lea    0x18(%rsp),%rsi          //rsi=栈+24 (栈0~20存储数1-6)
   0x0000000000401158 <+100>:	mov    %r14,%rax                //ax=栈0地址
   0x000000000040115b <+103>:	mov    $0x7,%ecx                //cx=7
   0x0000000000401160 <+108>:	mov    %ecx,%edx                //dx = cx       循环3起始
   0x0000000000401162 <+110>:	sub    (%rax),%edx              //dx -= *ax
   0x0000000000401164 <+112>:	mov    %edx,(%rax)              //*ax = dx
   0x0000000000401166 <+114>:	add    $0x4,%rax                //ax指向下一个数字  ax为循环3索引
   0x000000000040116a <+118>:	cmp    %rsi,%rax                //如果ax!=栈+24
   0x000000000040116d <+121>:	jne    0x401160 <phase_6+108>   //转108 循环3
   0x000000000040116f <+123>:	mov    $0x0,%esi                //si = 0   
   0x0000000000401174 <+128>:	jmp    0x401197 <phase_6+163>   //转163         循环3结束
   //循环3: 使每数1-数6与原地对7取补(1->6,2->5) 称取补后的数为b[i]=7-a[i]
   0x0000000000401176 <+130>:	mov    0x8(%rdx),%rdx           //dx += 0x8
   0x000000000040117a <+134>:	add    $0x1,%eax                //ax++
   0x000000000040117d <+137>:	cmp    %ecx,%eax                //比较数补与ax
   0x000000000040117f <+139>:	jne    0x401176 <phase_6+130>   //不等 转130
   0x0000000000401181 <+141>:	jmp    0x401188 <phase_6+148>   //等 转148
   0x0000000000401183 <+143>:	mov    $0x6032d0,%edx           //dx = 0x6032d0
   0x0000000000401188 <+148>:	mov    %rdx,0x20(%rsp,%rsi,2)   //(栈+2*si+32)=dx
   0x000000000040118d <+153>:	add    $0x4,%rsi                //si+=4         si作为循环4索引
   0x0000000000401191 <+157>:	cmp    $0x18,%rsi               //若si==24 
   0x0000000000401195 <+161>:	je     0x4011ab <phase_6+183>   //转183         循环4结束
   0x0000000000401197 <+163>:	mov    (%rsp,%rsi,1),%ecx       //cx = (栈+si)  循环4起始 
   0x000000000040119a <+166>:	cmp    $0x1,%ecx                //cx 与 1比较
   0x000000000040119d <+169>:	jle    0x401183 <phase_6+143>   //若cx<=1 转143 
   0x000000000040119f <+171>:	mov    $0x1,%eax                //ax = 1
   0x00000000004011a4 <+176>:	mov    $0x6032d0,%edx           //dx = 0x6032d0
   0x00000000004011a9 <+181>:	jmp    0x401176 <phase_6+130>   //转130
   //循环4: 使(栈32+8*(i-1))=0x6032d0+b[i]*16 
   //称地址 栈32+8*(i-1) 为d0~d5
   //称其中储存的数据,即0x6032d0+b[i]*16,为k0~k5
   0x00000000004011ab <+183>:	mov    0x20(%rsp),%rbx          //bx = k[0]
   0x00000000004011b0 <+188>:	lea    0x28(%rsp),%rax          //ax = &k[1] = d[0]
   0x00000000004011b5 <+193>:	lea    0x50(%rsp),%rsi          //si = &栈+0x50 = d[6]
   0x00000000004011ba <+198>:	mov    %rbx,%rcx                //cx = bx
   0x00000000004011bd <+201>:	mov    (%rax),%rdx              //dx = (ax)  循环5起始
   0x00000000004011c0 <+204>:	mov    %rdx,0x8(%rcx)           //cx+8储存dx 例如 k0+8储存k1 k4+8储存k5
   0x00000000004011c4 <+208>:	add    $0x8,%rax                //ax = &(下一个)
   0x00000000004011c8 <+212>:	cmp    %rsi,%rax
   0x00000000004011cb <+215>:	je     0x4011d2 <phase_6+222>   //循环5结束 转222
   0x00000000004011cd <+217>:	mov    %rdx,%rcx                //rcx = k5  
   0x00000000004011d0 <+220>:	jmp    0x4011bd <phase_6+201>   //转201
   //循环5:  k0+8储存k1 v4+8储存k5
   //若将k[i]作为地址,指向数字v[i]
   0x00000000004011d2 <+222>:	movq   $0x0,0x8(%rdx)           //k5+8储存0
   0x00000000004011da <+230>:	mov    $0x5,%ebp                //bp=5  作为索引
   0x00000000004011df <+235>:	mov    0x8(%rbx),%rax           //ax = (k[i]+8) = k[i+1]   循环6起始
   0x00000000004011e3 <+239>:	mov    (%rax),%eax              //ax = (k[i+1]) = v[i+1]
   0x00000000004011e5 <+241>:	cmp    %eax,(%rbx)              //比较(rbx) 与 ax , bx=k[i], (bx)=v[i]
   0x00000000004011e7 <+243>:	jge    0x4011ee <phase_6+250>   //若(rbx)>ax 转 250
   0x00000000004011e9 <+245>:	callq  0x40143a <explode_bomb>
   0x00000000004011ee <+250>:	mov    0x8(%rbx),%rbx           //bx+=8
   0x00000000004011f2 <+254>:	sub    $0x1,%ebp                //bp-1  
   0x00000000004011f5 <+257>:	jne    0x4011df <phase_6+235>   //循环6
   //循环6: 保证v[i]>v[i+1]
   0x00000000004011f7 <+259>:	add    $0x50,%rsp               
   0x00000000004011fb <+263>:	pop    %rbx
   0x00000000004011fc <+264>:	pop    %rbp
   0x00000000004011fd <+265>:	pop    %r12
   0x00000000004011ff <+267>:	pop    %r13
   0x0000000000401201 <+269>:	pop    %r14
   0x0000000000401203 <+271>:	retq   
 */
}

/* 注解p6_1 0x6032d0附近储存的值
    (gdb) print *(int*) (0x6032d0+16*0)
    $83 = 332
    (gdb) print *(int*) (0x6032d0+16*1)
    $84 = 168
    (gdb) print *(int*) (0x6032d0+16*2)
    $85 = 924
    (gdb) print *(int*) (0x6032d0+16*3)
    $86 = 691
    (gdb) print *(int*) (0x6032d0+16*4)
    $88 = 477
    (gdb) print *(int*) (0x6032d0+16*5)
    $89 = 443
 */

/* 答案
若使得v[0]~v[5]依次为924,691,477,443,332,168
则b[i]-1 应依次为: 2,3,4,5,0,1
原值a[i] 应依次为: 4,3,2,1,6,5
 */




/* 故事还没有结束... */
phase_defuse(){
    /* 
Dump of assembler code for function phase_defused:
    0x00000000004015c4 <+0>:	sub    $0x78,%rsp
    0x00000000004015c8 <+4>:	mov    %fs:0x28,%rax
    0x00000000004015d1 <+13>:	mov    %rax,0x68(%rsp)
    0x00000000004015d6 <+18>:	xor    %eax,%eax
    0x00000000004015d8 <+20>:	cmpl   $0x6,0x202181(%rip)        # 0x603760 <num_input_strings>
    0x00000000004015df <+27>:	jne    0x40163f <phase_defused+123>
    0x00000000004015e1 <+29>:	lea    0x10(%rsp),%r8
    0x00000000004015e6 <+34>:	lea    0xc(%rsp),%rcx
    0x00000000004015eb <+39>:	lea    0x8(%rsp),%rdx
    0x00000000004015f0 <+44>:	mov    $0x402619,%esi
    0x00000000004015f5 <+49>:	mov    $0x603870,%edi
    0x00000000004015fa <+54>:	callq  0x400bf0 <__isoc99_sscanf@plt>
    0x00000000004015ff <+59>:	cmp    $0x3,%eax
    0x0000000000401602 <+62>:	jne    0x401635 <phase_defused+113>
    0x0000000000401604 <+64>:	mov    $0x402622,%esi
    0x0000000000401609 <+69>:	lea    0x10(%rsp),%rdi
    0x000000000040160e <+74>:	callq  0x401338 <strings_not_equal>
    0x0000000000401613 <+79>:	test   %eax,%eax
    0x0000000000401615 <+81>:	jne    0x401635 <phase_defused+113>
    0x0000000000401617 <+83>:	mov    $0x4024f8,%edi
    0x000000000040161c <+88>:	callq  0x400b10 <puts@plt>
    0x0000000000401621 <+93>:	mov    $0x402520,%edi
    0x0000000000401626 <+98>:	callq  0x400b10 <puts@plt>
    0x000000000040162b <+103>:	mov    $0x0,%eax
    0x0000000000401630 <+108>:	callq  0x401242 <secret_phase>
    0x0000000000401635 <+113>:	mov    $0x402558,%edi
    0x000000000040163a <+118>:	callq  0x400b10 <puts@plt>
    0x000000000040163f <+123>:	mov    0x68(%rsp),%rax
    0x0000000000401644 <+128>:	xor    %fs:0x28,%rax
    0x000000000040164d <+137>:	je     0x401654 <phase_defused+144>
    0x000000000040164f <+139>:	callq  0x400b30 <__stack_chk_fail@plt>
    0x0000000000401654 <+144>:	add    $0x78,%rsp
    0x0000000000401658 <+148>:	retq  
    
     */
}
