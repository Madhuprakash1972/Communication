#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
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
	int iClientAddrLength = sizeof(struct sockaddr_in);
	unsigned short usPortNumber = 8080;
	unsigned char arrcData[1024] = {0};
	struct sockaddr_in sServer_Address;
	struct sockaddr_in SClientAddr;

        iServerfd = socket(AF_INET,SOCK_STREAM ,IPPROTO_TCP);
//      iServerfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
        	iRetVal = listen(iServerfd, 5);
                if(iRetVal)
                {
                	printf("Listen failed\n");
                        return;
                }
		printf("Listen success\n");
       	}

		printf("Waiting for client to connect\n");
	iClientSocketFD = accept(iServerfd,(struct sockaddr *)&SClientAddr, &iClientAddrLength);
	if(iClientSocketFD > 0)
        {
		while(1)
		{
			printf("Waiting for Data\n");
			iRetVal = recv(iClientSocketFD,arrcData,sizeof(arrcData),0);
			if(iRetVal > 0)
			{
				printf("From Client : %s\n",arrcData);
				iRetVal = send(iClientSocketFD,arrcData,iRetVal,0);
				if(iRetVal < 0)
				{
					printf("Send Failed\n");
				}
				else
				{
					printf("Send cnt : %d\n",iRetVal);
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
}

