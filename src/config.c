/************************************************************
* File name     : config.c
* Description   : source file for configuration
* Author        : Jeevan Suresh
* License       : Copyright (c) 2026 Trenser 
                    All Rights Reserved
**************************************************************/

//******************************* Include Files ******************************* //
#include <stdio.h>
#include "config.h"
#include <stdlib.h>

//******************************* Function Declaration ******************************* //
SERVER_CONFIG* GetServerConfig(void);

//******************************* Function Definition ******************************* //

/**********************************************************************
* Function name     : GetServerConfig
* Description       : to load Server Configuration
* Arguments         : void
* Return type       : SERVER_CONFIG* - pointer to server configuration
*************************************************************************/
SERVER_CONFIG* GetServerConfig(void) 
{
    printf("Do you want to load custom server configuration? (y/n): ");
    char choice = getchar();
    getchar(); // consume newline
    if (choice == 'y' || choice == 'Y') 
    {
        static SERVER_CONFIG custom_config;
        printf("Enter server IP address: ");
        static char ip_buffer[16];
        scanf("%15s", ip_buffer);
        getchar(); // consume newline
        custom_config.ip = ip_buffer;
        printf("Enter server port: ");
        scanf("%d", &custom_config.port);
        getchar(); // consume newline
        printf("Loading custom server configuration: IP=%s, PORT=%d\n", custom_config.ip, custom_config.port);
        return &custom_config;
    }
    else 
    {
        printf("Loading default server configuration: IP=%s, PORT=%d\n", default_config.ip, default_config.port);
    }
    return (SERVER_CONFIG*)&default_config;
}


/* End of file */