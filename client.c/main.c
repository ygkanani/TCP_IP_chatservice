//
//  main.c
//  client.c
//
//  Created by yash kanani on 21/07/15.
//  Copyright (c) 2015 yash kanani. All rights reserved.
//

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#define MAXSIZE 1024;

int main(void)
{
    int sockfd = 0,n = 0,result;
      unsigned short port;
    char recvBuff[1024],addr[INET_ADDRSTRLEN];
    struct sockaddr_in serv_addr;
    
    memset(recvBuff, '0' ,sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
      printf("\nenter server ip:");
      scanf("%s",addr);
      inet_pton(AF_INET, addr, &(serv_addr.sin_addr));
      printf("\nenter server port:");
      scanf("%hu",&port);
      serv_addr.sin_port=HTONS(port);
      
    
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }
      getchar();
    
      for(;;)
            
      {
            
            memset(recvBuff, '0' ,sizeof(recvBuff));
            
            printf("enter the string: ");
            
            
            n=0;
            
            while((recvBuff[n++]=getchar())!='\n');
            
            recvBuff[n--]='\0';
            
            write(sockfd,recvBuff,strlen(recvBuff));
            
            if((strncmp(recvBuff,"bye",3))==0)
                  
            {
                  
                  //recvBuff[result]='\0';
                  
                  //printf("%s: %s",inet_ntoa(serv_addr.sin_addr),recvBuff);
                  
                  //close(sockfd);
                  
                  printf("\n");
                  
                  break;
                  
            }
            
            
            
            memset(recvBuff, '0' ,sizeof(recvBuff));
            
            result = read(sockfd,recvBuff,strlen(recvBuff));
            
            recvBuff[result]='\0';
            
            printf("%s: %s",inet_ntoa(serv_addr.sin_addr),recvBuff);
            
      }
      
      close(sockfd);
      

    return 0;
}

