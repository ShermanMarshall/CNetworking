#include "simpleserver.h"

int main() {
	int listenfd, connfd;
	pid_t childpid;
	struct sockaddr_in client, server;
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(0);

	char* ip = "127.0.0.1";
	//char* bin = malloc(sizeof(char) * 4);
	//printf("IP is: %s", bin);// convertIP(ip));
	printf("IP is: %d\n", convertIP(ip));
}

char** getQuad(char* quad, int* err) {
	int valid = 0, tmpIdx = 0; *err = 0;

	char** values = malloc(sizeof(char*) * 4);
	char* tmp = malloc(sizeof(char) * TMP_BYTES);

	for (int x = 0, y = 1, idx = 0; x < strlen(quad); x++, y++) {
		//Invalid character present
		if ((quad[x] < '0' || quad[x] > '9') && (quad[x] != '.')) {
			err = -1;
			return values;
		}
		//Handle next component of the quad
		if (quad[x] == '.') {
			//Two dots in succession
			if (tmpIdx == 0) { 
				err = -1;
				return values;
			}
			valid++;
			values[idx++] = tmp;
			printf("Values %i: %s\n",idx, tmp);
			tmpIdx = 0;
			bzero(tmp, TMP_BYTES);
			y = 1;
			//More than 3 numbers in the 'byte'
		} else if (y > 4) { 
			*err = -1;
			return values;
		} else  
			tmp[tmpIdx++] = quad[x];
	}
	values[3] = tmp;
	printf("Values %i: %s\n", 3, values[3]);
	if (valid != 3) 
		*err = -1;

	return values;
}

int convertIP (char* ip) {
	int val = 0, tmp = 0, err = 0;
	char** quad = getQuad(ip, &err);
/*	
	char* quad[4]; quad[0] = "127"; quad[1] = "0"; quad[2] = "0"; quad[3] = "1";
*/

	if (err == -1)
		return -1;

	for (int x = 3, y = 0; y < 4; y++) {
		tmp = atoi(quad[y]);
		printf("Quad[y]: %s\n", quad[y]);
		if (tmp < 0 || tmp > 255)
			return -1;

		val += tmp * pow(256, x--);
		printf("Val: %d\n", tmp * pow(256, x+1));
	}
	return val;
}
