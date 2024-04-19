#include <iostream>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <string.h>

using namespace std;

int Base64Encode(const unsigned char *in, int len, char *out_base64)
{
    if (!in || len <= 0 || !out_base64)
    {
        return 0;
    }
    // 内存源 source
    auto mem_bio = BIO_new(BIO_s_mem());
    if (!mem_bio)
    {
        return 0;
    }
    // base64 filter
    auto b64_bio = BIO_new(BIO_f_base64());
    if (!b64_bio)
    {
        BIO_free(mem_bio);
        return 0;
    }

    // 形成BIO链 B64->mem
    BIO_push(b64_bio, mem_bio);
    // 配置转码行为，超过64字节不换行
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);

    // 写入到base64 filter 进行编码 结果会传递到链表的下一个节点 到mem中读取结果（链表头部代表整个链表）
    // 编码数据每64字节会加\n 换行符,，默认结尾有换行符
    int ret = BIO_write(b64_bio, in, len);
    if (ret <= 0)
    {
        // 释放整个链表资源
        BIO_free_all(b64_bio);
        return 0;
    }

    // 刷新缓存，写入链表的mem
    BIO_flush(b64_bio);

    // 从链表源内存读取
    BUF_MEM *p_data = nullptr;
    int out_size = 0;
    BIO_get_mem_ptr(b64_bio, &p_data);
    if (p_data)
    {
        memcpy(out_base64, p_data->data, p_data->length);
        out_size = p_data->length;
    }

    BIO_free_all(b64_bio);
    return out_size;
}

int Base64Decode(const char *in, int len, unsigned char *out_data)
{
    if (!in || len <= 0 || !out_data)
    {
        return 0;
    }
    // 内存源（base64格式内容）
    auto mem_bio = BIO_new_mem_buf(in, len);
    if (!mem_bio)
    {
        return 0;
    }

    // base64 过滤器
    auto b64_bio = BIO_new(BIO_f_base64());
    if (!b64_bio)
    {
        BIO_free(mem_bio);
        return 0;
    }
    // 形成BIO链
    BIO_push(b64_bio, mem_bio);

    // 读取 解码 [默认读取换行符做结束]
    BIO_set_flags(b64_bio, BIO_FLAGS_BASE64_NO_NL);
    size_t size = 0;
    BIO_read_ex(b64_bio, out_data, len, &size);

    // 释放资源
    BIO_free_all(b64_bio);
    return size;
}

int main(int argc, char *argv[])
{
    cout << "Test openssl BIO base64!" << endl;

    unsigned char data[] = "测试base64数据0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
    int len = sizeof(data);
    char out[4096] = {0};
    unsigned char out2[4096] = {0};
    cout << "source:" << data << endl;
    int ret = Base64Encode(data, len, out);
    if (ret > 0)
    {
        out[ret] = '\0';
        cout << "encode: [" << out << "]" << endl;
    }
    ret = Base64Decode(out, ret, out2);
    cout << "decode:" << out2 << endl;

    return 0;
}