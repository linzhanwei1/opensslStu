# 对称加密简述
- 加密与解密双方使用相同的密钥进行加解密操作
- 安全高效
- 安全问题
    + 密钥管理
    + 前置泄露
    + 网络通信要配合非对称密钥
# 分组密码模式
- 明文的长度可能超过密码长度，需要迭代加密，称之为分组密码模式
- 流密码
    + 对一串数据进行连续处理，需要由内部状态
- 分组密码
    + 每次处理一块数据，这一块数据就是分组，比特数就是分组长度
    + AES 128比特(16字节) DES 64比特(8字节)
- 分组密码的ECB(不建议) 和 CBC
# 对称分组加密应用场景
- 文件或者视频加密
- 加密比特币私钥
- 消息或者配置项加密
- SSL通信加密
# 使用异或实现一个简易的对称加密算法
- A明文 B明文
- A异或B = 密文 A&oplus;B
- (A&oplus;B)&oplus;B = A
- 密码补全和初始化
- 数据补全策略  PADDING_PKCS7 PADDING_ZERO
# DES加密代码测试
- 调用OpenSSL接口进行DES ECB模式加解密
- 模拟对ECB加密的攻击并测试CBC模式
- API
``` C++
int DES_set_key(const_DES_cblock *key, DES_key_schedule *schedule)
void DES_ecb_encrypt(const_DES_cblock *input, DES_cblock *output, DES_key_schedule *ks, int enc)
void DES_cbc_encrypt(const unsigned char *input, unsigned char *output, long length, DES_key_schedule *schedule, DES_cblock *ivec, int enc)
void DES_ncbc_encrypt(const unsigned char *input, unsigned char *output, long length, DES_key_schedule *schedule, DES_cblock *ivec, int enc)
```

