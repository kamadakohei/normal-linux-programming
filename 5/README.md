# 5章

## 各種system call

- read(2)
    - ストリームからバイト列を読み込む
    - ssize_t read(int fd, void *buf, size_t buf_size);
    - ssize_tは符号付き整数型、size_tは符号なし整数型
    - ストリームから最大buf_size読んで、bufに格納する
    - buf_sizeはbufのサイズを渡すことがおおい
    - 最大まで読めない場合もあるのでかならず返り値を確認する
- write(2)
    - ストリームにバイト列を書き込む
    - ssize_t write(int fd, const void *buf, size_t buf_size);
    - bufから最大buf_sizeまでストリームに書き込む
    - 最大までかけない場合もあるのでかならず返り値を確認する
- open(2)
    - ファイルに接続するストリームを作成する
    - int open(const char *pathname, int flags);
- close(2)
    - ストリームを閉じる
    - int close(int fd);
    - プロセス終了時に開放されるが、プロセスが使えるストリームには上限があり、
      ストリームの先にプロセスがいると相手も終了できないので必ず閉じる
- read, write, open, closeは成功すると0以上、失敗すると-1を返す
- また、エラーが発生した場合、`errno`にエラーコードが設定される
- perror(2)
    - 渡した文字列とシステムエラーメッセージが標準出力される
    - strerrorはerrnoを渡すとエラーメッセージを返すが、上書きされるので注意
    - void perror(const char *s);
- lseek(2)
    - ファイルディスクリプタのオフセットを変更する
    - off_t lseek(int fd, off_t offset, int whence);
- dup(2), dup2(2)
    - ファイルディスクリプタを複製する
    - int dup(int oldfd);
- ioctl(2)
    - ストリームの先にあるデバイスに対して制御コマンドを送る
    - int ioctl(int fd, unsigned long request, ...);
- fcntl(2)
    - ファイルディスクリプタのフラグを変更する
    - int fcntl(int fd, int cmd, ...);

## その他注意点

- 文字列(char *)を扱うAPIの中でも'\0'で終端される想定のものとそうでないものがある
- 混合して使わないようにする
- 例えば、read(2)は'\0'を終端文字として扱わないが、prinf(3)は'\0'を終端文字として扱う