///
/// Created by Anonymous275 on 3/17/2020
///

#include <string>
#include <WinSock2.h>
#include <iostream>
#include <vector>

std::string HTTP_REQUEST(){

    WSADATA wsaData;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;
    int lineCount=0;
    int rowCount=0;
    struct hostent *host;
    std::locale local;
    char buffer[10000];
    int i = 0 ;
    int nDataLength;

    std::string website_HTML;

    std::string url = "s1.yourthought.co.uk";

    std::string get_http = "GET /servers-info HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        std::cout << "WSAStartup failed.\n";
        system("pause");
        //return 1;
    }

    Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    host = gethostbyname(url.c_str());

    SockAddr.sin_port=htons(3599); //PORT
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    if(connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr)) != 0){
        std::cout << "Could not connect";
        //system("pause");
        //return 1;
    }

    send(Socket,get_http.c_str(), strlen(get_http.c_str()),0 );

    while ((nDataLength = recv(Socket,buffer,10000,0)) > 0){
        int i = 0;
        while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r'){

            website_HTML+=buffer[i];
            i += 1;
        }
    }

    closesocket(Socket);
    WSACleanup();

    return website_HTML;
}