#include "html.hpp"

using namespace hi::web;

#include <iostream>
#include <string>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#endif

void initializeSockets() {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

void cleanupSockets() {
#ifdef _WIN32
    WSACleanup();
#endif
}

int main() {
    initializeSockets();

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct sockaddr_in serverAddr;
    struct hostent* server;

    server = gethostbyname("example.com");
    if (server == nullptr) {
        std::cerr << "No such host" << std::endl;
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);
    serverAddr.sin_port = htons(80);

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        return 1;
    }

    std::string request = "GET / HTTP/1.1\r\n";
    request += "Host: example.com\r\n";
    request += "Connection: close\r\n\r\n";

    ssize_t sent = send(sockfd, request.c_str(), request.length(), 0);
    if (sent < 0) {
        std::cerr << "Error sending request" << std::endl;
        return 1;
    }

    char buffer[4096];
    std::string response;
    ssize_t received;
    while ((received = recv(sockfd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[received] = '\0';
        response += buffer;
    }

    if (received < 0) {
        std::cerr << "Error receiving response" << std::endl;
        return 1;
    }

    std::cout << response << std::endl;

#ifdef _WIN32
    closesocket(sockfd);
#else
    close(sockfd);
#endif

    cleanupSockets();

    return 0;
}