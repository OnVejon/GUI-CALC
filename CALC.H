#include "INPUT.H"
#include <math.h>

#define MAX 200
void compute();
int howdot(char str[]);
double calculated(char ch,double x,double y);

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void compute()
{
	char ch;
	char textbuff[MAX];
	char s_stack[MAX];
	double d_stack[MAX];
	int i=0,s_top=-1,d_top=-1;
	while(1)
	{
		
		if((ch=GetNumCh())!='\0')
		{
			if((ch>='0'&&ch<='9')||ch=='.')
			{
				if(i>15)
					i=0;
				textbuff[i++]=ch;
				textbuff[i]='\0';
				
				if(howdot(textbuff)>1)
				{					
					textbuff[--i]='\0';
				}
				massage(textbuff);
			}else if(ch=='(')
			{
				s_stack[++s_top]=ch;
			}else if(ch==')')
			{
				d_stack[++d_top]=atof(textbuff);
				while(d_top>=0&&s_top>=0&&s_stack[s_top]!='(')
				{
					d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
					d_top--;
				}
				if(d_top<=0||s_top<=0)
				{
					massage("error ()");
					s_top=-1;
					d_top=-1;
					
					i=0;
					textbuff[i]='\0';
					massage("0.");
				}else
				{
					s_top--;
					fprintf(textbuff,"%f",d_stack[d_top]);
					massage(textbuff);
				}
				
			}else if(ch==0x1)
			{
				return;
			}else if(ch=='D')
			{
				textbuff[--i]='\0';
				massage(textbuff);
			}else if(ch=='=')
			{
				d_stack[++d_top]=atof(textbuff);
				while(s_top>=0)
				{
					d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
					d_top--;
				}
				
				fprintf(textbuff,"%f",d_stack[d_top]);
				massage(textbuff);
			}else
			{
				d_stack[++d_top]=atof(textbuff);
				i=0;
				if(s_top>=0&&s_stack[s_top]!='(')
				{
					 if(ch=='+'||ch=='-')
					{	
						
						d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
						d_top--;
						
						fprintf(textbuff,"%f",d_stack[d_top]);
						massage(textbuff);
						
						
					}else if(ch=='*'||ch=='/')
					{
						if(s_stack[s_top]=='^'||s_stack[s_top]=='*'||s_stack[s_top]=='/')
						{							
							d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
							d_top--;
							
							fprintf(textbuff,"%f",d_stack[d_top]);
							massage(textbuff);
						}
					}
					
				}
				s_stack[++s_top]=ch;
			}
			
			
		}
	}
}



/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
int howdot(char str[])
{
	int i=0,j=0;
	while(str[j]!='\0')
	{
		if(str[j]=='.')
			i++;
		j++;
	}
	return i;
}

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
double calculated(char ch,double x,double y)
{
	switch(ch)
	{
		case '^':return pow(x,y);
		case '*':return x*y;
		case '/':if(y!=0)return x/y; else {massage("error div 0");} 
		case '+':return x+y;
		case '-':return x-y;
	}
}
