> Note: 本文件仅指出少量术语和普通词汇，对于术语，与中文大多呈一一对应的关系，故后面一般给出对应中文；
>
> 对于普通词汇，与中文可能是一对多的关系，故一般以英文释义，对于给出中文的，仅为单词释义的一种，请注意单词的多义性。

## L2，BITS BYTES AND INTEGER

### Terminology

`threshold` 阈值

`digital processing` `analog processing` 数字处理，模拟处理

`boolean algebra`布尔代数

`&`: ampersand 

`|`:  vertical bar 

`*`: asterisk 

`^`: caret

`~`: tilde 

`2^0`, two to the zero

`intersection` 交集

`union` 并集

`symmetric difference` 对称差集

`complement` 补集

`shifting` 位移

`unsigned number` 无符号数  ==对应Umin,Umax,Tmin,Tmax等表示最值的==

`two's complement number` 补码

`power of 2 `     *2的幂级*

`corner case`   边界情况

`commutative` 符合交换律的

`associative` 符合结合律的





### Normal

- `interpolate` [在文稿中]加入，插入

  > .**e.g. These odd assertions were interpolated into the manuscript some time after 1400.**

- `anticipate` 预先考虑并满足 

  > **e.g. If you're a careful C programmer, you'll have to anticipate the corner cases.**

- `obscure`  鲜为人知&&晦涩难懂的&&隐晦的

  > **e.g. The contracts are written in obscure language.**

- `holdover from`  **an action, feeling, or idea that has continued from the past into the present**

- `aligned`  与...一致, 对齐

  > **e.g. This policy is closely aligned with the goals of the organization**

- `quirky`  古怪的

  > **e.g.  **



## L3  BITS BYTES AND INTEGER CONT

### Terminology

`bias` 偏移量

> Before you do the shift, you should add a ==bias==.

`_ `:  underscore, 下划线

> `size_t` is read as `size underscore t`

`approximation` 近似值

> So if you just want to get a quick  figure and of course these are approximations.

`endian`  字节序

little endian order&big endian order [参考1][https://blog.csdn.net/waitingbb123/article/details/80504093][参考2][https://blog.csdn.net/tyshtang/article/details/50277105]

主要讲解存储数据是从高位开始还是低位开始，JAVA is big endian, IP protocol is big endian, others often little endian.

`%` ：percent

> e.g. %p read as`percent P`, %d read as `percent d`

### Normal

`intuitive` 直观的  

> ...Which is in some ways easier to understand and more intuitive.

`lose ground` 撤退，后退，处于不利地位

`counter example` 反例

> One general way to find counter examples is to try team in.

## L4,FLOATING POINT

### Terminology

`fractional binary number`: 二进制小数

`rational number`: 有理数

`sign bit`: 符号位

`significand M & mantissa`：尾数M

`exponent`: 阶码

 `exp bits` ：（可以意译为）阶码位，阶码部分

`frac bits`：（可以意译为）尾数位，尾数部分

`normalized`: 规格化的 

`positive infinity`: 正无穷

`negative infinity`: 负无穷

`NaN`: not a number

`monotonicity`: 单调性

### Normal

`trade-off`: 权衡，妥协

`funky`: 时髦的

> There is funky intel extended precision. 还有一种新颖的英特尔扩展精度

`spirit`: 精髓

> If you get the spirit, you get  this nice smooth transition from denorm to normalize.

`mechanical `: 机械的，固定的

`propagate`: 相加



## L5 Machine Level Programming | Basis

### Terminology

`-`: hyphen,连字符

`!`: exclamation, 感叹号

`assembler`: 汇编器

`disassembler`: 反汇编器

### Normal

`accrual`: 自然积累，逐渐形成， v,n

> It's been an accrual and evolution of different features layered on top of each other.

`pejorative`:  贬义的，用于侮辱的，带有侮辱性质的

> He used the word 'girl' in the pejorative sense when referring to the women who worked for him.

`goofy`：傻，愚笨的

`scratch the surface`：只触及问题的表面

`ferocious `：猛烈的，残酷的

`patent suit`：专利诉讼

`counterpart`：相似的事物

并没有任何特殊的意义。`It doesn't have any special significance to it.`

我们下面会详细介绍它。`We'll go into more detail about it.`

历史遗留物。`historical legacy stuff`

