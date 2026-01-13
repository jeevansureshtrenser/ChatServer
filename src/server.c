/************************************************************
* File name     : server.c
* Description   : source file for server implementation
* Author        : Jeevan Suresh
* License       : Copyright (c) 2025 Trenser 
                    All Rights Reserved
**************************************************************/

//******************************* Include Files ******************************* //
#include "config.h"
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//******************************* Function Declaration ******************************* //

struct sockaddr_in* InitializeServer(int* sockfd);
int CleanupServer(int socket);

//******************************* Function Definition ******************************* //

/**********************************************************************
* Function name     : InitializeServer
* Description       : to initialize server
* Arguments         : void
* Return type       : int - socket file descriptor
*************************************************************************/
struct sockaddr_in* InitializeServer(int* sockfd)
{
    int server_fd = DEF_CLEAR;
    struct sockaddr_in *address = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
    if (address == NULL) {
        perror("Failed to allocate memory for server address");
        return NULL;
    }
    else
    {
        /* No-op */
    }
    SERVER_CONFIG* config = GetServerConfig();
    if(config == NULL) {
        perror("Failed to get server configuration");
        return NULL;
    }
    else
    {
        /* No-op */
    }

    printf("Starting server at IP: %s, PORT: %d\n", config->ip, config->port);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, PROTOCOL)) == SUCCESS)
    {
        perror("socket failed");
        return NULL;
    }
    else
    {
        /* No-op */
    }

    printf("Socket created successfully.\n");


    // Bind socket to port
    address->sin_family = AF_INET;
    address->sin_port = htons(config->port);

    // Convert user string to binary form 
    if (inet_pton(AF_INET, config->ip, (struct sockaddr_in*)&address->sin_addr) <= DEF_CLEAR) 
    { 
        perror("Invalid address");
        return NULL;
    }
    else
    {
        /* No-op */
    }
    printf("Binding to port %d...\n", config->port);

    if (bind(server_fd, (struct sockaddr *)address, sizeof(struct sockaddr_in)) < DEF_CLEAR) {
        perror("bind failed");
        return NULL;
    }
    else
    {
        /* No-op */
    }
    printf("Bind successful.\n");
    *sockfd = server_fd;
    printf("Connected to port %d...\n", PORT);
    return address;
}

/**********************************************************************
* Function name     : CleanupServer
* Description       : to cleanup server
* Arguments         : int socket - socket file descriptor
* Return type       : int - 0 on success, -1 on error
*************************************************************************/
int CleanupServer(int socket)
{
    if(close(socket) <= FAILURE) {
        return -1; // error
    }
    else
    {
        /* No-op */
    }
    return 0; // success
}
