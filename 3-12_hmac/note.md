# HMAC 消息认证码
- 哈希运算认证码(Hash-based Message Authentication Code)
- 与密钥相关的单向散列函数
- 应用在SSL协议中
- 消息是否被正确传输了
    + 消息完整性
    + 消息认证
# HMAC 安全
- 重放
    + 时间戳，nonce随机数
- 无法解决问题
    + 第三方证明
        + C
        + A=>B C无法确认消息时A发送给B的，就算A把密钥给了C，也有可能是B，发送给A的
    + 无法防止否认(抵赖)
        + 双方共享密钥