/*
This module presents the home screen to the user
*/
#define sizearray(a)  (sizeof(a) / sizeof((a)[0]))

int web_module_aboutus(void){
  	FILE *ptr_file;
        char buf[1000];
 	char path[1035];
	printf("<div><font style=\"font-weight: bold; font-size: 2em; color:white\">Team Eureka</font><br /><br />\n");

	printf("Team Eureka was formed in early November 2013 with the joining of the main contributors to the XDA Chromecast community, which included ddggttff3, kyonz, and tchebb. The objectives of the team is to provide the best device experience to the community, to encourage development from other users, and to remain clear and transparent in both our operation and our releases. The group was formed to transform the Chromecast into the device Google engineers clearly envisioned, but were hamstrung from executing due to external influences. (Thanks Obama!)<br /><br />\n");

	printf("The unique skills of each member of the team provides a full compliment of abilities that can be called upon and it is clear that together; Team Eureka has the best chance of achieving the best advancement for the rooted Chromecast community.<br /><br />\n");

	printf("We hope that you are as excited about the current projects of the team as we are and we look forward to aligning the Chromecast device with our vision. We hope one day that google will share this vision of the device with the world.<br /><br />\n");

//Line Break
	printf("<hr/><br />\n");

//DD

	printf("<font style=\"font-weight: bold; font-size: 1.5em; color:white\">ddggttff3 - Release Manager, Developer</font><br /><b>www.twitter.com/riptide_wave</b> <br/><b>www.github.com/riptidewave93</b><br /><br />\n");

	printf("Chris Blake (ddggttff3) provides a great deal of passion to the team while also being a full time student studying in the field of System and Network Administration. He is enthusiastic and determined to provide a rich experience to the Chromecast community, while also helping increase the functionality of the device. To the rest of the team he is known as the unappointed “head of logistics”.<br /><br />");

	printf(" Notable mentions to the Chromecast community include PwnedCast, and his Tutorial Videos.<br /><br />");

//Tchebb
	printf("<font style=\"font-weight: bold; font-size: 1.5em; color:white\">tchebb - Quality Assurance, Developer</font><br /><br />\n");

	printf("Thomas Hebb (tchebb) is the purest definition of a young prodigy and the team is incredibly proud to have him as a key member. If you need a linux guru, or an obscure graphics driver developed - he’s your #1 man. When he is not developing for FlashCast or submitting patches to Arch Linux, he is working on his education at *RETRACTED*. He one day hopes to work for *RETRACTED* although chances are good that one day they’ll hope to work for him.<br /><br />");

	printf("Notable mentions to the Chromecast community include FlashCast and providing early insight and development that has formed the basis for the rooted Chromecast community.<br /><br />");


//Kyonz



	printf("<font style=\"font-weight: bold; font-size: 1.5em; color:white\">kyonz - Public Relations, Developer</font><br /><b>www.twitter.com/kyonz</b> <br/><b>www.linkedin.com/in/trevorpreston</b><br /><br />\n");

	printf("Trevor Preston (kyonz) hails from the unlikely country of New Zealand (where the ChromeCast is currently unavailable) and when not spending time fighting Sauron spends most of his time working in the world of systems as a Solutions Architect. Interests include following technological advancements in progressing fields and the ethical and ecological impacts that are created as well as having a fond keenness in physical and logical automation which lead him to fall in love with the Chromecast device.<br /><br />");

	printf("Notable mentions to the Chromecast community include KyoCast and the Team Eureka web panel, which is pretty badass, am I right?<br /><br />");
//more info
	printf("</div>\n");      

}
