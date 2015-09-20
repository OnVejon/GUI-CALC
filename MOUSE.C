#include "mouse.h"

main()
{
	char textbuff[22]={0};
	int i=0;
	char ch;
	initGraph();
	resetmouse();
	showmouse();
	
	UI();
	massage("0.");
	while(!kbhit())
	{
		
		if((ch=mouse0x5())!='\0')
		{
			textbuff[i++]=ch;
			textbuff[i]='\0';
			if(i>15)
				i=0;
			massage(textbuff);
			if(ch=='=')
			{
				endGraph();
				exit();
			}
		}
	}
	endGraph();
}