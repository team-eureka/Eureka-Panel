/*
This module presents basic device information to the user
*/

int web_module_status(void){

  	FILE *ptr_file;
       char buf[1000];

	printf("<font style=\"font-weight: bold; font-size: 1.5em; color:white\">Network Status</font><br/>");
 	
	 ptr_file = popen("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $2}' | busybox cut -c6-","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "IP address is: <font style=\"color:white;\"> <b>%s</b></font><br />", buf );
        }
	 pclose(ptr_file);
        
	 ptr_file=popen("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $4}' | busybox cut -c6-","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Subnet mask is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }
	 pclose(ptr_file);

        ptr_file=popen("busybox route -n | busybox grep -e \"UG\" | busybox awk '{print $2}' ","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Default gateway is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }
	 pclose(ptr_file);

	printf("<br />","r");
	printf("<font style=\"font-weight: bold; font-size: 1.5em; color:white\">System Status</font><br/>");

	 ptr_file=popen("cat /data/chrome/.eureka.conf | grep eureka-name | busybox awk -F \":\" '{print $2}' | busybox awk -F '\"' '{print $2}' | busybox tr '\n' ' '","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Device Name: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }
	 pclose(ptr_file);

        ptr_file=popen("cat /sys/devices/platform/mv88de3100-hwmon.0/hwmon/hwmon0/tsen_temp","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "CPU Temp: <font style=\"color:white;\"> <b>%sC</b></font> <br />", buf );
        }
	 pclose(ptr_file);

        ptr_file=popen("cat /factory/serial.txt | busybox tr '\n' ' '","r");
        while (fgets(buf,1000, ptr_file)!=NULL){
          printf( "Serial #: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
        }
	 pclose(ptr_file);

}

