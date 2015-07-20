#include "sys/socket.h"
#include "netinet/in.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define TMP_BYTES 3

int convertIP (char* quad);
char** getQuad(char* quad);

int main() {
	int listenfd, connfd;
	pid_t childpid;
	struct sockaddr_in client, server;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(0);

	char* ip = "127.0.0.1";
	char* bin = malloc(sizeof(char) * 4);

	printf("IP is: %s", bin);// convertIP(ip));
}

char** getQuad(char* quad, int* err) {
	int valid = 0, tmpIdx = 0; err = 0;
	char* values[4], tmp = malloc(sizeof(char)*3);
	for (int x = 0, y = 1, idx = 0; x < strlen(quad); x++, y++) {
		if ((quad[x] < '0' || quad[x] > '9') && (quad[x] != '.')) {
			err = -1;
			return values;
		}
		if (quad[x] == '.') {
			valid++;
			values[idx++] = tmp;
			tmpIdx = 0;
			bzero(tmp, TMP_BYTES);
			y = 1;
		} else if (y > 2) { 
			err = -1;
			return values;
		} else 
			tmp[tmpIdx++] = quad[x];
	}
	if (valid == 3) {
		char* values[4];
		char* tmp = "";
		for (int x = 0, y = 0; x < strlen(quad); x++) {
			if (quad[x] == '.')
		}
	}
}

int convertIP (char* ip) {
	int err = 0;
	char** quad = getQuad(ip, &err);
	for (int x = 3, y = 0; y < 4; y++) {
		val += (atoi() * pow(256, x));
		printf("Val: %d\n", val);
	}
	return val;
}
