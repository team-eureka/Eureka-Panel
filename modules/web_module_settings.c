#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "assert.h"
#include "string.h"
#include "minIni.h"
#include "malloc.h"
#include "stdbool.h"

/*
This module handles post of settings
*/
//Format functions

int printFieldChange(char *DisplayName, char *Section, char *Field){
  long n;
  char str[1024];
  //printf ("Section %s, Field %s", Section, Field);
  read_config_var(Section, Field, str);
  printf("<div class=\"text dark\"><label style=\"text-align: left; display: inline-block\"><div style=\"width:200px\">%s</div></label><input name=\"%s/%s\" type=\"text\" id=\"value\" value=\"%s\" size=\"30\" style=\"width:300px\"/></div><br />\n", DisplayName, Section, Field,  str );

}

int printFieldValue(char *DisplayName, char *Section, char *Field){
  long n;
  char str[1024];
  //printf ("Section %s, Field %s", Section, Field);
  read_config_var(Section, Field, str);
  printf("<div class=\"text dark\"><label style=\"text-align: left; display: inline-block\"><div style=\"width:200px\">%s</div></label><label style=\"text-align: left; display: inline-block\"><div style=\"width:300px\">%s</div></label></div><br />\n", DisplayName, str );

}


int printRadioFieldChange(char *DisplayName, char *Section, char *Field){
  long n;
  char str[1024];
  char *enableChk = "";
  char *disableChk = "";
  bool valueStatus;
  //printf ("Section %s, Field %s", Section, Field);
  read_config_var(Section, Field, str);

  if(checkBoolValue(Section, Field) == 0){
	disableChk = "checked";
  } else { enableChk = "checked"; }

  printf("<div class=\"text dark\"><label style=\"text-align: left; display: inline-block\"><div style=\"width:200px\">%s</div></label><div style=\"width:300px; text-align:left; display: inline-block\"><input type=\"radio\" name=\"%s/%s\" id=\"value\" value=\"1\" size=\"30\" style=\"width:30px\" %s/>Enable <input type=\"radio\" name=\"%s/%s\" id=\"value\" value=\"0\" size=\"30\" style=\"width:30px\" %s/> Disable </div></div><br />\n", DisplayName, Section, Field, enableChk, Section, Field, disableChk );

}
int checkBoolValue(char *Section, char *Field){
  long n;
  char str[1024];
  read_config_var(Section, Field, str);
  if(compStr(str, "0", sizearray(str))){
  return 0;
  } else {
  return 1;
  }
}

int checkStringValue(char *Section, char *Field, char *Value){
  long n;
  char str[1024];
  read_config_var(Section, Field, str);
  if(compStr(str, Value, sizearray(str))){
  return 1;
  } else {
  return 0;
  }
}

int printDNSProviders(){
  long n;
  char str[1024];
  char buf[1024];
  char *token;
  char providerDisplayName[1024];
  char selectedProvider[1024];
  char *selectedProviderText;
  char *providerPrimaryIP;
  char *providerSecondaryIP;

  printf("<div class=\"text dark\"><label style=\"text-align: left; display: inline-block\"><div style=\"width:200px\">DNS Provider</div></label><div style=\"width:300px; text-align:left; display: inline-block\"> ");
  printf("<select name=\"SmartDNS/selected\" style=\"background: #141517; color: white; border-color: black; border-style: solid; border-width: 1px; width: 300px; border-radius: 2px; height: 26px; \">");
  read_config_var("SmartDNS", "selected", selectedProvider);
  read_config_var("SmartDNS", "Providers", str);
  
  token = strtok (str,",");
  while (token != NULL) {
  
  if(compStr(selectedProvider, token, sizearray(selectedProvider))){
	selectedProviderText = "selected";
  } else { selectedProviderText = ""; }
  //buf = "";
  strcpy(buf, "SmartDns-");
  strcat(buf, token);
  //get DisplayName from config
  read_config_var(buf, "displayName", providerDisplayName);
  
  printf("<option value=\"%s\" %s>%s</option>", token, selectedProviderText, providerDisplayName);

  token = strtok (NULL, ","); 
  }
  //check if other is selectedProvider
  if(compStr(selectedProvider, "other", sizearray(selectedProvider))){
	selectedProviderText = "selected";
  } else { selectedProviderText = ""; }
  
  printf("<option value=\"other\" %s>Other (Please Specify)</option>", selectedProviderText);

  printf("</select></div><br/><br/>");

}


int web_module_settings(){
  //echo out current used variables
  printf("<div align=\"center\" style=\"text-align:center;\">");
  printf("<form id=\"form1\" name=\"form1\" method=\"post\" action=\"\">  <input name=\"action\" type=\"hidden\" id=  \"action\" value=\"update\" />");
  printf("<input name=\"page\" type=\"hidden\" id=  \"settings\" value=\"settings\" />");
  printf("\n<br/><div style=\"display: inline-block\"><div style=\"width:500px; text-align:left\"><font style=\"color:white\"><b>Rom Settings</b></font></div></div><br/>\n");
  printRadioFieldChange("Team Eureka OTA Updates", "EurekaRom", "ota");
  
  printf("\n<br/><div style=\"display: inline-block\"><div style=\"width:500px; text-align:left\"><font style=\"color:white\"><b>WhiteList</b></font></div></div><br/>\n");
  printRadioFieldChange("Use Google Whitelist", "WhiteList", "useGoogle");
  if(checkBoolValue("WhiteList", "useGoogle") == 0){
  printRadioFieldChange("Use Local Whitelist", "WhiteList", "useLocal");
  	if(checkBoolValue("WhiteList", "useLocal") == 0){
  		printFieldChange("Whitelisting Download URL", "WhiteList", "downloadurl");
  	}
  }
  printf("\n<br/><div style=\"display: inline-block\"><div style=\"width:500px; text-align:left\"><font style=\"color:white\"><b>DNS</b></font></div></div><br/>\n");

  printRadioFieldChange("Use DHCP", "DNS", "useDHCP");
  if(checkBoolValue("DNS", "useDHCP") == 0){
  printDNSProviders();
  if(checkStringValue("SmartDNS", "selected", "other")){
  	printFieldChange("Primary DNS Server", "DNS", "Primary");
  	printFieldChange("Secondary DNS Server", "DNS", "Secondary");
  } else {
	printFieldValue("Primary DNS Server", "DNS", "Primary");
  	printFieldValue("Secondary DNS Server", "DNS", "Secondary");
  }
  }
  printf("<div style=\"display: inline-block\"><button type=\"submit\">Apply Updates</button></form>");
  printf("<form onsubmit=\"return confirm('Are you sure you want to Reboot your chromecast?');\" id=\"form1\" name=\"form1\" method=\"get\" action=\"\" style=\"display: inline-block\"><button name=\"page\" type=\"submit\" id=\"page\" value=\"Reboot\">Reboot Device</button></form></div></div>\n");

  

}
