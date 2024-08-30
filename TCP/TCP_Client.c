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
        if(iServerfd < 0)
        {
	        printf("Socket creation failed\n");
                return;
        }

	printf("Socket Created\n");
	sServer_Address.sin_family      = AF_INET;
    sServer_Address.sin_addr.s_addr = inet_addr("127.0.0.1");
    sServer_Address.sin_port        = htons(8080);

	iRetVal = connect(iServerfd,(struct sockaddr *)&sServer_Address, sizeof(struct sockaddr_in));
	printf("Connect retval : %d\n",iRetVal);
	if(iRetVal == 0)
    {
		while(1)
		{
			printf("Enter Data to send : ");
			scanf("%s",arrcData);
			iRetVal = send(iServerfd,arrcData,strlen(arrcData),0);
			if(iRetVal > 0)
			{
				printf("Send success\n");
				iRetVal = recv(iServerfd,arrcData,sizeof(arrcData),0);
				if(iRetVal < 0)
				{
					printf("Recv Failed\n");
				}
				else
				{
					printf("Recv Data : %s\n",arrcData);
				}
			}
			else
			{
				printf("Send Failed\n");
			}
		}
	}
	else
	{
		printf("Connect Failed\n");
	}
}

