# README

这是我在2020年6月26日~7月1日完成的Bomb Lab

## 题目

题目原文件位于[这个文件夹](../../Lab-Handout/L2_bomblab-handout)下

## 文件说明

1. [bomb](bomb) 这是给出的二进制炸弹文件, 我们的目标是对其反编译, 并从汇编代码中获得拆除6个炸弹的钥匙🔑

2. [bomb.c](bomb.c) 这是给出的bomb炸弹的源文件, 但是只包括main函数的实现. 最开始看一下就用不到了.

3. [bomp-dump.c](bomp-dump.c) 这是我在解题过程中的所有汇编代码与分析. 但是所有内容已经全部集结在文件Note.md中了. 

4. [func4.c](func4.c) 这是拆除第四个炸弹时辅助的一个函数

5. [L2-Bomb-Note.md](L2-Bomb-Note.md) 这是关于这个炸弹的解题思路与学习笔记, 只看该文件即可.

   **笔记直接显式地包括答案, 不建议试图自主解决的朋友使用!**



## 如何开始?

1. 请自主配置Linux系统或使用VM虚拟机
2. 将题目原文件复制至虚拟机中
3. 使用`gdb bomb`进入gdb调试界面. 如果提示找不到命令可以尝试使用`sudo apt-get install gdb`或自行搜索解决.
4. 根据[gdbnotes-x86-64 PDF文件](../../Lab-Handout/L2_bomblab-handout/gdbnotes-x86-64.pdf)或自行搜索gdb调试方法, 开始解题.