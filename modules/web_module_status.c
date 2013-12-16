/*
This module presents basic device information to the user
*/

int web_module_status(void){

  	FILE *ptr_file;
       char buf[1000];
  	
	 ptr_file = popen("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $2}' | busybox cut -c6-","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "IP address is: <font style=\"color:white;\"> <b>%s</b></font><br />", buf );
        }

        ptr_file=popen("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $4}' | busybox cut -c6-","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Subnet mask is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }

        ptr_file=popen("busybox route -n | busybox grep -e \"UG\" | busybox awk '{print $2}' ","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Default gateway is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }

        ptr_file=popen("cat /sys/devices/platform/mv88de3100-hwmon.0/hwmon/hwmon0/tsen_temp","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "System Temp: <font style=\"color:white;\"> <b>%sC</b></font> <br />", buf );
        }
}

