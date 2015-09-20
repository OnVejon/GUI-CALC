#define MAX 200
double compute(char str[]);


double compute(char str[])
{
	double dStack[200];
	char sStack[200];
	int d_top=-1,s_top=-1;
	int i=0;
	
	while (str[i]!='\0')
	{
		if(str[i]=='(')
		{
			sStack[++s_top]=str[i++];
		}else if(str[i]==')')
		{
			while(d_top>=0&&s_top>=0&&sStack[s_top]!='(')
			{
				dStack[d_top-1]=calculated(sStack[top--],dStack[d_top-1],dStack[d_top]);
				d_top--;
			}
			if(s_top<0||d_top<0)
			{
				
			}
			s_top--;
		}else if(str[i]=='^')
		{
			while(d_top>=0&&s_top>=0&&)
		}
	}
}

double calculated(char ch,double x,double y)
{
	switch(ch)
	{
		case '^':return pow(x,y);
		case '*':return x*y;
		case '/':if(y!=0)return x/y; else {error(0);} 
		case '+':return x+y;
		case '-':return x-y;
	}
}