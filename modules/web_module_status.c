/*
This module presents logcat information to the user
*/

int web_module_status(void){
      //Read whitelist from file, print to web.
  	FILE *ptr_file;
        char buf[1000];
  	//check if whitelist apps.conf exists in data (if not use system apps.conf)
         system("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $2}' | busybox cut -c6- > /tmp/tmp.tmp");
        ptr_file=fopen("/tmp/tmp.tmp","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "IP address is: <font style=\"color:white;\"> <b>%s</b></font><br />", buf );
        }
         system("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $4}' | busybox cut -c6- > /tmp/tmp.tmp");
        ptr_file=fopen("/tmp/tmp.tmp","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Subnet mask is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }

         system("busybox route -n | busybox grep -e \"UG\" | busybox awk '{print $2}' > /tmp/tmp.tmp");
        ptr_file=fopen("/tmp/tmp.tmp","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Default gateway is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }
        system("rm /tmp/tmp.tmp");

}

