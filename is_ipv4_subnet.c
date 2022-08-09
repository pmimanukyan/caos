#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

bool is_ipv4_subnet(const char *mask, const char *subnet_address, const char *address) {
    int mask_part1, mask_part2, mask_part3, mask_part4;
    int subnet_part1, subnet_part2, subnet_part3, subnet_part4;
    int address_part1, address_part2, address_part3, address_part4;

    sscanf(mask, "%d.%d.%d.%d", &mask_part1, &mask_part2, &mask_part3, &mask_part4);
    sscanf(subnet_address, "%d.%d.%d.%d", &subnet_part1, &subnet_part2, &subnet_part3, &subnet_part4);
    sscanf(address, "%d.%d.%d.%d", &address_part1, &address_part2, &address_part3, &address_part4);

    return (mask_part1 & address_part1) == subnet_part1 && (mask_part2 & address_part2) == subnet_part2 &&
           (mask_part3 & address_part3) == subnet_part3 && (mask_part4 & address_part4) == subnet_part4;
}