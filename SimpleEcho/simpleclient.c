#include "echo.h"

void str_cli (FILE* fd, int sockfd);

int main() {
	int sockfd;
	struct sockaddr_in server;
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(27014);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	int err = connect(sockfd, (struct sockaddr*) &server, sizeof(server));
	if (err < 0) {
		printf("Error connecting to server\n");
		return 0;
	}
	str_cli(stdin, sockfd);
}

void str_cli (FILE* fd, int sockfd) {
	char sendline[100], recvline[100], *terminate = "exit\n";

	do {
		bzero(sendline, 100);
		bzero(recvline, 100);
		printf("Input data to send: ");
		fgets(sendline, 100, fd);
	
		write(sockfd, sendline, strlen(sendline));

		if (read(sockfd, recvline, 100) == 0) {
			printf("Error reading data\n");
			return;
		} else {
			printf("Data received: %s\n", recvline);
		}
	
	} while (strcmp(sendline, terminate) != 0);
}
