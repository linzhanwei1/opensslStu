# opensslStu

## 下载Openssl源代码
```
git clone https://github.com/openssl/openssl.git
```

## 编译和安装
- 切换分支
```
git checkout tags/openssl-3.1.0 -b openssl-3.1.0
```
- 编译源代码
```
./config
make
make install
ldconfig
```
## Q&A
- error while loading shared libraries: libcrypto.so.3: cannot open shared object file: No such file or directory
1. 使用ln命令船舰软连接到/usr/lib中
```
ln -s /usr/local/lib64/libcrypto.so.3 /usr/lib
```
2. 修改动态库加载相关环境变量LD_LIBRARY_PATH
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib64/
```
3. 修改/etc/so.conf,然后刷新（建议）
```
sudo vim /etc/ld.so.conf
在文件尾部添加 "/usr/local/lib64"
保存退出
sudo ldconfig
```
- 配置git
```
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
```