#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    // Check if the correct number of command-line arguments is provided
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    // Extract the port number from the command-line arguments
    portno = atoi(argv[2]);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    // Get the server's hostent structure using the provided hostname
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    // Initialize the serv_addr structure with server information
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    // Prompt the user to enter a message
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    // Send the user's message to the server
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");

    // Clear the buffer and read the server's response
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) 
         error("ERROR reading from socket");

    // Display the server's response
    printf("%s\n", buffer);

    // Close the socket and exit
    close(sockfd);
    return 0;
}
