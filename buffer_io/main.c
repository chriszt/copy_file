#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const static int BUF_SIZE = 8192;

int copy_file (char *src, char *dst)
{
    FILE *src_fp = NULL;
    FILE *dst_fp = NULL;
    char buf[BUF_SIZE];
    long len;

    src_fp = fopen(src, "r");
    if (src_fp == NULL) {
        fprintf(stderr, "open %s fail\n", src);
        return EXIT_FAILURE;
    }
    printf("open %s ok\n", src);

    dst_fp = fopen(dst, "w");
    if (dst_fp == NULL) {
        fprintf(stderr, "create %s fail\n", dst);
        fclose(src_fp);
        src_fp = NULL;
        return EXIT_FAILURE;
    }
    printf("create %s ok\n", dst);
    
    fseek(src_fp, 0, SEEK_END);
    len = ftell(src_fp);
    rewind(src_fp);
    printf("%s length: %ld (B)\n", src, len);

    printf("copy %s --> %s ...\n", src, dst);
    while (1) {
        memset(buf, 0, BUF_SIZE);
        fread(buf, BUF_SIZE, 1, src_fp);
        if (feof(src_fp)) {
            fwrite(buf, len, 1, dst_fp);
            break;
        }
        fwrite(buf, BUF_SIZE, 1, dst_fp);
        len -= BUF_SIZE;
    }
    printf("copy %s --> %s [ok]\n", src, dst);

    fclose(src_fp);
    src_fp = NULL;
    fclose(dst_fp);
    dst_fp = NULL;
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

