#include <iostream>
#include <cstring>
#include <openssl/hmac.h>
#include <string>

using namespace std;

#define TESTA_KEY "123456"
#define HASH_SIZE 32
string GetHmac1(void)
{
    unsigned char data[1024] = "HMAC1";
    unsigned char mac[1024] = {0};
    unsigned int mac_size = 0;
    int data_size = strlen((char *)data);
    char key[1024] = TESTA_KEY;
    HMAC(EVP_sha256(), key, strlen(key), data, data_size, mac, &mac_size);
    string msg(mac, mac + mac_size);
    msg.append(data, data + data_size);

    return msg;
}

void TestHmac(void)
{
    unsigned char out[1024];
    unsigned int out_size = 0;
    string msg1 = GetHmac1();
    const char *data = msg1.data() + HASH_SIZE;
    int data_size = msg1.size() - HASH_SIZE;             //去掉头部
    string hmac(msg1.begin(), msg1.begin() + HASH_SIZE); //待验证的mac
    //验证消息完整和认证
    HMAC(EVP_sha256(), TESTA_KEY, strlen(TESTA_KEY), (unsigned char *)data, data_size, out,
         &out_size);
    string smac(out, out + out_size);
    if (hmac == smac) {
        cout << "hmac success! no chance!" << endl;
    } else {
        cout << "hmac failed! msg changed!" << endl;
    }

    // 篡改消息
    msg1[33] = 'B';
    //验证消息完整和认证
    HMAC(EVP_sha256(), TESTA_KEY, strlen(TESTA_KEY), (unsigned char *)data, data_size, out,
         &out_size);
    smac = string(out, out + out_size);
    if (hmac == smac) {
        cout << "hmac success! no chance!" << endl;
    } else {
        cout << "hmac failed! msg changed!" << endl;
    }
}

int main(int argc, char *argv[])
{
    TestHmac();

    return 0;
}