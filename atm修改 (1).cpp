#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"time.h"
#include"cstdio"
#include"windows.h"
#include"conio.h"
#include"iostream"
#include"cstdlib"
#include"ctime"
#include"cmath"



//光标定位
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

void start();

//中文
void C_Sign_Up();                      //中文注册
void C_Sign_In();                      //中文登录 
void C_Main_Menu();                    //中文主菜单页
void C_DepositMoney();                 //中文存款业务
void C_DepositMoney1();                //中文存款失败选项
void C_DepositMoney2();                //中文存款成功选项
void C_Withdraw_Money();               //中文取款业务
void C_Withdraw_Money1();              //中文取款失败选项
void C_Withdraw_Money2();              //中文取款成功选项
void C_Transfer_Money();               //中文转账业务
void C_Transfer_Money1();              //中文转账失败选项
void C_Transfer_Money2();              //中文转账失败选项
void C_Enquiry();                      //中文查询业务
void C_Enquiry_balance();              //中文查询余豆
void C_Enquiry_Information();          //中文查询个人信息
void C_Enquiry_Record();               //中文查询流水记录
void C_Change_Information();           //中文修改信息选项页
void C_Change_User();                  //中文修改用户名称
void C_Change_AccountNum();            //中文修改账户
void C_Change_phone();                 //中文修改联系电话
void C_Change_Password();              //中文修改密码

//English
void E_Sign_Up();                      //英文注册
void E_Sign_In();                      //英文登录 
void E_Main_Menu();                    //英文菜单页
void E_DepositMoney();                 //英文存款业务
void E_Withdraw_Money();               //英文取款业务
void E_Transfer_Money();               //英文转账业务
void E_Enquiry();                      //英文查询业务
void E_Enquiry_balance();              //英文查询余豆
void E_Enquiry_Information();          //英文查询个人信息
void E_Enquiry_Record();               //英文查询流水记录
void E_Change_Information();           //英文修改信息选项页
void E_Change_User();                  //英文修改用户名称
void E_Change_AccountNum();            //英文修改账户
void E_Change_phone();                 //英文修改联系电话
void E_Change_Password();              //英文修改密码

//CE
void gotoxy();
void getPassword();
void CE_Time();                       //系统时间
void CE_Close_Account();              //注销账户选项页
void CE_Close_Account1();             //注销账户
void CE_Save_User_Data();             //保存用户数据
void CE_Save_Transaction_Data();      //保存交易数据
void CE_Initial_Password();           //初始化密码函数
void CE_Initialize_User_Data();       //初始化用户数据
void CE_Initialize_Transaction_Data();//初始化交易数据
void CE_Set_Name();                   //中英文设置姓名
void CE_Set_Password();               //中英文设置密码
void CE_Set_PhoneNumber();            //中英文设置电话号码
void CE_Add_Account_Number();         //中英文设置账户号码函数
void CE_Deposit_Transaction();        //存款交易
void CE_Withdraw_Transaction();       //取款交易
void CE_Transfer_Transaction();       //转账交易        
void hide();
void print_wall();
void print_snake();
bool is_correct();
bool print_food();
bool go_ahead();
void locate();
 

int Language, Sin, Bank;
int Random_Number;           //随机数
int ACCOUNT;                 //当前账号数值
int TACCOUNT;                //当前对方账号数值
int SXF;                     //手续费
float SXFmoey;               //手续费金额
int AccountNum1 = 1231231000;//建设银行
int TCSm, TCSn;
char str[50];
//用户信息链表
struct Account
{
	//char bank[100];//银行
	char name[100];//用户名称
	char account_number[50];//账户账号
	char phone_number[12];//电话号码
	char password[10];//密码
	float balance;//余额 

	struct Account* next;
};

//交易信息链表
struct Trade
{
	char Taccount_number[50];//账户账号
	char Time[100];//时间
	char Operation[100];//操作类型
	char TarUse[50];//目标账户账号
	float Money;//操作数量

	struct Trade* Tnext;
};

typedef struct Account Account;
typedef struct Trade Trade;

//用户信息
Account* Pset = (Account*)malloc(sizeof(Account));
Account* head = NULL;
Account* tail = NULL;
Account* curAccount;
Account* curAccountO;
Account IV;

//交易信息
Trade* Thead = NULL;
Trade* Ttail = NULL;
Trade* TcurAccount;
Trade TA;
char tmp1[100];

//选项光标
void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}
using namespace std;


//光标
void locate(int x, int y)
{
	coord.X = y;
	coord.Y = x;
	SetConsoleCursorPosition(hout, coord);
};
//隐藏光标
void hide()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cursor_info);
}
//星号密码
void getPassword(char* storePw, int maxPwLen)
{
	char c = '\0';          //存放用户键入的每个字符
	char* pc = storePw;    //为方便指向密码字符串中每个字符
	int pwlen = 0;          //当前password的长度

	while (1)
	{
		c = getch();

		//如果用户按下回车符，停止循环
		if (c == '\r')
			break;

		//将用户输入的有效字符存入密码串，不考虑空字符'\0'
		if (pwlen >= 0 && pwlen < maxPwLen - 1 && c)
		{
			*pc = c;
			pc++;
			pwlen++;
			putchar('*');
		}
	}
}

//查找当前账户
int findAccount(Account IV1)//登录时查找当前账户
{
	Account* curP = head;
	Trade* TcurP = Thead;
	while (curP != NULL)
	{
		if (strcmp(curP->account_number, IV1.account_number) == 0)
		{
			return 1;
		}
		curP = curP->next;
	}
	return 0;
}

//验证当前账户密码
int findPassword(Account IV1)//登录时查找当前账户密码
{
	Account* curP = head;
	while (curP != NULL)
	{
		if (strcmp(curP->account_number, IV1.account_number) == 0 && strcmp(curP->password, IV1.password) == 0)
		{
			curAccount = curP;
			return 1;
		}
		curP = curP->next;
	}
	return 0;
}

//查找是否被已有账户
int findAccount2(Account IV)
{
	Account* curP = head;
	while (curP != NULL)
	{
		if (strcmp(curP->account_number, IV.account_number) == 0)
		{
			return 1;
		}
		curP = curP->next;
	}
	return 0;
}

//查找转账对象
int findAccount3(Account TT)
{
	Account* curP = head;
	while (curP != NULL)
	{
		if (strcmp(curAccount->account_number, TT.account_number) == 0)
		{
			int b, k = 0;
			if (Language == 1)
				printf("\n不能给自己转账！\n");
			else
				printf("\nYou can't transfer money to yourself!\n");
			while (k < 3)
			{
				if (Language == 1)
				{
					printf("\n\n\n\t\t【1】再次输入对方账户号码");
					printf("\n\n\n\t\t【2】返回主页");
					printf("\n\n\n\t\t【0】退出系统\n\n");
				}
				else
				{
					printf("\n\n\n\t\t【1】Re-enter the account number of the other party");
					printf("\n\n\n\t\t【2】Return to the homepage");
					printf("\n\n\n\t\t【0】Exit the system\n\n");
				}
				scanf("%d", &b);
				switch (b)
				{
				case 1:
					system("cls");
					if (Language == 1)
						C_Transfer_Money();
					else
						E_Transfer_Money();
					k = 3;
					break;
				case 2:
					system("cls");
					C_Main_Menu();
					k = 3;
					break;
				case 0:
					k = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k++;
					break;
				}
			}
		}
		else if (strcmp(curP->account_number, TT.account_number) == 0)
		{
			curAccountO = curP;//当前转账对象账户
			return 1;
		}
		curP = curP->next;
	}
	return 0;
}

//时间
void CE_Time()
{
	time_t t = time(0);
	Random_Number = time(0) % 4 + 1;
	char tmp[20];
	strftime(tmp, sizeof(tmp), "%Y/%m/%d/%X", localtime(&t));
	strftime(tmp1, sizeof(tmp), "%Y-%m-%d", localtime(&t));
	strcpy(TA.Time, tmp);
}

