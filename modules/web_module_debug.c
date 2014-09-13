/*
This module presents the debug page
*/

int web_module_debug(char *command)
{
    FILE *ptr_file;
    char buf[1000];
    char path[1035];
    printf("<font style=\"font-weight: bold; font-size: 2em; color:white\">Debug Tools</font><br />\n");
    printf("<div align=\"center\" style=\"text-align:center;\" >");
    printf("<div style=\"display: inline-block\" >");
    printf("<form id=\"logCatForm\" style=\"display: inline-block\">");
    printf("<input name=\"headers\" type=\"hidden\" id=  \"headers\" value=\"0\" />");
    printf("<input name=\"footers\" type=\"hidden\" id=  \"footers\" value=\"0\" />");
    printf("<input name=\"popup\" type=\"hidden\" id=  \"popup\" value=\"1\" />");
    printf("<input name=\"page\" type=\"hidden\" id=  \"logcat\" value=\"logcat\" />");
    printf("<button name=\"\" type=\"submit\" id=\"ajaxsubmit\" value=\"ajaxsubmit\">Logcat</button></form>\n");
    printf("<form id=\"form1\" name=\"form1\" method=\"get\" action=\"\" style=\"display: inline-block\"><button name=\"page\" type=\"submit\" id=\"page\" value=\"forceeurekaupdate\"  style=\"display: inline-block\">Force Update</button></form>\n");
    printf("<form id=\"form2\" name=\"form2\" method=\"get\" action=\"\" style=\"display: inline-block\"><button name=\"page2\" type=\"submit\" id=\"page2\" value=\"dumpstate\"  style=\"display: inline-block\">Get dumpstate</button></form>\n");
    printf("</div></div><br /><br />\n\n\n");
    printf("<div class=\"text dark\"><label style=\"text-align: left; display: inline-block\"><div style=\"width:120px\">Send Command: </div></label><form id=\"form1\" name=\"form1\" method=\"post\" action=\"\" style=\"display: inline-block\"><input name=\"page\" type=\"hidden\" id=  \"debug\" value=\"debug\" /><input name=\"command\" type=\"text\" id=\"command\" value=\"%s\" size=\"30\" style=\"width:790px\" /> <button style=\"display: inline-block\">Send</button></form></div><br />", command);
    printf("<div class=\"text dark\"><label style=\"text-align: left; display: inline-block\"><div style=\"width:120px\">Output: </div></label><textarea size=\"30\" rows=\"15\" style=\"width:840px; background:#141517; color:white; border:1px; border-color:black\" class=\"text dark\">");

    ptr_file = popen(command, "r");
    while (fgets(path, sizeof(path)-1, ptr_file) != NULL)
    {
        printf( "%s", path );
    }
    pclose(ptr_file);

    printf("</textarea> </div><br />");
    printf("<div id=\"response\"></div>");
    printf("<script type=\"text/javascript\">\n");
    printf("var logCat = document.getElementById('logCatForm');\n");
    printf("logCat.onsubmit = function() {\n");
    printf("window.open('?headers=0&footers=0&popup=1&page=logcat', 'Popup_Window', 'toolbar=0,scrollbars=0,location=0,statusbar=0,menubar=0,resizable=1,width=900,height=500,left = 312,top = 234');\n");
    printf("this.target = 'Popup_Window';\n");
    printf("}\n");
    printf("</script>\n\n");
}
