#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 9090

#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    int client_len;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == INVALID_SOCKET)
    {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_socket,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Bind failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    // Listen
    if (listen(server_socket, 5) == SOCKET_ERROR)
    {
        printf("Listen failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("TCP Echo Server listening on port %d...\n", PORT);

    // Accept client
    client_len = sizeof(client_addr);

    client_socket = accept(server_socket,
                           (struct sockaddr *)&client_addr,
                           &client_len);

    if (client_socket == INVALID_SOCKET)
    {
        printf("Accept failed\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Client connected!\n");

    // Receive and echo
    while (1)
    {
        bytes_received = recv(client_socket,
                              buffer,
                              BUFFER_SIZE - 1,
                              0);

        if (bytes_received <= 0)
        {
            printf("Client disconnected.\n");
            break;
        }

        buffer[bytes_received] = '\0';

        printf("Client: %s", buffer);

        // Send the same data back
        send(client_socket,
             buffer,
             bytes_received,
             0);
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();

    return 0;
}
