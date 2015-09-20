/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
#include <GRAPHICS.H>
#define BOX_L 64
#define BOX_H 48
#define NUB 15

typedef struct {
	char ch;
	int x;
	int y;
}Bottom;

Bottom Bottoms[5][4];

void UI(void);
void initGraph(void);
void endGraph(void);
void CNumBox(int x,int y,char ch);
void initBottoms();
void showBottoms();
void massage(char *textBuff);
int max_x,max_y;


/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void initGraph(void)
{
	int driver=0,mode;
	
	registerbgidriver(EGAVGA_driver);
	initgraph(&driver,&mode, "");
	
}


/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void endGraph(void)
{
	getch();
	closegraph();
}
/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void drawmat(char *mat,int matsize,int x,int y,int color)
/*依次：字模指针、点阵大小、起始坐标(x,y)、颜色*/
{int i,j,k,n;
 n=(matsize-1)/8+1;
 for(j=0;j<matsize;j++)
  for(i=0;i<n;i++)
   for(k=0;k<8;k++)
    if(mat[j*n+i]&(0x80>>k))  /*测试为1的位则显示*/
     putpixel(x+i*8+k,y+j,color);
}


/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void UI(void)
{
	
	
	int mleft, mtop, mright, mbottom;
	max_x=getmaxx();/*640*/
	max_y=getmaxy();/*480*/
	
	mleft=max_x/2-(3*BOX_L);
    mtop=max_y/2-(4*BOX_H+30);
	mright=max_x/2+(3*BOX_L);
	mbottom=max_y/2+(4*BOX_H)+30;
	
	
	
	
	
	cleardevice();
	rectangle(mleft,mtop,mright,mbottom);
	
	rectangle(mleft+2*NUB,mtop+2*NUB,mright-2*NUB,mtop+3*NUB+2*BOX_H);
	initBottoms();
	showBottoms();
	
}

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void initBottoms()
{
	int i,j;
	int mleft, mtop, mright, mbottom;
	char num_ch[5][4]={"C0.=","123+","456-","789*","()^/"};
	
	mleft=max_x/2-(3*BOX_L);
   
	mbottom=max_y/2+(4*BOX_H)+30;
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			Bottoms[i][j].ch=num_ch[i][j];
			Bottoms[i][j].x=mleft+j*(NUB+BOX_L)+3*NUB-5;
			Bottoms[i][j].y=mbottom-((i+1)*(NUB+BOX_H/2)+2*NUB);
		}
	}
}

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void showBottoms()
{
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<4;j++)
		{
			CNumBox(Bottoms[i][j].x,Bottoms[i][j].y,Bottoms[i][j].ch);
		}
	}
}



/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void massage(char *textBuff)
{
	int mleft, mtop, mright, mbottom;
	int text_box_lx,text_box_ly;
	int i,j;
	
	mleft=max_x/2-(3*BOX_L);
    mtop=max_y/2-(4*BOX_H+30);
	mright=max_x/2+(3*BOX_L);   
	
	text_box_lx=mright-2*NUB-10;
	text_box_ly=mtop+3*NUB+2*BOX_H-10;
	
	
	setcolor(WHITE);
	for(i=0;i<NUB+2*BOX_H-20;i++)
		line(mleft+2*NUB+10,mtop+2*NUB+10+i,text_box_lx,mtop+2*NUB+10+i);
	
	
	setcolor(BLACK);
	settextstyle(0,0,2);
	if((i=strlen(textBuff))<22)
	{
		outtextxy(text_box_lx-20-16*i,text_box_ly-BOX_H,textBuff);
	}
	
}
/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void CNumBox(int x,int y,char ch)
{
	char a[2]={0};
	a[0]=ch;
	
	setfillstyle(1,WHITE);
	setcolor(WHITE);
	rectangle(x,y,x+BOX_L,y+BOX_H/2);
	floodfill(x+1,y+2,WHITE);
	setcolor(BLACK);
	outtextxy(x+BOX_L/2,y+BOX_H/6,a);
}
