
#ifndef _CALC.H_
#define _CALC.H_

#include "INPUT.H"
#include <math.h>
#include "mouse.h"
#define MAX 200
void compute();
int howdot(char str[]);
void delete_zero(char str[]);
double calculated(char ch,double x,double y);
int IsNumber(char ch);
int IsOperator(char ch);
int IsControl(char ch);
/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void compute()
{
	char ch,old_ch='\0';
	char textbuff[MAX],textbuff_1[MAX]="";
	char s_stack[MAX];
	double d_stack[MAX];
	int i=0,j=0,s_top=-1,d_top=-1;
	
	
	textbuff[i]='0';
	textbuff[i+1]='\0';
	massage(textbuff);
	while(1)
	{
		ch=mouse_left();
		if(ch=='\0')
			ch=GetNumCh();
		if(ch!='\0'&&ch!=' ')
		{
			textbuff_1[j++]=ch;
			textbuff_1[j]='\0';
			if(IsNumber(ch))/*遇到数字*/
			{
				if(old_ch=='=')
				{
					j=0;
					textbuff_1[j++]=ch;
					textbuff_1[j]='\0';
				}
				if(i>12)
					i=0;
				if(ch=='.'&&i==0)
					textbuff[i++]='0';
				
				textbuff[i++]=ch;
				textbuff[i]='\0';
				
				
				if(howdot(textbuff)>1)
				{					
					textbuff[--i]='\0';
				}
				massage(textbuff);
			}else if(ch=='(')/*遇到括号（*/
			{
				if(IsNumber(old_ch)||old_ch==')')
				{
					massage("E Error!");
					i=0;
					j=0;
					s_top=-1;
					d_top=-1;
				}else
				{
					s_stack[++s_top]=ch;
				}
				
				
			}else if(ch==')')/*遇到括号）*/
			{
				if(IsNumber(old_ch))
				{
					d_stack[++d_top]=atof(textbuff);
					while(d_top>=0&&s_top>=0&&s_stack[s_top]!='(')
					{
						d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
						d_top--;
					}
					if(d_top<0||s_top<0)
					{
						massage("error ()");
						
						s_top=-1;
						d_top=-1;
						
						i=0;
						textbuff[i]='0';
						textbuff[i+1]='\0';
						
					}else
					{
						s_top--;
						sprintf(textbuff,"%f",d_stack[d_top--]);
						delete_zero(textbuff);
						massage(textbuff);
						
						i=0;
						
					}
				}else
				{
					massage("E Error!");
					i=0;
					j=0;
					s_top=-1;
					d_top=-1;
				}
				
				
			}else if(ch=='E')/*==ESC*/
			{
				j=0;
				textbuff_1[j]='\0';
				return;
			}else if(ch=='C')/*==Clear*/
			{
				s_top=-1;
				d_top=-1;
				j=0;
				textbuff_1[j]='\0';
				i=0;
				textbuff[i]='0';
				textbuff[i+1]='\0';
				massage(textbuff);
			}else if(ch=='D')/*==back or delete*/
			{
				textbuff[--i]='\0';
				j--;
				textbuff_1[--j]='\0';
				if(j<0)
				{
					j=0;
				}
				if(i<=0)
				{
					i=0;
					textbuff[i]='0';
					textbuff[i+1]='\0';
				}
				massage(textbuff);
			}else if(ch=='=')/*得出答案*/
			{
				d_stack[++d_top]=atof(textbuff);
				while(s_top>=0)
				{
					d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
					d_top--;
				}
				
				sprintf(textbuff,"%f",d_stack[d_top--]);
				
				delete_zero(textbuff);
				
				massage(textbuff);
				
				textbuff_1[j-1]='=';
				massage_1(textbuff_1);
				
				j=strlen(textbuff);
				stpcpy(textbuff_1,textbuff);
				if(textbuff_1[j-1]=='.')
				{
					textbuff_1[--j]='\0';
				}
				i=0;
			}else			/*遇到运算符*/
			{
				if(!IsOperator(old_ch))
				{
					d_stack[++d_top]=atof(textbuff);
					i=0;
					if(s_top>=0&&s_stack[s_top]!='(')/*遇到栈中已经有运算符*/
					{
						 if(ch=='+'||ch=='-')/*栈中运算符优先级判断*/
						{	
							
							d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
							d_top--;
							
							sprintf(textbuff,"%f",d_stack[d_top]);
							delete_zero(textbuff);
							massage(textbuff);
							
							
						}else if(ch=='*'||ch=='/')
						{
							if(s_stack[s_top]=='^'||s_stack[s_top]=='*'||s_stack[s_top]=='/')
							{							
								d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
								d_top--;
								
								sprintf(textbuff,"%f",d_stack[d_top]);
								delete_zero(textbuff);
								massage(textbuff);
								
							}
						}
						
					}else if(old_ch=='('||old_ch=='C'||old_ch=='=')
					{
						d_stack[++d_top]=0.0;
					}
					s_stack[++s_top]=ch;
				}else
				{
					textbuff_1[--j]='\0';
					textbuff_1[j-1]=ch;
					s_stack[s_top]=ch;
				}
				
				
				
				
			}
			if(ch!='=')
				massage_1(textbuff_1);
			old_ch=ch;
		}
		
	}
}

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/


/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/

int IsNumber(char ch)
{
	if((ch>='0'&&ch<='9')||ch=='.')
		return 1;
	else
		return 0;
}

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/

int IsOperator(char ch)
{
	if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^')
		return 1;
	else
		return 0;
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
		{
			i++;
			
		}
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

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void delete_zero(char str[])
{
	int j=0;
	while(str[j]!='\0')j++;
	
	while(str[--j]=='0')
	{
		str[j]='\0';
		
	}
}


#endif