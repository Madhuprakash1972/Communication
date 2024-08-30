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

void main()
{
        int iRetVal = 0;
        int iServerfd = 0;
	int iClientSocketFD = 0;
	int iNum=0;
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
	sServer_Address.sin_family      = AF_INET;
        sServer_Address.sin_addr.s_addr = htonl(INADDR_ANY);
        sServer_Address.sin_port        = htons(usPortNumber);

	iRetVal = bind(iServerfd,(struct sockaddr *)&sServer_Address,sizeof(sServer_Address));
	if(iRetVal)
        {
        	printf("Bind Failed\n");
                return;
        }
        else
        {
		printf("Bind success\n");
       	}

			printf("Waiting for Data\n");
		while(1)
		{
			iRetVal = recvfrom(iServerfd,&iValue,sizeof(iValue),MSG_WAITALL,(struct sockaddr *)&SClientAddr,&iClientAddrLength);
			
			if(iRetVal > 0)
			{
				
				printf("From Client : %d\n",iValue);
				printf("Send to Client : ");
				scanf("%d",&iValue);
				iRetVal = sendto(iServerfd,&iValue,iRetVal,MSG_CONFIRM,(struct sockaddr *)&SClientAddr,iClientAddrLength);
			
				if(iRetVal < 0)
				{
					printf("Send Failed\n");
				}
				else
				{
					//printf("Send cnt : %d\n",iRetVal);
					//memset(arrcData,0,strlen(arrcData));
				}
			}
			else if(iRetVal == 0)
			{
				printf("Client closed\n");
				break;
			}
			else
			{
				printf("Recv Failed\n");
			}
		}
}

