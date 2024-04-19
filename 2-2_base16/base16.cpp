#include <iostream>

using namespace std;

static const char BASE16_ENC_TABLE[] = "0123456789ABCDEF";
static const char BASE16_DEC_TABLE[] = {
    //'0'-'9' => 48~57      'A'-'F' => 65~70
    -1,                                     // 0
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 1-10
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 11-20
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 21-30
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 31-40
    -1, -1, -1, -1, -1, -1, -1, 0, 1, 2,    // 41-50
    3, 4, 5, 6, 7, 8, 9, -1, -1, -1,        // 51-60
    -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, // 61-70
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 71-80
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 81-90
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 91-100
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 101-110
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 111-120
    -1, -1, -1, -1, -1, -1, -1              // 121-127
};

int Base16Encode(const unsigned char *in, int size, char *out)
{
    // base16转码后空间扩大一倍 4位转成1个字符
    for (int i = 0; i < size; i++)
    {
        // 一个字节取出高4位和低4位
        char h = in[i] >> 4;
        char l = in[i] & 0x0F;
        out[i * 2] = BASE16_ENC_TABLE[h];
        out[i * 2 + 1] = BASE16_ENC_TABLE[l];
    }

    return size * 2;
}

int Base16Decode(const string &in, unsigned char *out)
{
    // 将2个base16字符拼接成一个二进制数据
    for (int i = 0; i < in.size(); i += 2)
    {
        unsigned char ch = in[i];
        unsigned char cl = in[i + 1];
        unsigned char h = BASE16_DEC_TABLE[ch];
        unsigned char l = BASE16_DEC_TABLE[cl];

        out[i / 2] = (h << 4) + l;
    }

    return in.size() / 2;
}

int main(int argc, char *argv[])
{
    cout << "Test Base16" << endl
         << endl;
    const unsigned char data[] = "测试Base16";
    int len = sizeof(data);
    char out1[1024] = {0};
    unsigned char out2[1024];

    cout << data << endl;
    int ret = Base16Encode(data, len, out1);
    cout << ret << ":" << out1 << endl;
    ret = Base16Decode(out1, out2);
    cout << ret << ":" << out2 << endl;

    return 0;
}