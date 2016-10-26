
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define PORT 8000

static char s_wifi_ip_address[32];

bool broadcast_receiver_run() {
        int sockfd;  // socket
        char buf[10];
        struct sockaddr_in sendaddr;
        struct sockaddr_in recvaddr;   // broadcast address
        int numbytes;
        int addr_len;
        int broadcast=1;

        if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
                perror("socket");
                exit(1);
        }

       if((setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,
                                &broadcast,sizeof broadcast)) == -1) {
                perror("setsockopt - SO_SOCKET ");
                exit(1);
        }
 
        printf("Socket created\n");
 
        sendaddr.sin_family = AF_INET;
        sendaddr.sin_port = htons(PORT);
        sendaddr.sin_addr.s_addr = INADDR_ANY;
        memset(sendaddr.sin_zero,'\0', sizeof sendaddr.sin_zero);

        recvaddr.sin_family = AF_INET;
        recvaddr.sin_port = htons(PORT);
        recvaddr.sin_addr.s_addr = INADDR_ANY;
        memset(recvaddr.sin_zero,'\0',sizeof recvaddr.sin_zero);

        if (bind(sockfd, (struct sockaddr*) &recvaddr, sizeof recvaddr) == -1) {
                perror("bind");
                exit(1);
        }
 
		while (true) {
			addr_len = sizeof sendaddr;
			if ((numbytes = recvfrom(sockfd, buf, sizeof buf, 0,
				(struct sockaddr *)&sendaddr, (socklen_t *)&addr_len)) == -1) {
				perror("recvfrom");
				buf[0] = '\1';
				break;
			}
		
			printf("%s",buf);
			if (*buf == 0)
				break;
			else if (*buf == 'F') {
				system("st key push s1"); // focus press hold
			}
			else if (*buf == 'C') {
				system("st key push s2; st key release s2; st key release s1"); // shutter press and release all
			}
			else if (*buf == 'S') {
				system("st key push s2; st key release s2"); // shutter press and release
			}
			else if (*buf == 'R') {
				system("st key release s2; st key release s1"); // shutter release all
			}
			else if (*buf == 'X') {  // exit
				break;
			}
		}
		close(sockfd);
        return *buf;
}

const char *network_get_wifi_ip_address(void) {
    int sock;
    struct ifreq ifr;

    printf("network_get_wifi_ip_address\n");

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;

    //if (is_new_nx_model()) {
        strncpy(ifr.ifr_name, "mlan0", IFNAMSIZ-1);  // NX1 or NX500 only
    //} else {
    //    strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
    //}
    if (ioctl(sock, SIOCGIFADDR, &ifr) == -1) {
        perror("ioctl() failed");
        s_wifi_ip_address[0] = '\0';
        return NULL;
    }

    close(sock);

    strncpy(s_wifi_ip_address,
            inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr),
            sizeof(s_wifi_ip_address));

    return s_wifi_ip_address;
}


int main(int argc, char **argv) {
    const char *ip_addr;
    int result;

    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    printf("NX500 remote capture daemon\n");
    while (true) {
        ip_addr = network_get_wifi_ip_address();
        if (ip_addr == NULL) {
            sleep(1);
            continue;
        }
    printf("wifi check completed\n");

        result = broadcast_receiver_run();

        if (result == 0) {
            break;
        }
        // wait for threads termination
        sleep(3);
    }

    return 0;
}
