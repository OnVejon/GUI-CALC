#include <dos.h >
#include <conio.h>
#include <graphics.h>
#include <bios.h>
#define MouseStatusMouseOn  1
/*#include <E:\Win-TC\projects\Desk.c>*/
/*#include <E:\Win-TC\projects\MouseR.c>*/         /*这里是包含文件头*/
struct mouse
{
   int top;
   int botton;
   int left;
   int rigth;
}Smouse;
extern void Dosk();

  unsigned int size;
  void *ball;
  
int MouseX        =0;        /*存放鼠标的水平方向的值*/
int MouseY        =0;
char MouseType    =1;


enum MOUSE_MESSAGES_CODE
{        NOTHING=0,
        LBUTTONCLK=1,

};
int arrowMousePixSave[16][10];
int arrowMouseDraw[16][10]={    /*设计鼠标的形状,其中1:表示鼠标的边界,2:表示鼠标边界所包围的区域,3:表示鼠标以外的区域*/
 {1,1,3,3,3,3,3,3,3,3},{1,2,1,3,3,3,3,3,3,3},{1,2,2,1,3,3,3,3,3,3},{1,2,2,2,1,3,3,3,3,3},
 {1,2,2,2,2,1,3,3,3,3},{1,2,2,2,2,2,1,3,3,3},{1,2,2,2,2,2,2,1,3,3},{1,2,2,2,2,2,2,2,1,3},
 {1,2,2,2,2,2,2,2,2,1},{1,2,2,2,2,2,2,1,3,3},{1,2,2,2,2,2,1,3,3,3},{1,2,1,3,1,2,2,1,3,3},
 {1,1,3,3,1,2,2,1,3,3},{3,3,3,3,3,1,2,2,1,3},{3,3,3,3,3,1,2,2,1,3},{3,3,3,3,3,3,1,1,2,1} };
 

 
int editMousePixSave[15][5];
 
int editMouseDraw[15][5]={
{1,1,3,1,1},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},
{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{3,3,1,3,3},{1,1,3,1,1} 
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
void SetMouseHori(int minX,int maxX)
 {
    _AX=0x07;
    _CX=minX;
    _DX=maxX;
    geninterrupt(0x33);
}

void SetMouseVert(int minY,int maxY)
 {
    _AX=0x08;
    _CX=minY;
    _DX=maxY;
    geninterrupt(0x33);
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
void SetMouseXY(int x,int y)
 {
   _AX=0x04;
   _CX=x;
   _DX=y;
    geninterrupt(0x33);
 }
void GetMouseXY()
{
    _AX=0x03;
    geninterrupt(0x33);
    MouseX=_CX;        /*将鼠标水平方向位置存放到MouseX*/
    MouseY=_DX;        /*将鼠标垂直方向位置存放到MouseY*/

}
void initgr(void) /* BGI初始化 */
{
  int gd = DETECT, gm = 0; /* 和gd = VGA,gm = VGAHI是同样效果 */
  registerbgidriver(EGAVGA_driver);/* 注册BGI驱动后可以不需要.BGI文件的支持运行 */
  initgraph(&gd, &gm, "");
  SetMouseXY(0,0);
  SetMouseHori(0,600);
  SetMouseVert(0,450);
  setfillstyle(SOLID_FILL,7);
           bar(100,280,140,300);

  size=imagesize(100,280,141,301);
  ball=malloc(size);
  getimage(100,280,141,301,ball);
}


void main()
{   int q=0;
   float p=0;
    int temp1=0;
    int x,y,MouseMSG,M;
  int tempx,tempy,mouseMsg;

  char ch1;
  tempx=tempy=100;
  initgr();
   GetMouseXY();
   x=MouseX;
   y=MouseY;
   putimage(100,280,ball,XOR_PUT);
   while(!kbhit())
    {

        GetMouseXY();/*get current mouse position */
        /*更新鼠标位置*/
        if(tempx!=MouseX || tempy!=MouseY)
        {
            MouseOff(tempx,tempy);
            MouseOn(MouseX,MouseY);        /*显示鼠标,但保存即将被鼠标覆盖的区域*/
            tempx=MouseX;                  /* cache current mouse pos */
            tempy=MouseY;
        }
        _AX=0x03;            /*读取鼠标按钮状态*/
       geninterrupt(0x33);        /*产生33号鼠标软中断*/

        if((_BX&1) && !(_BX&2))        /*鼠标左键被按下同时右键没有按下*/
            {
               MouseMSG=4;
               M=MouseMSG;
             }
         if((_BX&2) && !(_BX&1))        /*鼠标右键被按下同时左键没有按下*/
            {
              MouseMSG=5;
              M=MouseMSG;
            }
        if(_BX&1 && _BX&2)        /*鼠标左键和右键同时被按下*/
           {
             MouseMSG=3;
             M=MouseMSG;
           }
        _AX=0x06;            /*读取鼠标按钮释放信息*/
        _BX=0x00;            /*指定读取鼠标左键的释放信息*/
        geninterrupt(0x33);        /*产生33号鼠标软中断*/
        if(_BX==1)            /*如果鼠标左键的释放数为1*/
           MouseMSG=2;            /*产生一个单击左键信息*/
         if(_BX==0&&M==4)
             if( tempx>=100&&tempx<=140&& tempy>=280&&tempy<=300)
             {
               setcolor(RED);
               /*outtextxy(100,100,"111111111111111111111");*/
               GetMouseXY();
                if(tempx!=MouseX || tempy!=MouseY)
                  {
                         /*outtextxy(200,200,"2222222222222");*/
                         putimage(300,270,ball,XOR_PUT);
                         delay(100);

                    }
             }
        /* if(_BX==1&&M==4)   */

 

         _AX=0x06;            /*读取鼠标按钮释放信息*/
        _BX=0x01;            /*指定读取鼠标右键的释放信息*/
        geninterrupt(0x33);        /*产生33号鼠标软中断*/
        if(_BX==1)            /*如果鼠标左键的释放次数为1*/
          MouseMSG=1;            /*产生一个单击右键信息*/

 

   }

}
