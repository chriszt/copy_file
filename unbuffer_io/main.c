#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const static int BUF_SIZE = 8192;

int copy_file (char *src, char *dst)
{
    int src_fd = -1;
    int dst_fd = -1;
    char buf[BUF_SIZE];
    ssize_t n;
    off_t len = 0;

    src_fd = open(src, O_RDONLY);
    if (src_fd < 0) {
        fprintf(stderr, "open %s fail\n", src);
        return EXIT_FAILURE;
    }
    printf("open %s ok\n", src);

    dst_fd = open(dst, O_WRONLY | O_CREAT, 0666);
    if (dst_fd < 0) {
        fprintf(stderr, "create %s fail\n", dst);
        close(src_fd);
        src_fd = -1;
        return EXIT_FAILURE;
    }
    printf("create %s ok\n", dst);
    
    len = lseek(src_fd, 0, SEEK_END);
    lseek(src_fd, 0, SEEK_SET);
    printf("%s length: %ld (B)\n", src, len);

    printf("copy %s --> %s ...\n", src, dst);
    while (1) {
        memset(buf, 0, BUF_SIZE);
        n = read(src_fd, buf, BUF_SIZE);
        if (n < BUF_SIZE) {
            write(dst_fd, buf, len);
            break;
        }
        write(dst_fd, buf, BUF_SIZE);
        len -= BUF_SIZE;
    }
    printf("copy %s --> %s [ok]\n", src, dst);

    close(src_fd);
    src_fd = -1;
    close(dst_fd);
    dst_fd = -1;
    return EXIT_SUCCESS;
}

int main (int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "invalid parameters\n");
        return 1;
    }

    return copy_file(argv[1], argv[2]);
}
