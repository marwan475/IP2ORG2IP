/*
 * Addison McAuley, 11295940, amm637
 * Marwan Mostafa, 11305332 , mam024
 */

#include <prog.h>

#define BUF_LENGTH 1024

int main(int argc, char* argv[]) {
	/* Command Line Args */
 	char* dest_machine;
 	char* inputfile;
	char* port;

	int i;
	int r;
	char output[32];
	uint16_t buff[32];
	char* dest_ip;
  	FILE* file;
  	char line[256];
  	int reqtype;
  	char* addr;
  	int year;
  	int month;
  	int day;
  	uint16_t *packet;

  	/* Sockets */
  	int s;
  	struct addrinfo hints;
  	struct addrinfo *serv_info;

  	/* Host from Machine Stuff */
  	struct hostent hbuf, *get_host_result;
  	struct in_addr **addr_list;
  	char buf[BUF_LENGTH];
  	int err;

  	if (argc != 4){
    	fprintf(stderr,"incorrect amount of args: server_host inputfile port\n");
    	exit(1);
  	}

  	dest_machine = argv[1];
  	inputfile = argv[2];
  	port = argv[3];

  	/* Socket Creation */
  	memset(&hints, 0, sizeof(hints));
  	hints.ai_family = AF_INET;
  	hints.ai_socktype = SOCK_STREAM;

  	/* IP from Hostname */
  	if (gethostbyname_r(dest_machine, &hbuf, buf, BUF_LENGTH,
    	&get_host_result, &err) != 0) {
    	perror("gethostbyname_r");
  	}

  	addr_list = (struct in_addr **)get_host_result->h_addr_list;

  	dest_ip = inet_ntoa(*addr_list[0]);

  	/* Getting Address Info */
  	if ((err = getaddrinfo(dest_ip, port, &hints, &serv_info)) != 0) {
    	/* Failure */
  	}	

  	s = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);

  	if (s == -1) {
    	perror("socket");
  	}

  	if (connect(s, serv_info->ai_addr, serv_info->ai_addrlen) == -1) {
    	perror("connect");
  	}	


  	/*Opening input file for reading TODO(check return)*/
  	file = fopen(inputfile,"r");

  	while(fgets(line,sizeof(line),file) != NULL){
    	reqtype = atoi(strtok(line," "));
    	addr = strtok(NULL," ");
    	year = atoi(strtok(NULL," "));
    	month = atoi(strtok(NULL," "));
    	day = atoi(strtok(NULL," "));
		
		if (reqtype) {
			fprintf(stdout, "IP for %s on %d-%d-%d: ",
							addr,
							year,
							month,
							day);
		}
		else {
			fprintf(stdout, "Organization for %s on %d-%d-%d: ",
							addr,
							year,
							month,
							day);
		}

    	packet = format_clientpacket(reqtype, addr, year, month, day);
			
    	/* Convert packet to network */
    	packet_to_network(packet, 16);		

    	if (send(s, packet, 32, 0) == -1) {
     		fprintf(stderr,"send error");
    	}	      	 
		
    	free(packet);

    	r = recv(s,buff,64,0);

    	packet_to_host(buff,32);

    	for (i = 0;i<32;i++){
      	output[i] = (char) buff[i];
    	}
	
		fprintf(stdout, output);
	}
	
	return 0;
}
