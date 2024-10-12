#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")  // Link with Winsock library

void func(SOCKET sockfd);

unsigned long long factorial(int n);

int main() {
    WSADATA wsaData;
    SOCKET sockfd;
    struct sockaddr_in servaddr, cliaddr;
    int len;

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

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    printf("Bind successful\n");
    func(sockfd);

    // Clean up Winsock
    closesocket(sockfd);
    WSACleanup();
    return 0;
}

void func(SOCKET sockfd) {
    int number;
    unsigned long long result;
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);

    // Receive the number from the client
    printf("Waiting for data from client...\n");
    recvfrom(sockfd, (char*)&number, sizeof(number), 0, (struct sockaddr*)&cliaddr, &len);

    printf("Received from client - Number: %d\n", number);

    // Calculate Factorial
    result = factorial(number);

    // Send the calculated factorial back to the client
    sendto(sockfd, (char*)&result, sizeof(result), 0, (struct sockaddr*)&cliaddr, len);
    printf("Factorial sent to client\n");
}

// Function to calculate factorial
unsigned long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }

    return result;
}
