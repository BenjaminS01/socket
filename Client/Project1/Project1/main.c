#define _CRT_SECURE_NO_WARNINGS


#define _WINSOCK_DEPRECATED_NO_WARNINGS

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

#define BUFFERSIZE 100
#define PORT 7923
#define SERVER "87.118.112.203"



int main() {

    

        SOCKET sd;
        struct sockaddr_in saddr;
        
        char sbuf[BUFFERSIZE];
        int sbuflen;
        int err;

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

        memset((char*)&saddr, 0, sizeof(saddr));
        saddr.sin_family = PF_INET;
        saddr.sin_port = htons(PORT);
        saddr.sin_addr.s_addr = inet_addr(SERVER);

        strcpy(sbuf, "Swarovsky, Benjamin"); 
        sbuflen = strlen(sbuf); 
      

        if (connect(sd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0) {
            perror("connect");     
            return -1; 
        }
        if (send(sd, sbuf, sbuflen, 0) != sbuflen) { 
            perror("send");     
            return -1; 
        }

        Sleep(2000);

        int bytest_recv = 0;

        bytest_recv = recv(sd, sbuf, sizeof(sbuf), 0);
        
            write(1, sbuf, bytest_recv);
            if (send(sd, sbuf, sbuflen, 0) != sbuflen) {
                perror("send");
                return -1;
            }
            

        if (bytest_recv == -1)
            printf("Error\n");

        

        if (send(sd, sbuf, sbuflen, 0) != sbuflen) {
            perror("send");
            return -1;
        }

        Sleep(2000);

        bytest_recv = recv(sd, sbuf, sizeof(sbuf), 0);
            write(1, sbuf, bytest_recv);
        

        if (bytest_recv == -1)
            printf("Error\n");

        closesocket(sd);
        WSACleanup();
    

    return 0;
}



