#include "mouse.h"
#include "calc.h"
main()
{
	char textbuff[22]={0};
	int i=0;
	char ch;
	initGraph();
	/*resetmouse();
	showmouse();*/
	
	UI();
	
	while(!kbhit())
	{
		
		ch=mouse_left();
		if(ch!='\0')
		{
			textbuff[i++]=ch;
			massage(textbuff);
		}
	}
	endGraph();
}