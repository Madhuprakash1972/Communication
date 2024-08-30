#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SEND 1
#define RECV 2
#define EXIT 0

void main()
{
	int iRetVal = 0;
	int iServerfd = 0;
	int iClientSocketFD = 0;
	int iClientAddrLength = sizeof(struct sockaddr_in);
	unsigned short usPortNumber = 8090;
	unsigned char arrcData[1024] = {0};
	unsigned int iValue = 0;
	struct sockaddr_in sServer_Address;
	struct sockaddr_in SClientAddr;

	iServerfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(iServerfd < 0)
	{
		printf("Socket creation failed\n");
		return;
	}

	printf("Socket Created\n");

	SClientAddr.sin_family      = AF_INET;
        SClientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        SClientAddr.sin_port        = htons(usPortNumber);
	while(1)
	{
		printf("Enter Data to send in Numbers : ");
		scanf("%d",&iValue);
		iRetVal = sendto(iServerfd,&iValue,sizeof(iValue),MSG_CONFIRM,(struct sockaddr *)&SClientAddr,iClientAddrLength);
		if(iRetVal > 0)
		{
			printf("Send success\n");
			iRetVal = recvfrom(iServerfd,&iValue,sizeof(iValue),MSG_WAITALL,(struct sockaddr *)&SClientAddr,&iClientAddrLength);
			//printf("Recieved from Server : %d" ,iValue);
			if(iRetVal < 0)
			{
				printf("Recv Failed\n");
			}
			else
			{
				printf("Recv Data : %d\n",iValue);
			}
		}
		else
		{
			printf("Send Failed\n");
		}
	}
}

