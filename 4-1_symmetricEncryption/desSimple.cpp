#include <iostream>
#include <openssl/des.h>
#include <cstring>

using namespace std;

//交易数据
struct Slip {
    char from[16] = {0};
    char to[16] = {0};
    long long amount = 0;
};

static const_DES_cblock key = "1234567";
static DES_key_schedule key_sch;

void EnSlip(const Slip &s, unsigned char *out, int &out_size)
{
    int size = sizeof(s);
    auto p = (const unsigned char *)&s;
    auto o = out;
    DES_set_key(&key, &key_sch);
    for (int i = 0; i < size; i += 8) {
        DES_ecb_encrypt((const_DES_cblock *)p, (DES_cblock *)o, &key_sch, DES_ENCRYPT);
        p += 8;
        o += 8;
        out_size += 8;
    }
    //补充数据
}
void DeSlip(const unsigned char *in, int size, Slip &s)
{
    auto p = (const unsigned char *)in;
    auto o = (unsigned char *)&s;
    DES_set_key(&key, &key_sch);
    for (int i = 0; i < size; i += 8) {
        DES_ecb_encrypt((const_DES_cblock *)p, (DES_cblock *)o, &key_sch, DES_DECRYPT);
        p += 8;
        o += 8;
    }
}

void AttackData(unsigned char *out)
{
    //修改密文 from 和 to 对调
    unsigned char tmp[1024] = {0};

    memcpy(tmp, out, 16);
    memcpy(out, out + 16, 16);
    memcpy(out + 16, tmp, 16);
}

int main(int argc, char *argv[])
{
    {
        unsigned char out[1024] = {0};
        int out_size = 0;
        Slip s1 = {"USER_A", "USER_B", 10000};
        cout << "s1 from:" << s1.from << endl;
        cout << "s1 to:" << s1.to << endl;
        cout << "s1 amount:" << s1.amount << endl;
        EnSlip(s1, out, out_size);
        cout << out_size << "|"
             << "En:" << out << endl;
        //攻击密文
        AttackData(out);

        Slip s2;
        DeSlip(out, out_size, s2);
        cout << "s2 from:" << s2.from << endl;
        cout << "s2 to:" << s2.to << endl;
        cout << "s2 amount:" << s2.amount << endl;
    }

    unsigned char data[] = "1234567";
    unsigned char out[1024] = {0};
    unsigned char out2[1024] = {0};

    DES_set_key(&key, &key_sch);
    DES_ecb_encrypt((const_DES_cblock *)data, (const_DES_cblock *)out, &key_sch, DES_ENCRYPT);
    cout << "encrypt: " << out << endl;
    DES_ecb_encrypt((const_DES_cblock *)out, (const_DES_cblock *)out2, &key_sch, DES_DECRYPT);
    cout << "decrypt: " << out2 << endl;

    return 0;
}