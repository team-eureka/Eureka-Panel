//
// Compile with arm-unknown-linux-gnueabi-gcc -o EurekaSettings EurekaSettings.c minIni.c
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "minIni.h"
#include "unistd.h"
//required for chmod
#include "sys/types.h"
#include "sys/stat.h"

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

//define System and Configuration config path
char * systemConfigValue = "/system/usr/share/eureka.ini";
char * userConfigValue = "/data/share/eureka.ini";

//Return configuration path (default to system if user unavailable)
char * configReadPath(void) {
  if(access(userConfigValue, R_OK) != -1 ) {
      return userConfigValue;
  } else {
      return systemConfigValue;
  }
}

//Return write configuration path
char * configWritePath(void) {
  return userConfigValue;
}

//Read configuration variable from config file
long read_config_var(const char *r_Section, const char *r_Key, char *r_Buffer){
  char *configStr = configReadPath();

  //get variable from userConfig
  ini_gets(r_Section, r_Key, "undefined", r_Buffer, 100, userConfigValue);
  
  //check if userConfig returned undefined, if so use systemConfig
  if(compStr("undefined", r_Buffer)){
    ini_gets(r_Section, r_Key, "undefined", r_Buffer, 100, systemConfigValue);
  }
}

//Write configuration variable to config file
long write_config_var(const char *w_Section, const char *w_Key, const char *w_Value){
  char *configStr = configWritePath(); 
  ini_puts(w_Section, w_Key, w_Value, configStr);
  chmod(configStr, S_IRUSR | S_IWUSR |S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
}



//Function to compare 2 character arrays for string comparison
int compStr (const char *s1, char *s2, size_t sz) {
    while (sz != 0) {
        // At end of both strings, equal.
        if ((*s1 == '\0') && (*s2 == '\0')) break;

        // Treat spaces at end and end-string the same.
        if ((*s1 == '\0') && (*s2 == ' ')) { s2++; sz--; continue; }
        if ((*s1 == ' ') && (*s2 == '\0')) { s1++; sz--; continue; }

        // Detect difference otherwise.
        if (*s1 != *s2) return 0;
        s1++; s2++; sz--;
    }
    return 1;
}

//main function
int main(int argc, char *argv[] ) {
  long n;
  char str[100];
  
  if ( argc == 1 ) /* no additional arguments, present app information */
    {
        /* Print application details */
        printf( "\n###########################################################\n" );
        printf( "# EurekaSettings v1.0                                     #\n" );
        printf( "# Team Eureka [www.Team-Eureka.com]                       #\n" );
        printf( "###########################################################\n" );
        printf( "# Licensed under GPLv3                                    #\n" );
        printf( "# Utilises code from:                                     #\n" );
        printf( "# minini [https://code.google.com/p/minini]               #\n" );
        printf( "#            licensed under Apache v2                     #\n" );
        printf( "###########################################################\n" );
        printf( "Usage: %s get [section] [var]\n", argv[0] );
        printf( "       %s set [section] [var] [value]\n\n", argv[0] );
        return 0;
    }


  //Get configuration variables from ini file
  if(compStr("get", argv[1], sizearray(argv[1]))){
    if( argc == 4 ){
        n = read_config_var(argv[2], argv[3], str);
        printf("%s", str);
    } else {
        printf( "Incorrect Syntax\n Usage: %s get [section] [var]\n", argv[0]);
    } 
  }

  //Set configuration variables to data ini file
  else if(compStr("set", argv[1], sizearray(argv[1]))){
    if( argc == 5 ){
        n = write_config_var(argv[2], argv[3], argv[4]);
    } else {
        printf( "Incorrect Syntax\n Usage: %s set [section] [var] [value]\n", argv[0]);
    } 
  } else {
  //catch for any unavailable options
    printf( "Incorrect option \"%s\"\n Usage: %s get [section] [var]\n Usage: %s set [section] [var] [value] \n", argv[1], argv[0], argv[0]);
  }
  
}
