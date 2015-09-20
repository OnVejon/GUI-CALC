#include "stdio.h"
#include "graphics.h"
#include "alloc.h"
#include "stdlib.h"
#include "math.h" 

typedef struct tagBITMAPFILEHEADER
{
unsigned int bfType;
unsigned long bfSize;
unsigned int bfReserved1;
unsigned int bfReserved2;
unsigned long bfOffBits;
}BITMAPFILEHEADER; 

typedef struct tagBITMAPINFOHEADER
{
unsigned long biSize;
long biWidth;
long biHeight;
unsigned int biPanes;
unsigned int biBitCount;
unsigned long biCompression;
unsigned long biSizeImage;
long biXPelsPerMeter;
long biYPelsPerMeter;
unsigned long biClrUsed;
unsigned long biClrImportant;
}BITMAPINFOHEADER; 

typedef struct tagRGBQUAD
{
unsigned char rgbBlue;
unsigned char rgbGreen;
unsigned char rgbRed;
unsigned char rgbReserved;
}RGBQUAD; 

typedef struct tagBITMAPINFO
{
BITMAPINFOHEADER bmiHeader;
RGBQUAD bmiColors[];
}BITMAPINFO; 

int xmax;
int ymax; 

void InitGraph()
{
int mod=EGA;
int dr=EGAHI;
initgraph(&mod,&dr,"c://bgi");
xmax=getmaxx();
ymax=getmaxy();
} 

void CloseGraph()
{
closegraph();
} 

void Exit(char *ErrorCode)
{
printf("%s",ErrorCode);
getch();
exit(0);
} 

long WidthBytes(long Width,int BitCount)
{
long WBytes;
WBytes=(Width*BitCount+31)/8;
WBytes=WBytes/4*4;
return WBytes;
} 

unsigned char SetPalette(int Colors,unsigned char data)
{
switch(Colors)
{
case 16:
 switch(data)
 {
 case 1:
   return 4;
 case 4:
   return 1;
 case 3:
   return 6;
 case 6:
   return 3;
 case 9:
   return 12;
 case 12:
   return 9;
 case 11:
   return 14;
 case 14:
   return 11;
 default:
   return data;
 }
case 2:
 if(data==1)
   return 15;
 else
   return 0;
}
} 

void main()
{
long i,j;
long WBytes;
int Colors;
long Height,Width;
FILE *fp;
void *Temp=NULL;
BITMAPFILEHEADER bfh;
BITMAPINFOHEADER bih;
unsigned char SrcData,data;
InitGraph();
if((fp=fopen("calc.bmp","rb"))==NULL)
{
Exit("Can Not Open The File.\n");
}
fread(&bfh,sizeof(BITMAPFILEHEADER),1,fp);
if(bfh.bfType!='M'*256+'B')
{
Exit("This Is Not A Bmp File.\n");
}
fread(&bih,sizeof(BITMAPINFOHEADER),1,fp);
Height=bih.biHeight;
Width=bih.biWidth;
WBytes=WidthBytes(Width,bih.biBitCount);
Colors=1<<bih.biBitCount;
if(!(Colors==16||Colors==2))
{
Exit("This Programme Only For 16 Colors Bitmap.\n");
}
fread(Temp,sizeof(RGBQUAD),Colors,fp);
printf("%d %d",'\f','\t');
for(i=Height-1;i>=0;i--)
{
 fseek(fp,54+Colors*sizeof(RGBQUAD)+i*WBytes,SEEK_SET);
 for(j=0;j<Width;j++)
 {
   switch(Colors)
   {
   case 16:
     if(j%2==0)
     {
	fread(&SrcData,1,1,fp);
data=SetPalette(Colors,SrcData/16);
putpixel(j,Height-1-i,data);
     }
     else
     {
data=SetPalette(Colors,SrcData%16);
putpixel(j,Height-1-i,data);
     }
     break;
   case 2:
     if(j%8==0)
     {
fread(&SrcData,1,1,fp);
data=SetPalette(Colors,(SrcData>>7)%2);
putpixel(j,Height-1-i,data);
     }
     else
     {
data=SetPalette(Colors,(SrcData>>(7-j%8))%2);
putpixel(j,Height-1-i,data);
     }
   }
 }
}
getch();
CloseGraph();
} 

