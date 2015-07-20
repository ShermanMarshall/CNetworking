#ifndef __simpleserver__
#define __simpleserver__

//Necessary includes
#include "sys/socket.h"
#include "netinet/in.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"

//Constants
#define TMP_BYTES 3
#define QUAD 4

//Prototypes
int convertIP (char* quad);
char** getQuad(char* quad, int* err);

#endif
