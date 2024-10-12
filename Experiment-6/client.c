#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Link with Winsock library

void func(SOCKET sockfd, struct sockaddr_in servaddr);

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in servaddr;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  // Use SOCK_DGRAM for UDP
    if (sockfd == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    printf("Socket created\n");

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(43451);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    func(sockfd, servaddr);

    // Clean up Winsock
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET sockfd, struct sockaddr_in servaddr) {
    int number;
    unsigned long long factorial;

    // Get the number from the user
    printf("Enter a number: ");
    scanf("%d", &number);

    // Send the number to the server
    sendto(sockfd, (char*)&number, sizeof(number), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

    // Receive the calculated factorial from the server
    int servlen = sizeof(servaddr);
    int recv_len = recvfrom(sockfd, (char*)&factorial, sizeof(factorial), 0, (struct sockaddr*)&servaddr, &servlen);

    // Check if the data was received
    if (recv_len == SOCKET_ERROR) {
        printf("Failed to receive response from server.\n");
    } else {
        printf("Factorial of %d: %llu\n", number, factorial);
    }
}
