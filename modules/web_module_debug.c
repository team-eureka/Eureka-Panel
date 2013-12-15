/*
This module presents logcat information to the user
*/

int web_module_debug(void){


      printf("<div align=\"center\" style=\"text-align:center;\">");
  printf("<form id=\"logCatForm\" style=\"display: inline-block\">");
  printf("<input name=\"headers\" type=\"hidden\" id=  \"headers\" value=\"0\" />");
  printf("<input name=\"footers\" type=\"hidden\" id=  \"footers\" value=\"0\" />");
  printf("<input name=\"popup\" type=\"hidden\" id=  \"popup\" value=\"1\" />");
printf("<input name=\"page\" type=\"hidden\" id=  \"logcat\" value=\"logcat\" />");
  printf("<button name=\"\" type=\"submit\" id=\"ajaxsubmit\" value=\"ajaxsubmit\">Logcat</button></form>\n");

      printf("</div>\n\n\n");

	printf("<div id=\"response\"></div>");

printf("<script type=\"text/javascript\">\n");


printf("var logCat = document.getElementById('logCatForm');\n");
printf("logCat.onsubmit = function() {\n");
printf("window.open('?headers=0&footers=0&popup=1&page=logcat', 'Popup_Window', 'toolbar=0,scrollbars=0,location=0,statusbar=0,menubar=0,resizable=1,width=900,height=500,left = 312,top = 234');\n");
printf("this.target = 'Popup_Window';\n");
printf("}\n");
printf("</script>\n\n");

}

