#include "simpleserver.h"
void str_cli (FILE* fd, int sockfd);

int main() {
	int sockfd;
	struct sockaddr_in server;
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(27014);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int err = connect(sockfd, &server, sizeof(server));
	if (err < 0) {
		printf("Error connecting to server\n");
		return 0;
	}
	str_cli(stdin, sockfd);
	exit(0);
}

void str_cli (FILE* fd, int sockfd) {
	char sendline[100], recvline[100];

	do {
		fgets(sendline, 100, stdin);
	} while (!strncmp(sendline, "exit", 100));
}
