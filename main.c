#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
struct bus
{
	char name[10];		//公交车名称
	int begin_time;		//首班时间
	int end_time;		//末班时间
	int price;			//票价
	int journey;		//全程公里数
	int sum;			//总数量
	char level[10];		//搭乘难易程度
	struct bus *next;
	struct bus *last;
};//公交信息链表

struct journey
{
	char now[20];
	struct journey *next;
	struct journey *last;
};//公交线路链表


int Show_LogIn();	//显示登陆界面
int Show_Menu();	//显示主界面
int LogIn();		//登陆
int user_ordinary();//普通用户登录
int uesr_repaint(char *str, int n);	//重绘普通用户登陆界面
int root_repaint(char *str, int n);	//重绘管理员登陆界面
int uesr_register();//普通用户注册
int user_root();	//管理员用户登录
int Std_Error();	//显示主界面函数
int Std_Space();	//标准对齐空格
int encrypt(char *str);	//加密
int decrypt(char *str);	//解密
struct bus* BusNode();	//创建公交车节点
struct bus* CreatBusLink();	//创建公交车信息节点链表
int freeBusLink(struct bus *head);//释放链表  
int print_bus(struct bus *phead);//打印公交车信息
int show_head(char *str);	//显示头部					
struct bus *del_bus(struct bus *phead);//删除公交车信息	很混乱，需要修改
struct bus * read_file();//从文件中读取公交车信息
int save(struct bus *phead); //保存信息
struct bus* bus_append(struct bus *phead);//增加公交信息
struct journey *station_node();	//创建线路节点
struct journey *CreatJourneyLink();//创建线路链表					   
int print_station();//显示公交线路信息
int read_me();

int main()
{
	int con;
	system("color 3B");
	con=LogIn();
	if (con == 0)	exit(0);
	else
	{
		con=menu(con);
	}
}


