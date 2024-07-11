/*
 * Addison McAuley, 11295940, amm637
 * Marwan Mostafa, 11305332, mam024
*/

#include <prog.h>

void operate(int reqtype,char* addr,char* year,char* month,char* day) {

  char* input;
  char* input_ip;
  char* input_prefix;

  FILE* file;	
  char line[256];
  char tmp[256];
  char tmp1[6];
  char* rest = NULL;
  char* t;
  FILE* f2;

  char* ip;
  char* prefix;
  char* asn = NULL;
  int a;

  char command[64];
  char command1[64];

  input = addr;

  /*IP2ORG*/
  if (reqtype == 0){

    sprintf(command1, "./ip_to_asn.sh %s %s %s",year,month,day);
    system(command1);

    file = fopen("tmp.txt", "r");

    fgets(tmp,sizeof(tmp),file);

    tmp[44] = '\0';

		printf("%s\n", tmp);

    file = fopen(tmp, "r");

    input_ip = strtok_r(input, "/", &input_prefix);

    while (fgets(line, sizeof(line), file) != NULL) {
      ip = strtok_r(line, " \t", &rest);
      /* If IP's don't match, move onto next entry */
      if (strcmp(ip, input_ip) != 0) {
	continue;
      }
      prefix = strtok_r(NULL, " \t", &rest);
      /* Only if both IP and Prefix match, we break out of loop */
      if (strcmp(prefix, input_prefix) != 0) {
        continue;
      }
      asn = strtok_r(NULL, " \t\n", &rest);
      break;	
    }

    fclose(file);
	
    /* Check if found entry or EOF */
	if (asn == NULL) {
		file = fopen("output.txt", "w");
		fwrite("No entry found\n", 1, 20, file);
		fclose(file);
		printf("Did not find entry with provided ip\n");
		return;
	}
    printf("found entry with asn: %s\n", asn);

    sprintf(command, "./asn_to_org.sh %s %s %s %s", asn, year, month, day);

    /* Do API call for provided asn */
    system(command);
    }

    /*ORG2IP TODO*/
    if (reqtype == 1){ 	

      /*VULNERABLE TO RCE, REMOTE CODE EXECUTION*/	    
      sprintf(command1, "./org_to_asn.sh %s ",addr);  
      system(command1);

      file = fopen("tmp1.txt", "r");

      fgets(tmp1,sizeof(tmp1),file);

      fclose(file);

      system("rm -f tmp1.txt");

      sprintf(command, "./ip_to_asn.sh %s %s %s",year,month,day);
      system(command);

      file = fopen("tmp.txt", "r");

      fgets(tmp,sizeof(tmp),file);

      tmp[44] = '\0';

      system("rm -f tmp.txt");

      file = fopen(tmp, "r");

      a = atoi(tmp1);

      /*need for if nothing is found server dosent segfault later*/
      system("touch output.txt");

      while (fgets(line, sizeof(line), file) != NULL) {
	if (a == 0)break;      
        t = strtok(line, " \t");
	t = strtok(NULL, " \t");
	t = strtok(NULL, " \t");
      
        if (a == atoi(t)){
	  t = strtok(line, " \t");
	  f2 = fopen("output.txt","w");
	  fprintf(f2,"%s\n",t);
	  fclose(f2);
	  break;
	}	

      }
    }
}
