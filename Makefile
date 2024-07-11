# Addison McAuley, 11295940, amm637
# Marwan Mostafa, 11305332, mam024

CC=gcc
CFLAGS=-g
CPPFLAGS=-std=gnu90 -Wall -Wextra -pedantic
.PHONY = clean

all: client server 

client: client.o format_packet.o packet_conversion.o
	${CC} -o client client.o format_packet.o packet_conversion.o

client.o: client.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c client.c -I.

server: server.o packet_conversion.o server_ops.o iterate.o format_packet.o
	${CC} -o server server.o packet_conversion.o server_ops.o iterate.o format_packet.o

server.o: server.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c server.c -I.

iterate.o: iterate.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c iterate.c -I.

format_packet.o: format_packet.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c format_packet.c -I.

packet_conversion.o: packet_conversion.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c packet_conversion.c -I.

server_ops.o: server_ops.c
	${CC} ${CPPFLAGS} ${CFLAGS} -c server_ops.c -I.

clean:
	rm -r *.o client server database/*.pfx2as 
