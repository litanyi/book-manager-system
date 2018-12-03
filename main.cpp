/*需要在源代码相同目录下创建四个txt文件：tushu_list.txt,jieshu_list.txt,xuesheng_list.txt,guanliyuan.txt*/
#include<stdio.h>
#include<stdlib.h>                     
#include<string.h>
struct tushu{             /*图书结构体*/
	char num[11];         /*编号*/
	char name[31];        /*书名*/
	char writer[21];      /*作者*/
	char press[21];       /*出版社*/
	char kind[21];        /*类别*/ 
	double time;          /*时间*/
	double price;         /*价格*/
	struct tushu *next;
};
struct stu                /*学生结构体*/
{
	int snum;             /*学号*/
	char mima[11];        /*密码*/
    struct stu *next;
};
struct jieshu{            /*借书信息结构体*/ 
	int xuehao;			  /*学生学号*/ 
	char num[11];         /*编号*/
	char name[31];        /*书名*/
	char writer[21];      /*作者*/
	char press[21];       /*出版社*/
	char kind[21];        /*类别*/ 
	double time;          /*时间*/
	double price;         /*价格*/
	struct jieshu *next; 
};
int denglu=-1;								/*已登录学生学号*/ 
FILE *fp;                                	/*图书文件*/
FILE *fp1;       					     	/*管理员信息文件*/  
FILE *fp2;      						 	/*学生信息文件*/
FILE *fp3;                                  /*借书信息文件*/ 
int  main();								/*主函数声明*/ 
struct tushu * create();                 	/*从文件创建图书链表（从文件中读出图书信息，建立单链表）*/
struct stu * xcreate();                  	/*从文件创建学生信息(从文件读出学生信息，建立学生链表)*/
struct jieshu * jcreate();					//从文件创建借书信息链表
struct jieshu * borrowcreate(struct tushu *k,struct jieshu *h);//直接创建借书信息链表 
struct tushu * Input();                  	/*图书添加（可进行图书的添加）*/
void menu();   						     	/*管理员主菜单（管理员进入对图书及学生信息进行管理操作）*/
void xmenu();   						 	/*学生主菜单（学生进入可对图书，密码进行操作）*/
void gfind();   						 	/*管理员查询（管理员可按一定的方式查询图书）*/
void xfind();   						 	/*学生查询（学生可按一定的方式查询图书）*/
void secret();  						 	/*管理员权限（管理员登陆所用，输入错误次数过多自动退出）*/
void sort(struct tushu *head);           	/*排序（管理员可按一定的方式对图书进行排序，排序完之后可选择文件进行保存）*/
void fprint(struct tushu *head);         	/*保存(可追加的保存，如添加可用)*/
void jsprint(struct jieshu *h);             //将借书信息添加到借书文件 
void jfprint_(struct tushu *head);       	/*借书保存（借书成功之后自动从图书馆删除）*/
void fprint_(struct tushu *head);        	/*保存（可覆盖保存如修改，删除，排序后用）*/
void gBrowse(struct tushu *head);        	/*管理员浏览（对图书进行遍历）*/
void xBrowse(struct tushu *head);        	/*学生浏览（学生对图书进行遍历）*/
void count(struct tushu *head);          	/*统计数量（管理员可对图书进行统计）*/
void Findofname(struct tushu *head);     	/*按书名查找*/
void Findofwriter(struct tushu *head);  	/*按作者查找*/
void Findofkind(struct tushu *head);     	/*按类别查找*/
void xFindofname(struct tushu *head);    	/*学生按书名查找*/
void xFindofwriter(struct tushu *head);     /*学生按作者查找*/
void xFindofkind(struct tushu *head);    	/*学生按类别查找*/
void Sort_time(struct tushu * head);     	/*按时间排序（管理员按时间对图书进行排序，排序完之后可选择文件进行保存）*/
void Sort_price(struct tushu * head);    	/*按价格排序*/
void Sort_num(struct tushu * head);         /*按编号排序*/
void Delete(struct tushu * head,char m[15]);/*按编号删除（管理员可按编号删除图书）*/
void Revise(struct tushu *head);         	/*修改	（管理员可对图书进行修改，并选择是否保存）*/
void borrow(struct tushu *head);         	/*借书*/
void huanshu(struct tushu *head);        	/*还书（学生借完书之后进行还书，若没有图书则不能借）*/
void gxinxi();                           	/*管理员信息（有管理员的账号及密码，可进行修改）*/
void xmima(struct stu *head1);           	/*学生密码修改（学生可对自己的密码进行修改）*/
void xsecret(struct stu *head1);         	/*学生权限（学生登陆所用）*/
void jsdelete(struct jieshu *h);			//学生还书时删除借书记录 
void putin(jieshu *h);                      //将还书信息加入图书文件 
/*-------------------------------------------------------------------------------------------------------------------*/
void menu()/*管理员主菜单（管理员进入对图书及学生信息进行管理操作）*/
{
	int choice,n=0;
	struct tushu *head;
	struct stu *head1,*p;
	char m[15];
there:
	printf("             ┏━┓━━━━━━━━━━━━━━━━━━━┏━┓\n");  
	printf("             ┃  ┃             图书管理系统             ┃  ┃\n");
	printf("             ┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃\n");
	printf("             ┃               ●[0]退出系统                  ┃\n"); 
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[1]返回主菜单                ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[2]浏览图书                  ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[3]统计图书数目              ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[4]查询                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[5]添加                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[6]排序                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[7]修改                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[8]删除                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[9]修改账号及密码            ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[10]学生信息                 ┃\n");
	printf("             ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("                               请选择:");
	fflush(stdin);
	head=create();
	scanf("%d",&choice);
	if(choice==1)
	{ 
		system("cls");
		printf("\n\n\n\t\t您已退出登录！\n\n\n\n");
		system("pause");
		main();
	}
	else if(choice==2)
	{
		system("cls");
		if(head==NULL)
		{
			printf("没有图书，请先添加图书！\n");
			system("pause");
			system("cls");
			menu();
		}
		gBrowse(head);
	}
	else if(choice==3)
	{
		system("cls");
		count(head);
	}
	else if(choice==4)
	{
		system("cls");
		if(head==NULL)
		{
			printf("没有图书，请先添加图书！\n");
			system("pause");
			system("cls");
			menu();
		}
		gfind();
	}
	else if(choice==5)
	{
		Input();
	}
	else if(choice==6)
	{
		system("cls");
		if(head==NULL)
		{
			printf("没有图书，请先添加图书！\n");
			system("pause");
			system("cls");
			menu();
		}
		sort(head);
	}
	else if(choice==7)
	{
		system("cls");
		if(head==NULL)
		{
			printf("没有图书，请先添加图书！\n");
			system("pause");
			system("cls");
			menu();
		}
		Revise(head) ;
	}
	else if(choice==8)
	{
		if(head==NULL)
		{
			printf("没有图书，请先添加图书！\n");
			system("pause");
			system("cls");
			menu();
		}
		printf(" 请输入想要删除的图书编号："); 
		scanf("%s",m);
		Delete(head,m);
	}
	else if(choice==9)
	{
		gxinxi();
	}
	else if(choice==10)
	{
		system("cls");
		head1=xcreate();
		if(head1==NULL)
		{
			printf("没有学生信息,请到xuesheng_list.txt添加!\n");
			system("pause");
			system("cls");
			menu();
		}
		printf("学生学号    密码\n");
		for(p=head1;p!=NULL;p=p->next)
		{
			printf("%-10d  %-10s\n",p->snum,p->mima);
		}
		system("pause");
		system("cls");
		menu();
	}
	else if(choice==0)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("           ━━━━━━━━  感谢使用图书管理系统  ━━━━━━━━\n\n\n\n\n");
		exit(0);
	}
	else
	{
		system("cls");
		printf("\n\n\n\n             ━━━━ 输入错误，请重新输入！━━━━      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ━━━━━━━━  你错误次数太多，自动退出! ━━━━━━━━\n\n\n");
			printf("           ━━━━━━━━  感谢使用图书管理系统  ━━━━━━━━\n\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
//-----------------
void xmenu()/*学生主菜单（学生进入可对图书，密码进行操作）*/ 
{ 
	struct tushu *head;
	struct stu *head1;
	int choice,n=0;
there:
	printf("             ┏━┓━━━━━━━━━━━━━━━━━━━┏━┓\n");  
	printf("             ┃  ┃            图书借阅系统              ┃  ┃\n");
	printf("             ┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃\n");
	printf("             ┃               ●[0]退出系统                  ┃\n"); 
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[1]返回主菜单                ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[2]浏览图书                  ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[3]查询                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[4]借书                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[5]还书                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[6]修改密码                  ┃\n");
	printf("             ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("                               请选择:");
	fflush(stdin);
	head=create();
	scanf("%d",&choice);
	if(choice==1)
	{ 
		denglu=-1; 
		system("cls");
		printf("\n\n\n\t\t您已退出登录！\n\n\n\n");
		system("pause");
		main();
	}
	else if(choice==2)
	{
		system("cls");
		if(head==NULL)
	    {
			printf("没有图书!\n");
			system("pause");
			system("cls");
			xmenu();
		}
		xBrowse(head);
	}
	else if(choice==3)
	{
		if(head==NULL)
		{
			printf("没有图书!\n");
			system("pause");
			system("cls");
			xmenu();
			}
		xfind();
	}
	else if(choice==4)
	{
		if(head==NULL)
		{
			printf("没有图书!\n");
			system("pause");
			system("cls");
			xmenu();
		}
		borrow(head);
	}
	else if(choice==5)
	{
		huanshu(head);
	}
	else if(choice==6)
	{
		system("cls");
		head1=xcreate();
		if(head1==NULL)
		{
		printf("学生信息被清空!!\n");
		system("pause");
		system("cls");
		xmenu();
		}
		xmima(head1); ;
	}
	else if(choice==0)
	{
		system("cls");
		printf("\n\n\n\n");
		printf("           ━━━━━━━━  感谢使用图书管理系统  ━━━━━━━━\n\n\n");
		exit(0);
	}
	else
	{
		system("cls");
		printf("\n\n\n\n             ━━━━ 输入错误，请重新输入！━━━━      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ━━━━━━━━  你错误次数太多，自动退出! ━━━━━━━━\n\n\n");
			printf("           ━━━━━━━━  感谢使用图书管理系统  ━━━━━━━━\n\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
//--------------------
void gfind()/*管理员查询（管理员可按一定的方式查询图书）*/
{
	int choice,n=0;
	struct tushu *head;
there:
	system("cls");
	printf("             ┏━┓━━━━━━━━━━━━━━━━━━━┏━┓\n");
	printf("             ┃  ┃             图书借阅系统             ┃  ┃\n");
	printf("             ┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃\n");
	printf("             ┃               ●[0]返回                      ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[1]按书名查找                ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[2]按作者查找                ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[3]按类别查找                ┃\n");
	printf("             ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("                               请选择:");
	fflush(stdin);
	head=create();
	scanf("%d",&choice);
	if(choice==1)
	{
		system("cls");
		Findofname(head);
	}
	else if(choice==2)
	{
		system("cls");
		Findofwriter(head);
	}
	else if(choice==3)
	{
		system("cls");
		Findofkind(head);
	}
	else if(choice==0)
	{
		system("cls");
		menu();
	}
	else
	{
		system("cls");
		printf("\n\n\n\n             ━━━━ 输入错误，请重新输入！━━━━      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ━━━━━━━━  你错误次数太多，自动退出! ━━━━━━━━\n\n\n");
			printf("           ━━━━━━━━  感谢使用图书管理系统  ━━━━━━━━\n\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
//---------------------
void xfind() /*学生查询（学生可按一定的方式查询图书）*/
{
	struct tushu *head;
	int choice,n=0;
there:
	system("cls");
	printf("             ┏━┓━━━━━━━━━━━━━━━━━━━┏━┓\n");  
	printf("             ┃  ┃            图书借阅系统              ┃  ┃\n");
	printf("             ┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃\n");
	printf("             ┃               ●[0]返回                      ┃\n"); 
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[1]按书名查找                ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[2]按作者查找                ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃               ●[3]按类别查找                ┃\n");
	printf("             ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("                               请选择:");
	fflush(stdin);
	head=create();
	scanf("%d",&choice);
	if(choice==1)
	{
		system("cls");
		xFindofname(head);
	}
	else if(choice==2)
	{
		system("cls");
		xFindofwriter(head);
	}
	else if(choice==3)
	{
		system("cls");
		xFindofkind(head);
	}
	else if(choice==0)
	{
		system("cls");
		xmenu();
	}
	else
	{
		system("cls");
		printf("\n\n\n\n             ━━━━ 输入错误，请重新输入！━━━━      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ━━━━━━━━  你错误次数太多，自动退出! ━━━━━━━━\n\n\n");
			printf("           ━━━━━━━━  感谢使用图书借阅系统  ━━━━━━━━\n\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
//-------------------
void  sort(struct tushu *head)
{
	struct tushu *head2;
	int choice,n=0;
there:
	system("cls");
	printf("             ┏━┓━━━━━━━━━━━━━━━━━━━┏━┓\n");  
	printf("             ┃  ┃          图书借阅系统                ┃  ┃\n");
	printf("             ┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃\n");
    printf("             ┃               ●[0]返回                      ┃\n"); 
    printf("             ┃                                              ┃\n");
    printf("             ┃               ●[1]按时间排序                ┃\n");
    printf("             ┃                                              ┃\n");
    printf("             ┃               ●[2]按价格排序                ┃\n");
    printf("             ┃                                              ┃\n");
    printf("             ┃               ●[3]按编号排序                ┃\n");
    printf("             ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    printf("                               请选择:");
	fflush(stdin);
	head2=create();
	scanf("%d",&choice);
	if(choice==1)
	{
		system("cls"); 
		Sort_time(head2);
	}
	else if(choice==2)
	{
		system("cls");
		Sort_price(head2);
	}
	else if(choice==3)
	{
		system("cls");
		Sort_num(head2);
	}
	else if(choice==0)
	{
		system("cls");
		menu();
	}
	else
	{
		system("cls");
		printf("\n\n\n\n             ━━━━ 输入错误，请重新输入！━━━━      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ━━━━━━━━  你错误次数太多，自动退出! ━━━━━━━━\n\n\n");
			printf("           ━━━━━━━━  感谢使用图书借阅系统  ━━━━━━━━\n\n\n");
            system("pause");
	        exit(0);
		}
		goto there;
	}
}
//---------------------
struct tushu *Input()
{ 
	struct tushu *p1,*p2,*head,*ptr; 
	char num;
	int x,i=0;
	system("cls");
	p1=(struct tushu *)malloc(sizeof(struct tushu));
    head=p1;
	p1->price=-1;
	while(i!=1)
	{
		printf("请输入编号。若要结束图书信息录入，请输入'#'。\n");
		scanf("%s",p1->num);
		if(strcmp(p1->num,"#")==0)
			i=1;
		while(i!=1)
		{
			printf("请依次输入书名 作者 出版社 类别 出版年份 价格:\n");
			scanf("%s%s%s%s%lf%lf", p1->name,p1->writer,p1->press,p1->kind,&p1->time,&p1->price);
			p2=p1;
			p1=(struct tushu *)malloc(sizeof(struct tushu));
		    p2->next=p1;
			break;
		}
	}
	if(p1->price!=-1)
		p2->next=NULL;
	else
		head=NULL;
	system("cls");
	printf("\n\n\n\t\t\t图书信息输入结束！\n\n\n");
	system("pause");
    system("cls");
	printf("\n\n\n\t\t\t是否保存图书信息？（1.是/2.否）：");
	scanf("%d",&x); 
	if(x==1) 
		fprint(head);
	else
	{
	 system("cls");
		printf("\n\n\n\t\t\t 文件没有被保存！\n\n\n\n");
	system("pause");
	system("cls");
	menu();
	}
 } 
//------------------------
void fprint(struct tushu *head) 
{ 
	struct tushu *p1; 
	if((fp=fopen("tushu_list.txt","a"))==NULL) 
	{ 
		printf("File open error!\n");
		system("pause"); 
		exit(0); 
	}
	if(head==NULL)
	{
		printf("没有图书保存！\n");
		system("pause");
		system("cls");
		menu();
	}
	for(p1=head;p1!=NULL;p1=p1->next) /*遍历*/
		fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*将图书信息写入文件*/ 
	fclose(fp);
	system("cls");
	printf("\n 图书信息已成功保存到文件tushu_list.txt 中！\n");
    system("pause");
    system("cls");
    getchar();
    menu();
}
//---------------------
void fprint_(struct tushu *head) 
{ 
	struct tushu *p1;
	char a[31];
	printf("请输入你保存的文件！\n");
	scanf("%s",a);
	if((fp=fopen(a,"w"))==NULL)
	{
		printf("File open error!\n");
		system("pause"); 
		exit(0);
	}
 if(head==NULL)
 {
	 system("cls");
	 printf("没有图书！\n");
	 system("pause");
	 system("cls");
	 menu();
 }	
 for(p1=head;p1!=NULL;p1=p1->next)
	 fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*将图书信息写入文件*/
 fclose(fp);
 system("cls");
 printf("\n 图书信息已成功保存到文件 %s 中！\n",a);
 system("pause");
 system("cls");
 menu();
}
//-------------------------
void hfprint(struct tushu *head) 
{ 
	struct tushu *p1; 
	if((fp=fopen("tushu_list.txt","a"))==NULL) 
	{ 
		printf("File open error!\n");
		system("pause"); 
		exit(0);
	} 
	if(head==NULL)
	{
		printf("没有还书！\n");
		xmenu();
	}
	for(p1=head;p1!=NULL;p1=p1->next) /*遍历*/
		fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*将图书信息写入文件*/ 
	fclose(fp);
	xmenu();
}
//----------------------
void jfprint_(struct tushu *head)
 { 
	struct tushu *p1;
	if((fp=fopen("tushu_list.txt","w"))==NULL)
	{
		printf("File open error!\n");
		system("pause"); 
		exit(0);
	}
	if(head==NULL)
	{
		xmenu();
	}
	for(p1=head;p1!=NULL;p1=p1->next)
	{
		fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*将图书信息写入文件*/
	}
	fclose(fp);
	system("cls");
	getchar(); 
	xmenu();
}
//------------------------
void jsprint(jieshu *h)
{
	struct jieshu *pj;
	if((fp3=fopen("jieshu_list.txt","a"))==NULL)
	{
		printf("File open error!\n");
		system("pause");
		exit(0); 
	}
	for(pj=h;pj!=NULL;pj=pj->next)
		fprintf(fp3,"%-10d  %-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n",pj->xuehao,pj->num,pj->name,pj->writer,pj->press,pj->kind,pj->time,pj->price );
	fclose(fp3);
}
//-----------------------
struct tushu * create()
{
	struct tushu *head=NULL, *p,*p1,*p2;
	if((fp=fopen("tushu_list.txt","r"))==NULL)/*先安全打开目录文件*/ 
	{
		printf("File open error!\n");
		system("pause");
		exit(0); 
	}
	while(!feof(fp))/*读取并创建链表*/ 
	{
		p=(struct tushu *)malloc(sizeof(struct tushu)); 
		p->price=-1;
		fscanf(fp,"%s%s%s%s%s%lf%lf", p->num,p->name,p->writer,p->press,p->kind,&p->time,&p->price); 
		if(p->price==-1)
		{
			free(p);
			break;
		}
		if(head==NULL)
		{ 
			head=p;
			p1=p;
			p1->next=NULL;
		} 
		else
		{
			p1->next=p;
			p2=p1;
			p1=p;
			p1->next=NULL;
		}
	} 
	fclose(fp);
	return head;
}
//-------------------------
 struct jieshu * jcreate()
{
 	struct jieshu *head=NULL, *p,*p1,*p2;
	if((fp3=fopen("jieshu_list.txt","r"))==NULL) 
	{
		printf("File open error!\n");
		system("pause");
		exit(0); 
	}
	while(!feof(fp3)) 
	{
		p=(struct jieshu *)malloc(sizeof(struct jieshu)); 
		p->price=-1;
		fscanf(fp3,"%d%s%s%s%s%s%lf%lf",&p->xuehao,p->num,p->name,p->writer,p->press,p->kind,&p->time,&p->price); 
		if(p->price==-1)
		{
			free(p);
			break;
		}
		if(head==NULL)
		{ 
			head=p;
			p1=p;
			p1->next=NULL;
		} 
		else
		{
			p1->next=p;
			p2=p1;
			p1=p;
			p1->next=NULL;
		}
	} 
	fclose(fp3);
	return head;	
} 
//------------------------------
struct jieshu * borrowcreate(struct tushu *k,struct jieshu *h)
{
    struct jieshu *head;
    head=(struct jieshu *)malloc(sizeof(struct jieshu));
    if (h==NULL)
    {
 		h=head;
 		h->xuehao=denglu;
 		strcpy(h->num,k->num);
 		strcpy(h->name,k->name);
 		strcpy(h->writer,k->writer);
 		strcpy(h->press,k->press);
 		strcpy(h->kind,k->kind);
 		h->time=k->time;
 		h->price=k->price;
 		h->next=NULL;
 		return h;
 	}
 	else
 	{
	 	head->xuehao=denglu;
 		strcpy(head->num,k->num);
 		strcpy(head->name,k->name);
 		strcpy(head->writer,k->writer);
 		strcpy(head->press,k->press);
 		strcpy(head->kind,k->kind);
 		head->time=k->time;
 		head->price=k->price;
		head->next=h;
		return head;	
    }
} 
//--------------------------
 void gBrowse(struct tushu *head)
 {
	 struct tushu *p1;
	 printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 for(p1=head;p1!=NULL;p1=p1->next)
	 {
		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price);
	 }
	 system("pause");
	 system("cls");
	 menu();
 }
//---------------------------- 
void xBrowse(struct tushu *head)
 {
	 struct tushu *p1;
	 printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 for(p1=head;p1!=NULL;p1=p1->next)
	 {
         printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price);
	 }
	 system("pause");
	 system("cls");
	 xmenu();
 }
//-----------------------------
 void count(struct tushu *head) /*统计图书数目*/
 {
	 int n=0;
	 struct tushu *p1; 
	 for(p1=head;p1!=NULL;p1=p1->next)
		 n++;
	 printf("\n此系统统计在内的图书共有 %d 册。\n",n);/*计算并输 出图书数目*/ 
	 system("pause");
	 system("cls");
	 menu();
}
//----------------------------
void Findofname(struct tushu *head) /*按书名查询图书*/ 
{ 
	int i=0,n;
	char b[31];
	struct tushu *p;
	p=head;
	printf("\n请输入要查询的图书名称：");
	scanf("%s",b);
	while(p!=NULL)
	{
		if(strcmp(p->name,b)==0)
		{ 
	        printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 		printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			i++;
		}
		p=p->next;
	}
	if(i==0) 
	{
		system("cls");
		printf("\n 对不起！没有找到名为《%s》的图书！\n",b);
	    system("pause");
	}
	printf("\n\n\n\t\t\t是否继续查找图书信息？（1.是/其他.返回）：");
	scanf("%d",&n); 
	if(n==1) 
	gfind();
	else
	{
		system("cls");
		menu();
	}
}
//------------------------------
 void Findofwriter(struct tushu *head)
 {
	 int i=0,n;
	 char b[21]; 
	 struct tushu *p;
	 p=head;
	 printf("\n请输入要查询的图书作者姓名：");
	 scanf("%s",b);
	 while(p!=NULL)
	 { 
		 if(strcmp(p->writer,b)==0)
		 {
			 printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			 i++;
		 }
		 p=p->next;
	 }
	 if(i==0)
	 {
		 system("cls");
		 printf("\n 对不起！没有找到' %s '所著的相关图书！\n",b);
		 system("pause");
	 }
	 printf("\n\n\n\t\t\t是否继续查找图书信息？（1.是/其他.返回）：");
	 scanf("%d",&n); 
	 if(n==1) 
		 gfind();
	 else
	 {
		 system("cls");
		 menu();
	 }
 }
//----------------------------------
 void Findofkind(struct tushu *head)
 {
	 int i=0,n; 
	 char b[21]; 
	 struct tushu *p;
	 p=head; 
	 printf("\n请输入您要查询的图书类别：");
	 scanf("%s",b); 
	 while(p!=NULL)
	 {
		 if(strcmp(p->kind,b)==0)
		 {
			 printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price); 
			 i++;
		 } 
		 p=p->next; 
	 }
	 if(i==0)
	 {
		system("cls");
		printf("\n 对不起！没有找到类别为' %s '的图书！\n",b);
		system("pause");
	}
	 printf("\n\n\n\t\t\t是否继续查找图书信息？（1.是/其他.返回）：");
	 scanf("%d",&n); 
	 if(n==1) 
		 gfind();
	 else
	 {
		 system("cls");
		 menu();
	 }
 }
//---------------------------------
 void xFindofname(struct tushu *head) /*按书名查询图书*/ 
 { 
	 int i=0,n;
	 char b[31];
	 struct tushu *p;
	 p=head;
	 printf("\n请输入要查询的图书名称：");
	 scanf("%s",b);
	 while(p!=NULL)
	 {
		 if(strcmp(p->name,b)==0)
		 { 
			 printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			 i++;
		 }
		 p=p->next; 
	 }
	 if(i==0) 
	 {
		 system("cls");
		 printf("\n 对不起！没有找到名为《%s》的图书！\n",b);
		 system("pause");
	 }
	 printf("\n\n\n\t\t\t是否继续查找图书信息？（1.是/其他.返回）：");
	 scanf("%d",&n); 
	 if(n==1) 
		 xfind();
	 else
	 {
		 system("cls");
		 xmenu();
	 }
 }
//--------------------------
 void xFindofwriter(struct tushu *head)
 {
	 int i=0,n; 
	 char b[21]; 
	 struct tushu *p;
	 p=head;
	 printf("\n请输入要查询的图书作者姓名：");
	 scanf("%s",b);
	 while(p!=NULL)
	 { 
		 if(strcmp(p->writer,b)==0)
		 {
			 printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			 i++;
		 }
		 p=p->next;
	 }
	 if(i==0)
		 system("cls");
	 printf("\n 对不起！没有找到' %s '所著的相关图书！\n",b);
	 system("pause");
	 printf("\n\n\n\t\t\t是否继续查找图书信息？（1.是/其他.返回）：");
	 scanf("%d",&n); 
	 if(n==1) 
		 xfind();
	 else
	 {
		 system("cls");
		 xmenu();
	 }
 }
 //-----------------------
void xFindofkind(struct tushu *head) 
{
	int i=0,n; 
	char b[21]; 
	struct tushu *p;
	p=head; 
	printf("\n请输入您要查询的图书类别：");
	scanf("%s",b); 
	while(p!=NULL)
	{
		if(strcmp(p->kind,b)==0)
		{
			printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	 		printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			i++;
		} 
		p=p->next;
	}
	if(i==0)
		system("cls");
		printf("\n 对不起！没有找到类别为' %s '的图书！\n",b);
		system("pause");
		printf("\n\n\n\t\t\t是否继续查找图书信息？（1.是/其他.返回）：");
		scanf("%d",&n); 
		if(n==1) 
			xfind();
		else
		{
			system("cls");
			xmenu();
		}
}
//--------------------------
void Sort_time(struct tushu * head) 
{
	struct  tushu *p1,*p2,*p3,*p4=NULL,*p5;
	int x;
	for(p1=head;p1->next!=p4;)
	{
		for(p2=p1;p2->next!=p4;)
		{
			if(p2->time>p2->next->time)			
			{
				if(p2==p1)
				{
					p1=p2->next;
					p2->next=p1->next;
					p1->next=p2;
					p3=p1;
				}
				else
				{
					p3->next=p2->next;
					p3=p2->next;
					p2->next=p3->next;
					p3->next=p2;
				}
			}
			else
			{
				p3=p2;
				p2=p2->next;
			}
		}
		p4=p2;
	}
	printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	for(p5=p1;p5!=NULL;p5=p5->next)  
	printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p5->num,p5->name,p5->writer,p5->press,p5->kind,p5->time,p5->price);
	system("pause");
	system("cls");
	printf("\n\n\n\t\t\t是否保存图书信息？（1.是/2.否(返回)）：");
	scanf("%d",&x); 
	if(x==1)
		fprint_(p1);
	else
		system("cls");
	printf("\n\n\n\t\t\t 没有被保存到文件！\n\n\n\n");
	system("pause");
	system("cls");
	menu();
	return;
}
//----------------------------
void Sort_price(struct tushu * head) 
{ 
	struct  tushu *p1,*p2,*p3,*p4=NULL,*p5;
	int x;
	for(p1=head;p1->next!=p4;)
	{
		for(p2=p1;p2->next!=p4;)
		{
			if(p2->price>p2->next->price)		
			{
				if(p2==p1)
				{
					p1=p2->next;
					p2->next=p1->next;
					p1->next=p2;
					p3=p1;
				}
				else
				{
					p3->next=p2->next;
					p3=p2->next;
					p2->next=p3->next;
					p3->next=p2;
				}
			}
			else
			{
				p3=p2;
				p2=p2->next;
			}
		}
		p4=p2;
	}
	printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	for(p5=p1;p5!=NULL;p5=p5->next)  
	printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p5->num,p5->name,p5->writer,p5->press,p5->kind,p5->time,p5->price);
	system("pause");
	system("cls");
	printf("\n\n\n\t\t\t是否保存图书信息？（1.是/2.否(返回)）：");
	scanf("%d",&x); 
	if(x==1)
		fprint_(p1);
	else
		system("cls");
	printf("\n\n\n\t\t\t 没有被保存到文件！\n\n\n\n");
	system("pause");
	system("cls");
	menu();
	return;
 }
//------------------------------
void Sort_num(struct tushu * head) 
{
	struct  tushu *p1,*p2,*p3,*p4=NULL,*p5;
	int x;
	for(p1=head;p1->next!=p4;)
	//对链表进行从大到小排序（这里用冒泡法）
	//p1使之总是指向头结点，p4使之总是指向已排序好的最前面的结点
	//p3作为中介，保存p2的上一个结点
	{
		for(p2=p1;p2->next!=p4;)
		{
			if(strcmp(p2->num,p2->next->num)>0)//p2的值大于p2->next的值，交换			
			{
				if(p2==p1)//头结点要交换
				{
					p1=p2->next;
					p2->next=p1->next;
					p1->next=p2;
					p3=p1;
				}
				else
				{
					p3->next=p2->next;
					p3=p2->next;
					p2->next=p3->next;
					p3->next=p2;
				}
			}
			else//不需要交换，则p2、p3前进1位
			{
				p3=p2;
				p2=p2->next;
			}
		}
		p4=p2;
	}
	printf("编号        书名                            作者                  出版社                类别                  出版时间    价格\n");
	for(p5=p1;p5!=NULL;p5=p5->next)  
	printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p5->num,p5->name,p5->writer,p5->press,p5->kind,p5->time,p5->price);
	system("pause");
	system("cls");
	printf("\n\n\n\t\t\t是否保存图书信息？（1.是/2.否(返回)）：");
	scanf("%d",&x); 
	if(x==1)
		fprint_(p1);
	else
		system("cls");
	printf("\n\n\n\t\t\t 没有被保存到文件！\n\n\n\n");
	system("pause");
	system("cls");
	menu();
	return;
}
//--------------------------------
void Delete(struct tushu * head,char m[15]) 
{ 
	struct tushu *ptr1,*ptr2;
	int x,n=0; 
	if((strcmp(head->num,m)==0)&&head->next==NULL)
	{
		printf("删除成功！\n");
        system("pause");
		system("cls");
		head=NULL;
        fprint_(head);
	}
	while((strcmp(head->num,m)==0)&&head!=NULL) 
	{
		ptr2=head; 
		head=head->next;
		n++;
		free(ptr2); 
	} 
	if(head==NULL)
	{
		printf("已无图书信息！\n"); 
		menu();
	} 
	ptr1=head;
	ptr2=head->next;
	while(ptr2!=NULL){
	 if(strcmp(ptr2->num,m)==0)
	 {
		 ptr1->next=ptr2->next;
		 n++;
		 free(ptr2);
	 }
	 else
		 ptr1=ptr2;
	 ptr2=ptr1->next;
	} 
	if(n==0)
	{
	    system("cls");
		printf("没有删除你要删除的图书！\n");
		system("pause");
		system("cls");
		menu();
		return;
	}
	else
		printf("\n 编号为' %s '目标图书已被删除，并保存至文件！\n",m); 
	printf("\n\n\n\t\t\t是否保存图书信息？（1.是/2.否(返回)）：");
	scanf("%d",&x); 
	if(x==1)
		fprint_(head);
	else
		system("cls");
		printf("\n\n\n\t\t\t 并没有被保存到文件！\n\n\n\n");
		system("pause");
		system("cls");
		menu();
		return;
}
//-----------------------------
void Revise(struct tushu *head)
{
	struct tushu *p;
	char num[11]; 
	char name[31];
	char writer[21]; 
	char press[21];
	char kind[21]; 
	double time;
	double price;
	int x,panduan=0;
	char m[11];
	p=head;
	printf("请输入要修改书本的编号:");
	scanf("%s",m);
	while(p!=NULL)
	{
		if(strcmp(p->num,m)==0)
		{
			printf("请依次输入书名 作者 出版社 类别 出版年份 价格\n");
			scanf("%s%s%s%s%lf%lf", name,writer,press,kind,&time,&price);
			strcpy(p->name,name);
			strcpy(p->writer,writer);
			strcpy(p->press,press);
			strcpy(p->kind,kind);
			p->time=time;
			p->price=price;
			printf("\n");
			panduan=1;
		}
		p=p->next;
	}
	if(panduan==0)
	{
		printf("\n                      ━━━━  没有图书记录!  ━━━━\n\n");
		system("pause");
		system("cls");
		menu();
	}
	else	
		printf("\n 编号为' %s '目标图书已被修改！\n",m); 
	printf("\n\n\n\t\t\t是否保存图书信息？（1.是/2.否(返回)）：");
	scanf("%d",&x); 
	if(x==1)
		fprint_(head);
	else
		system("cls");
		printf("\n\n\n\t\t\t 没有被保存到文件！\n\n\n\n");
		system("pause");
		system("cls");
		menu();
		return;
}
//-------------------------------
void borrow(struct tushu *head)//借书 
{ 
	struct tushu *ptr1,*ptr2;
	struct jieshu *xinxi=NULL;
	char m[11];
	int n=0;
	system("cls");
	printf("请输入你想借的图书的编号:\n");
	scanf("%s",m);
    if((strcmp(head->num,m)==0)&&head->next==NULL)
	{
		xinxi=borrowcreate(head,xinxi);
		printf("\n\n\n借书成功！\n\n\n\n");
        system("pause");
		system("cls");
		head=NULL;
		jsprint(xinxi);
        jfprint_(head);
	}
	while((strcmp(head->num,m)==0)&&head!=NULL) 
	{
		ptr2=head;
		xinxi=borrowcreate(ptr2,xinxi); 
		head=head->next;
		free(ptr2);
		n++;
	} 
	if(head==NULL)
	{
		system("pause");
		system("cls");
		printf("无图书信息！\n");
		xmenu();
	} 
	ptr1=head;
	ptr2=head->next;
	while(ptr2!=NULL)
	{
		if(strcmp(ptr2->num,m)==0)
		{
			ptr1->next=ptr2->next;
			xinxi=borrowcreate(ptr2,xinxi);
			free(ptr2);
			n++;
		}
		else
			ptr1=ptr2;
		ptr2=ptr1->next;
	}
	if(n==0)
	{
		printf("无图书信息！\n");
		system("pause");
		system("cls");
		xmenu();
	}
	else
		printf("\n\n\n借书成功！\n\n\n\n");
	
	system("pause");
	system("cls");
	jsprint(xinxi);
	jfprint_(head);
}
//------------------------------
void huanshu(struct tushu *head)	//需写一个jsdelete函数删除jieshu_list.txt文件内容和一个putin函数将数据重写入tushu_list.txt 
{
	system("cls");
	struct jieshu *jsinfo,*p,*p1;
	char booknum[11];
	jsinfo=jcreate();
	if (jsinfo==NULL)
	{
		printf("\n\n\n\t\t没有借书记录，无法进行还书操作!\n\n\n\n");
		system("pause");
		system("cls");
	}
	else
	{
		printf("请输入你所要还的书的编号，若想取消还书操作请输入'#':\n");
		scanf("%s",booknum);
		printf("\n\n\n");
		if(strcmp(booknum,"#")==0)
		{
			printf("没有进行还书操作!\n\n\n");
		    system("pause");
		    system("cls");
		}
		else
		{
			for(p1=p=jsinfo;p!=NULL;p=p->next)
			{
				if((strcmp(p->num,booknum)==0)&&(denglu==p->xuehao))
					break;
				p1=p;
			}
			if(p==NULL)
			{
				printf("您输入的图书编号有误，无法进行还书操作!\n\n\n");
		        system("pause");
		        system("cls");
			}
			else
			{
				if(p==p1)
					jsinfo=p->next;
				else
					p1->next=p->next;
				jsdelete(jsinfo);
				putin(p);
				printf("还书成功！\n\n\n");
				system("pause");
		        system("cls");
			} 
		} 
	}
	xmenu();
}
//----------------------------------
void jsdelete(struct jieshu *h)
{
	struct jieshu *pj;
	if((fp3=fopen("jieshu_list.txt","w"))==NULL)
	{
		printf("File open error!\n");
		system("pause"); 
		exit(0);
	}
	for(pj=h;pj!=NULL;pj=pj->next)
		fprintf(fp3,"%-10d  %-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n",pj->xuehao,pj->num,pj->name,pj->writer,pj->press,pj->kind,pj->time,pj->price);
	fclose(fp3);	
}
//------------------------------
void putin(jieshu *h)
{
	if((fp=fopen("tushu_list.txt","a"))==NULL) 
	{ 
		printf("File open error!\n");
		system("pause"); 
		exit(0); 
	}
	fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", h->num,h->name,h->writer,h->press,h->kind,h->time,h->price);
	fclose(fp);
}
//------------------------------
void gxinxi()
{
	int i;
	char pa[11];
	char zhanghao[21];
there:
	system("cls");
	printf("请输入新帐号(不大于20个字符)，按Enter结束\n");
	scanf("%s",zhanghao);
	printf("请输入新密码(不大于10个字符)，按Enter结束！\n");
	scanf("%s",pa);
	system("cls");
	printf("是否确认修改，1是/其他（返回）！\n");
    scanf("%d",&i);
	if(i==1)
	{
		system("cls");
		printf("账号及密码修改成功，请牢记！\n");
		if((fp1=fopen("guanliyuan.txt","w"))==NULL)
		{
			printf("File open error! \n");
			system("pause");
			exit(0);
		}
		fprintf(fp1,"%-20s \t %-10s",zhanghao,pa);
		if(fclose(fp1))
		{
			printf("Can not close the file!  \n");
			exit(0);
		}
		system("pause");
		system("cls");
		menu();
	}
	else
		menu();
}
//---------------------------
struct stu * xcreate()
{
	struct stu *head1=NULL,*p,*p1,*p2;
	if((fp2=fopen("xuesheng_list.txt","r"))==NULL)
	{
		printf("File open error!\n");
		system("pause");
		exit(0); 
	}
	while(!feof(fp2))
	{
		p=(struct stu *)malloc(sizeof(struct stu)); 
		p->snum=-1;
		fscanf(fp2,"%d%s",&p->snum,p->mima); 
		if(p->snum==-1){
			free(p);
			break;
		}
		if(head1==NULL)
		{ 
			head1=p;
			p1=p;
			p1->next=NULL;
		} 
		else
		{
			p1->next=p;
			p2=p1;
			p1=p;
			p1->next=NULL;
		}
	} 
	fclose(fp2);
	return head1;
}
//-----------------------
void xsecret(struct stu *head1)
{
	struct stu  *p;
	char pa[11];
	int zhanghao;
	int i=0;
	printf("【友情提示】你共有三次输入账号密码的机会！\n");
	there:
	printf("请输入学号，按Enter结束！\n");
	scanf("%d",&zhanghao);
	printf("请输入密码(不大于10个字符)，按Enter结束！初始密码为123456\n");
	scanf("%s",pa);
	for(p=head1;p!=NULL;p=p->next)
	{
		if((zhanghao==p->snum)&&(strcmp(pa,p->mima)==0))
		{
			denglu=zhanghao;
			system("cls");
			xmenu();
		}
	}
	i++;
	if(i<3)
	{ 
		printf("你输入的学号不存在或密码错误，请重新输入！\n\n");
		system("pause");
		system("cls");
		goto there;
	}
	else
	{
		system("cls");
		printf("你输入的学号不存在或密码错误！\n");
		printf("\n\n\n\t\t您已达到输入次数上限！正在自动返回主菜单！\n\n\n\n");
		system("pause");
		system("cls");
		main();
	}
}
//--------------------------
void xmima(struct stu *head1)
{
	struct stu *p;
	char pa[11],pb[11],pc[11];
	int zhanghao;
	int i,j;
	int k=0;
there:
	zhanghao=denglu; 
	printf("请输入你的原密码(不大于10个字符)，按Enter结束！\n");
	scanf("%s",pa);
	for(p=head1;p!=NULL;p=p->next)
	{
		if((zhanghao==p->snum)&&(strcmp(pa,p->mima)==0))
		{
			k=k+1;
			break;
		}		
	}
		if(k==1)
		{
			printf("请输入新密码(不大于10个字符)！\n");
            scanf("%s",pb);
            printf("请再次输入新密码(不大于10个字符)！\n");
            scanf("%s",pc);
			if(strcmp(pb,pc)==0)
			{

				system("pause");
				system("cls");          
				printf("是否确认修改，1是/其他（返回）！\n");
				scanf("%d",&i);
				if(i==1)
				{
					printf("密码修改成功，请牢记！\n");
					system("pause");
					system("cls");
					strcpy(p->mima,pb);
					if((fp2=fopen("xuesheng_list.txt","w"))==NULL)
					{
						printf("File open error! \n");
						system("pause");
						exit(0);
					}
					for(p=head1;p!=NULL;p=p->next)
					fprintf(fp2,"%-10d \t %-10s\n",p->snum,p->mima);
					if(fclose(fp2))
					{
						printf("Can not close the file!  \n");
						exit(0);
					}
					system("cls");
					xmenu();
				}
				else
				{
					printf("密码没有修改！\n");
					xmenu();
				}
			}
			else
			{
				system("cls");
				printf("你两次输入的密码不一致，请重新输入！\n\n");
				system("pause");
				system("cls");
				printf("是否继续修改，1是/其他（返回）！\n");
                scanf("%d",&j);
				if(j==1)
				{
					system("cls");
					xmima(head1);
				}
				else
				{
					system("cls");
					xmenu();
				}
			}
		}
		else 
		{
		printf("输入的原密码错误！\n");
		system("pause");
		system("cls");
		xmenu();
		}
}
//-----------------------------
void secret()
{
	int n=3;
	char pa[11],p1[11];
	char zhanghao[21],p[21];
	printf("\n\n*******************************************************************\n");
	printf("                     欢迎进入图书管理系统\n");
	printf("*******************************************************************\n\n\n");
	system("pause");
	system("cls");
	printf("\t    [现在进行权限核查]\n友情提醒：你共有三次输入账号和密码的机会！\n");
	printf("初始管理员账号和密码分别为guanliyuan,123456\n\n\n\n");
	system("pause");
	system("cls");
there:		
	if(n==2||n==1)
	{
		system("cls");
		printf("注意：你已输入错误%d次,剩余次数%d\n请输入帐号(不大于20个字符),按Enter结束:\n",3-n,n);
	}
	if(n==3)
		printf("剩余次数:%d\n请输入帐号(不大于20个字符)，按Enter结束:\n",n);
	scanf("%s",zhanghao);
	printf("请输入密码(不大于10个字符),按Enter结束:\n");
	scanf("%s",pa);
	if((fp1=fopen("guanliyuan.txt","r"))==NULL)
	{
		printf("File open error! \n");
		system("pause");
		exit(0);
	}
	fscanf(fp1,"%s%s",p,p1);
	if(fclose(fp1))
	{
		printf("Can not close the file!  \n");
		exit(0);
	}
	if((strcmp(zhanghao,p)==0)&&(strcmp(pa,p1)==0))
	{
		system("cls");
		menu();
	}
	else
	{ 
		n--;
		if(n==0)
		{
			system("cls");
			printf("\n\n对不起，你连续三次输入密码错误，没有使用管理员系统的权限！\n即将返回主菜单！\n\n\n");
			system("pause");
			system("cls");
			main();
		}
		goto there;
	}
}
//-----------------------------------
main()
{
	int i,j=0;
	struct stu *head1;
	system("mode con cols=140 lines=40"); 
	system("color 27"); 
	printf("             ┏━┓━━━━━━━━━━━━━━━━━━━┏━┓\n");  
	printf("             ┃  ┃         欢迎使用图书管理系统         ┃  ┃\n");
	printf("             ┃  ┗━━━━━━━━━━━━━━━━━━━┛  ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃              制作人：半藏                    ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃              制作日期：2016.12               ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┃                                              ┃\n");
	printf("             ┗━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("按Enter键进入......\n");
	getchar();
there:
	fflush(stdin);
	system("cls");
	printf("\n\n\n1 :管理员登陆系统\n\n2 :学生登陆系统\n\n0 :退出\n\n\n\n");
    printf("请选择:");
	scanf("%d",&i);
	if(i==0)
	{
		system("cls");
		printf("\n\n\n\n*********************************************************************************\n");
		printf("                           感谢使用图书管理系统\n");
		printf("*********************************************************************************\n\n\n");
		system("pause");
		exit(0);
	}
	else if(i==1)
	{
		system("cls");
		secret();
	}
	else if(i==2)
	{
		system("cls");
		head1=xcreate();
        if(head1==NULL)
		{
			printf("暂没有学生信息，学生不能登录!\n");
			system("pause");
			system("cls");
			main();
		}
        xsecret(head1);
	}
	else
	{
		printf("\n\n输入错误，请重新输入！\n\n\n");
		system("pause");
		system("cls"); 
		j++;
		if(j==3)
		{
			system("cls");
			printf("\n\n\n*************************************************************************\n\n");
			printf("\n\n\t\t你输入的次数过多，自动退出！谢谢使用！\n\n");
			printf("\n\n*************************************************************************\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
