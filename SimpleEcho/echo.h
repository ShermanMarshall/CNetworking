#ifndef __echo__
#define __echo__

//Necessary includes
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"

//Constants
#define TMP_BYTES 3
#define QUAD 4

//Prototypes
int convertIP (char* quad);
int* getQuad(char* quad, int* err);
void str_echo(int sockdesc);

#endif
