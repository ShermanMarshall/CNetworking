#include "echo.h"

int main() {
	int listenfd, connfd;
	pid_t childpid;
	struct sockaddr_in client, server;
	socklen_t client_len;
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(27014);
	listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenfd < 0) {
		printf("Error creating socket\n");
		return 0;
	}
	int err = bind(listenfd, (struct sockaddr*) &server, sizeof(server));
	if (err < 0) {
		printf("Error binding socket\n");
		return 0;
	}
	err = listen(listenfd, 100);
	if (err < 0) {
		printf("Error setting sockfd backlog\n");
		return 0;
	}
	while (1) {
		client_len = sizeof(client);
		connfd = accept(listenfd, (struct sockaddr*) &client, &client_len);
		if (connfd < 0) {
			printf("Error receiving connection\nProcess Terminated\n");
			return 0;
		}
		if ((childpid = fork()) == 0) {
			printf("Process began\n");
			str_echo(connfd);
			printf("complete\n");
			close(listenfd);
		}
		close(connfd);
	}
}

void str_echo(int sockdesc) {
	ssize_t n;
	char buffer[100], *terminate = "exit\n";
	bzero(buffer, 0);
again:
	while ( (n = read(sockdesc, buffer, 100) ) > 0 ) {
		printf("Received: %s\n", buffer);
		write(sockdesc, buffer, n);
		printf("wrote: %s\n", buffer);
		bzero(buffer, sizeof(buffer));
	}
	if (n < 0 && errno == EINTR)
		goto again;
}