//注销
void CE_Close_Account()
{
	printf("\n\n\t是否注销该账户？\n\n\t");
	int aaa, k1 = 1;
	while (k1)
	{
		k1 = 0;
		printf("\n\n\t\t【1】注销\n");
		printf("\n\n\t\t【2】返回主页\n");
		printf("\n\n\t\t【0】退出系统\n");
		scanf("%d", &aaa);
		switch (aaa)
		{
		case 1:
			system("cls");
			CE_Close_Account1();
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			break;
		case 0:
			system("cls");
			CE_Save_User_Data();
			exit(0);
			break;
		default:
			system("cls");
			printf("\n\n\t\t输入错误！\n");
			k1 = 1;
			break;
		}
	}
}

//注销
void CE_Close_Account1()
{
	printf("\n\n\t\t注销成功，欢迎您下次光临。\n");
	strcpy(curAccount->name, "XXXX");
	strcpy(curAccount->account_number, "XXXX");
	strcpy(curAccount->phone_number, "XXXX");
	strcpy(curAccount->password, "XXXX");
	CE_Save_User_Data();
	exit(0);

}

//保存用户数据
void CE_Save_User_Data()
{
	FILE* fp = fopen("D:/atm.txt", "w");//保存用户数据
	if (fp != NULL)
	{
		Account* curP = head;
		while (curP != NULL)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%f\n", curP->account_number, curP->name, curP->phone_number, curP->password, curP->balance);
			curP = curP->next;
		}
		fclose(fp);
	}
}

//保存交易数据
void CE_Save_Transaction_Data()
{
	FILE* Tfp = fopen("D:/atmtrade.txt", "at+");//保存交易数据
	if (Tfp != NULL)
	{
		Trade* TcurP = Thead;
		while (TcurP != NULL)
		{
			if (TcurP->Tnext == NULL)
			{
				fprintf(Tfp, "%s\t%s\t%s\t%s\t%f\n", TcurP->Taccount_number, TcurP->Time, TcurP->Operation, TcurP->TarUse, TcurP->Money);
			}
			TcurP = TcurP->Tnext;
		}
		fclose(Tfp);
	}
}

//初始化用户信息
void CE_Initialize_User_Data()
{
	FILE* fp = fopen("D:/atm.txt", "r");
	if (fp != NULL)
	{
		while (!feof(fp))
		{
			Account* newNodeP = (Account*)malloc(sizeof(Account));
			fscanf(fp, "%s\t%s\t%s\t%s\t%f\n", newNodeP->account_number, newNodeP->name, newNodeP->phone_number, newNodeP->password, &newNodeP->balance);
			newNodeP->next = NULL;

			if (head == NULL)
			{
				head = newNodeP;
				tail = newNodeP;
			}
			else
			{
				tail->next = newNodeP;
				tail = newNodeP;
			}
		}
		fclose(fp);
	}
}

//初始化交易信息
void CE_Initialize_Transaction_Data()
{
	FILE* Tfp = fopen("D:/atmtrade.txt", "r");
	if (Tfp != NULL)
	{
		while (!feof(Tfp))
		{
			Trade* TnewNodeP = (Trade*)malloc(sizeof(Trade));
			fscanf(Tfp, "%s\t%s\t%s\t%s\t%f\n", TnewNodeP->Taccount_number, TnewNodeP->Time, TnewNodeP->Operation, TnewNodeP->TarUse, &TnewNodeP->Money);
			TnewNodeP->Tnext = NULL;

			if (Thead == NULL)
			{
				Thead = TnewNodeP;
				Ttail = TnewNodeP;
			}
			else
			{
				Ttail->Tnext = TnewNodeP;
				Ttail = TnewNodeP;
			}
		}
		fclose(Tfp);
	}
}

//初始化密码
void CE_Initial_Password()
{
	strcpy(curAccount->password, "XXXXXX");
}

//中英文设置姓名
void CE_Set_Name()
{
	int a = 0;
	while (a < 3)
	{
		a++;
		if (Language == 1)
		{
			printf("\n\t>>请输入你的姓名：\n");
		}
		else
			printf("\n\t>>Please enter your name:\n");
		scanf("%s", IV.name);
		if (strlen(IV.name) < 100)
		{
			strcpy(Pset->name, IV.name);
			break;
		}
		else
		{
			if (Language == 1)
			{
				system("cls");
				printf("\n\t\t你的姓名设置过长。\n\n\t请重新设置：\n");
			}
			else
				printf("\n\t\tYour name is set too long.\n\n\tPlease reset it:\n");
		}
	}
}

