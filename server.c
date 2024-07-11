/*
 * Addison McAuley, 11295940, amm637
 * Marwan Mostafa, 11305332, mam024
*/

#include <prog.h>

int main(int argc,char *argv[])
{
	char* port; /*port for server to listen on*/
	int s; /*main socket*/
	int b; /*return value of bind*/
 	int l; /*return value of listen*/

  	/*vars for getaddrinfo*/
  	int status;
  	struct addrinfo hints;
  	struct addrinfo *servinfo;

  	/*checking arg count*/
  	if (argc != 2){
    	fprintf(stderr,"inccorect amount of args: only port required\n");
    	exit(1);
  	}

  	/*saving port from cmd arg*/
  	port = argv[1];

  	/*setting up structs for getaddrinfo*/
  	memset(&hints, 0, sizeof hints);
  	hints.ai_family = AF_INET;     
  	hints.ai_socktype = SOCK_STREAM; 
  	hints.ai_flags = AI_PASSIVE;

  	/*calling getaddrinfo*/
  	status = getaddrinfo(NULL,port,&hints, &servinfo);

  	/*checking return of getaddrinfo*/
  	if (status != 0){
    	fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    	exit(1);
  	}

  	/*seting up main socket*/
  	s = socket(servinfo->ai_family,
		servinfo->ai_socktype,
		servinfo->ai_protocol);

  	/*checking return of socket*/
  	if (s == -1){
    	fprintf(stderr,"socket error:");
    	exit(1);
  	}

  	/*bind socket to port*/
  	b = bind(s,servinfo->ai_addr,servinfo->ai_addrlen);

  	/*checking bind return value*/
  	if (b == -1){
    	fprintf(stderr,"bind error");
    	exit(1);
  	}

  	/*calling listen on main socket*/
  	l = listen(s,1);

  	/*checking return value of listen*/
  	if (l == -1){
    	fprintf(stderr,"listen error");
    	exit(1);
  	}

  	/*handling conenctions base on implmentation type*/
  	handle_connections(s);

  	/*freeing alocated structs*/
  	freeaddrinfo(servinfo);

  	return 0;
}

