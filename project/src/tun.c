#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "tun.h"

int tun_alloc(char *dev, int flags) {

    struct ifreq ifr;
    int fd, err;
    char *clonedev = "/dev/net/tun";

    if( (fd = open(clonedev , O_RDWR)) < 0 ) {
        perror("Opening /dev/net/tun");
        return fd;
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = flags;

    if (*dev) {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if( (err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0 ) {
        perror("ioctl(TUNSETIFF)");
        close(fd);
        return err;
    }

    strcpy(dev, ifr.ifr_name);

    return fd;
}

void tun_set_ip(char *ip, char *tun_name) {
    pid_t p = fork();
    if (p == 0) {
        execlp("ip", "ip", "address", "add", ip, "dev", tun_name, NULL);
    }
    wait(NULL);
}

void tun_up(char *tun_name) {
    pid_t p = fork();
    if (p == 0) {
        execlp("ip", "ip", "link", "set", "dev", tun_name,"up", NULL);
    }
    wait(NULL);
}
