#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in server;

    FILE *file;

    char buffer[BUFFER_SIZE];

    int bytesRead;
    int totalSent;
    int sent;

    /* Initialize Winsock */
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed.\n");
        return 1;
    }

    printf("=================================\n");
    printf("       FILE CLIENT\n");
    printf("=================================\n");

    /* Open hi.txt */
    file = fopen("hi.txt", "rb");

    if (file == NULL)
    {
        printf("Error: hi.txt not found!\n");
        printf("Make sure hi.txt is inside the Client folder.\n");

        WSACleanup();
        return 1;
    }

    printf("hi.txt opened successfully.\n");

    /* Create socket */
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == INVALID_SOCKET)
    {
        printf("Socket creation failed.\n");

        fclose(file);
        WSACleanup();

        return 1;
    }

    /* Server address */
    server.sin_family = AF_INET;

    /*
       127.0.0.1 means the server
       is running on the same computer.
    */
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    server.sin_port = htons(PORT);

    /* Connect to server */
    printf("Connecting to server...\n");

    if (connect(
            clientSocket,
            (struct sockaddr *)&server,
            sizeof(server)) == SOCKET_ERROR)
    {
        printf("Connection failed.\n");
        printf("Make sure server.exe is running first.\n");

        fclose(file);
        closesocket(clientSocket);
        WSACleanup();

        return 1;
    }

    printf("Connected to server!\n");
    printf("Sending hi.txt...\n");

    /* Read and send the complete file */
    while ((bytesRead = fread(
                buffer,
                1,
                BUFFER_SIZE,
                file)) > 0)
    {
        totalSent = 0;

        /* Make sure all bytes are sent */
        while (totalSent < bytesRead)
        {
            sent = send(
                clientSocket,
                buffer + totalSent,
                bytesRead - totalSent,
                0
            );

            if (sent == SOCKET_ERROR)
            {
                printf("Error while sending file.\n");

                fclose(file);
                closesocket(clientSocket);
                WSACleanup();

                return 1;
            }

            totalSent += sent;
        }
    }

    printf("File sent successfully!\n");

    fclose(file);

    /*
       Tell the server that there is
       no more data to send.
    */
    shutdown(clientSocket, SD_SEND);

    /* Close socket */
    closesocket(clientSocket);

    WSACleanup();

    return 0;
}
