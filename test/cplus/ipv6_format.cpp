// Last Update:2017-05-25 09:59:20
/**
 * @file ipv6_format.cpp
 * @brief 
 * @author luxueqian
 * @version 0.1.00
 * @date 2017-05-25
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;

static void format_ipv4_to_binary(std::string ipstr, uint8_t *ip_v4)
{
    unsigned char buf[sizeof(struct in_addr)];
    int ret = inet_pton(AF_INET, ipstr.c_str(), buf);
    if(ret <= 0)
    {
        return;
    }
    memcpy(ip_v4, buf, sizeof(struct in_addr));
}
static void format_ipv4_to_string(uint8_t *ip_v4, std::string &ipstr)
{
    char str[INET_ADDRSTRLEN+1];

    if (inet_ntop(AF_INET, ip_v4, str, INET_ADDRSTRLEN) == NULL) {
        //failure
        return ;
    }
    ipstr = str;
}

static void format_ipv6_to_binary(std::string ipstr, uint8_t *ip_v6)
{
    unsigned char buf[sizeof(struct in6_addr)];
    if(inet_pton(AF_INET6, ipstr.c_str(), buf) <= 0)
    {
        return;
    }
    memcpy(ip_v6, buf, sizeof(struct in6_addr));
}

static void format_ipv6_to_string(uint8_t *ip_v6, std::string &ipstr)
{
    char str[INET6_ADDRSTRLEN+1];
    if (inet_ntop(AF_INET6, ip_v6, str, INET6_ADDRSTRLEN) == NULL) {
        //failure
        return ;
    }
    ipstr = str;
}

int main(int argc, char *argv[])
{
    std::string src_ipv6 = "FFFF::85:44:4342";
    std::string src_ipv4 = "172.19.21.6";
    uint32_t ip_v4_int = 0;
    uint8_t i4[sizeof(in_addr)] = {0};
    uint8_t i6[sizeof(in6_addr)] = {0};
    std::string dst;
    int i = 0;
    format_ipv4_to_binary(src_ipv4, i4);
    format_ipv4_to_string(i4, dst);
    for(i = 0; i < 4; i++)
    {
        printf("%d ", i4[i]);
    }
    printf("\n");
    printf("i4 dst = %s\n", dst.c_str());
    format_ipv6_to_binary(src_ipv6, i6);
    format_ipv6_to_string(i6, dst);
    for(i = 0; i < 16; i++)
    {
        printf("%x ", i6[i]);
    }
    printf("\n");
    printf("i6 dst = %s\n", dst.c_str());

    return 0;
}

#if 0
int
main(int argc, char *argv[])
{
    unsigned char buf[sizeof(struct in6_addr)];
    int domain, s;
    char str[INET6_ADDRSTRLEN];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s {i4|i6|<num>} string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    domain = (strcmp(argv[1], "i4") == 0) ? AF_INET :
        (strcmp(argv[1], "i6") == 0) ? AF_INET6 : atoi(argv[1]);

    s = inet_pton(domain, argv[2], buf);
    if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format");
        else
            perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    if (inet_ntop(domain, buf, str, INET6_ADDRSTRLEN) == NULL) {
        perror("inet_ntop");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", str);

    exit(EXIT_SUCCESS);
}
#endif
