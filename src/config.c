/************************************************************
* File name     : config.c
* Description   : source file for configuration
* Author        : Jeevan Suresh
* License       : Copyright (c) xxx Trenser 
                    All Rights Reserved
**************************************************************/

//******************************* Include Files ******************************* //
#include <stdio.h>
#include "config.h"
#include <stdlib.h>

//******************************* Function Declaration ******************************* //
CLIENT_CONFIG* GetClientConfig(void);

//******************************* Function Definition ******************************* //

/**********************************************************************
* Function name     : get_client_config
* Description       : to load Client Configuration
* Arguments         : void
* Return type       : ClientConfig* - pointer to client configuration
*************************************************************************/
CLIENT_CONFIG* GetClientConfig(void) 
{
    printf("Do you want to load custom client configuration? (y/n): ");
    char choice = getchar();
    getchar(); // consume newline
    if (choice == 'y' || choice == 'Y') 
    {
        static CLIENT_CONFIG custom_config;
        printf("Enter server IP address: ");
        static char ip_buffer[BUF_SIZE];
        scanf("%15s", ip_buffer);
        getchar(); // consume newline
        custom_config.ip = ip_buffer;
        printf("Enter server port: ");
        scanf("%d", &custom_config.port);
        getchar(); // consume newline
        printf("Loading custom client configuration: IP=%s, PORT=%d\n", custom_config.ip, custom_config.port);
        return &custom_config;
    }
    else 
    {
        printf("Loading default client configuration: IP=%s, PORT=%d\n", default_config.ip, default_config.port);
    }
    return (CLIENT_CONFIG*)&default_config;
}