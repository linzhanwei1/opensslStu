#include <iostream>
#include <openssl/md5.h>
#include <fstream>
#include <thread>
#include <vector>
#include <openssl/sha.h>
#include <cstring>

using namespace std;

string GetFileListHash(string filepath)
{
    string hash;
    //以二进制方式打开文件(判断一个文件是否被修改)
    ifstream ifs(filepath, ios::binary);
    if (!ifs) {
        return hash;
    }

    //一次读取多少字节
    int block_size = 128;
    unsigned char buf[1024] = {0};

    //hash输出
    unsigned char out[1024] = {0};

    while (!ifs.eof()) {
        ifs.read((char *)buf, block_size);
        int read_size = ifs.gcount();
        if (read_size <= 0) {
            break;
        }
        MD5(buf, read_size, out);
        hash.insert(hash.end(), out, out + 16);
    }
    ifs.close();
    MD5(reinterpret_cast<const unsigned char *>(hash.data()), hash.size(), out);

    return string(out, out + 16);
}

//文件可信树Hash
string GetFileMerkleHash(string filepath)
{
    string hash;
    //存放hash叶子节点,后面所有结果都存在其中
    vector<string> hashes;
    ifstream ifs(filepath, ios::binary);
    if (!ifs)
        return hash;
    unsigned char buf[1024] = {0};
    unsigned char out[1024] = {0};
    int block_size = 128;
    while (!ifs.eof()) {
        ifs.read(reinterpret_cast<char *>(buf), block_size);
        int read_size = ifs.gcount();
        if (read_size <= 0)
            break;
        SHA1(buf, read_size, out);
        //写入叶子节点的hash值
        hashes.push_back(string(out, out + 20));
    }

    while (hashes.size() > 1) { //==1 表示已经计算到root节点
        //不是二的倍数补节点(二叉树)
        if (hashes.size() & 1) {
            //补充最后一个节点
            hashes.push_back(hashes.back());
        }
        //将hash结果还写入hashes中
        for (int i = 0; i < hashes.size() / 2; i++) {
            //两个节点拼起来 i表示的是父节点
            string tmp = hashes[i * 2];
            tmp += hashes[i * 2 + 1];
            SHA1(reinterpret_cast<const unsigned char *>(tmp.data()), tmp.size(), out);
            //写入结果
            hashes[i] = string(out, out + 20);
        }
        //hash列表删除上一次多余的节点
        hashes.resize(hashes.size() / 2);
    }

    if (hashes.size() == 0)
        return hash; //空串
    return hashes[0];
}

void PrintHex(string data)
{
    for (auto c : data) {
        cout << hex << static_cast<int>((unsigned char)c);
    }
    cout << endl;
}

void TestBit(void)
{
    unsigned char data[128] = "测试比特币挖矿，模拟交易链";
    int data_size = strlen((char *)data);
    unsigned int nonce = 0; // 找到nonce
    unsigned char md1[1024] = {0};
    unsigned char md2[1024] = {0};

    for (;;) {
        nonce++;
        memcpy(data + data_size, &nonce, sizeof(nonce));
        SHA256(data, data_size + sizeof(nonce), md1);
        SHA256(md1, 64, md2);
        if (md2[0] == 0 && md2[1] == 0 && md2[2] == 0)
            break;
    }

    cout << "nonce = " << dec << nonce << endl;
}

int main(int argc, char *argv[])
{
    cout << "Test Hash!" << endl;
    unsigned char data[] = "md5";
    int len = sizeof(data);
    unsigned char out[1024] = {0};

    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, data, len);
    MD5_Final(out, &c);

    for (int i = 0; i < 16; i++) {
        cout << hex << static_cast<int>(out[i]);
    }
    cout << endl;

    data[0] = 9;
    MD5(data, len, out);
    for (int i = 0; i < 16; i++) {
        cout << hex << static_cast<int>(out[i]);
    }
    cout << endl;

    cout << "hashList:" << endl;
    string filepath = "testHash.cpp";
    string hash1 = GetFileListHash(filepath);
    PrintHex(hash1);

    //验证文件完整性
    // for (;;) {
    //     string hash2 = GetFileListHash(filepath);
    //     string thash = GetFileMerkleHash(filepath);
    //     cout << "HashList:\t";
    //     PrintHex(hash2);
    //     cout << "MerkleTree:\t";
    //     PrintHex(thash);
    //     if (hash2 != hash1) {
    //         cout << "文件被修改: ";
    //         PrintHex(hash2);
    //     }
    //     this_thread::sleep_for(1s);
    // }

    TestBit();

    return 0;
}