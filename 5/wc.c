#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static void do_wc(const char *path);

static void die(const char *s);

int
main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
    }

    do_wc(argv[1]);
    exit(0);
}

#define  BUFFER_SIZE 2048

static void
do_wc(const char *path) {
    int fd;
    unsigned char buf[BUFFER_SIZE];
    ssize_t n;
    unsigned long count = 0;

    fd = open(path, O_RDONLY);
    if (fd < 0) die(path);
    for (;;) {
        n = read(fd, buf, sizeof buf);
        if (n < 0) die(path);
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            if (buf[i] == '\n') {
                count++;
            }
        }
    }
    if (close(fd) < 0) die(path);
    printf("%s: %d\n", path, count);
}

static void
die(const char *s) {
    perror(s);
    exit(1);
}