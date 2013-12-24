/*
This module presents the home screen to the user
*/

#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

int web_module_home(void)
{
    FILE *ptr_file;
    char buf[1000];
    char path[1035];
    printf("<div class=\"col1of2\"><font style=\"font-weight: bold; font-size: 2em; color:white\">Device Status</font><br /><br />\n");

    ptr_file = popen("busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $2}' | busybox cut -c6- ", "r");
    while (fgets(path, sizeof(path)-1, ptr_file) != NULL)
    {
        printf( "IP address: <font style=\"color:white;\"> <b>%s</b></font>", path );
    }
    pclose(ptr_file);


    ptr_file = popen("busybox ipcalc -p 1.1.1.1 $(busybox ifconfig | busybox grep -e \"inet:\" -e \"addr:\" | busybox grep -v \"inet6\" | busybox grep -v \"127.0.0.1\" | busybox head -n 1 | busybox awk '{print $4}' | busybox cut -c6- ) -s | busybox awk -F \"=\" '{print $2}'", "r");
    while (fgets(path, sizeof(path)-1, ptr_file) != NULL)
    {
        printf( "<font style=\"color:white;\"><b>/%s</b></font> <br />", path );
    }

    ptr_file = popen("busybox route -n | busybox grep -e \"UG\" | busybox awk '{print $2}'", "r");
    while (fgets(path, sizeof(path)-1, ptr_file) != NULL)
    {
        printf("Default gateway: <font style=\"color:white;\"> <b>%s</b></font> <br /><br />", path );
    }
    pclose(ptr_file);

    //check internet connectivity
    printf("Internet Connectivity:  <b>");
    ptr_file = popen("ping -c 1 -w 1 google.com > /dev/null ; echo $?", "r");
    while (fgets(path, sizeof(path)-1, ptr_file) != NULL)
    {

        if (compStr(path, "0\n", sizearray(path) ))
        {
            printf("<font style=\"color:Green;\">Available");
        }
        else
        {
            printf("<font style=\"color:Red;\">Unavailable");
        }

    }
    pclose(ptr_file);
    printf("</b></font><br />");

	//more info
    printf("<br/><br/><font style=\"font-weight: bold; font-size: 2em; color:white\">Welcome</font><br /><br />Team Eureka is very happy to welcome you to the brand new web panel! <br/><br/>We hope that you are as excited about the changes we've made as we are and we'd like to take this opportunity to welcome you to our family. <br/><br/>We're still hard at work to bring new features and improve the quality of your Chromecast experience, if you have any questions, comments or feature requests please feel free to contact us on Twitter, XDA or email us at <a href=\"mailto:info@team-eureka.com\">info@team-eureka.com</a></div>\n");
    printf("<div class=\"last-col\" style=\"text-align:right;\"><div style=\"padding-left: 50px; width:400px; text-align:right;\"><a class=\"twitter-timeline\" href=\"https://twitter.com/Dev_Team_Eureka\" data-widget-id=\"406686413359300608\">Tweets by @Dev_Team_Eureka</a>\n");
    printf("<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+\"://platform.twitter.com/widgets.js\";fjs.parentNode.insertBefore(js,fjs);}}(document,\"script\",\"twitter-wjs\");</script></div></div>\n");
}