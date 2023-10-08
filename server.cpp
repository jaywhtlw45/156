#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Function to display an error message and exit
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;  // Socket file descriptors and port number
    socklen_t clilen;              // Length of client address structure
    char buffer[256];              // Buffer to store incoming data
    struct sockaddr_in serv_addr, cli_addr;  // Server and client address structures
    int n;                         // Number of bytes read/written

    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");

    // Clear the server address structure
    bzero((char *)&serv_addr, sizeof(serv_addr));

    // Extract the port number from command-line arguments
    portno = atoi(argv[1]);

    // Set server address properties
    serv_addr.sin_family = AF_INET;         // IPv4 address family
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Accept connections on any interface
    serv_addr.sin_port = htons(portno);     // Port number in network byte order

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    // Listen for incoming connections with a maximum queue size of 5
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    // Accept an incoming connection and create a new socket for it
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
        error("ERROR on accept");

    // Clear the data buffer
    bzero(buffer, 256);

    // Read data from the client into the buffer
    n = read(newsockfd, buffer, 255);
    if (n < 0)
        error("ERROR reading from socket");

    // Print the received message
    printf("Here is the message: %s\n", buffer);

    // Send a response message back to the client
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)
        error("ERROR writing to socket");

    // Close the client socket
    close(newsockfd);

    // Close the server socket
    close(sockfd);

    return 0;
}
