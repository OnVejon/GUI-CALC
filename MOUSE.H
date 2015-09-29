/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
#ifndef _MOUSE.H_
#define _MOUSE.H_

#include "ui.h"
#include <dos.h>
#include <GRAPHICS.H>
#define LEFT_UP 0
#define LEFT_DOWN 1

int resetmouse(void);
void showmouse(void);
char far mouse_left();

int MouseType=1;


  

int arrowMousePixSave[16][10];
int arrowMouseDraw[16][10]={    /*设计鼠标的形状,其中1:表示鼠标的边界,2:表示鼠标边界所包围的区域,3:表示鼠标以外的区域*/
 {1,1,3,3,3,3,3,3,3,3},
 {1,2,1,3,3,3,3,3,3,3},
 {1,2,2,1,3,3,3,3,3,3},
 {1,2,2,2,1,3,3,3,3,3},
 {1,2,2,2,2,1,3,3,3,3},
 {1,2,2,2,2,2,1,3,3,3},
 {1,2,2,2,2,2,2,1,3,3},
 {1,2,2,2,2,2,2,2,1,3},
 {1,2,2,2,2,2,2,2,2,1},
 {1,2,2,2,2,2,2,1,3,3},
 {1,2,2,2,2,2,1,3,3,3},
 {1,2,1,3,1,2,2,1,3,3},
 {1,1,3,3,1,2,2,1,3,3},
 {3,3,3,3,3,1,2,2,1,3},
 {3,3,3,3,3,1,2,2,1,3},
 {3,3,3,3,3,3,1,1,2,1} 
 };

int editMousePixSave[15][5];
 
int editMouseDraw[15][5]={
{1,1,3,1,1},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{3,3,1,3,3},
{1,1,3,1,1}
};

void GetMouseXY(); 
    
void MouseOn(int mousex,int mousey)
{
    int i,j;
    int color;
    if(MouseType==1)
    {
        for(i=0;i<16;i++)
			for(j=0;j<10;j++)
			{
				arrowMousePixSave[i][j]=getpixel(mousex+j,mousey+i);/* 保存原来的颜色*/
				if(arrowMouseDraw[i][j]==1)
					putpixel(mousex+j,mousey+i,0);
				else if(arrowMouseDraw[i][j]==2)        /* 画鼠标*/
					putpixel(mousex+j,mousey+i,15);
			}
    }
    else if(MouseType==2)
    {
		for(i=0;i<15;i++)
			for(j=0;j<5;j++)
			{
				editMousePixSave[i][j]=getpixel(mousex-2+j,mousey-7+i);
				if(editMouseDraw[i][j]==1)            /*由于编辑鼠标的热点在鼠标的中心*/
					putpixel(mousex-2+j,mousey-7+i,0);
			}
    }
}

/*隐藏鼠标*/
void MouseOff(int mousex,int mousey)
{
   int i,j,x,y,color;
   x=mousex;
   y=mousey;
   if(MouseType==1)
   {
      for(i=0;i<16;i++)
      for(j=0;j<10;j++)
      {
        if(arrowMouseDraw[i][j]==3)
        continue;
        color=getpixel(x+j,y+i);
        putpixel(x+j,y+i,color^color);        /*原位置异或清除*/
        putpixel(x+j,y+i,arrowMousePixSave[i][j]);/* 还原原背景*/
      }
   }
   else if(MouseType==2)
   {
        for(i=0;i<15;i++)
      for(j=0;j<5;j++)
        {
           if(editMouseDraw[i][j]==3)
            continue;
			color=getpixel(x-2+j,y-7+i);
			putpixel(x-2+j,y-7+i,color^color);    /*原位置异或清除*/
			putpixel(x-2+j,y-7+i,editMousePixSave[i][j]);/* 还原原背景*/
        }

    }
}



/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
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


/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
int resetmouse(void)
{
    int m1, m2, m3, m4;

    m1 = 0x0;
    mouse(&m1, &m2, &m3, &m4);
	
    return(m1);

}

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void showmouse(void)
{
    int ax, bx, cx, dx;
	ax=0x04;
	cx=0;
	dx=0;
	mouse(&ax, &bx, &cx, &dx);
    ax = 0x01;
    mouse(&ax, &bx, &cx, &dx); 
}
/*************************************************************************************************/
/*功能05H                                                                                        */
/*功能描述：读取鼠标按键信息                                                                     */
/*入口参数：AX＝05H，BX＝指定的按键：0—左键，1—右键，2—中键                                      */
/*出口参数：AX＝按键状态，参见功能3H中BX的说明                                                   */
/*BX＝按键次数                                                                                   */
/*CX＝水平位置(最后按键时)                                                                       */
/*DX＝垂直位置(最后按键时)                                                                       */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/

char far mouse_left()
{
	int ax, bx, cx, dx;
	static int tmpx=0,tmpy=0;
	static int MSG=LEFT_UP;
	int tx,ty;
	int i=0,j=0;
	
    ax = 0x03;
	
    mouse(&ax, &bx, &cx, &dx); 
	MouseOff(tmpx,tmpy);
	MouseOn(cx,dx);
	tmpx=cx;
	tmpy=dx;
	
    if((bx&1) && !(bx&2))        /*鼠标左键被按下同时右键没有按下*/
    {
        MSG=LEFT_DOWN;
	}		
	ax=0x06;            /*读取鼠标按钮释放信息*/
	bx=0x00;            /*指定读取鼠标左键的释放信息*/
	mouse(&ax, &bx, &cx, &dx);	
	
	if(bx==1&&MSG==LEFT_DOWN)
		{
			MSG=LEFT_UP;
			while(i<6&&j<4)
			{
				tx=Bottoms[i][j].x;
				ty=Bottoms[i][j].y;
				if((cx>=tx&&cx<=tx+BOX_L)&&(dx>=ty&&dx<=ty+BOX_H/2))
					break;
				j++;
				if(j>=4)
				{
					i++;
					j=0;
				}
					
			}
			if(i<6&&j<4)
				return Bottoms[i][j].ch;
		}         

	return '\0';
}

#endif


