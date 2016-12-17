//
//  HelloSocket.cpp
//  
//
//  Created by Lei Mao
//
//  Usage:
//      1. Compile this file using "gcc HelloSocket.cpp -o HelloSocket"
//      2. Run the binary with "./HelloSocket" (Starting the server)
//      3. On the other terminal, do "telnet localhost 10000" (Establish connection from client side)
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock; // server socket
    sockaddr_in server, client; // server and client struct
    unsigned int len = sizeof(sockaddr_in);
    
    // Step 1 - Creating The Socket
    // AF_INET: ipv4, SOCK_STREAM: TCP (use SOCK_DGRAM for UDP)
    if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {
        perror("socket ");
        exit(-1);
    }
    // Fill in the server struct
    server.sin_family = AF_INET;            // ipv4
    server.sin_port = htons(10000);         // port: host order to network order (short)
    server.sin_addr.s_addr = INADDR_ANY;    // the socket accepts connections to all the IPs of the machine
    bzero(&server.sin_zero, 8);             // zero out other bytes of the struct
    
    
    // Step 2 - Bind the Socket to the server's IP address
    if ( bind(sock, (sockaddr *)&server, len) == -1 ) {
        perror("bind ");
        exit(-1);
    }
    
    
    // Step 3 - Start Listening on the server
    // arg "5" means maximum number of connections can be queued
    if ( listen(sock, 5) == -1 ) {
        perror("listen ");
        exit(-1);
    }
    
    int cli; // client socket
    char mesg[] = "Hello there! This is a socket connection!\n";
    int sent; // bytes sent to client
    // Step 4 - Try accepting connection from client
    // This will block until a client connection is established
    while (1) {
        if ( (cli = accept(sock, (sockaddr *)&client, &len)) == -1) {
            perror("accept ");
            exit(-1);
        }
        
        
        // Step 5 - Send Data/Msg To Client, when connection established
        sent = send(cli, mesg, strlen(mesg), 0);
        printf("Sent %d bytes to client: %s\n", sent, inet_ntoa(client.sin_addr));
        
        
        // Step 6 - Close The Connection
        close(cli);
    }
    
    return 0;
}


/*
     struct sockaddr_in {
         short            sin_family;   // e.g. AF_INET
         unsigned short   sin_port;     // e.g. htons(3490)
         struct in_addr   sin_addr;     // see struct in_addr, below
         char             sin_zero[8];  // zero this if you want to
     };
     
     struct in_addr {
        unsigned long s_addr;  // load with inet_aton()
     };
 */
