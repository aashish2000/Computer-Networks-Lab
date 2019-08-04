// Client side implementation of UDP client-server model 
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
	char buff[1024];
	
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(7223); 
	servaddr.sin_addr.s_addr = inet_addr("10.6.12.7"); 
	
	int n, len; 
	
	while(1) {
		printf("Enter the message: ");
		gets(buffer);
		if (strcmp(buffer,"quit") == 0) {
			sendto(sockfd, (const char *)buffer, strlen(buffer),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr)); 
			printf("Connection termination message sent.\n");
			return 0;
		}
		sendto(sockfd, (const char *)buffer, strlen(buffer),MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr)); 
		printf("Message sent.\n"); 
		
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len); 
		buffer[n] = '\0'; 
		printf("Server: %s\n", buffer); 
	}
	

	close(sockfd);
	
	return 0; 
} 

