/************************************************************
* File name     : client.c
* Description   : source file for client implementation
* Author        : Jeevan Suresh
* License       : Copyright (c) xxx Trenser 
                    All Rights Reserved
**************************************************************/

//******************************* Include Files ******************************* //
#include "config.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//******************************* Function Declaration ******************************* //
struct sockaddr_in* InitializeClient(int *sockfd);
int CleanupClient(int socket);

//******************************* Function Definition ******************************* //

/**********************************************************************
* Function name     : InitializeClient
* Description       : to initialize client
* Arguments         : void
* Return type       : int - socket file descriptor
*************************************************************************/
struct sockaddr_in* InitializeClient(int *sockfd)
{
    int client_fd = DEF_CLEAR;
    struct sockaddr_in *address = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    if(address == NULL)
    {
        perror("Failed to allocate memory for sockaddr_in");
        return NULL;
    }
    else
    {
        /* No-op */
    }
    CLIENT_CONFIG* config = GetClientConfig();
    if(config == NULL)
    {
        free(address);
        perror("Failed to get client configuration");
        return NULL;
    }
    else
    {
        /* No-op */
    }

    // Create socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_DGRAM, PROTOCOL)) == SUCCESS)
    {
        perror("socket failed");
        return NULL;
    }
    else
    {
        /* No-op */
    }

    // Bind socket to port
    address->sin_family = AF_INET;
    address->sin_port = htons(config->port);

    // Convert user string to binary form 
    if (inet_pton(AF_INET, config->ip, &address->sin_addr) <= DEF_CLEAR) 
    { 
        perror("Invalid address");
        return NULL;
    }
    else
    {
        /* No-op */
    }
    *sockfd = client_fd;
    printf("Connected to port %d...\n", config->port);
    return address;

}

/**********************************************************************
* Function name     : CleanupClient
* Description       : to cleanup client
* Arguments         : int socket - socket file descriptor
* Return type       : int - zero on success, -one on error
*************************************************************************/
int CleanupClient(int socket)
{
    if(close(socket) <= FAILURE) {
        return FAILURE; // error
    }
    else
    {
        /* No-op */
    }
    return SUCCESS; // success
}
