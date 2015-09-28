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
		
		mouse0x5();
	}
	endGraph();
}