/*
 * Addison McAuley, 11295940, amm637
 * Marwan Mostafa, 11305332, mam024
*/

#include <prog.h>
#include <pthread.h>

struct sockaddr_storage their_addr;
socklen_t addr_size;
pthread_t threads[1024];
int count;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *connection(void *dta)
{
  int r;
  int c;
  int *conp;
  uint16_t buf[16];
  uint16_t *response;
  int s;

  int reqtype;
  char addr[20];
  char year[5];
  char month[3];
  char day[3];

  conp = (int*) dta;
  c = conp[0];

  while(1){
    /*recv msg request from client*/
    memset(addr,0,20);
    memset(buf,0,32);	    
    r = recv(c,buf,32,0);
    if ( r > 0){
      /*wait for turn with DB*/	  
      pthread_mutex_lock( &mutex1 );
      fprintf(stdout,"server recieved request\n");

      /*network to host conversion*/
      packet_to_host(buf,16);

      /*extract info from request*/
      extract_clientpacket(buf,&reqtype,addr,year,month,day);      

      /*preform request*/
      operate(reqtype,addr,year,month,day);

      response = (uint16_t*) malloc(sizeof(uint16_t)*32);

      format_response(response);

      packet_to_network(response,32);

      pthread_mutex_unlock( &mutex1 );
    
      /*send response to client*/
      s = send(c,response,64,0);
      fprintf(stdout,"server sent response\n");
      if (s != -1){
        free(response);
      }else{
        free(response);	    
        close(c);
        break;
      }

    }
    
  }

  free(conp);
  return NULL;
}

void handle_connections(int socket)
{
  int c;
  int *conp;

  count = 0;

  fprintf(stdout,"server running using MultiThread\n");

  while (1){
    /*accepting new connection and storing it*/
    c = accept(socket, (struct sockaddr *)&their_addr, &addr_size);

    fprintf(stdout,"server recieved connection\n");

    /*checking return value of accept*/
    if (c == -1){
      fprintf(stderr,"accept error");
      exit(1);
    }

    conp = (int*)malloc(sizeof(int)*2);

    conp[0] = c;
    conp[1] = count;

    pthread_create(&threads[count],NULL,connection,(void*)conp);

    count++;
  }
}


