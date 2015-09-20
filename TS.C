
#include "stdio.h"
#include "dir.h"
#include "dos.h"
#include "graphics.h"

char *malloc();/*malloc转换*/

char bmp_to_dat(char *bmp,char *dat)
/*将16色BMP文件转换为可以用putimage输出的格式，bmp为原BMP文件，dat为转化文件*/
{unsigned char c[8],scan_times,scan_pixs;
unsigned char workpos;int i,j,k,n,nowpos,iw,ih;
static int color[16]={0,4,2,6,1,5,3,7,8,12,10,14,9,13,11,15};
unsigned char workline[640],scanline[640];
FILE *fp,*targetfp;
union
{unsigned char value;
  struct
  {unsigned cl:4;
   unsigned ch:4;
  }color;
}mycolor;

if((fp=fopen(bmp,"rb"))==NULL)return(0);
targetfp=fopen(dat,"wb");

fseek(fp,18,SEEK_SET);
iw=0;ih=0;
fread(&iw,4,1,fp);        /*读图像宽度*/
fread(&ih,4,1,fp);        /*读图像高度*/
if(iw==0&&ih==0&&iw>640&&ih>480)
{fclose(fp);fclose(targetfp);return(0);}

iw--;ih--;            /*∵putimage中的长宽比实际数值少1*/
scan_times=iw/8+1;        /*行处理单位数*/
scan_pixs=scan_times*4;        /*行像素字节数∵1单位=4字节*/

fputc(iw%256,targetfp);        /*填充信息头：长、宽部分*/
fputc(iw/256,targetfp);
fputc(ih%256,targetfp);
fputc(ih/256,targetfp);
fseek(fp,-scan_pixs,SEEK_END);

for(j=0;j<=ih;j++)
{nowpos=0;
  fread(scanline,scan_pixs,1,fp);
  fseek(fp,-scan_pixs*2,SEEK_CUR);
  for(n=3;n>=0;n--)        /*解码4个位面*/
  {for(i=0;i<scan_times;i++)    /*解码各编码单位*/
   {workpos=0;
    for(k=0;k<4;k++)        /*分离出8个像素*/
    {mycolor.value=scanline[i*4+k];
     c[k*2]=color[mycolor.color.ch];
     c[k*2+1]=color[mycolor.color.cl];
    }
    for(k=0;k<8;k++)workpos+=(c[k]>>n&1)<<(7-k);
    workline[nowpos]=workpos;nowpos++;
  }}
  fwrite(workline,scan_pixs,1,targetfp);
}
fclose(fp);fclose(targetfp);
return(1);
}

main()
{
	struct ffblk ff;
	int gd=DETECT,gm,n;
	char *buffer,bmpfile[13],_16file[13]={0};
	FILE *fp;
	
	initgraph(&gd,&gm,"c://bgi");
	strcpy(bmpfile,"calc.bmp");
	strncpy(_16file,bmpfile,strlen(bmpfile)-3);
	strcat(_16file,"dat");
	if(!bmp_to_dat(bmpfile,_16file))
	{	puts("File Error!");closegraph();exit(0);}
	fp=fopen(_16file,"rb");
	findfirst(_16file,&ff,FA_ARCH);
	if((buffer=malloc(ff.ff_fsize))==NULL)exit(0);
	n=0;
	while(!feof(fp))
	{
		buffer[n]=fgetc(fp);
		n++;
	}
	putimage(63,5,buffer,COPY_PUT);
	getch();
	closegraph();
	free(buffer);
	fclose(fp);
}