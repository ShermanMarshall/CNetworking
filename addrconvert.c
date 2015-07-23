#include "echo.h"

int main() {
	int listenfd, connfd;
	pid_t childpid;
	struct sockaddr_in client, server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(0);
	char* ip = "127.0.0.1";
	printf("IP is: %d\n", convertIP(ip));
}

int* getQuad(char* quad, int* err) {
	int valid = 0, tmpIdx = 0; *err = 0;
	char* tmp = malloc(sizeof(char) * TMP_BYTES);
	int* points = malloc(sizeof(int*) * 4);
	for (int x = 0, y = 1, idx = 0; x < strlen(quad); x++, y++) {
		//Invalid character present
		if ((quad[x] < '0' || quad[x] > '9') && (quad[x] != '.')) {
			*err = -1;
			return points;
		}
		//Handle next component of the quad
		if (quad[x] == '.') {
			//Two dots in succession
			if (tmpIdx == 0) { 
				*err = -1;
				return points;
			}
			valid++;
			points[idx++] = atoi(tmp);
			tmpIdx = 0;
			bzero(tmp, TMP_BYTES);
			y = 1;
			//More than 3 numbers in the 'byte'
		} else if (y > 4) { 
			*err = -1;
			return points;
		} else  
			tmp[tmpIdx++] = quad[x];
	}
	points[3] = atoi(tmp);
	if (valid != 3) 
		*err = -1;
	return points;
}

int convertIP (char* ip) {
	int val = 0, tmp = 0, err = 0;
	int* quad = getQuad(ip, &err);
	if (err == -1)
		return -1;
	for (int x = 3, y = 0; y < 4; y++) {
		if (tmp < 0 || tmp > 255)
			return -1;
		val += quad[y] * pow(256, x--);
	}
	return val;
}
