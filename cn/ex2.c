#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 9090
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_received;

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == INVALID_SOCKET)
    {
        printf("Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(client_socket,
                (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Connection failed\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    printf("Connected to TCP Echo Server!\n");

    while (1)
    {
        printf("\nEnter message: ");

        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message
        send(client_socket, buffer, strlen(buffer), 0);

        // Exit
        if (strncmp(buffer, "exit", 4) == 0)
            break;

        // Receive echo
        bytes_received = recv(client_socket,
                              buffer,
                              BUFFER_SIZE - 1,
                              0);

        if (bytes_received <= 0)
        {
            printf("Server disconnected.\n");
            break;
        }

        buffer[bytes_received] = '\0';

        printf("Echo from server: %s", buffer);
    }

    closesocket(client_socket);
    WSACleanup();

    return 0;
}
