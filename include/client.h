/************************************************************
* File name     : config.h
* Description   : header file for configuration
* Author        : Jeevan Suresh
* License       : Copyright (c) 2025 Trenser 
                    All Rights Reserved
**************************************************************/

#ifndef __SERVER_H__
#define __SERVER_H__

#include  <arpa/inet.h>
/******************************Function declaration******************************/
extern struct sockaddr_in* InitializeClient(int *sockfd);
extern int CleanupClient(int socket);
#endif // __SERVER_H__