#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include "config.h"
#include "client.h"

int sockfd = DEF_CLEAR; 
struct sockaddr_in *servaddr = NULL; 
socklen_t addrlen = sizeof(struct sockaddr_in); 
void *receive_messages(void *arg) 
{ 
    char *buffer = (char *)malloc(MAX_BUFFER_SIZE);
    int iReadBytes = DEF_CLEAR;
    while (DEF_TRUE)
    { 
        iReadBytes = recvfrom(sockfd, buffer, MAX_BUFFER_SIZE - DEF_SET, DEF_CLEAR, NULL, NULL);
        if(iReadBytes > DEF_CLEAR)
        {
            buffer[iReadBytes] = NULL_CHAR;
            printf("\nMessage from server: %s", buffer);
            fflush(stdout);
        }
        memset(buffer, DEF_CLEAR, MAX_BUFFER_SIZE);
        iReadBytes = DEF_CLEAR;
        sleep(TIMEOUT_SEC);
    } 
    return NULL;
}
void *send_messages(void *arg)
{ 
    char *buffer = (char *)malloc(MAX_BUFFER_SIZE); 
    while (DEF_TRUE)
    {
        if(fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL) 
        {
            if(sendto(sockfd, buffer, strlen(buffer), DEF_CLEAR, (struct sockaddr*)servaddr, addrlen) < DEF_CLEAR)
            {
                perror("Failed to send message");
            }
            else
            {
                /* No-op */
            }
        }
        else
        {
            /* No-op */
        }
        memset(buffer, DEF_CLEAR, MAX_BUFFER_SIZE);
        sleep(TIMEOUT_SEC);
    }
    return NULL;
}

int main() 
{
    pthread_t recv_thread = DEF_CLEAR;
    pthread_t send_thread = DEF_CLEAR;
    servaddr = InitializeClient(&sockfd);
    if(servaddr == NULL)
    {
        perror("Failed to initialize client");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }

    if (sockfd < DEF_CLEAR) 
    {
        perror("Failed to initialize client");
        exit(EXIT_FAILURE);
    }   
    else
    {
        /* No-op */
    }

#ifdef NON_BLOCKING
    if(fcntl(sockfd, F_SETFL, O_NONBLOCK) < DEF_CLEAR) {
        perror("Failed to set non-blocking mode");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
#endif
    if(pthread_create(&recv_thread, NULL, receive_messages, NULL) != SUCCESS) {
        perror("Failed to create receive thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    if(pthread_create(&send_thread, NULL, send_messages, NULL) != SUCCESS) {
        perror("Failed to create send thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    if(pthread_join(recv_thread, NULL) != SUCCESS) {
        perror("Failed to join receive thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    if(pthread_join(send_thread, NULL) != SUCCESS) {
        perror("Failed to join send thread");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* No-op */
    }
    CleanupClient(sockfd);
    free(servaddr);

    return SUCCESS;
}
