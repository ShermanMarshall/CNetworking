#include "arpa/inet.h"
#include "netinet/in.h"
#include "stdio.h"

int main() {
	struct in_addr addr;
	addr.s_addr = 0;

	printf("IP: %i\n", inet_aton("127.0.0.1", &addr));
	printf("IP Bin: %i\n", addr.s_addr);

	addr.s_addr = inet_addr("127.0.0.1");
	printf("IP: %i\n", addr.s_addr);

	char* ip = inet_ntoa(addr);
	printf("IP: %s\n", ip);
	
	printf("Host IP: %i\n", ntohl(addr.s_addr));
}
