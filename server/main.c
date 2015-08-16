//
//  main.c
//  server
//
//  Created by yash kanani on 21/07/15.
//  Copyright (c) 2015 yash kanani. All rights reserved.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
    int listenfd = 0,connfd = 0,len;
    struct sockaddr_in serv_addr,client_addr;
    char sendBuff[1025];
    int numrv,result;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd==-1)
    {
        printf("socket creation failed\n");
        exit(0);
    }
    else
        printf("socket retrieve success\n");
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);
    
    if((bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr)))!=0)
    {
        printf("socket bind failed\n");
        exit(0);
    }
    
    if(listen(listenfd, 10) == -1){
        printf("Failed to listen\n");
        return -1;
    }
    
    while(1)
        
    {
        
        len=sizeof(client_addr);
        
        connfd = accept(listenfd, (struct sockaddr*)&client_addr ,&len); // accept awaiting request
        
        if(connfd<0)
            
        {
            
            printf("server accept failed\n");
            
            exit(0);
            
        } else {
            
            printf("connection established with: %s\n",inet_ntoa(client_addr.sin_addr));
            
        }
        
        
        
        for(;;)
            
        {
            
            memset(sendBuff, '0', sizeof(sendBuff));
            
            result=read(connfd, sendBuff, strlen(sendBuff));
            
            if(strncmp("bye",sendBuff,3)==0)
                
            {
                
                sendBuff[result]='\0';
                
                printf("%s: %s",inet_ntoa(client_addr.sin_addr),sendBuff);
                
                
                
                printf("Waiting for client\n");
                
                break;
                
            }
            
            sendBuff[result]='\0';
            
            printf("%s: %s",inet_ntoa(client_addr.sin_addr),sendBuff);
            
            printf("to client: ");
            
            memset(sendBuff, '0', sizeof(sendBuff));
            
            numrv=0;
            
            while((sendBuff[numrv++]=getchar())!='\n');
            
            sendBuff[numrv--]='\0';
            
            write(connfd, sendBuff, strlen(sendBuff));
            
        }
        
        close(connfd);
        
        //sleep(1);
        
        
        
    }
    

    return 0;
}

