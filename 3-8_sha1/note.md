# SHA-1算法分析
- 安全散列算法(Secure Hash Algorithm)；
- 消息摘要(Message Digest)；
- 产生160比特(20字节)散列值H0 H2 H2 H3 H4；
- 强抗碰撞已经攻破；
- 和md5一样都是由md4导出
# Merkle Tree 可信树
-           A                 A
-          / \              /    \
-         B    C           B      C
-        / \   |          / \    /  \
-       D  E   F         D   E   F   F
-      / \/ \ / \       / \ / \ / \ / \ 
-     1  23 4 5 6      1  2 3 4 5 6 5 6
- 每个块都会有一个Merkle树，它从叶子节点(树的底部)开始，一个叶子节点就是一个交易哈希(比特币使用双SHA256哈希)
- Merkle树的好处就是一个节点可以在不下载整个块的情况下，验证是否包含某笔交易
# 模拟比特币挖矿
- block的版本version;
- 上一个block的hash值：prev_hash;
- 需要写入的交易记录的hash树的值:merkle_root;
- 更新事件：ntime
- 当前难度：nbits
- 挖矿的过程就是找到nonce使得
- SHA256(SHA256(version + prev_hash + merkel_root + ntime + nbits + nonce)) < TARGET
- TARGET可以根据当前难度求出的 0000FFFF