
// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  

#define MAXLINE 1024 
  
// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from server";
    char buff[1024]; 
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information  
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = inet_addr("10.6.12.7"); 
    servaddr.sin_port = htons(7223); 
	
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = inet_addr("10.6.12.7"); 
    cliaddr.sin_port = htons(7223); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    
    int len, n; 
    while (1) {
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
		buffer[n] = '\0'; 
		if (strcmp(buffer,"quit") == 0) {
			return 0;
		}
		
		printf("Client: %s\n", buffer);
		
		printf("Enter the message: ");
		gets(buffer);
		
		sendto(sockfd, (const char *)buffer, strlen(buffer),  
		    MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
		        len); 
		printf("Message sent.\n"); 
    } 
    
    return 0; 
} 

