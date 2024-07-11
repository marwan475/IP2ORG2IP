/*
 * Addison McAuley, 11295940, amm637
 * Marwan Mostafa, 11305332, mam024 
 */

#ifndef __NETWORK_H__
#define __NETWORK_H__

#define ERROR_EXIT -1
#define SUCCESS_EXIT 0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

uint16_t *format_clientpacket(int reqtype,char* addr,int year,int month,int day);
void packet_to_host(uint16_t* packet, size_t length);
void packet_to_network(uint16_t* packet, size_t length);
void handle_connections(int socket);
void extract_clientpacket(uint16_t *packet,int *reqtype,char* addr,char* year,char* month,char* day);
void operate(int reqtype,char* addr,char* year,char* month,char* day);
void format_response(uint16_t *response);

#endif
