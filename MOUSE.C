#include <dos.h>
#include <GRAPHICS.H>

#define RESET_MOUSE 0x00
#define SHOW_MOUSE 0x01
#define LEFT_BUTTON 0
#define RIGHT_BUTTON 1
#define EITHER_BUTTON 2
#define CHECK_BUTTON_PRESSED 0x05

void mouse(int *ax, int *bx, int *cx, int *dx)
{
    union REGS inregs, outregs;

    inregs.x.ax = *ax;
    inregs.x.bx = *bx;
    inregs.x.cx = *cx;
    inregs.x.dx = *dx;
    int86(0x33, &inregs ,&outregs);
    *ax = outregs.x.ax;
    *bx = outregs.x.bx;
    *cx = outregs.x.cx;
    *dx = outregs.x.dx;
}

int resetmouse(void)
{
    int m1, m2, m3, m4;

    m1 = RESET_MOUSE;
    mouse(&m1, &m2, &m3, &m4);

    return(m1);

}

void showmouse(void)
{
    int m1, m2, m3, m4;

    m1 = SHOW_MOUSE;
    mouse(&m1, &m2, &m3, &m4); 
}

int testbutton(int testtype, int whichbutton)
{
        int m1, m2, m3, m4;

        m1 = testtype;
        if (whichbutton == LEFT_BUTTON || whichbutton == EITHER_BUTTON)
        {
            m2 = LEFT_BUTTON;
            mouse(&m1, &m2, &m3, &m4);
            if (m2) return 1; 
        }
        if (whichbutton == RIGHT_BUTTON || whichbutton == EITHER_BUTTON)
        {
            m2 = RIGHT_BUTTON;
            mouse(&m1, &m2, &m3, &m4);
            if (m2) return 1; 
        } 
        return 0;
}


int left_pressed(void)
{
        return(testbutton(CHECK_BUTTON_PRESSED, LEFT_BUTTON)); 
}

main()
{
	int i;
	int driver=0,mode;
	int max_x,max_y;
	registerbgidriver(EGAVGA_driver);
	
	initgraph(&driver,&mode, "");
	resetmouse();
	showmouse();
	max_x=getmaxx();
	max_y=getmaxy();
	printf("MAxx=%d,maxy=%d",max_x,max_y);
	while(!kbhit())
	{
		if(left_pressed())
		printf("1 ");

	}
	closegraph();
}

