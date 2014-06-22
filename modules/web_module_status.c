/*
This module presents basic device information to the user
*/

int web_module_status(void)
{

    FILE *ptr_file;
    char buf[1000];
    char command[1000];
    char verinfo[100];

    // start page output
    printf("<font style=\"font-weight: bold; font-size: 2em; color:white\">Network Status</font><br/><br/>");
    ptr_file = popen("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $2}' | busybox cut -c6-","r");
    while (fgets(buf,1000, ptr_file)!=NULL)
    {
        printf( "IP address is: <font style=\"color:white;\"> <b>%s</b></font><br />", buf );
    }
    pclose(ptr_file);

    ptr_file=popen("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $4}' | busybox cut -c6-","r");
    while (fgets(buf,1000, ptr_file)!=NULL)
    {
        printf( "Subnet mask is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
    }
    pclose(ptr_file);

    ptr_file=popen("busybox route -n | busybox grep -e \"UG\" | busybox awk '{print $2}' ","r");
    while (fgets(buf,1000, ptr_file)!=NULL)
    {
        printf( "Default gateway is: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
    }
    pclose(ptr_file);

    printf("<br />","r");
    printf("<font style=\"font-weight: bold; font-size: 2em; color:white\">System Status</font><br/><br/>");

    ptr_file=popen("cat /data/chrome/.eureka.conf | grep eureka-name | busybox awk -F \":\" '{print $2}' | busybox awk -F '\"' '{print $2}' | busybox tr '\n' ' '","r");
    while (fgets(buf,1000, ptr_file)!=NULL)
    {
        printf( "Device Name: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
    }
    pclose(ptr_file);

    ptr_file=popen("cat /factory/serial.txt | busybox tr '\n' ' '","r");
    while (fgets(buf,1000, ptr_file)!=NULL)
    {
        printf( "Serial #: <font style=\"color:white;\"> <b>%s</b></font> <br />", buf );
    }
    pclose(ptr_file);

    printf("ROM Version: ");
    ptr_file=popen("grep -e '^ro.build.version.incremental=' /build.prop | busybox cut -d '=' -f 2 | busybox tr '\n' '.' && cat /system/etc/chromecast-ota.rev | busybox tr '\n' '&' && echo 'serial=' | busybox tr '\n' ' ' | busybox sed 's/ //g' && busybox sha1sum /factory/serial.txt | busybox awk '{ print $1 }' | busybox tr '\n' ' ' | busybox sed 's/ //g'","r");
    while (fgets(buf,1000, ptr_file)!=NULL)
    {
        strcpy(verinfo,buf);
    }
    pclose(ptr_file);
    ptr_file = popen("ping -c 1 -w 1 google.com > /dev/null ; echo $?", "r");
    while (fgets(buf, sizeof(buf)-1, ptr_file) != NULL)
    {
        if (compStr(buf, "0\n", sizearray(buf) ))
        {
            snprintf(command, 1000, "curl \"http://ota.team-eureka.com/ota/vercheck.php?version=%s\"", verinfo);
            ptr_file=popen(command, "r");
            while (fgets(buf, sizeof(buf)-1, ptr_file) != NULL)
            {
                if (compStr(buf, "0", sizearray(buf) ))
                {
                    printf("<font style=\"color:Green;\"><b>Up to Date</b></font>");
                }
                else
                {
                    printf("<font style=\"color:Red;\"><b>Update Available</b></font>");
                }
            }
        }
    }
    printf("<br />");
    pclose(ptr_file);
    ptr_file=popen("cat /sys/devices/platform/mv88de3100-hwmon.0/hwmon/hwmon0/tsen_temp","r");
    while (fgets(buf,1000, ptr_file)!=NULL)
    {
        printf( "CPU Temp: <font style=\"color:white;\"> <b>%sC</b></font> <br />", buf );
    }
    pclose(ptr_file);
}