/*
 * Addison McAuley, 11295940, amm637
 * Marwan Mostafa, 11305332, mam024 
 */

#include <prog.h>

uint16_t *format_clientpacket(int reqtype,char* addr,int year,int month,int day)
{
  int IP[5];
  uint16_t *packet;
  char *domain;
  int i;

  packet = (uint16_t*)malloc(sizeof(uint16_t)*16);

  /*Format IP2ORG packet*/	
  if (reqtype == 0){
    IP[0] = atoi(strtok(addr,"."));
    IP[1] = atoi(strtok(NULL,"."));
    IP[2] = atoi(strtok(NULL,"."));
    IP[3] = atoi(strtok(NULL,"/"));
    IP[4] = atoi(strtok(NULL, " \n\t"));

    packet[0] = (uint16_t) reqtype;
    packet[1] = (uint16_t) year;
    packet[2] = (uint16_t) month;
    packet[3] = (uint16_t) day;
    packet[4] = (uint16_t) IP[0];
    packet[5] = (uint16_t) IP[1];
    packet[6] = (uint16_t) IP[2];
    packet[7] = (uint16_t) IP[3];
    packet[8] = (uint16_t) IP[4];

  }

  /*Format ORG2IP packet*/
  if (reqtype == 1){
    domain = addr;

    packet[0] = (uint16_t) reqtype;
    packet[1] = (uint16_t) year;
    packet[2] = (uint16_t) month;
    packet[3] = (uint16_t) day;


    for (i=0;i<12;i++){
      if (domain[i] == 0)break;	    
      packet[i+4] = (uint16_t) domain[i];
    }

  }

  return packet;
}

void extract_clientpacket(uint16_t *packet,int *reqtype,char* addr,char* year,char* month,char* day){
  
  int i;	

  *reqtype = (int) packet[0];
  sprintf(year, "%d", packet[1]);
  sprintf(month, "%02d", packet[2]);
  sprintf(day, "%02d", packet[3]);

  if (*reqtype == 0){
    sprintf(addr, "%d.%d.%d.%d/%d", packet[4], packet[5], packet[6], packet[7], packet[8]);
  }

  if (*reqtype == 1){
    for (i=0;i<12;i++){
      if (packet[i+4] == 0) break;	    
      addr[i] = (char) packet[i+4];
    } 
  }

}

void format_response(uint16_t *response){
 
  FILE* file;	
  char line[32];
  int i;

  file = fopen("output.txt", "r");

  fgets(line,32,file);

  fclose(file);

  system("rm -f output.txt");

  for(i = 0;i<32;i++){
    response[i] = (uint16_t)line[i];
  }

}
