// Last Update:2017-05-27 15:44:11
/**
 * @file stru.c
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-05-19
 */
#include <stdio.h>
#include <stdlib.h>
struct sdshdr
{
    int len;
    int free;
    char buf[];
};

struct sdshdr_new
{
    int len;
    int free;
    char *buf;
};


int main(int argc, char *argv[])
{
    struct sdshdr *sh = NULL;
    sh = malloc(sizeof(struct sdshdr) + 1000 + 1);
    printf("sh = 0x%x, &(sh->len) = 0x%x, &(sh->free) = 0x%x, sh->buf = 0x%x\n",
            sh, &(sh->len), &(sh->free), sh->buf);
    printf("sh->buf - sh = %d, sizeof(sh) = %d\n", (unsigned int)(sh->buf) - (unsigned int)sh, sizeof(struct sdshdr));

    struct sdshdr_new *nsh = NULL;
    nsh = malloc(sizeof(struct sdshdr_new));
    nsh->buf = malloc(1000 + 1);
    printf("nsh = 0x%x, &(nsh->len) = 0x%x, &(nsh->free) = 0x%x, nsh->buf = 0x%x\n",
            nsh, &(nsh->len), &(nsh->free), nsh->buf);
    printf("nsh->buf - nsh = %d, sizeof(nsh) = %d\n", (unsigned int)(nsh->buf) - (unsigned int)nsh, sizeof(struct sdshdr_new));
    return 0;
}