//中英文设置密码
void CE_Set_Password()
{
	int a = 0;
	while (a < 3)
	{
		a++;
		if (Language == 1)
		{
			printf("\n\t>>请设置你的账户密码【6位】：\n");
		}
		else
			printf("\n\t>>Please set your account password [6 digits]：\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(IV.password, storePassword);
		if (strlen(IV.password) == 6)
		{
			strcpy(Pset->password, IV.password);
			break;
		}
		else
		{
			if (Language == 1)
			{
				system("cls");
				printf("\n\t\t密码为六位，你的密码设置有误！\n\n\t请重新设置：\n");
			}
			else
				printf("\n\t\tThe password is six digits, your password is set incorrectly！\n\n\tPlease reset it:\n");

		}
	}
}

//中英文设置电话号
void CE_Set_PhoneNumber()
{
	int a = 0;
	while (a < 3)
	{
		a++;
		if (Language == 1)
		{
			printf("\n\t>>请输入你的电话号码【11位】：\n");
		}
		else
			printf("\n\t>>Please enter your phone number [11 digits]:\n");
		scanf("%s", IV.phone_number);
		if (strlen(IV.phone_number) == 11)
		{
			strcpy(Pset->phone_number, IV.phone_number);
			break;
		}
		else
		{
			if (Language == 1)
			{
				system("cls");
				printf("\n\t\t预留号码应为十一位数，你的预留号码设置有误！\n\n\t请重新输入：\n");
			}
			else
				printf("\n\t\tThe reserved number should be eleven digits, your reserved number is set incorrectly!\n\n\tPlease reset it:\n");
		}
	}
}

//中英文增加账户账号
void CE_Add_Account_Number()
{
	switch (Bank)
	{
	case 1:
		AccountNum1++;
		itoa(AccountNum1, IV.account_number, 10);
		break;
	}
}

//中英文存款流水记录
void CE_Deposit_Transaction()
{
	Trade* TP = (Trade*)malloc(sizeof(Trade));
	TP->Tnext = NULL;
	if (Thead == NULL)
	{
		Thead = TP;
		Ttail = TP;
	}
	else
	{
		Ttail->Tnext = TP;
		Ttail = TP;
		strcpy(TP->Taccount_number, curAccount->account_number);
		strcpy(TP->Time, TA.Time);
		strcpy(TP->Operation, "AA");
		TP->Money = TA.Money;
		strcpy(TP->TarUse, "由本账户存款");
		CE_Save_Transaction_Data();
	}
}

//中英文取款流水记录
void  CE_Withdraw_Transaction()
{
	Trade* TP = (Trade*)malloc(sizeof(Trade));
	TP->Tnext = NULL;
	if (Thead == NULL)
	{
		Thead = TP;
		Ttail = TP;
	}
	else
	{
		Ttail->Tnext = TP;
		Ttail = TP;
		strcpy(TP->Taccount_number, curAccount->account_number);
		strcpy(TP->Time, TA.Time);
		strcpy(TP->Operation, "BB");
		TP->Money = TA.Money;
		strcpy(TP->TarUse, "由本账户取款");
		CE_Save_Transaction_Data();
	}
}

//中英文转账转出流水记录
void  CE_Transfer_Transaction()
{
	Trade* TP = (Trade*)malloc(sizeof(Trade));
	TP->Tnext = NULL;
	if (Thead == NULL)
	{
		Thead = TP;
		Ttail = TP;
	}
	else
	{
		Ttail->Tnext = TP;
		Ttail = TP;
		strcpy(TP->Taccount_number, curAccount->account_number);
		strcpy(TP->Time, TA.Time);
		strcpy(TP->Operation, "BA");
		strcpy(TP->TarUse, curAccountO->account_number);
		TP->Money = TA.Money;
		CE_Save_Transaction_Data();
	}


	//转账转入流水记录

	Trade* TPi = (Trade*)malloc(sizeof(Trade));//定义交易结构体 变量 转入TPi
	TPi->Tnext = NULL;
	if (Thead == NULL)
	{
		Thead = TPi;
		Ttail = TPi;
	}
	else
	{
		Ttail->Tnext = TPi;
		Ttail = TPi;
		strcpy(TPi->Taccount_number, curAccountO->account_number);//当前转入账号赋值给TPi
		strcpy(TPi->Time, TA.Time);//当前时间赋值给TPi
		strcpy(TPi->Operation, "AB");//当前操作类型赋值给TPi
		strcpy(TPi->TarUse, curAccount->account_number);
		TPi->Money = -TA.Money;//当前交易金额赋值给TPi
		CE_Save_Transaction_Data();
	}
}



//中英文手续费流水记录
void CE_SXF_Transaction()
{
	Trade* TP = (Trade*)malloc(sizeof(Trade));
	TP->Tnext = NULL;
	if (Thead == NULL)
	{
		Thead = TP;
		Ttail = TP;
	}
	else
	{
		Ttail->Tnext = TP;
		Ttail = TP; 
		strcpy(TP->Taccount_number, curAccount->account_number);
		strcpy(TP->Time, TA.Time);
		strcpy(TP->Operation, "CC");
		strcpy(TP->TarUse, "本账户转账");
		TP->Money = -SXFmoey;
		CE_Save_Transaction_Data();
	}
}
//中英文打印流水
void CE_Print_Transaction()
{
	int k = 0, w = 0;
	Trade* TcurP = Thead;
	if (Language == 1)
		printf("\n序号\t时间：\t\t\t\t交易类型：\t\t交易数量：\t交易备注：\n\n");
	else
		printf("\nNum:\tTime:\t\t\t\tTrading Type:\t\tTrading money quantity:\tRemark:\n\n");
	while (TcurP != NULL)//交易记录
	{
		if (strcmp(curAccount->account_number, TcurP->Taccount_number) == 0)
		{
			w++;
			TcurAccount = TcurP;
			if (Language == 1)
			{
				if (strcmp(TcurAccount->Operation, "AA") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\t收入\t\t%8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\t收入\t\t+%-8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
				else if (strcmp(TcurAccount->Operation, "BB") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\t支出\t\t%8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\t支出\t\t+%-8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
				else if (strcmp(TcurAccount->Operation, "BA") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\t支出\t\t%8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\t支出\t\t+%-8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
				else if (strcmp(TcurAccount->Operation, "AB") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\t收入\t\t%8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\t收入\t\t+%-8.2f\t\t%s\t\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
			}
			else
			{
				if (strcmp(TcurAccount->Operation, "AA") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\tSave\t\t%8.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\tSave\t\t+%08.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
				else if (strcmp(TcurAccount->Operation, "BB") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\tTake\t\t%8.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\tTake\t\t+%08.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
				else if (strcmp(TcurAccount->Operation, "AB") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\tSend\t\t%8.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\tSend\t\t+%08.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
				else if (strcmp(TcurAccount->Operation, "BA") == 0)
				{
					if (TcurAccount->Money < 0)
						printf("\n<%d>\t%s\t\tSend\t\t%8.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
					else
						printf("\n<%d>\t%s\t\tSend\t\t+%08.2f\t\t%s\t||\n", w, TcurAccount->Time, TcurAccount->Money, TcurAccount->TarUse);
				}
			}

			k++;
		}
		TcurP = TcurP->Tnext;
	}
	if (k == 0)
	{
		if (Language == 1)
			printf("\n\t暂无交易记录\n\t\t\n\n");
		else
			printf("\n\tNo transaction record now.\n\t\t\n\n");
	}
}

//选择银行
void CE_ChooseBank()
{
	int a, k = 1;
	while (k)
	{
		k = 0;
		if (Language == 1)
		{
			printf("\n请选择你要注册账号的所属银行：\n\n");
			printf("\n\n\t\t【1】建设银行\n");
			printf("\n\n\t\t【0】退出系统\n");
			printf("\n\n\t\t\t你的选择：___\b\b\b");
		}
		else
		{
			printf("\nPlease 选择你要注册账号的所属银行：\n\n");
			printf("\n\n\t\t【1】China Construction Bank\n");
			printf("\n\n\t\t【0】Exit the system\n");
			printf("\n\n\t\t\tYour choice：___\b\b\b");
		}
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			Bank = 1;
			break;
		case 2:
			Bank = 2;
			break;
		case 3:
			Bank = 3;
			break;
		case 0:
			system("cls");
			CE_Save_User_Data();
			exit(0);
			break;
		default:
			system("cls");
			printf("\n\n\t\tEnter eroor！\n");
			k = 1;
			break;
		}
	}
}

//中文注册
void C_Sign_Up()//中文注册函数
{
	int a, k = 0;
	system("cls");
	printf("\n【注册】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	CE_ChooseBank();
	Pset->next = NULL;//Account* Pset = (Account*)malloc(sizeof(Account));//已定义
	if (head == NULL)
	{
		head = Pset;
		tail = Pset;//如果这是第一个创建的结点，则将头 尾指针指向这个结点
	}
	else
		tail->next = Pset; //如果不是第一个创建的结点，则将上一个结点的后继指针指向当前结点
	CE_Set_Name();//跳转中文设置姓名函数
	CE_Add_Account_Number();//跳转到中文设置账户号码函数
	strcpy(Pset->account_number, IV.account_number);
	CE_Set_PhoneNumber();//跳转到中文设置预留电话函数
	CE_Set_Password();//跳转到中文设置密码函数
	Pset->balance = 0;
	CE_Save_User_Data();
	while (k < 3)
	{
		system("cls");
		printf("\n\t\t注册成功\n");
		printf("\n\t>>你的账户号码为 %s\n", Pset->account_number);
		printf("\n\n\t\t【1】返回登录\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &a);
		if (a == 1)
		{
			system("cls");
			C_Sign_In();
			break;
		}
		else if (a == 0)
		{
			exit(0);
		}
		else
		{
			k++;
			printf("\n密码输入错误! \t%d\t请按照提示重新输入：\n", 3 - k);
		}
	}
}

//英语注册
void E_Sign_Up()//英语注册函数
{
	int a, k = 0;
	printf("\nWelcome to register\n\n");

	CE_ChooseBank();
	Pset->next = NULL;
	if (head == NULL)
	{
		head = Pset;
		tail = Pset;
	}
	else
	{
		tail->next = Pset;
		CE_Set_Name();
		CE_Add_Account_Number();
		strcpy(Pset->account_number, IV.account_number);
		CE_Set_PhoneNumber();
		CE_Set_Password();
		Pset->balance = 0;
		CE_Save_User_Data();
		while (k < 3)
		{
			system("cls");
			printf("\n\t\tRegistration Success!\n");
			printf("\n\t>>Your account number is  %s\n", Pset->account_number);
			printf("\n\n\t\t【1】 Return to login\n");
			printf("\n\n\t\t【0】 Exit the system\n");
			printf("\n\n\t\t\tYour chioce：___\b\b\b");
			scanf("%d", &a);
			if (a == 1)
			{
				system("cls");
				E_Sign_In();
				break;
			}
			else if (a == 0)
			{
				exit(0);
			}
			else
			{
				k++;
				printf("\nPassword entered incorrectly! \t%d\tPlease re-enter as prompted:\n", 3 - k);
			}
		}
	}
}

//中文登录
void C_Sign_In()
{
	system("cls");
	int m = 0, n = 0;
	while (m < 3)//3次输入错账号将退出系统
	{
		Account IV1;//账户中间变量1
		printf("\n【登录】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\n\t>>请输入账号：\n");
		printf("\n\n\t\t\t__________\b\b\b\b\b\b\b\b\b\b");
		scanf("%s", IV1.account_number);
		system("cls");
		if (findAccount(IV1))
		{
			while (n < 3)//3次输入错密码将退出系统
			{
				printf("\n【登录】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
			 
				printf("\n\n\n\t>>请输入密码：\n");
				char storePassword[10] = { '\0' };    //存储用户输入的密码
				printf("\n\n\t\t\t______\b\b\b\b\b\b");
				getPassword(storePassword, 10);
				strcpy(IV1.password, storePassword);
				system("cls");
				if (findPassword(IV1))
				{
					m = 3;
					n = 3;
					if (Sin == 1)
						C_Main_Menu();
					
					else
						C_Main_Menu();
					break;
				}
				else
				{
					m++;
					n++;
					if (n == 3)
					{
						printf("\n\n\t该账号已经被冻结，请联系后台找回。\n");
						CE_Initial_Password();
						break;
					}
					else
					{
						printf("\n\n\t密码错误  %d次机会后账号将会被冻结\n", 3 - n);
					}
				}
			}
		}
		else
		{
			m++;
			printf("\n\n\t没有查找到该用户!  %d  请重新输入：\n", 3 - m);
			if (m == 3)
			{
				printf("\n\n\t错误，已退出系统\n");
				CE_Save_User_Data();
				exit(0);
			}
		}
	}
}

//英语登录
void E_Sign_In()
{
	system("cls");
	int m = 0, n = 0;
	while (m < 3)//3次输入错账号将退出系统
	{
		Account IV1;//账户中间变量1
		printf("\nSign in\n==========================================\n");
		printf("\n\n\t>>Please enter account number:\n");
		printf("\n\n\t\t\t__________\b\b\b\b\b\b\b\b\b\b");
		scanf("%s", IV1.account_number);
		system("cls");
		if (findAccount(IV1))
		{
			while (n < 3)//3次输入错密码将退出系统
			{
				printf("\nSign in\n========================================\n\n\n\t>>>>Please enter password:\n");
				char storePassword[10] = { '\0' };    //存储用户输入的密码
				printf("\n\n\t\t\t______\b\b\b\b\b\b");
				getPassword(storePassword, 10);
				strcpy(IV1.password, storePassword);
				system("cls");

				if (findPassword(IV1))
				{
					m = 3;
					n = 3;
					printf("\nMenu\n========================================\n");
					E_Main_Menu();
					break;
				}
				else
				{
					m++;
					n++;
					if (n == 3)
					{
						printf("\n\n\tThe account has been frozen, please contact the background to retrieve it.\n");
						CE_Initial_Password();
						break;
					}
					else
					{
						printf("\n\n\tThe password is wrong, the account will be frozen after %d chance\n", 3 - n);
					}
				}
			}
		}
		else
		{
			m++;
			printf("\n\n\tThe user was not found! %d Please re-enter:\n", 3 - m);
			if (m == 3)
			{
				printf("\n\n\tError, logged out\n");
				CE_Save_User_Data();
				exit(0);
			}
		}
	}
}

//中文菜单页
void C_Main_Menu()//
{
	printf("\n【菜单】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	int a, k1 = 1;
	while (k1)
	{
		k1 = 0;
		printf("\n\n\t\t【1】存款\n");
		printf("\n\n\t\t【2】取款\n");
		printf("\n\n\t\t【3】转帐\n");
		printf("\n\n\t\t【4】查询\n");
		printf("\n\n\t\t【5】修改个人资料\n");
		printf("\n\n\t\t【6】注销账号\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			C_DepositMoney();
			break;
		case 2:
			system("cls");
			C_Withdraw_Money();
			break;
		case 3:
			system("cls");
			C_Transfer_Money();
			break;
		case 4:
			system("cls");
			C_Enquiry();
			break;
		case 5:
			system("cls");
			C_Change_Information();
			break;
		case 6:
			system("cls");
			CE_Close_Account();
			break;
		case 0:
			system("cls");
			CE_Save_User_Data();
			exit(0);
			break;
		default:
			system("cls");
			printf("\n【菜单】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\n\n\t\t输入错误！\n");
			k1 = 1;
			break;
		}
	}
}


//英语菜单页
void E_Main_Menu()//
{
	int a, k1 = 1;
	while (k1)
	{
		k1 = 0;
		printf("\n\n\t\t【1】Deposit money\n");
		printf("\n\n\t\t【2】Withdraw money\n");
		printf("\n\n\t\t【3】Transfer money\n");
		printf("\n\n\t\t【4】Inquire\n");
		printf("\n\n\t\t【5】Modify personal information\n");
		printf("\n\n\t\t【6】Logout\n");
		printf("\n\n\t\t【0】Exit system\n");
		printf("\n\n\t\t\tYour chioce：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			E_DepositMoney();
			break;
		case 2:
			system("cls");
			E_Withdraw_Money();
			break;
		case 3:
			system("cls");
			E_Transfer_Money();
			break;
		case 4:
			system("cls");
			E_Enquiry();
			break;
		case 5:
			system("cls");
			E_Change_Information();
			break;
		case 6:
			system("cls");
			CE_Close_Account();
			break;
		case 0:
			system("cls");
			CE_Save_User_Data();
			exit(0);
			break;
		default:
			system("cls");
			printf("\n\n\t\tIncorrect input!\n");
			k1 = 1;
			break;
		}
	}
}

//中文存款业务
void C_DepositMoney()
{
	int a;
	printf("\n\t\t\t【存款】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	printf("\n\n\n\t【温馨提示】1.存款金额须为100的整数。\n\n\t\t     2.单笔金额不得超过10000。");
	printf("\n\n\n\t>>请输入你要存入的金额：\n");
	printf("\n\n\t\t\t______\b\b\b\b\b\b");
	scanf("%d", &a);
	if (a % 100 || a > 10000)
	{
		system("cls");
		printf("\n【存款】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (Sin == 1)
		{
			if (a > 10000)
			{
				printf("单笔不得超过10000。\n\n");
			}
			else
				printf("存款金额须为100的整数。\n\n");
			C_DepositMoney1();//存款失败选项
		}
		else if (Sin == 3)
		{
			if (a > 10000)
			{
				printf("\n\n\n\n\n\n\n\n\n\t单笔不得超过10000。\n\n");
			}
			else
				printf("\n\n\n\n\n\n\n\n\n\t存款金额须为100的整数。\n\n");

		}
	}
	else
	{
		CE_Time();
		TA.Money = a * 1.00;
		curAccount->balance = curAccount->balance + TA.Money;
		system("cls");
		printf("\n【存款】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		CE_Save_User_Data();
		CE_Deposit_Transaction();
		if (Sin == 1)
		{
			printf("\n\t您本次已成功存入%.2f元!\n", TA.Money);
			C_DepositMoney2();//存款成功选项
		}
		else if (Sin == 3)
		{
			printf("\n\n\n\n\n\n\n\n\n\t您本次已成功存入%.2f元!\n", TA.Money); 
		}
	}
}

//存款失败选项
void C_DepositMoney1()
{
	int k = 0, b;
	while (k < 3)
	{
		printf("\n\n\t\t【1】重新输入存款金额\n");
		printf("\n\n\t\t【2】返回主页\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &b);
		switch (b)
		{
		case 1:
			system("cls");
			C_DepositMoney();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//存款成功选项
void C_DepositMoney2()
{
	int k = 0, b;
	while (k < 3)
	{
		printf("\n\n\t\t【1】再存一笔\n");
		printf("\n\n\t\t【2】返回主页\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &b);
		switch (b)
		{
		case 1:
			system("cls");
			C_DepositMoney();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}



//英语存款业务
void E_DepositMoney()
{
	int a;
	printf("\n[Save Beans]\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	printf("\n\n\n\t[Reminder] 1. The number of money must be an integer of 100.\n\n\t\t2. A single deposit of beans cannot exceed 10,000.");
	printf("\n\n\n\t>>Please enter the money you want to deposit:\n");
	printf("\n\n\t\t\tYour chioce：___\b\b\b");
	scanf("%d", &a);
	if (a % 100 || a > 10000)
	{
		int k = 0, b;
		system("cls");
		printf("\n[Save Beans]\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (a > 10000)
		{
			printf("Single deposit must not exceed 10000.\n\n");
		}
		else
			printf("The amount of money must be an integer of 100.\n\n");
		while (k < 3)
		{
			printf("\n\n\t\t【1】Re-enter the amount of money\n");
			printf("\n\n\t\t【2】Return to homepage\n");
			printf("\n\n\t\t【0】Exit the system\n");
			printf("\n\n\t\t\tYour chioce：___\b\b\b");
			scanf("%d", &b);
			switch (b)
			{
			case 1:
				system("cls");
				E_DepositMoney();
				k = 3;
				break;
			case 2:
				system("cls");
				E_Main_Menu();
				k = 3;
				break;
			case 0:
				k = 3;
				CE_Save_User_Data();
				exit(0);
			default:
				k++;
				break;
			}
		}
	}
	else
	{
		CE_Time();
		TA.Money = a * 1.00;
		curAccount->balance = curAccount->balance + TA.Money;
		system("cls");
		printf("\n[Save Beans]\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\nYou have successfully deposited %.2f yuan!\n", TA.Money);
		CE_Save_User_Data();
		CE_Deposit_Transaction();
		int k = 0, b;
		while (k < 3)
		{
			printf("\n\n\t\t【1】Save another one\n");
			printf("\n\n\t\t【2】Return to homepage\n");
			printf("\n\n\t\t【0】Exit the system\n");
			printf("\n\n\t\t\tYour chioce：___\b\b\b");
			scanf("%d", &b);
			switch (b)
			{
			case 1:
				system("cls");
				E_DepositMoney();
				k = 3;
				break;
			case 2:
				system("cls");
				E_Main_Menu();
				k = 3;
				break;
			case 0:
				k = 3;
				CE_Save_User_Data();
				exit(0);
			default:
				k++;
				break;
			}
		}
	}
}

//中文取款业务
void C_Withdraw_Money()
{
	int a;
	printf("\n【取款】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	printf("\n\n\n\t\t【温馨提示】1.取款金额须为100的整数。");
	printf("\n\n\n\t\t\t     2.单笔不得超过10000。");
	printf("\n\n\n\t\t>>请输入你要取出的金额：______\b\b\b\b\b\b");
	scanf("%d", &a);
	if (a % 100 || a > 10000)
	{
		system("cls");
		printf("\n【取款】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (Sin == 1)
		{
			if (a > 10000)
			{
				printf("单笔不得超过10000。\n\n");
			}
			else
				printf("取款金额须为100的整数。\n\n");
			C_Withdraw_Money1();//取款失败选项
		}
		else if (Sin == 3)
		{
			if (a > 10000)
			{
				printf("\n\n\n\n\n\n\n\n\n\t单笔不得超过10000。\n\n");
			}
			else
				printf("\n\n\n\n\n\n\n\n\n\t取款金额为100的整数。\n\n");
			
		}
	}
	else
	{
		CE_Time();
		TA.Money = a * -1.00;
		if (curAccount->balance + TA.Money < 0)
		{
			system("cls");
			printf("\n【取款】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			if (Sin == 1)
			{
				printf("\n\t余额不足!\n");
				C_Withdraw_Money1();//取款失败选项
			}
			else if (Sin == 3)
			{
				printf("\n\n\n\n\n\n\n\n\n\t余额不足!\n");
			
			}
		}
		else
		{
			curAccount->balance = curAccount->balance + TA.Money;
			system("cls");
			printf("\n【取款】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			CE_Save_User_Data();
			CE_Withdraw_Transaction();
			if (Sin == 1)
			{
				printf("\n\t取款成功!\n");
				C_Withdraw_Money2();//取款成功选项
			}
			else if (Sin == 3)
			{
				printf("\n\n\n\n\n\n\n\n\n\t取款成功!\n");
			
			}
		}
	}
}

//取款失败选项
void C_Withdraw_Money1()
{
	int k = 0, b;
	while (k < 3)
	{
		printf("\n\n\n\t\t【1】重新输入取款金额");
		printf("\n\n\n\t\t【2】返回主页");
		printf("\n\n\n\t\t【0】退出系统");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &b);
		switch (b)
		{
		case 1:
			system("cls");
			C_Withdraw_Money();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//取款成功选项
void C_Withdraw_Money2()
{
	int k = 0, b;
	while (k < 3)
	{
		printf("\n\n\n\t\t【1】再次取钱");
		printf("\n\n\n\t\t【2】返回主页");
		printf("\n\n\n\t\t【0】退出系统\n\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &b);
		switch (b)
		{
		case 1:
			system("cls");
			C_Withdraw_Money();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}


//英语取款业务
void E_Withdraw_Money()
{
	int a;
	printf("\n【Take money】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	printf("\n\n\n\t\t[Reminder] 1. The number of money must be an integer of 100.");
	printf("\n\n\n\t\t\t2. A single fetch must not exceed 10000.");
	printf("\n\n\n\t\t>>Please enter the money you want to take out:\n\n");
	printf("\n\n\t\t\t______\b\b\b\b\b\b");
	scanf("%d", &a);
	if (a % 100 || a > 10000)
	{
		int k = 0, b;
		system("cls");
		printf("\n【Take money】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (a > 10000)
		{
			printf("Single deposit must not exceed 10000.\n\n");
		}
		else
			printf("The amount of money must be an integer of 100.\n\n");
		while (k < 3)
		{
			printf("\n\n\n\t\t【1】 Re-enter the amount of money");
			printf("\n\n\n\t\t【2】 Return to home page");
			printf("\n\n\n\t\t【0】 Exit the system");
			printf("\n\n\t\t\tYour chioce：___\b\b\b");
			scanf("%d", &b);
			switch (b)
			{
			case 1:
				system("cls");
				E_Withdraw_Money();
				k = 3;
				break;
			case 2:
				system("cls");
				E_Main_Menu();
				k = 3;
				break;
			case 0:
				k = 3;
				CE_Save_User_Data();
				exit(0);
			default:
				k++;
				break;
			}
		}
	}
	else
	{
		CE_Time();
		TA.Money = a * -1.00;
		if (curAccount->balance + TA.Money < 0)
		{
			int k = 0, b;
			system("cls");
			printf("\n【Take money】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\nNot enough money!\n");
			while (k < 3)
			{
				printf("\n\n\n\t\t【1】 Re-enter the amount of money");
				printf("\n\n\n\t\t【2】 Return to home page");
				printf("\n\n\n\t\t【0】 Exit the system\n");
				printf("\n\n\t\t\tYour chioce：___\b\b\b");
				scanf("%d", &b);
				switch (b)
				{
				case 1:
					system("cls");
					E_Withdraw_Money();
					k = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k = 3;
					break;
				case 0:
					k = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k++;
					break;
				}
			}
		}
		else
		{
			curAccount->balance = curAccount->balance + TA.Money;
			system("cls");
			printf("\n【Take money】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\nGet the money successfully!!!!\n");
			CE_Save_User_Data();
			CE_Withdraw_Transaction();
			int k = 0, b;
			while (k < 3)
			{
				printf("\n\n\n\t\t【1】 Take beans again");
				printf("\n\n\n\t\t【2】 Return to home page");
				printf("\n\n\n\t\t【0】 Exit the system\n\n");
				printf("\n\n\t\t\tYour chioce：___\b\b\b");
				scanf("%d", &b);
				switch (b)
				{
				case 1:
					system("cls");
					E_Withdraw_Money();
					k = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k = 3;
					break;
				case 0:
					k = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k++;
					break;
				}
			}
		}
	}
}

//转账业务
void C_Transfer_Money()
{
	int a = 100;
	printf("\n\t\t【转账】\t\t%s", tmp1);
	printf("\t1◆单笔转账不得超过10000元。\n\t\n");
	printf("\t----------------------------------------------------\n");
	printf("\n\n\n\n\t\t>>请输入你要转出到的账户：__________\b\b\b\b\b\b\b\b\b\b");
	Account TT;//目标账户
	scanf("%s", &TT.account_number);
	if (findAccount3(TT))
	{
		ACCOUNT = atoi(curAccount->account_number);//当前账户转换为数值
		TACCOUNT = atoi(TT.account_number);        //当前对方账户转换为数值
		system("cls");
		printf("\n【转账】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (Sin == 1)
		{
			printf("\t1◆单笔转账不得超过10000元。\n\t\n");
		
			printf("\t----------------------------------------------------\n");
			printf("\n\n\t\t>>请输入你要转出的金额：______\b\b\b\b\b\b");
		}
		else if (Sin == 3)
		{
			printf("\n\n\t\t>>请输入你要转出的金额：______\b\b\b\b\b\b");
		}
		scanf("%d", &a);
		if (a > 10000)
		{

			if (Sin == 1)
			{
				printf("\n\t单笔转账不得超过10000。\n\n");
				C_Transfer_Money1();//取款失败选项
			}
			else if (Sin == 3)
			{
				printf("\n\n\n\n\n\n\n\n\n\t单笔转账不得超过10000。\n\n");
				
			}
		}
		else
		{
			CE_Time();
			TA.Money = a * -1.00;
			SXFmoey = SXF * 0.01 * a;
			if (curAccount->balance + TA.Money - SXFmoey < 0)
			{
				system("cls");
				printf("\n【转账】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
			 

				if (Sin == 1)
				{
					printf("\n\t余额不足!\n");
					C_Transfer_Money1();          //转账失败选项
				}
				else if (Sin == 3)
				{
					printf("\n\n\n\n\n\n\n\n\n\t余额不足!\n");
					
				}
			}
			else
			{
				system("cls");
				printf("\n【转账】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
			 
				curAccount->balance = curAccount->balance + TA.Money - SXFmoey;//当前账户减去转账金额和手续费
				curAccountO->balance = curAccountO->balance - TA.Money;      //对方账户加上转账金额
				CE_Transfer_Transaction();
				CE_Save_User_Data();
				if (Sin == 1)
				{
					printf("\n\t转账成功!!!!\n");
					C_Transfer_Money2();           //转账成功选项
				}
				else if (Sin == 3)
				{
					printf("\n\n\n\n\n\n\n\n\n\t转账成功!!!!\n");
				
				}
			}
		}
	}
	else
	{
		system("cls");
		printf("\n【转账】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (Sin == 1)
		{
			printf("\n\t对方账户不存在！！！！");
			C_Transfer_Money1();             //取款失败选项
		}
		else if (Sin == 3)
		{
			printf("\n\n\n\n\n\n\n\n\n\t对方账户不存在！！！！");
		
		}
	}
}

//转账失败选项
void C_Transfer_Money1()
{
	int k = 0, b;
	while (k < 3)
	{
		printf("\n\n\n\t\t【1】重新转账");
		printf("\n\n\n\t\t【2】返回主页");
		printf("\n\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &b);
		switch (b)
		{
		case 1:
			system("cls");
			C_Transfer_Money();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//转账成功选项
void C_Transfer_Money2()
{
	int k2 = 0, b;
	while (k2 < 3)
	{
		printf("\n\n\n\t\t【1】再次转账");
		printf("\n\n\n\t\t【2】返回主页");
		printf("\n\n\n\t\t【0】退出系统\n\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &b);
		switch (b)
		{
		case 1:
			system("cls");
			C_Transfer_Money();
			k2 = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k2 = 3;
			break;
		case 0:
			k2 = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k2++;
			break;
		}
	}
}



//转账业务
void E_Transfer_Money()
{
	int a = 100;
	printf("\n【Send Beans】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	printf("\n\n\n\t【Reminder】1. No more than 10000 yuan can be sent at a time.\n");
	printf("\n\n\t\t2.Beware of scams.");
	printf("\n\n\t\t>>Please enter the account you want to send to:\n\n");
	printf("\n\n\t\t\t___\b\b\b");
	Account TT;
	scanf("%s", &TT.account_number);
	if (findAccount3(TT))
	{
		system("cls");
		printf("\n【Send Beans】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\n\t【Reminder】1. No more than 10000 yuan can be sent at a time.\n");
		printf("\n\n\t\t2.Beware of scams.");
		printf("\n\n\t\t>>Please enter the amount of money you want to send:\n");
		scanf("%d", &a);
		if (a > 10000)
		{
			printf("\n\tSingle delivery of beans must not exceed 10000\n\t\t\n\n");
			E_Transfer_Money();
		}
		CE_Time();
		TA.Money = a * -1.00;
		if (curAccount->balance + TA.Money < 0)
		{
			int k = 0, b;
			system("cls");
			printf("\n【Send Beans】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\nNot enough money!\n");
			while (k < 3)
			{
				printf("\n\n\n\t\t【1】 Re-enter the amount of money");
				printf("\n\n\n\t\t【2】 Return to home page");
				printf("\n\n\n\t\t【0】 Exit the system\n");
				printf("\n\n\t\t\tYour chioce：___\b\b\b");
				scanf("%d", &b);
				switch (b)
				{
				case 1:
					system("cls");
					E_Transfer_Money();
					k = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k = 3;
					break;
				case 0:
					k = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k++;
					break;
				}
			}
		}
		else
		{
			system("cls");
			printf("\n【Send money】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\nSuccessful delivery of money!\n");
			curAccount->balance = curAccount->balance + TA.Money;//当前账户减去转账金额
			curAccountO->balance = curAccountO->balance - TA.Money;//对方账户加上转账金额
			CE_Transfer_Transaction();
			CE_Save_User_Data();
			int k = 0, b;
			while (k < 3)
			{
				printf("\n\n\n\t\t[1] Transfer money again");
				printf("\n\n\n\t\t[2] Return to the home page");
				printf("\n\n\n\t\t[0] Exit the system\n");
				printf("\n\n\t\t\tYour chioce：___\b\b\b");
				scanf("%d", &b);
				switch (b)
				{
				case 1:
					system("cls");
					E_Transfer_Money();
					k = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k = 3;
					break;
				case 0:
					k = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k++;
					break;
				}
			}
		}
	}
	else
	{
		int b, k = 0;
		system("cls");
		printf("\n【Send money】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\nThe account of the other party does not exist!!!!");
		while (k < 3)
		{
			printf("\n\n\n\t\t【1】 Re-enter the other party's account number");
			printf("\n\n\n\t\t【2】 Return to home page");
			printf("\n\n\n\t\t【0】 Exit the system\n\n");
			printf("\n\n\t\t\tYour chioce：___\b\b\b");
			scanf("%d", &b);
			switch (b)
			{
			case 1:
				system("cls");
				E_Transfer_Money();
				k = 3;
				break;
			case 2:
				system("cls");
				E_Main_Menu();
				k = 3;
				break;
			case 0:
				k = 3;
				CE_Save_User_Data();
				exit(0);
			default:
				k++;
				break;
			}
		}
	}
}

//查询业务页
void C_Enquiry()
{

	int a, k = 0;
	while (k < 3)
	{
		printf("\n【查询】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\t\t【1】账户余额查询\n");
		printf("\n\n\t\t【2】个人信息查询\n");
		printf("\n\n\t\t【3】交易记录查询\n");
		printf("\n\n\t\t【4】返回主页\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			C_Enquiry_balance();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Enquiry_Information();
			k = 3;
			break;
		case 3:
			system("cls");
			C_Enquiry_Record();
			k = 3;
			break;
		case 4:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			system("cls");
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//查询业务页
void E_Enquiry()
{

	int a, k = 0;
	while (k < 3)
	{
		printf("\n【Inquire】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\t\t【1】Account balance inquiry\n");
		printf("\n\n\t\t【2】Personal information query\n");
		printf("\n\n\t\t【3】Transaction record query\n");
		printf("\n\n\t\t【4】Return to homepage\n");
		printf("\n\n\t\t【0】Exit the system\n");
		printf("\n\n\t\t\tYour choice：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			E_Enquiry_balance();
			k = 3;
			break;
		case 2:
			system("cls");
			E_Enquiry_Information();
			k = 3;
			break;
		case 3:
			system("cls");
			E_Enquiry_Record();
			k = 3;
			break;
		case 4:
			system("cls");
			E_Main_Menu();
			k = 3;
			break;
		case 0:
			system("cls");
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//账户余额查询
void C_Enquiry_balance()
{
	printf("\n【账户余额查询】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	CE_Time();
	printf("\n\t您的余额为：\n\t\t%.2f\n", curAccount->balance);
	printf("\n");
	int a, k = 0;
	while (k < 3)
	{
		printf("\n\n\t\t【1】返回上一页\n");
		printf("\n\n\t\t【2】返回主页\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			C_Enquiry();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//账户余额查询
void E_Enquiry_balance()
{
	printf("\n【Account balance query】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	CE_Time();
	printf("\n\tYour money also include:\n\t\t%.2f\n", curAccount->balance);
	printf("\n");
	int a, k = 0;
	while (k < 3)
	{
		printf("\n\n\t\t【1】Return to the previous page\n");
		printf("\n\n\t\t【2】Return to homepage\n");
		printf("\n\n\t\t【0】Exit the system\n");
		printf("\n\n\t\t\tYour choice：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			E_Enquiry();
			k = 3;
			break;
		case 2:
			system("cls");
			E_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//个人信息查询
void C_Enquiry_Information()
{
	printf("\n【个人信息查询】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	printf("\n\t姓名：\n\t\t%s\n", curAccount->name);
	printf("\n\t账号：\n\t\t%s\n", curAccount->account_number);
	printf("\n\t预留手机号：\n\t\t%s\n\n", curAccount->phone_number);
	int a, k = 0;
	while (k < 3)
	{
		printf("\n\n\t\t\t【1】返回上一页\n");
		printf("\n\n\t\t\t【2】返回主页\n");
		printf("\n\n\t\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			C_Enquiry();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//个人信息查询
void E_Enquiry_Information()
{
	printf("\n【Personal information inquiry】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	printf("\n\tName：\n\t\t%s\n", curAccount->name);
	printf("\n\tAccount number：\n\t\t%s\n", curAccount->account_number);
	printf("\n\tReserved phone number：\n\t\t%s\n\n", curAccount->phone_number);
	int a, k = 0;
	while (k < 3)
	{
		printf("\n\n\t\t\t【1】Return to the previous page\n");
		printf("\n\n\t\t\t【2】Return to homepage\n");
		printf("\n\n\t\t\t【0】Exit the system\n");
		printf("\n\n\t\t\tYour chioce：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			E_Enquiry();
			k = 3;
			break;
		case 2:
			system("cls");
			E_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//交易记录查询
void C_Enquiry_Record()
{
	printf("\n【交易记录查询】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	CE_Print_Transaction();
	int a, k = 0;
	while (k < 3)
	{
		printf("\n\n\t\t【1】返回上一页\n");
		printf("\n\n\t\t【2】返回主页\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			C_Enquiry();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//交易记录查询
void E_Enquiry_Record()
{
	printf("\n【Transaction record query】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
 
	CE_Print_Transaction();
	int a, k = 0;
	while (k < 3)
	{
		printf("\n\n\t\t【1】Return to the previous page\n");
		printf("\n\n\t\t【2】Return to homepage\n");
		printf("\n\n\t\t【0】Exit the system\n");
		printf("\n\n\t\t\tYour choice：___\b\b\b");
		scanf("%d", &a);
		switch (a)
		{
		case 1:
			system("cls");
			C_Enquiry();
			k = 3;
			break;
		case 2:
			system("cls");
			C_Main_Menu();
			k = 3;
			break;
		case 0:
			k = 3;
			CE_Save_User_Data();
			exit(0);
		default:
			k++;
			break;
		}
	}
}

//修改信息选项页
void C_Change_Information()
{
	system("cls");
	int a, k2 = 1;
	while (k2)
	{
		printf("\n【修改个人资料】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\t\t【1】修改用户名称\n");
		printf("\n\n\t\t【2】修改账户号码\n");
		printf("\n\n\t\t【3】修改联系电话\n");
		printf("\n\n\t\t【4】修改账户密码\n");
		printf("\n\n\t\t【9】返回上一页\n");
		printf("\n\n\t\t【0】退出系统\n");
		printf("\n\n\t\t\t你的选择：___\b\b\b");
		scanf("%d", &a);

		switch (a)
		{
		case 1:
			C_Change_User();
			k2 = 0;
			break;
		case 2:
			C_Change_AccountNum();
			k2 = 0;
			break;
		case 3:
			C_Change_phone();
			k2 = 0;
			break;
		case 4:
			C_Change_Password();
			k2 = 0;
			break;
		case 9:
			C_Main_Menu();
			k2 = 0;
			break;
		case 0:
			CE_Save_User_Data();
			exit(0);
		default:
			system("cls");
			printf("输入错误！\t请按照提示重新输入：\n");
			break;
		}
	}
}

//修改信息选项页
void E_Change_Information()
{
	system("cls");
	int a, k2 = 1;
	while (k2)
	{

		printf("\n【Modify personal information】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\t\t【1】Modify user name\n");
		printf("\n\n\t\t【2】Modify account number\n");
		printf("\n\n\t\t【3】Modify contact number\n");
		printf("\n\n\t\t【4】Change account password\n");
		printf("\n\n\t\t【9】Go back to the last page\n");
		printf("\n\n\t\t【0】Exit system\n");
		printf("\n\n\t\t\tYour chioce：___\b\b\b");
		scanf("%d", &a);

		switch (a)
		{
		case 1:
			E_Change_User();
			k2 = 0;
			break;
		case 2:
			E_Change_AccountNum();
			k2 = 0;
			break;
		case 3:
			E_Change_phone();
			k2 = 0;
			break;
		case 4:
			E_Change_Password();
			k2 = 0;
			break;
		case 9:
			E_Main_Menu();
			k2 = 0;
			break;
		case 0:
			CE_Save_User_Data();
			exit(0);
		default:
			system("cls");
			printf("input error! \tPlease re-enter as prompted:\n");
			break;
		}
	}
}

//修改用户
void C_Change_User()
{
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n【修改用户名称】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\t>>请输入密码：\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n【修改用户名称】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>请输入新用户名称:\n");
			printf("\n\n\t___\b\b\b\n");
			scanf("%s", curAccount->name);
			printf("\n【修改用户名称】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\n\n\t用户名称修改成功！\n");
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】返回上一页\n");
				printf("\n\n\t\t【2】返回主页\n");
				printf("\n\n\t\t【0】退出系统\n");
				printf("\n\n\t\t\t您的选择：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					C_Change_Information();
					k = 3;
					break;
				case 2:
					system("cls");
					C_Main_Menu();
					k = 3;
					break;
				case 0:
					k = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("密码输入错误! \t%d\t请按照提示重新输入：\n", 3 - k);
		}
	}
}

//修改用户
void E_Change_User()
{
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n【Modify user name】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\t>>Please enter password:\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n【Modify user name】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>Please enter a new user name:\n");
			scanf("%s", curAccount->name);
			printf("\n【Modify user name】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\n\n\tUser name modified successfully!\n");
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】Return to the previous page\n");
				printf("\n\n\t\t【2】Return to homepage\n");
				printf("\n\n\t\t【0】Exit the system\n");
				printf("\n\n\t\t\tYour chioce：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					E_Change_Information();
					k = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k = 3;
					break;
				case 0:
					k = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("Wrong password entered! \t%d\tPlease re-enter as prompted:\n", 3 - k);
		}
	}
}

//修改账户
void C_Change_AccountNum()
{
	system("cls");
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n【修改账户号码】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\n\t>>请输入密码：\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n【修改账户号码】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>请输入新账户号码:\n");
			scanf("%s", curAccount->account_number);
			system("cls");
			printf("\n【修改账户号码】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\n\n\t账户号码修改成功！\n");
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】返回上一页\n");
				printf("\n\n\t\t【2】返回主页\n");
				printf("\n\n\t\t【0】退出系统\n");
				printf("\n\n\t\t\t您的选择：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					C_Change_Information();
					k2 = 3;
					break;
				case 2:
					system("cls");
					C_Main_Menu();
					k2 = 3;
					break;
				case 0:
					k2 = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k2++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("密码输入错误! \t%d\t请按照提示重新输入：\n", 3 - k);
		}
	}
}

//修改账户
void E_Change_AccountNum()
{
	system("cls");
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n【Modify account number】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\n\t>>Please enter password:\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n【Modify account number】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>Please enter new account number:\n");
			scanf("%s", curAccount->account_number);
			system("cls");
			printf("\n【Modify account number】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\n\n\tThe account number has been modified successfully!\n");
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】Return to the previous page\n");
				printf("\n\n\t\t【2】Return to homepage\n");
				printf("\n\n\t\t【0】Exit the system\n");
				printf("\n\n\t\t\tYour choice：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					E_Change_Information();
					k2 = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k2 = 3;
					break;
				case 0:
					k2 = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k2++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("Wrong password entered! \t%d\tPlease re-enter as prompted:\n", 3 - k);
		}
	}
}

//修改联系电话
void C_Change_phone()
{
	system("cls");
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n【修改联系电话】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\t>>请输入密码：\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n【修改联系电话】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>请输入新联系电话号码:\n");
			scanf("%s", curAccount->phone_number);
			system("cls");
			printf("\n【修改联系电话】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\n\n\t联系电话修改成功！\n");
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】返回上一页\n");
				printf("\n\n\t\t【2】返回主页\n");
				printf("\n\n\t\t【0】退出系统\n");
				printf("\n\n\t\t\t您的选择：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					C_Change_Information();
					k2 = 3;
					break;
				case 2:
					system("cls");
					C_Main_Menu();
					k2 = 3;
					break;
				case 0:
					k2 = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k2++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("密码输入错误! \t%d\t请按照提示重新输入：\n", 3 - k);
		}
	}
}

//修改联系电话
void E_Change_phone()
{
	system("cls");
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n[Modify contact number]\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\n\t>>Please enter your password:\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n[Modify contact number]\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>Please enter a new contact phone number:\n");
			scanf("%s", curAccount->phone_number);
			system("cls");
			printf("\n[Modify contact number]\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			printf("\n\n\tContact phone number modified successfully!\n");
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】Go back to the last page\n");
				printf("\n\n\t\t【2】Return to home page\n");
				printf("\n\n\t\t【0】Exit system\n");
				printf("\n\n\t\t\tYour choice：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					E_Change_Information();
					k2 = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k2 = 3;
					break;
				case 0:
					k2 = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k2++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("\n\n\tPassword entered incorrectly! \t%d\tPlease re-enter as prompted:\n", 3 - k);
		}
	}
}

//修改密码
void C_Change_Password()
{
	system("cls");
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n【修改账户密码】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		printf("\n\n\n\t>>请输入原始密码：\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n【修改账户密码】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
	 
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>请输入新密码:\n");
			printf("\n\n\t\t\t______\b\b\b\b\b\b");
			getPassword(storePassword, 10);
			strcpy(curAccount->password, storePassword);
			system("cls");
			printf("\n【修改账户密码】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		 
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】返回上一页\n");
				printf("\n\n\t\t【2】返回主页\n");
				printf("\n\n\t\t【0】退出系统\n");
				printf("\n\n\t\t\t您的选择：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					C_Change_Information();
					k2 = 3;
					break;
				case 2:
					system("cls");
					C_Main_Menu();
					k2 = 3;
					break;
				case 0:
					k2 = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k2++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("\n\n\t密码输入错误! \t%d\t请按照提示重新输入：\n", 3 - k);
		}
	}
}

//修改密码
void E_Change_Password()
{
	system("cls");
	int a, k = 0;
	char Password[100];
	while (k < 3)
	{
		printf("\n【Change account password】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		printf("\n\n\n\t>>Please enter your password:\n");
		char storePassword[10] = { '\0' };    //存储用户输入的密码
		printf("\n\n\t\t\t______\b\b\b\b\b\b");
		getPassword(storePassword, 10);
		strcpy(Password, storePassword);
		system("cls");
		printf("\n【Change account password】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
		if (strcmp(Password, curAccount->password) == 0)
		{
			printf("\n\n\t>>Please enter a new password:\n");
			printf("\n\n\t\t\t______\b\b\b\b\b\b");
			getPassword(storePassword, 10);
			strcpy(curAccount->password, storePassword);
			system("cls");
			printf("\n【Change account password】\t\t\t\t\t\t\t\t\t\t%s", tmp1);
			
			CE_Save_User_Data();
			k = 3;

			int k2 = 0;
			while (k2 < 3)
			{
				printf("\n\n\t\t【1】Go back to the last page\n");
				printf("\n\n\t\t【2】Return to home page\n");
				printf("\n\n\t\t【0】Exit system\n");
				printf("\n\n\t\t\tYour choice：___\b\b\b");
				scanf("%d", &a);
				switch (a)
				{
				case 1:
					system("cls");
					E_Change_Information();
					k2 = 3;
					break;
				case 2:
					system("cls");
					E_Main_Menu();
					k2 = 3;
					break;
				case 0:
					k2 = 3;
					CE_Save_User_Data();
					exit(0);
				default:
					k2++;
					break;
				}
			}
		}
		else
		{
			k++;
			printf("\n\n\t密码输入错误! \t%d\t请按照提示重新输入：\n", 3 - k);
		}
	}
}

//开始界面
void start()
{
	printf("\n\t\t\t\t欢迎使用ATM\n");

	int k = 1;
	while (k)
	{
		printf("\n\n\t\t请选择语言：\t");
		printf("Please choose language：\n");
		printf("\n\n\t\t\t【1】中文\n");
		printf("\n\n\t\t\t【2】English\n");
		printf("\n\n\t\t\t【0】退出 Exit\n\n\n\t\t\t");
		printf("\n\n\t\t\t▲您的选择/Your choice：___\b\b\b");
		scanf("%d", &Language);
		switch (Language)
		{
		case 1:
			system("cls");
			printf("\n\n\t\t\t【1】用户登录\n");
			printf("\n\n\t\t\t【2】用户注册\n");
			printf("\n\n\t\t\t【其它】返回上一页\n");
			printf("\n\n\t\t\t|您的选择：___\b\b\b");
			break;
		case 2:
			system("cls");
			printf("\n\n\t\t\t【1】Sign in\n");
			printf("\n\n\t\t\t【2】Sign up\n");
			printf("\n\n\t\t\t【Others】Back to previous page\n");
			printf("\n\n\t\t\tYour choice：___\b\b\b");
			break;
		case 0:
			exit(0);
		default:
			k = 1;
			system("cls");
			printf("\n\n\t\t输入有误，请按照提示再次输入!\t\t");
			printf("Error,please follow the prompts to enter again!\n\n");
			break;
		}
		printf("___\b\b\b");
		scanf("%d", &Sin);
		k = 0;
		if (Sin == 1)
		{
			C_Sign_In();//中文注册函数
		}
		else if (Sin == 2)
		{
			Sin = 1;
			C_Sign_Up();
		}
		else
			k = 1;
	}
}


int main()
{
	CE_Time();
	CE_Initialize_User_Data();
	CE_Initialize_Transaction_Data();
	start();
	CE_Save_User_Data();
	CE_Save_Transaction_Data();
	return 0;
}

