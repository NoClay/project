	int key;
	int flag=1;
	while(flag)
	{
		printf("��ѡ�������\n");
		printf("(1)���ܣ�\n");
		printf("(2)���ܣ�\n");
		printf("(3)�˳���\n");
		scanf("%d",&key);
		switch(key)
		{
		case 1:lock_file(lock);system("cls");break;
		case 2:lock_file(unlock);system("cls");break;
		case 3:flag=0;break;
		defult:printf("�������");
		}
		system("cls");  
	}
