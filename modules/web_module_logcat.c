/*
This module presents logcat information to the user
*/

int web_module_logcat(void)
{
    //Read whitelist from file, print to web.
    FILE *ptr_file;
    char buf[1000];
    char path[1035];
    printf("<div style=\"font-size: 12px; font-family: Arial, sans-serif; background:#141517; color:white; border:1px; border-color:black\" class=\"text dark\">");
    //printf( "<font style=\"color:white\">Logcat Results:</font><br /><br />");
    //output logcat
    ptr_file = popen("logcat -d -t 40 -v time", "r");
    while (fgets(path, sizeof(path)-1, ptr_file) != NULL)
    {
        printf( "%s <br />", path );
    }
    pclose(ptr_file);
    printf("</div>");
}