//显示登陆界面函数
int Show_LogIn()
{
	char ch,str1[3]="\0";
	int i;
	ch = 001;
	show_head(str1);
	Std_Space();
	printf("1:普通用户登陆");
	printf("\n\n");
	Std_Space();
	printf("2:管理员登陆");
	printf("\n\n");
	Std_Space();
	printf("3:普通用户注册");
	printf("\n\n");
	Std_Space();
	printf("4:使用帮助手册");
	printf("\n\n");
	Std_Space();
	printf("0:退出");
	printf("\n\n\n");
	for (i = 0; i < 5; i++)
		printf(" ");
	printf("请输入所选服务的序号：");
}
//登陆模块
int LogIn()									//登陆模块
{
	char ch[10];
	int con=0;
	while (1)
	{
		Show_LogIn();
		scanf("%s",ch);
		getchar();
		switch (ch[0])
		{
		case '1':con=user_ordinary(); break;
		case '2':con=user_root(); break;
		case '3':uesr_register(); break;
		case '4':read_me(); break;
		case '0':printf("\n"); Std_Space(); printf("按任意键退出！"); exit(0); break;
		default:Std_Error(); break;
		}
		system("cls");
		if (con != 0)
		{
			return con;
		}
	}
	return 0;
}
//普通用户登录
int user_ordinary()
{
	char ch;
	char name[18];
	char pw[18];
	int i;
	char file_name[18];
	char file_pw[18];
	FILE *fp;
	ch = 001;
	system("cls");
	printf("\n\n");
	Std_Space();
	printf("欢迎使用公交管理系统\n");
	printf("\n");
	printf("\t普通用户登录\n");
	for (i = 0; i < 80; i++)
	{
		printf("%c", ch);
	}
	Std_Space();
	printf("用户名:");
	scanf("%s", name);
	Std_Space();
	getchar();
	printf("密码:");
	i = 0;
	while (pw[i] = getch() )
	{
		if (pw[i] == 13)	break;
		else if ((int)pw[i] == 8)
		{
			if (i != 0)
			{
				pw[i] = '\0';
				i--;
				pw[i] = '\0';
			}
			else
			{
				pw[i] = '\0';
			}
			uesr_repaint(name, i);
		}
		else
		{
			printf("*");
			i++;
		}
	}
	pw[i] = '\0';
	if ((fp = fopen("zoo", "r")) == NULL)
	{
		printf("\n");
		Std_Space();
		printf("该用户名和密码不存在！\n");
		Std_Space();
		printf("按任意键继续!\n");
		getch();
		return 0;
	}

	while (fscanf(fp, "%s %s", file_name, file_pw) != EOF)
	{
		decrypt(file_pw);
		if (!strcmp(file_name, name) && !strcmp(file_pw, pw))
		{
			fclose(fp);
			return 1;
		}
	}
	printf("\n");
	Std_Space();
	printf("该用户名和密码不存在！\n");
	Std_Space();
	printf("按任意键返回主菜单!\n");
	getch();
	fclose(fp);
	return 0;

}
//普通用户注册
int uesr_register()
{
	int i;
	char name[18],pw[18],ch;
	FILE *fp;
	ch = 001;
	system("cls");
	printf("\n\n");
	Std_Space();
	printf("欢迎使用公交管理系统\n");
	printf("\n");
	printf("\t普通用户注册\n");
	for (i = 0; i < 80; i++)
	{
		printf("%c", ch);
	}
	Std_Space();
	printf("用户名为：");
	scanf("%s",name);
	Std_Space();
	printf("密码为：");
	scanf("%s",pw);
	encrypt(pw);
	fp = fopen("zoo", "a+");
	fprintf(fp,"%s %s",name,pw);
	fputc('\n',fp);
	Std_Space();
	printf("创建完成~~lol\n");
	Std_Space();
	printf("按任意键退出！\n");
	getch();
	fclose(fp);
	return 1;
}
//管理员登陆 
int user_root()
{
	FILE *fp;
	char ch,name[18],pw[18];
	int i;
	char root_name[18] = "root";
	char root_pw[18] = "toor";
	ch = 001;
	system("cls");
	printf("\n\n");
	Std_Space();
	printf("欢迎使用公交管理系统\n");
	printf("\n");
	printf("\t管理员登陆\n");
	for (i = 0; i < 80; i++)
	{
		printf("%c", ch);
	}
	Std_Space();
	printf("管理员名:");
	scanf("%s",name);
	Std_Space();
	printf("密码:");
	//绘制*
	i = 0;
	while (pw[i] = getch())
	{
		if (pw[i] == 13)	break;
		else if ((int)pw[i] == 8)
		{
			if (i != 0)
			{
				pw[i] = '\0';
				i--;
				pw[i] = '\0';
			}
			else
			{
				pw[i] = '\0';
			}
			root_repaint(name, i);
		}
		else
		{
			printf("*");
			i++;
		}
	}
	pw[i] = '\0';
	//密码比较
	if (!strcmp(root_name, name) && !strcmp(root_pw, pw))
	{
		return 2;
	}
	Std_Space();
	printf("该用户名和密码不存在！\n");
	Std_Space();
	printf("按任意键返回主菜单!\n");
	getch();
	return 0;
}
//管理员密码重绘
int root_repaint(char *str,int n)
{
	int i;
	char ch;
	system("cls");
	ch = 001;
	printf("\n\n");
	Std_Space();
	printf("欢迎使用公交管理系统\n");
	printf("\n");
	printf("\t管理员登陆\n");
	for (i = 0; i < 80; i++)
	{
		printf("%c", ch);
	}
	Std_Space();
	printf("管理员名:%s\n",str);
	Std_Space();
	printf("密码:");
	for (i = 0; i < n; i++)
	{
		printf("*");
	}
	return 0;
}
//用户密码重绘
int uesr_repaint(char *str, int n)
{
	int i;
	char ch;
	ch = 001;
	system("cls");
	printf("\n\n");
	Std_Space();
	printf("欢迎使用公交管理系统\n");
	printf("\n");
	printf("\t普通用户登录\n");
	for (i = 0; i < 80; i++)
	{
		printf("%c", ch);
	}
	Std_Space();
	printf("用户名:");
	printf("%s\n",str);
	Std_Space();
	printf("密码:");
	for (i = 0; i < n; i++)
	{
		printf("*");
	}
	return 0;
}

