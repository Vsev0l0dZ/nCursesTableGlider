#ifndef DATADISPLAY_H
#define DATADISPLAY_H

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#include <ncurses.h>

#define MAX 255
#define PORT 8888
#define SA struct sockaddr


void colorON(WINDOW*, WINDOW*);
void colorOFF(WINDOW*, WINDOW*);

void dataDisplay(int);


#endif // DATADISPLAY_H
