
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

void do_Exit();/*E*/
void do_Clear();/*C*/
void do_Delete();/*D*/
void do_Equal();/*=*/
void do_Number();/*0~9 . */
void do_Operator();/* + - * /*/
void do_LParenthesis();/* ( */
void do_RParenthesis();/* ) */
void do_Error();
void show_Number();
int IsNumber(char ch);
int IsOperator(char ch);
int IsControl(char ch);

/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
char ch,old_ch='\0';
char s_stack[MAX];
double d_stack[MAX];
int i=0,j=0,s_top=-1,d_top=-1;
char textbuff[MAX]="0",textbuff_1[MAX]="";
/*************************************************************************************************/
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/
void compute()
{
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
				do_Number();
			}else if(ch=='(')/*遇到括号（*/
			{
				do_LParenthesis();
				
				
			}else if(ch==')')/*遇到括号）*/
			{
				do_RParenthesis();
			}else if(ch=='E')/*==ESC*/
			{
				do_Exit();
				
			}else if(ch=='C')/*==Clear*/
			{
				do_Clear();
			}else if(ch=='D')/*==back or delete*/
			{
				do_Delete();
			}else if(ch=='=')/*得出答案*/
			{
				do_Equal();
			}else			/*遇到运算符*/
			{
				do_Operator();
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


void do_Exit()
{
	j=0;
	textbuff_1[j]='\0';
	endGraph();
	exit(0);
}
void do_Clear()
{
	s_top=-1;
	d_top=-1;
	j=0;
	textbuff_1[j]='\0';
	i=0;
	textbuff[i]='0';
	textbuff[i+1]='\0';
	massage(textbuff);
}
void do_Delete()
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
}
void do_Equal()
{
	d_stack[++d_top]=atof(textbuff);
	while(s_top>=0)
	{
		d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
		d_top--;
	}
	
	show_Number();
	
	textbuff_1[j-1]='=';
	massage_1(textbuff_1);
	
	j=strlen(textbuff);
	stpcpy(textbuff_1,textbuff);
	if(textbuff_1[j-1]=='.')
	{
		textbuff_1[--j]='\0';
	}
	i=0;
}
void do_Number()
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
}
void do_Operator()
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
				
				show_Number();
				
				
			}else if(ch=='*'||ch=='/')
			{
				if(s_stack[s_top]=='^'||s_stack[s_top]=='*'||s_stack[s_top]=='/')
				{							
					d_stack[d_top-1]=calculated(s_stack[s_top--],d_stack[d_top-1],d_stack[d_top]);
					d_top--;
					
					show_Number();
					
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

void do_LParenthesis()
{
	if(IsNumber(old_ch)||old_ch==')')
	{
		do_Error();
	}else
	{
		s_stack[++s_top]=ch;
	}
}
void do_RParenthesis()
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
			do_Error();
			textbuff[i]='0';
			textbuff[i+1]='\0';
			
		}else
		{
			s_top--;
			show_Number();
			
			i=0;
			
		}
	}else
	{
		do_Error();
	}
				
				
}
void do_Error()
{
	massage("E Error!");
	i=0;
	j=0;
	s_top=-1;
	d_top=-1;
}
void show_Number()
{
	sprintf(textbuff,"%f",d_stack[d_top--]);
	delete_zero(textbuff);
	massage(textbuff);
}
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