//标准对齐空格
int Std_Space()	
{
	int i;
	for (i = 0; i < 30; i++)
		printf(" ");
	return 0;
}
//输入错误
int Std_Error()
{
	int i;
	for (i = 0; i < 5; i++)
		printf(" ");
	printf("输入错误，请重新输入T_T\n");
	printf("按任意键继续！");
	getchar();
	return 0;
}



//显示主界面函数
int Show_Menu()
{
	int i;
	char ch;
	ch = 001;	
	printf("\n\n");
	Std_Space();
	printf("欢迎使用公交管理系统\n");
	printf("\n\n");	
	for (i = 0; i < 80; i++)
	{
		printf("%c", ch);
	}
	Std_Space();
	printf("1:查看公交信息\n\n");
	Std_Space();
	printf("2:增加公交信息\n\n");	//添加公交车,添加公交线路
	Std_Space();
	printf("3:修改公交信息\n\n");	
	Std_Space();
	printf("4:删除公交信息\n\n");
	Std_Space();
	printf("5:站点查询\n\n");
	Std_Space();
	printf("0.退出\n\n");
	Std_Space();	
}
//主界面模块
int menu(int level)
{
	int choice, icount = 0, append_choice = 0;

	struct bus *phead, *temp, *pw,*nhead,*ntemp;
	FILE *fp;
	phead = read_file();
	while (1)
	{
		system("cls");
		Show_Menu();
		printf("请输入您所选服务的序号:");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1://查看公交信息
		{
			while (1)
			{
				show_head("查看公交信息");
				Std_Space();
				printf("1:查看公交车信息\n");
				Std_Space();
				printf("2:查看公交车线路信息\n");
				Std_Space();
				printf("0:返回上一级\n");
				Std_Space();
				printf("请输入你的选择:");
				choice = getchar();
				switch (choice)
				{
				case '1':
				{
					if (phead == NULL)
					{
						printf("\n");
						Std_Space();
						printf("暂无任何公交信息！\n");
						printf("\n");
						Std_Space();
						printf("按任意键返回！\n");
						getch();
						break;
					}
					else
					{
						print_bus(phead);
						getch();
						break;
					}; break;
				}
				case '2':
				{
					show_head("查看公交线路信息");
					Std_Space();
					print_station();
				}break;
				case '0':break;
				default:break;
				}
				if (choice == '0')	break;
			}
		}break;
		case 2://增加公交信息
		{
			while (1)
			{
				show_head("增加公交信息\n");
				Std_Space();
				printf("1:增加公交车信息\n");
				Std_Space();
				printf("2:增加公交车线路\n");
				Std_Space();
				printf("0:返回上一级\n");
				Std_Space();
				printf("请输入你的选择:");
				choice = getchar();
				switch (choice)
				{
				case '1':phead = bus_append(phead); break;
				case '2':station_append(); break;
				case '0':break;
				}
				if (choice == '0')	break;
			}
		}; break;
		case 3:break;//修改公交信息
		case 4:phead=del_bus(phead); break;//删除公交信息
		case 5:break;//站点查询
		case 0://存储信息并退出
		{
			save(phead);
		}
		default:break;
		}
	}
}


//加密
int encrypt(char *str)
{
	int i = 0;
	int temp; 
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			temp = str[i] - 48;
			str[i] = 57 - temp;
		}
		else if (str[i] >= 65 && str[i] <= 90)
		{
			temp = str[i] - 65;
			str[i] = 90 - temp;
		}
		else if (str[i] >= 97 && str[i] <= 122)
		{
			temp = str[i] - 97;
			str[i] = 122 - temp;
		}
		i++;
	}
	return 0;
}
//解密
int decrypt(char *str)
{
	int i = 0;
	int temp;
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			temp = 57-str[i];
			str[i] = 48+ temp;
		}
		else if (str[i] >= 65 && str[i] <= 90)
		{
			temp = 90-str[i];
			str[i] = 65 + temp;
		}
		else if (str[i] >= 97 && str[i] <= 122)
		{
			temp = 122 - str[i];
			str[i] = temp+97;
		}
		i++;
	}
	return 0;
}


