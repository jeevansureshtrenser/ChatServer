/************************************************************
* File name     : config.h
* Description   : header file for configuration
* Author        : Jeevan Suresh
* License       : Copyright (c) 2025 Trenser 
                    All Rights Reserved
**************************************************************/

#ifndef __CONFIG_H__
#define __CONFIG_H__ 

//******************************* Include Files ******************************* 
#include <arpa/inet.h>  

/******************************Macro Definitions******************************/
// Configuration header for Echo Server and Client
#define PORT            3000
#define SERVER_IP       "0.0.0.0"
#define SUCCESS         0
#define FAILURE         -1
#define DEF_CLEAR       0
#define DEF_SET         1
#define DEF_TRUE        1
#define DEF_FALSE       0

#define TIMEOUT_SEC     1
#define TIMEOUT_USEC    100
#define MAX_BUFFER_SIZE 1024

#define UDP             0
#define PROTOCOL        UDP
// Uncomment the following line to enable non-blocking sockets
//#define NON_BLOCKING

/******************************Global Variable declaration******************************/
typedef struct {
    const char* ip;
    int port;
} SERVER_CONFIG;

static const SERVER_CONFIG default_config = {
    SERVER_IP,
    PORT
};

/******************************Function declaration******************************/
extern SERVER_CONFIG* GetServerConfig();

#endif // __CONFIG_H__