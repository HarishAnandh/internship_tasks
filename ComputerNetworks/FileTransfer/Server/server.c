#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in server, client;
    int clientLen;
    char buffer[BUFFER_SIZE];
    int bytesReceived;
    FILE *file;

    /* Initialize Winsock */
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed.\n");
        return 1;
    }

    /* Create socket */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == INVALID_SOCKET)
    {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    /* Server address */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    /* Bind socket */
    if (bind(serverSocket,
             (struct sockaddr *)&server,
             sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed.\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    /* Listen */
    if (listen(serverSocket, 5) == SOCKET_ERROR)
    {
        printf("Listen failed.\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("=================================\n");
    printf("       FILE SERVER\n");
    printf("=================================\n");
    printf("Waiting for client...\n");

    /* Accept client */
    clientLen = sizeof(client);

    clientSocket = accept(
        serverSocket,
        (struct sockaddr *)&client,
        &clientLen
    );

    if (clientSocket == INVALID_SOCKET)
    {
        printf("Accept failed.\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Client connected!\n");
    printf("Receiving file...\n");

    /* Create output file */
    file = fopen("received_hi.txt", "wb");

    if (file == NULL)
    {
        printf("Could not create received_hi.txt\n");

        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();

        return 1;
    }

    /* Receive the complete file */
    while ((bytesReceived = recv(
                clientSocket,
                buffer,
                BUFFER_SIZE,
                0)) > 0)
    {
        fwrite(buffer, 1, bytesReceived, file);
    }

    fclose(file);

    if (bytesReceived == 0)
    {
        printf("File received successfully!\n");
        printf("Saved as: received_hi.txt\n");
    }
    else
    {
        printf("Error while receiving file.\n");
    }

    /* Close sockets */
    closesocket(clientSocket);
    closesocket(serverSocket);

    WSACleanup();

    return 0;
}