//创建公交车信息节点	无需改动
struct bus* BusNode()
{
	struct bus *phead;
	phead = (struct bus *)malloc(sizeof(struct bus));
	phead->last = NULL;
	phead->next = NULL;
	return phead;
}
//创建公交车信息节点链表	无需改动
struct bus* CreatBusLink()
{
	struct bus *phead, *temp,*pw;
	int i,icount;
	char ch,choice,ch1[]="增加公交线路";
	show_head(ch1);
	Std_Space();
	phead = BusNode();
	printf("请输入公交车名称:");
	scanf("%s",phead->name);
	Std_Space();
	printf("请输入公交首班时间:");
	scanf("%d",&phead->begin_time);
	Std_Space();
	printf("请输入公交末班时间:");
	scanf("%d", &phead->end_time);
	Std_Space();
	printf("请输入公交票价:");
	scanf("%d",&phead->price);
	Std_Space();
	printf("请输入全程长度:");
	scanf("%d",&phead->journey);
	Std_Space();
	printf("请输入该公交车总配车数:");
	scanf("%d",&phead->sum);
	Std_Space();
	printf("请输入等车难易度(简单，一般，较难):");
	scanf("%s",phead->level);
	Std_Space();
	getchar();
	temp = phead;
	pw = phead;
	printf("\n");
	Std_Space();
	printf("请问是否要继续输入(Y/y):");
	choice = getchar();
	while (1)
	{
		if (choice != 'Y'&&choice != 'y')
		{
			printf("\n");
			Std_Space();
			printf("录入完毕 ^_^ \n");
			Std_Space();
			printf("按任意键退出");
			return phead;
		}
		else
		{
			show_head(ch1);
			Std_Space();
			temp = BusNode();	//由temp指向新申请的空间
			printf("请输入公交车名称:");
			scanf("%s", temp->name);
			Std_Space();
			printf("请输入公交首班时间:");
			scanf("%d", &temp->begin_time);
			Std_Space();
			printf("请输入公交末班时间:");
			scanf("%d", &temp->end_time);
			Std_Space();
			printf("请输入公交票价:");
			scanf("%d", &temp->price);
			Std_Space();
			printf("请输入全程长度:");
			scanf("%d", &temp->journey);
			Std_Space();
			printf("请输入该公交车总配车数:");
			scanf("%d", &temp->sum);
			Std_Space();
			printf("请输入等车难易度(简单，一般，较难):");
			scanf("%s", temp->level);
			Std_Space();
			pw->next = temp;
			temp->last = pw;
			pw = temp;
			printf("\n");	
			getchar();
			Std_Space();
			printf("请问是否要继续输入(Y/y):");
			choice = getchar();
		}
	}
	return phead;
}
//释放链表。		无需改动
int freeBusLink(struct bus *head)
{
	struct bus *temp;
	temp = head;
	if (head == NULL)	return 0;
	while (head->next != NULL)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
	free(head);
	return 0;
}
//打印公交车信息(需对界面进行修改，并且整合打印路线。)
int print_bus(struct bus *phead)
{
	int i;
	char ch,str1[]="公交信息";
	show_head(str1);
	while (phead != NULL)
	{
		printf("  __________________\t公交车%s的信息为：\t\n",phead->name);
		printf("| [_][_][_][_][_][_] |\t首班-末班时间为: %d->%d\n",phead->begin_time,phead->end_time);
		printf("| o _         _  _ |\t票价为:%d元\t路程为:%d公里\n",phead->price,phead->journey);
		printf("`(_)------ - (_)(_)-\"\t总配车:%d 乘车难易程度:%s\n",phead->sum,phead->level);
		printf("  __________________\n\n");
		phead = phead->next;
	}
	return 0;
}
//删除公交车信息
struct bus *del_bus(struct bus *phead)
{
	int i,con=0,del_con=0;
	char name[20],ch;
	char str1[20] = "删除公交车";
	struct bus *temp, *pw;;
	temp = phead;	
	show_head(str1);
	printf("请输入要删除的公交车的名称:\n");
	scanf("%s", name);
	getchar();
	while (temp != NULL)
	{
		if (del_con == 1)
		{
			show_head(str1);
			printf("请输入要删除的公交车的名称:\n");
			del_con = 0;
			scanf("%s", name);
			getchar();
		}
		if (!strcmp(temp->name, name))
		{
			//如果删除的为头结点
			if (temp == phead)
			{
				if (temp->next == NULL)
				{
					phead = NULL;
					printf("\n\n删除完毕！\n\n");
					printf("请按任意键退出!\n");
					getch();
					return phead;
				}
				else
				{
					phead = phead->next;
					temp = phead;
					printf("\n\n删除完毕！\n\n");
					printf("是否继续删除？(Y/y)\n");
					ch = getchar();
					if (ch == 'Y' || ch == 'y')
					{
						del_con = 1;
						continue;
					}
					else
					{
						printf("请按任意键退出！\n");
						getch();
						return phead;
					}
				}
			}
			//如果删除的不为头结点
			else
			{
				temp->last->next = temp->next;
				printf("\n\n删除完毕！\n\n");
				printf("是否继续删除？(Y/y)\n");
				ch = getchar();
				if (ch == 'y' || ch == 'Y')
				{
					del_con = 1;
					continue;
				}
				else
				{
					printf("请按任意键退出！\n");
					getch();
					return phead;
				}
			}
		}
		temp = temp->next;
	}
	return NULL;
}
//显示头部
int show_head(char *str)
{
	int i;
	char ch;
	ch = 001;
	system("cls");
	printf("\n\n");
	Std_Space();
	printf("欢迎使用公交管理系统\n");
	printf("\n");
	printf("\t%s\n",str);
	for (i = 0; i < 80; i++)
	{
		printf("%c", ch);
	}
	return 0;
}
//从文件中读取公交车信息
struct bus * read_file()
{
	FILE *fp;
	int icount;
	struct bus *phead, *temp,*pw;
	phead = NULL;
	fp = fopen("bus.txt", "r");
	if (fp == NULL)
	{
		return phead;
	}
	else
	{
		icount = 0;
		phead = BusNode();
		temp = phead;
		pw = phead;
		while (fscanf(fp, "%s %d %d %d %d %d %s", temp->name, &temp->begin_time, &temp->end_time, &temp->price, &temp->journey, &temp->sum, temp->level) != EOF)
		{
			icount++;
			temp = BusNode();
			if (icount == 1)
			{
				phead->next = temp;
				temp->last = phead;
				pw = temp;
			}
			else
			{
				pw->next = temp;
				temp->last = pw;
				pw = temp;
			}
		}
		if (icount == 0)
		{
			return 0;
		}
		else
		{
			pw = pw->last;
			pw->next = NULL;
			fclose(fp);
			return phead;
		}
	}
}
//保存信息
int save(struct bus *phead)
{
	struct bus *temp;
	FILE *fp;
	temp = phead;
	fp = fopen("bus.txt", "w+");
	if (phead == NULL)
	{
		fclose(fp);
		exit(0);
	}
	temp = phead;
	while (temp != NULL)
	{
		fprintf(fp, "%s %d %d %d %d %d %s", temp->name, temp->begin_time, temp->end_time, temp->price, temp->journey, temp->sum, temp->level);
		fputc('\n', fp);
		temp = temp->next;
	}
	fclose(fp);
	freeBusLink(phead);
	exit(0);//可以加入存储动画
}
//增加公交信息
struct bus* bus_append(struct bus *phead)
{
	struct bus *head,*temp,*pw;
	if (phead == NULL)
	{
		head = CreatBusLink();
		return head;
	}
	pw = phead;
	while (pw->next != NULL)
	{
		pw = pw->next;
	}
	head = CreatBusLink();
	pw->next = head;
	head->last = pw;
	return phead;
}
//创建线路节点
struct journey *station_node()
{
	struct journey *phead;
	phead = (struct journey *)malloc(sizeof(struct journey));
	phead->next = NULL;
	phead->last = NULL;
	return phead;
}
//创建公交线路
struct journey *CreatJourneyLink()
{
	struct journey *head, *temp, *pw;
	FILE *fp;
	int i;
	i = 0;
	head = station_node();
	printf("请输入该线路的公交车名称:");
	scanf("%s",head->now); 
	printf("输入0停止录入公交路线！\n");
	temp = head;
	pw = head;
	 while (strcmp(temp->now,"0"))
	{
		temp = station_node();
		pw->next = temp;
		temp->last = pw;
		pw = temp;
		i++;
		printf("第%d站为:",i);
		scanf("%s",temp->now);
		getchar();
	}

