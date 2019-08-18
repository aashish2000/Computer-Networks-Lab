#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<strings.h>
#include<stdlib.h>
int main(int argc,char**argv)
{
	int sockfd;
	char fname[25];
	int len;
	printf("\n Enter the IP address of the server: ");
	char ipaddr[30];
	scanf("%s",ipaddr);
	struct sockaddr_in servaddr,cliaddr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(ipaddr);
	servaddr.sin_port = htons(atoi(argv[1]));
	inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	char buffer[100];
	FILE *f;
	printf("\n Enter filename to send: ");
	char filesend[30];
	scanf("%s", filesend);
	f = fopen(filesend,"r");
	fscanf(f,"%s",buffer);
	write(sockfd,buffer,100);
	printf("The file was sent successfully! \n");
}
