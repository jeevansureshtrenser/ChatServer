/************************************************************
* File name     : main.c
* Description   : source file for server main function
* Author        : Jeevan Suresh
* License       : Copyright (c) 2025 Trenser
                    All Rights Reserved
**************************************************************/

//******************************* Include Files ******************************* //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include "config.h"
#include "server.h"

//******************************* Global variable Declaration ******************************* //
int sockfd = DEF_CLEAR;
struct sockaddr_in *servaddr = NULL;
struct sockaddr_in clientaddr = {DEF_CLEAR};
socklen_t addrlen = sizeof(clientaddr);
//******************************* Function Definition ******************************* //
/**********************************************************************
* Function name     : receive_messages
* Description       : to receive messages from client
* Arguments         : void
* Return type       : void pointer
*************************************************************************/
void *ReceiveMessages(void *arg)
{
    int iReadBytes = DEF_CLEAR;
    char *buffer = (char*)malloc(MAX_BUFFER_SIZE);
    if (buffer == NULL)
    {
        perror("Failed to allocate memory for buffer");
        return NULL;
    }
    else
    {
        /* No-op */
    }
    while (DEF_TRUE)
    {
       iReadBytes = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE-DEF_SET, DEF_CLEAR, (struct sockaddr*)&clientaddr, &addrlen);
       if(iReadBytes > DEF_CLEAR)
       {
           buffer[iReadBytes] = '\0';
           printf("\nMessage from client: %s", buffer);
           fflush(stdout);
        }
        memset(buffer, DEF_CLEAR, MAX_BUFFER_SIZE);
        iReadBytes = DEF_CLEAR;
        sleep(TIMEOUT_SEC);
    } 
    return NULL; 
}
/**********************************************************************
* Function name     : send_messages
* Description       : to send messages to client
* Arguments         : void
* Return type       : void pointer
*************************************************************************/
void *SendMessages(void *arg)
{
    char *buffer = (char*)malloc(MAX_BUFFER_SIZE);
    if (buffer == NULL)
    {
        perror("Failed to allocate memory for buffer");
        return NULL;
    }
    else
    {
        /* No-op */
    }
    while (DEF_TRUE)
    {
        if(fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL)
        {
            if(sendto(sockfd, buffer, MAX_BUFFER_SIZE - DEF_SET, DEF_CLEAR, (struct sockaddr*)&clientaddr, addrlen) < DEF_CLEAR)
            {
                perror("Failed to send message");
            }
            else
            {
                /* No-op */
            }
        }
        sleep(TIMEOUT_SEC);
    }
    free(buffer);
    return NULL;
}
/**********************************************************************
* Function name     : main
* Description       : start of the program
* Arguments         : void
* Return type       : void
*************************************************************************/
int main()
{
    pthread_t recvthread = DEF_CLEAR;
    pthread_t sendthread = DEF_CLEAR;
    // Initialize server
    servaddr = InitializeServer(&sockfd);
    if(servaddr == NULL)
    {
        perror("Failed to initialize server");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    if (sockfd <= FAILURE)
    {
        free(servaddr);
        perror("Failed to initialize server");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }

#ifdef NON_BLOCKING
    if(fcntl(sockfd, F_SETFL, O_NONBLOCK) != SUCCESS)
    {
        free(servaddr);
        perror("Failed to set non-blocking mode");
        exit(EXIT_FAILURE);
    }
#endif
    // Communicate with client
    if(pthread_create(&recvthread, NULL, ReceiveMessages, NULL) != SUCCESS)
    {
        free(servaddr);
        perror("Failed to create receive thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    if(pthread_create(&sendthread, NULL, SendMessages, NULL) != SUCCESS)
    {
        free(servaddr);
        perror("Failed to create send thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    if(pthread_join(recvthread, NULL) != SUCCESS)
    {
        free(servaddr);
        perror("Failed to join receive thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    if(pthread_join(sendthread, NULL) != SUCCESS)
    {
        free(servaddr);
        perror("Failed to join send thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    // Cleanup server   
    CleanupServer(sockfd);
    free(servaddr);
    return SUCCESS;
}


/************************end of file ***********************************/
