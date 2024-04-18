#include <iostream>
#include <openssl/rand.h>
#include <time.h>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "First openssl code!" << endl;
    time_t t = time(nullptr);
    unsigned char buf[16] = {0};
    int re = RAND_bytes(buf, sizeof(buf));

    for (int i = 0; i < sizeof(buf); i++)
    {
        cout << hex << static_cast<int>(buf[i]) << " ";
    }
    cout << endl;

    return 0;
}