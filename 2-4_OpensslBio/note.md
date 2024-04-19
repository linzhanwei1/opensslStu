# OpensslBio接口
- BIO包含了多种接口，用于控制在BIO_METHOD中的不同实现函数，包括6中filter型和8种source/sink型。应用场景
- BIO_new 常见一个BIO对象
- 数据源：source/sink类型的BIO是数据源BIO_new(BIO_s_mem())
- 过滤：filter BIO就是把数据从一个BIO转换到另外一个BIO或应用接口
    + BIO_new(BIO_f_base64())
- BIO链：一个BIO链通常包括一个source BIO和一个或多个filter BIO
    + BIO_push(b64_io, mem_bio)
- 写编码，读编码BIO_write BIO_read_ex