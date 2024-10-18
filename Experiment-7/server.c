#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define PORT 8081
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address, client_addr;
    int addrlen = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};
    char *message = "Hello from server!\n";

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Socket creation failed. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    if (listen(server_fd, MAX_CLIENTS) == SOCKET_ERROR) {
        printf("Listen failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        printf("Waiting for a client to connect...\n");
        new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addrlen);
        if (new_socket == INVALID_SOCKET) {
            printf("Accept failed. Error Code: %d\n", WSAGetLastError());
            continue;
        }

        printf("Client connected from %s\n", inet_ntoa(client_addr.sin_addr));
        send(new_socket, message, strlen(message), 0);

        int recv_size;
        while ((recv_size = recv(new_socket, buffer, BUFFER_SIZE, 0)) > 0) {
            buffer[recv_size] = '\0';
            printf("Received from client: %s\n", buffer);
        }

        if (recv_size == 0) {
            printf("Client disconnected\n");
        } else if (recv_size < 0) {
            printf("Receive failed. Error Code: %d\n", WSAGetLastError());
        }

        closesocket(new_socket);
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}
