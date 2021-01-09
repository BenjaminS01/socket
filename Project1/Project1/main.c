#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string.h>

#pragma comment (lib, "Ws2_32.lib")
/*
#ifdef _WIN32
typedef int socklen_t;
#endif
*/

#define BUFSIZE 20
#define PORT 4680

int main() {

    while( 1){

    SOCKET sd;
    struct sockaddr_in saddr, caddr; 
    socklen_t caddrlen;
    char rbuf[BUFSIZE]; 
    int rbuflen;
    int err, num_recvd;

        WSADATA wsaData;   // if this doesn't work
        //WSAData wsaData; // then try this instead
        // MAKEWORD(1,1) for Winsock 1.1, MAKEWORD(2,0) for Winsock 2.0:
        if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
            fprintf(stderr, "WSAStartup failed.\n");
            exit(1);
        }

        sd = socket(AF_INET, SOCK_STREAM, 0);
        if (sd == INVALID_SOCKET) {
            err = WSAGetLastError();
            fprintf(stderr, "socket() failed, error %d\n", err);
            WSACleanup();
            return -1;
        }

        memset((char*)&saddr,0, sizeof(saddr)); 
        saddr.sin_family = AF_INET; 
        saddr.sin_port = htons(PORT); 
        saddr.sin_addr.s_addr = htonl(INADDR_ANY);

        if (bind(sd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) { 
            perror("bind");     return -1; 
        }

        caddrlen = sizeof(caddr);

        rbuflen = recvfrom(sd, rbuf, BUFSIZE, 0, (struct sockaddr*)&caddr, &caddrlen);

        if (rbuflen < 0) { 
            perror("recvfrom");    
            return -1; 
        }
        
        rbuf[rbuflen] = 0;
        printf("%s\n", rbuf); 

        closesocket(sd);
        WSACleanup();

    }

	return 0;
}

    

