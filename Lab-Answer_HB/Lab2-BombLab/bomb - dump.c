
#include <stdio.h>
#include <stdlib.h>
#include "support.h"
#include "phases.h"

/* 
 * Note to self: Remember to erase this file so my victims will have no
 * idea what is going on, and so they will all blow up in a
 * spectaculary fiendish explosion. -- Dr. Evil 
 */

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

/* main函数的汇编
Dump of assembler code for function main:
   0x0000000000400da0 <+0>:	push   %rbx         //保存寄存器rbx
   0x0000000000400da1 <+1>:	cmp    $0x1,%edi    //$1与%edi(函数第一个参数)比较, 判断函数参数数目
   0x0000000000400da4 <+4>:	jne    0x400db6 <main+22>   //如果是参数不为1 , 
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
    /* 
    Dump of assembler code for function phase_2:
    //rdi *input
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

/* 不懂 */
read_six_numbers(){
    /* 
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
     */

}