	//写入文件中
	fp = fopen(head->now,"w+");
	temp = head;
	while (temp->next != NULL)
	{
		fprintf(fp,"%s\n", temp->now);
		temp = temp->next;
	}
	fclose(fp);
	//写入公交线路总链表中
	fp = fopen("sum", "a+");
	fprintf(fp,"%s",head->now);
	printf("\n录入完毕！");
	return head;
}
//增加信息
int station_append()
{
	char ch, choice, ch1[] = "增加公交信息";
	while (1)
	{
		show_head(ch1);
		CreatJourneyLink();
		printf("请问是否要继续输入(Y/y):\n");
		choice = getchar();
		if (choice != 'Y'&&choice != 'y')
		{
			printf("请按任意键继续\n");
			getch();
			break;
		}
	}
	return 0;
}
//显示公交线路信息
int print_station()
{
	char station[20];
	char str[20] = "公交线路信息";
	FILE *fp;
	struct journey *phead,*temp,*pw;
	phead = station_node();//头结点
	temp = phead;			//头结点的下下个节点
	show_head(str);
	Std_Space();
	printf("请输入您要查询的公交车的名称:");
	scanf("%s",station);
	getchar();
	fp = fopen(station, "r");
	if (fp == NULL)
	{
		Std_Space();
		printf("暂无该公交线路的记录!\n");
		Std_Space();
		printf("按任意键返回上一级!\n");
		getch();
		return 0;
	}
	printf("\n");
	Std_Space();
	fscanf(fp,"%s",phead);			//获得当前节点，存储的为车辆信息
	printf("%s公交线路为:",phead);	

	pw = station_node();//第二个节点
	phead->next = pw;
	pw->last = phead;

	fscanf(fp, "%s", pw->now);//获取第二节点的信息，若用户正常输入，一定有
	printf("%s",pw->now);//输出第二个节点信息
	temp = station_node();
	temp->last = pw;
	pw->next = temp;
	pw = temp;
	while (fscanf(fp, "%s", temp->now)!=EOF)
	{
		printf("->%s",temp->now);
		pw = temp;
		temp = station_node();
		pw->next = temp;
		temp->last = pw;
	}
	getch();
	return 0;
}
//帮助手册
int read_me()
{
	char str2[20] = "帮助手册";

	int i,j;
	char ch = "";
	for (i = 0; i < 100; i++)
	{	
		show_head(str2);
		printf("版本号 1.0\n");
		printf("在使用中发现任何BUG都可以联系作者哦~欢迎指教\n");
		printf("作者QQ：1920395012\n");
		printf("作者e-mail:1386378163@163.com\n");
		printf("欢迎使用~\n");
		for (j = 0; j < i; j++)	printf("%c",32);
		printf(" __________________\n");
		for (j = 0; j < i; j++)	printf("%c",32);
		printf("|[_][_][_][_][_][_] |\n");
		for (j = 0; j < i; j++)	printf("%c",32);
		printf("|o _         _  _   |\n");
		for (j = 0; j < i; j++)	printf("%c",32);
		printf(" `(_)-------(_)(_)-\"\n");
		Sleep(100);
	}
	getch();
	return 0;
}

