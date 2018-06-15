#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100 

struct People //声明结构体类型struct People 
{
	int number; //员工的编号
	char name[20]; //员工的名字
	char bumen[20]; //员工所在部门
	char sex; //员工的性别
	int age; //员工的年龄
	float wages; //员工的基本工资
	char zhichen[20]; //员工的职称
	int time; //员工的工作时间
} peo[SIZE];   //定义结构体数组

int n; // 员工总数 

void Menu(); //调用菜单函数 
void Writepeople(); //读入信息
void SaveOnePeople(int i); //保存一个员工信息
void SaveAllPeople(); //保存全部员工信息
void AddPeople(); //增加员工信息
void InputOnePeople(int i); //输入一个员工信息
void DelPeople(); //删除员工信息
void ModifyPeople(); //修改员工信息
void OutputOnePeople(int i); //查询一个员工信息
void SearchMenu(); //查询员工信息操作
void SearchBumen(); //按所在部门查询员工信息
void SearchName(); //按姓名查询员工信息
void ShowOnePeople(int i); //员工信息的显示

// 主函数 
int main()
{
	printf("%d\n", n);
	
	char c; //第一次选择的变量 
	puts("*******************************************************************************");
	puts("*                                                                             *");
	puts("*                              人事管理系统                                   *");
	puts("*                                                                             *");
	puts("*******************************************************************************\n\n");
	puts("******************************●●欢迎使用●●*********************************"); //友善界面
	printf("continue or not(Y/N)?"); //判断是否进行下一步操作
	scanf("%c", &c);
	if (c == 'N' || c == 'n')
		printf("谢谢使用");
	else
	{
		printf("请继续下面操作:\n");
		Menu(); //调用菜单函数形成操作界面
		printf("请选择:");
		int c; //第二次选择的变量
		while (scanf("%d", &c) != EOF) //输入操作
		{
			while (c < 0 || c > 6)
			{
				printf("\n输入有误,请重输"); //判断选择的序号是否正确 
				scanf("%d", &c);
			}
			if (c == 0)
			{
				printf("谢谢使用!");
				return 0;
			}
			switch (c) //选择功能 
			{
			case 1:
				Writepeople();  //员工基本信息写入
				break;
			case 2:
				AddPeople();   //新员工录入
				break;
			case 3:
				DelPeople();  //员工信息的删改
				break;
			case 4:
				ModifyPeople();  //修改员工信息
				break;
			case 5:
				SearchMenu();  //查询员工信息
				break;
			case 6:
				printf("要显示谁？");
				int i; scanf("%d", &i);
				OutputOnePeople(i);  //员工信息的显示
				break;
			default:
				printf("\n出现错误!请重新选择!\n");
			}
			Menu(); // 显示主菜单 
		}
	}
}

// 菜单函数 
void Menu()
{
	printf("************请输入所需操作***********\n");//选择功能菜单
	printf("*************************************\n");
	printf("0.退出系统\n");
	printf("1.员工基本信息写入\n");
	printf("2.新员工录入\n");
	printf("3.员工信息的删改\n");
	printf("4.修改员工信息\n");
	printf("5.查询员工信息\n");
	printf("6.员工信息的显示\n");
	printf("**************************************\n");
}

// 员工基本信息写入函数
void Writepeople()
{
	int i, cnt;
	printf("当前员工人数：%d，请问要写入几人的信息？", n); 
	while (scanf("%d", &cnt) != EOF)
	{
		if (n+cnt > SIZE) printf("员工人数超出限制，请重新输入\n");
		else break;
	}
	for (i = 0; i < cnt; i++)  //用for循环输入员工信息
	{
		printf("员工编号:");
		scanf("%d", &peo[n+i].number);
		printf("员工姓名:");
		scanf("%s", peo[n+i].name);
		printf("所在部门:");
		scanf("%s", peo[n+i].bumen);
		printf("员工性别:");
		scanf(" %c", &peo[n+i].sex);
		printf("职工年龄:");
		scanf("%d", &peo[n+i].age);
		printf("工作时间:");
		scanf("%d", &peo[n+i].time);
		printf("基本工资:");
		scanf("%f", &peo[n+i].wages);
		printf("职称:");
		scanf("%s", peo[n+i].zhichen);
	}
	printf("录入完成\n");
	n += cnt; // 更新员工数量 
}

// 写入文件
void SaveAllPeople()  //定义函数save，向文件输出SIZE个员工的数据 
{
	FILE *fp;//定义一个指向文件型数据的指针变量 
	int i;
	if ((fp = fopen("people.dat", "rb+")) == NULL)//以二进制读写方式打开文件并使fp指向文件
	{
		printf("无法打开此文件\n");
		exit(1);  //用exit函数决定程序的进行，用此库函数 ,开头应包含stdlib.h头文件 
	}
	for (i = 0;i < SIZE;i++)
		if (fwrite(&peo[i], sizeof(struct People), 1, fp) != 1)
			printf("无法打开文件\n");
	fclose(fp);  //关闭文件 
	printf("\n保存成功\n");
}

