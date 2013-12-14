#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "assert.h"
#include "string.h"
#include "minIni.h"
#include "malloc.h"
#include "modules/common_func.c"
#include "modules/web_module_home.c"
#include "modules/web_module_logcat.c"
#include "modules/web_module_settings.c"
#include "modules/web_module_headers.c"
#include "modules/web_module_footer.c"
#include "modules/web_module_status.c"
#include "modules/web_module_companion.c"

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))
#define QS_LEN 65536
#define BLOCK_SIZE 512

//define System and Configuration config path





int processPostData(char *postData){
  char *token;
  char buf[1024];
  char decodedToken[100];
  char action[80];
  char section[80];
  char field[80];
  char value[80];
  int smartDnsUpdatePerformed;
  char smartDnsProviderPrimary[1024];
  char smartDnsProviderSecondary[1024];
  int n;
  system("echo \"posting\" > /data/www/tmp2.tmp");
  sscanf(postData, "action=%[0-9a-zA-Z]", &action);

  //postData = "action=update&section=thisone&";
  //sscanf(postData, "action=%[0-9a-zA-Z]&section=%[0-9a-zA-Z]&field=%[0-9a-zA-Z]&value=%[0-9a-zA-Z.:/-%]&", &action, &section, &field, &value);
  sscanf(postData, "action=%[0-9a-zA-Z]", &action);
 
  //urldecode2(decValue, value);
  if(compStr(action, "update", sizearray(action))){
  token = strtok (postData,"&");
        while (token != NULL) {
	urldecode2(decodedToken, token);
	//check if contains / so we know it's a var to update
	if(strstr(decodedToken, "/") != NULL) {
		//printf("token: %s <br />", decodedToken);
		sscanf(decodedToken, "%[0-9a-zA-Z]/%[0-9a-zA-Z]=%[0-9a-zA-Z.:/_%-]", section, field, value); 
		//check if DNS update and allowed to perform
		if(compStr(section, "DNS", sizearray(section)) && !compStr(field, "useDHCP", sizearray(field)) && (smartDnsUpdatePerformed == 1)){

		//do nothing
		} else {
		n = write_config_var(section, field, value);
		}

		//Check if an update for smartDNS selected which is not set to other
 		if(compStr(section, "SmartDNS", sizearray(section)) && compStr(field, "selected", sizearray(section)) && !compStr(value, "other", sizearray(section))) {
		strcpy(buf, "SmartDNS-");
		strcat(buf, value);
		//get DNS details for SmartDNS provider
		read_config_var(buf, "primary", smartDnsProviderPrimary);
		read_config_var(buf, "secondary", smartDnsProviderSecondary);
		//set DNS details to selected SmartDNS Provider
		n = write_config_var("DNS", "primary", smartDnsProviderPrimary);
		n = write_config_var("DNS", "secondary", smartDnsProviderSecondary);
		//set that DNS update has been performed so any unwanted commits don't occur after
		smartDnsUpdatePerformed=1;
		}


	}	 
	
	token = strtok (NULL, "&"); 
        }
	
  //n = write_config_var(section, field, decValue);
  }
}

//main function for web services
int main(void) {
  printf( "HTTP/1.1 200 OK\n" );
  printf( "Content-Type: text/html; charset=UTF-8\n" );
  
  long n;
  char strPage[1023];
  char str[1024];
  char *data;
  char *token;
  const char *key, *value;
  char *postBuffer = NULL;
  int postRead;
  unsigned int postLen;
  char *postData;
  char * queryString;
  char query_action[1024];
  char query_section[1024];
  char query_field[1024];
  char query_value[1024];

  data = malloc(QS_LEN);
  token = malloc(QS_LEN);
  key = malloc(QS_LEN);
  value = malloc(QS_LEN);
  


  //Operations if POST detected
  if(compStr(getenv("REQUEST_METHOD"), "POST", sizearray(getenv("REQUEST_METHOD")))){
    if (getenv("QUERY_STRING")) {
      token = strtok (getenv("QUERY_STRING"),"&");
      while (token != NULL) {
      sscanf(token, "%[^=]=%65536s", key, value); 
      if ( compStr(key, "page", sizearray(key) )) { 
      strcpy(strPage, value);
      }

     token = strtok (NULL, "&");     
      }
    }
    //handle post data



    postRead = getline(&postBuffer, &postLen, stdin);
    if (-1 != postRead){
      strcpy(postData, postBuffer);
    }
    
   if (compStr(strPage, "settings", sizearray(strPage) )) { 
             
             processPostData(postData);
	     web_module_headers(strPage);
             web_module_settings();
        }
    //printf(postData);
    //
    free(postBuffer);
    
  } else {
    if (!getenv("QUERY_STRING")) {
       //no query string
	web_module_headers("home");
     	web_module_home();
    }
    if (getenv("QUERY_STRING")) {
      //parse Query_STRING for page
      //query string present
      token = strtok (getenv("QUERY_STRING"),"&");
      while (token != NULL) {
      sscanf(token, "%[^=]=%65536s", key, value); 
      if ( compStr(key, "page", sizearray(key) )) { 
      //check for which page to load
	web_module_headers(value);
         if ( compStr(value, "home", sizearray(key) )) { 
             web_module_home();
         }
         if ( compStr(value, "logcat", sizearray(key) )) { 
             web_module_logcat();
         }
         if ( compStr(value, "settings", sizearray(key) )) { 
             web_module_settings();
         }
         if ( compStr(value, "status", sizearray(key) )) { 
             web_module_status();
         }
         if ( compStr(value, "companion", sizearray(key) )) { 
             web_module_companion();
         }
         if ( compStr(value, "Reboot", sizearray(key) )) { 
             reboot();
         }
      } else {
     web_module_headers("home");
     web_module_home();
     }

     token = strtok (NULL, "&");     
      }

      
     

    }
}


  web_module_footer();
}

