#include <stdio.h>
#include <stdint.h>

#include <arpa/inet.h>

void packet_to_host(uint16_t* packet, size_t length) {
	size_t i;

	for (i = 0; i < length; i++) {
		packet[i] = ntohs(packet[i]);
	}
}

void packet_to_network(uint16_t* packet, size_t length) {
	size_t i;
	
	for (i = 0; i < length; i++) {
		packet[i] = htons(packet[i]);
	}
}