// 员工信息的录入，这个函数实际上没有用到 
void SaveOnePeople(int i)
{
	FILE *fp;  //定义一个指向文件型数据的指针变量
	if ((fp = fopen("people.dat", "rb+")) == NULL)//以二进制读，写方式打开文件
	{
		printf("文件打开失败!\n");
		exit(1);
	}
	fseek(fp, sizeof(struct People) * i, 0);//文件指针定位到第i个员工
	fwrite(&peo[i], sizeof(struct People), 1, fp);//将第i个员工信息写入文件
	fclose(fp); //关闭文件 
}

// 增加员工信息
void AddPeople()
{
	printf("正在添加第%d位员工\n", ++n);
	InputOnePeople(n);
}

// 输入一个员工信息
void InputOnePeople(int i)
{
	printf("员工编号:");
	scanf("%d", &peo[i].number);
	printf("员工姓名:");
	scanf("%s", peo[i].name);
	printf("所在部门:");
	scanf("%s", peo[i].bumen);
	printf("员工性别:");
	scanf(" %c", &peo[i].sex);
	printf("职工年龄:");
	scanf("%d", &peo[i].age);
	printf("工作时间:");
	scanf("%d", &peo[i].time);
	printf("基本工资:");
	scanf("%f", &peo[i].wages);
	printf("职称:");
	scanf("%s", peo[i].zhichen);
}

// 员工信息的删除
void DelPeople()
{
	int i, x, k = -1; char c;
	printf("请输入要删除的员工的编号:");
	scanf("%d", &x);
	for (i = 0;i < n;i++)
		if (x == peo[i].number)
		{
			k = i; //找到要删除的员工编号，并用k记下其下标
			break;
		}
	if (k < 0) //k<0表示在数组中没有找到输入编号对应的员工
		printf("输入有误，请重新输入");
	else
	{
		printf("该员工信息如下:\n");
		OutputOnePeople(k);
		printf("确定删除?\n");
		printf("确定进行删除请按y；不进行删除请按n\n");
		scanf(" %c", &c);
		if (c == 'y') //c为y,表示确定进行删除操作
		{
			for (i = k;i < n;i++)
				peo[i] = peo[i + 1]; //删除第k个员工信息
			n--; //员工人数减1
			printf("删除成功\n");
		}
		else
			printf("取消删除!\n");
	}
	SaveAllPeople();
}

// 修改员工信息
void ModifyPeople()
{
	int k, x, i;
	printf("请输入要修改的员工的编号:");
	scanf("%d", &x);
	for (i = 0;i < n;i++)
		if (x == peo[i].number)
		{
			k = i; //找到要修改的员工，并用k记下其下标
			printf("请输入要修改员工修改后的的信息\n");
			InputOnePeople(k);
			printf("修改成功!\n");
			break;
		}
	SaveAllPeople(); //保存修改后的员工信息
}

// 查询一个员工信息
void OutputOnePeople(int i)
{
	printf("员工编号: %d\n", peo[i].number);
	printf("员工姓名: %s\n", peo[i].name);
	printf("所在部门: %s\n", peo[i].bumen);
	printf("员工性别: %c\n", peo[i].sex);
	printf("职工年龄: %d\n", peo[i].age);
	printf("工作时间: %d\n", peo[i].time);
	printf("基本工资: %f\n", peo[i].wages);
	printf("职称: %s\n", peo[i].zhichen);
}

// 查询员工信息操作
void SearchMenu()
{
	int s;
	while (1)
	{
		printf("**********************************************************\n");
		printf("******************** 欢迎进入查询系统  *******************\n");
		printf("**********************************************************\n");
		printf("\n");
		printf("*********************  请输入所需操作  *******************\n"); //选择功能菜单
		printf("**********************************************************\n");
		printf("0.返回主菜单\n");
		printf("1.按姓名查询\n");
		printf("2.按所在部门查询\n");
		printf("**********************************************************\n");
		printf("请输入操作选项:");
		scanf("%d", &s);
		getchar();
		switch (s)
		{
		case 1:
			SearchName();
			break;
		case 2:
			SearchBumen();
			break;
		case 0:
			return;
		default:
			printf("输入错误!请重新输入!\n");
		}
	}
}

// 按姓名查询员工信息
void SearchName()
{
	int i, j, k;
	char yname[20];
	printf("请输入员工姓名:");
	gets(yname);
	for (i = 0, j = 1;i < SIZE;i++)
		if (strcmp(peo[i].name, yname) == 0)
		{
			k = i; //找到要查询的员工姓名,并用k记下其下标
			printf("员工%d的信息:\n", j++);
			OutputOnePeople(k);  //调用函数显示信息
			return;
		}
	printf("抱歉!没有该员工信息!\n");
}

// 按所在部门查询员工信息
void SearchBumen()
{
	int i, j, k;
	char ybumen[20];
	printf("请输入员工所在部门:");
	gets(ybumen);
	for (i = 0, j = 1;i<SIZE;i++)
		if (strcmp(peo[i].bumen, ybumen) == 0)
		{
			k = i; //找到要查询的员工所在部门,并用k记下其下标
			printf("员工%d的信息:\n", j++);
			OutputOnePeople(k);
			printf("按任意键继续!\n");
			return;
		}
	printf("抱歉!没有该员工信息!\n");
}
