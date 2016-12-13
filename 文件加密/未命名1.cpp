	int key;
	int flag=1;
	while(flag)
	{
		printf("请选择操作：\n");
		printf("(1)加密：\n");
		printf("(2)解密：\n");
		printf("(3)退出：\n");
		scanf("%d",&key);
		switch(key)
		{
		case 1:lock_file(lock);system("cls");break;
		case 2:lock_file(unlock);system("cls");break;
		case 3:flag=0;break;
		defult:printf("输入错误！");
		}
		system("cls");  
	}
