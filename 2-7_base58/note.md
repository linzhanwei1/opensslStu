# base58
- 编码集不同，Base58的编码集在Base64的字符集的基础上去掉了比较容易混淆的字符；
- Base58不含Base64中的0(数字0)、O(大写字母O)、i(小写字母L)、I(大写字母I)，以及"+"和"/"两个字符。
- 需要人(看或写)的场景使用

# 辗转相除法
- 两个数的最大公约数等于它们中较小的数和两数之差的最大公约数；
- 欧几里德(Euclidean)算法，是求最大公约数的算法；
- 两个数的最大公约数是指能同时整除它们的最大正整数。辗转相除法的基本原理是:两个数的最大公约数等于它们中较小的数和两数之差的最大公约数。
---
    1. base_58是用于Bitcoin中使用的一种独特的编码方式，主要用于产生Bitcoin的钱包地址；
    2. 相比base_64，base_58不使用数字"0"，字母大写"O"，字母大写"I"，和字母小写"i"，以及"+"和"/"符号
---
- 也就是字符1代表0，字符2代表1，字符3代表2...字符z代表57。
- 如果将1234转换为58进制；
- 第一步：1234除以58，商21，余数为16，查表得H；
- 第二步：21除以58，商0，余数为21，查表得N；
- 所以得到base58编码为：NH；
如果待转换的数前面有0怎么办？直接附加编码1来代表，有多少个就附加多少个(编码中1代表0)。
# base58输出字节数
- 在编码后字符串中，是从58个字符当中选择，需要表示的位数是log<sub>2</sub>58，每一个字母代表的信息量是log<sub>2</sub>58；
- 输入的字节：(length * 8)bit;
- 预留的字符数量就是(length * 8)/log<sub>2</sub>58;
- length * (log<sub>2</sub>256 / log<sub>2</sub>58)
- length * 1.38