
main()
{
	char ch='\0';
	while(ch!='.')
	{
		if(!kbhit())
		{
			ch=getch();
			if(ch=='\0')
			{
				printf("0 ");
				ch=getch();
			}
			printf("%x ",ch);
		}
	}
}