/*��Ҫ��Դ������ͬĿ¼�´����ĸ�txt�ļ���tushu_list.txt,jieshu_list.txt,xuesheng_list.txt,guanliyuan.txt*/
#include<stdio.h>
#include<stdlib.h>                     
#include<string.h>
struct tushu{             /*ͼ��ṹ��*/
	char num[11];         /*���*/
	char name[31];        /*����*/
	char writer[21];      /*����*/
	char press[21];       /*������*/
	char kind[21];        /*���*/ 
	double time;          /*ʱ��*/
	double price;         /*�۸�*/
	struct tushu *next;
};
struct stu                /*ѧ���ṹ��*/
{
	int snum;             /*ѧ��*/
	char mima[11];        /*����*/
    struct stu *next;
};
struct jieshu{            /*������Ϣ�ṹ��*/ 
	int xuehao;			  /*ѧ��ѧ��*/ 
	char num[11];         /*���*/
	char name[31];        /*����*/
	char writer[21];      /*����*/
	char press[21];       /*������*/
	char kind[21];        /*���*/ 
	double time;          /*ʱ��*/
	double price;         /*�۸�*/
	struct jieshu *next; 
};
int denglu=-1;								/*�ѵ�¼ѧ��ѧ��*/ 
FILE *fp;                                	/*ͼ���ļ�*/
FILE *fp1;       					     	/*����Ա��Ϣ�ļ�*/  
FILE *fp2;      						 	/*ѧ����Ϣ�ļ�*/
FILE *fp3;                                  /*������Ϣ�ļ�*/ 
int  main();								/*����������*/ 
struct tushu * create();                 	/*���ļ�����ͼ���������ļ��ж���ͼ����Ϣ������������*/
struct stu * xcreate();                  	/*���ļ�����ѧ����Ϣ(���ļ�����ѧ����Ϣ������ѧ������)*/
struct jieshu * jcreate();					//���ļ�����������Ϣ����
struct jieshu * borrowcreate(struct tushu *k,struct jieshu *h);//ֱ�Ӵ���������Ϣ���� 
struct tushu * Input();                  	/*ͼ����ӣ��ɽ���ͼ�����ӣ�*/
void menu();   						     	/*����Ա���˵�������Ա�����ͼ�鼰ѧ����Ϣ���й��������*/
void xmenu();   						 	/*ѧ�����˵���ѧ������ɶ�ͼ�飬������в�����*/
void gfind();   						 	/*����Ա��ѯ������Ա�ɰ�һ���ķ�ʽ��ѯͼ�飩*/
void xfind();   						 	/*ѧ����ѯ��ѧ���ɰ�һ���ķ�ʽ��ѯͼ�飩*/
void secret();  						 	/*����ԱȨ�ޣ�����Ա��½���ã����������������Զ��˳���*/
void sort(struct tushu *head);           	/*���򣨹���Ա�ɰ�һ���ķ�ʽ��ͼ���������������֮���ѡ���ļ����б��棩*/
void fprint(struct tushu *head);         	/*����(��׷�ӵı��棬����ӿ���)*/
void jsprint(struct jieshu *h);             //��������Ϣ��ӵ������ļ� 
void jfprint_(struct tushu *head);       	/*���鱣�棨����ɹ�֮���Զ���ͼ���ɾ����*/
void fprint_(struct tushu *head);        	/*���棨�ɸ��Ǳ������޸ģ�ɾ����������ã�*/
void gBrowse(struct tushu *head);        	/*����Ա�������ͼ����б�����*/
void xBrowse(struct tushu *head);        	/*ѧ�������ѧ����ͼ����б�����*/
void count(struct tushu *head);          	/*ͳ������������Ա�ɶ�ͼ�����ͳ�ƣ�*/
void Findofname(struct tushu *head);     	/*����������*/
void Findofwriter(struct tushu *head);  	/*�����߲���*/
void Findofkind(struct tushu *head);     	/*��������*/
void xFindofname(struct tushu *head);    	/*ѧ������������*/
void xFindofwriter(struct tushu *head);     /*ѧ�������߲���*/
void xFindofkind(struct tushu *head);    	/*ѧ����������*/
void Sort_time(struct tushu * head);     	/*��ʱ�����򣨹���Ա��ʱ���ͼ���������������֮���ѡ���ļ����б��棩*/
void Sort_price(struct tushu * head);    	/*���۸�����*/
void Sort_num(struct tushu * head);         /*���������*/
void Delete(struct tushu * head,char m[15]);/*�����ɾ��������Ա�ɰ����ɾ��ͼ�飩*/
void Revise(struct tushu *head);         	/*�޸�	������Ա�ɶ�ͼ������޸ģ���ѡ���Ƿ񱣴棩*/
void borrow(struct tushu *head);         	/*����*/
void huanshu(struct tushu *head);        	/*���飨ѧ��������֮����л��飬��û��ͼ�����ܽ裩*/
void gxinxi();                           	/*����Ա��Ϣ���й���Ա���˺ż����룬�ɽ����޸ģ�*/
void xmima(struct stu *head1);           	/*ѧ�������޸ģ�ѧ���ɶ��Լ�����������޸ģ�*/
void xsecret(struct stu *head1);         	/*ѧ��Ȩ�ޣ�ѧ����½���ã�*/
void jsdelete(struct jieshu *h);			//ѧ������ʱɾ�������¼ 
void putin(jieshu *h);                      //��������Ϣ����ͼ���ļ� 
/*-------------------------------------------------------------------------------------------------------------------*/
void menu()/*����Ա���˵�������Ա�����ͼ�鼰ѧ����Ϣ���й��������*/
{
	int choice,n=0;
	struct tushu *head;
	struct stu *head1,*p;
	char m[15];
there:
	printf("             ��������������������������������������������������\n");  
	printf("             ��  ��             ͼ�����ϵͳ             ��  ��\n");
	printf("             ��  ������������������������������������������  ��\n");
	printf("             ��               ��[0]�˳�ϵͳ                  ��\n"); 
	printf("             ��                                              ��\n");
	printf("             ��               ��[1]�������˵�                ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[2]���ͼ��                  ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[3]ͳ��ͼ����Ŀ              ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[4]��ѯ                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[5]���                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[6]����                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[7]�޸�                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[8]ɾ��                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[9]�޸��˺ż�����            ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[10]ѧ����Ϣ                 ��\n");
	printf("             ��������������������������������������������������\n");
	printf("                               ��ѡ��:");
	fflush(stdin);
	head=create();
	scanf("%d",&choice);
	if(choice==1)
	{ 
		system("cls");
		printf("\n\n\n\t\t�����˳���¼��\n\n\n\n");
		system("pause");
		main();
	}
	else if(choice==2)
	{
		system("cls");
		if(head==NULL)
		{
			printf("û��ͼ�飬�������ͼ�飡\n");
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
			printf("û��ͼ�飬�������ͼ�飡\n");
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
			printf("û��ͼ�飬�������ͼ�飡\n");
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
			printf("û��ͼ�飬�������ͼ�飡\n");
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
			printf("û��ͼ�飬�������ͼ�飡\n");
			system("pause");
			system("cls");
			menu();
		}
		printf(" ��������Ҫɾ����ͼ���ţ�"); 
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
			printf("û��ѧ����Ϣ,�뵽xuesheng_list.txt���!\n");
			system("pause");
			system("cls");
			menu();
		}
		printf("ѧ��ѧ��    ����\n");
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
		printf("           ����������������  ��лʹ��ͼ�����ϵͳ  ����������������\n\n\n\n\n");
		exit(0);
	}
	else
	{
		system("cls");
		printf("\n\n\n\n             �������� ����������������룡��������      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ����������������  ��������̫�࣬�Զ��˳�! ����������������\n\n\n");
			printf("           ����������������  ��лʹ��ͼ�����ϵͳ  ����������������\n\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
//-----------------
void xmenu()/*ѧ�����˵���ѧ������ɶ�ͼ�飬������в�����*/ 
{ 
	struct tushu *head;
	struct stu *head1;
	int choice,n=0;
there:
	printf("             ��������������������������������������������������\n");  
	printf("             ��  ��            ͼ�����ϵͳ              ��  ��\n");
	printf("             ��  ������������������������������������������  ��\n");
	printf("             ��               ��[0]�˳�ϵͳ                  ��\n"); 
	printf("             ��                                              ��\n");
	printf("             ��               ��[1]�������˵�                ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[2]���ͼ��                  ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[3]��ѯ                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[4]����                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[5]����                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[6]�޸�����                  ��\n");
	printf("             ��������������������������������������������������\n");
	printf("                               ��ѡ��:");
	fflush(stdin);
	head=create();
	scanf("%d",&choice);
	if(choice==1)
	{ 
		denglu=-1; 
		system("cls");
		printf("\n\n\n\t\t�����˳���¼��\n\n\n\n");
		system("pause");
		main();
	}
	else if(choice==2)
	{
		system("cls");
		if(head==NULL)
	    {
			printf("û��ͼ��!\n");
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
			printf("û��ͼ��!\n");
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
			printf("û��ͼ��!\n");
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
		printf("ѧ����Ϣ�����!!\n");
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
		printf("           ����������������  ��лʹ��ͼ�����ϵͳ  ����������������\n\n\n");
		exit(0);
	}
	else
	{
		system("cls");
		printf("\n\n\n\n             �������� ����������������룡��������      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ����������������  ��������̫�࣬�Զ��˳�! ����������������\n\n\n");
			printf("           ����������������  ��лʹ��ͼ�����ϵͳ  ����������������\n\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
//--------------------
void gfind()/*����Ա��ѯ������Ա�ɰ�һ���ķ�ʽ��ѯͼ�飩*/
{
	int choice,n=0;
	struct tushu *head;
there:
	system("cls");
	printf("             ��������������������������������������������������\n");
	printf("             ��  ��             ͼ�����ϵͳ             ��  ��\n");
	printf("             ��  ������������������������������������������  ��\n");
	printf("             ��               ��[0]����                      ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[1]����������                ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[2]�����߲���                ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[3]��������                ��\n");
	printf("             ��������������������������������������������������\n");
	printf("                               ��ѡ��:");
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
		printf("\n\n\n\n             �������� ����������������룡��������      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ����������������  ��������̫�࣬�Զ��˳�! ����������������\n\n\n");
			printf("           ����������������  ��лʹ��ͼ�����ϵͳ  ����������������\n\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
//---------------------
void xfind() /*ѧ����ѯ��ѧ���ɰ�һ���ķ�ʽ��ѯͼ�飩*/
{
	struct tushu *head;
	int choice,n=0;
there:
	system("cls");
	printf("             ��������������������������������������������������\n");  
	printf("             ��  ��            ͼ�����ϵͳ              ��  ��\n");
	printf("             ��  ������������������������������������������  ��\n");
	printf("             ��               ��[0]����                      ��\n"); 
	printf("             ��                                              ��\n");
	printf("             ��               ��[1]����������                ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[2]�����߲���                ��\n");
	printf("             ��                                              ��\n");
	printf("             ��               ��[3]��������                ��\n");
	printf("             ��������������������������������������������������\n");
	printf("                               ��ѡ��:");
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
		printf("\n\n\n\n             �������� ����������������룡��������      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ����������������  ��������̫�࣬�Զ��˳�! ����������������\n\n\n");
			printf("           ����������������  ��лʹ��ͼ�����ϵͳ  ����������������\n\n\n");
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
	printf("             ��������������������������������������������������\n");  
	printf("             ��  ��          ͼ�����ϵͳ                ��  ��\n");
	printf("             ��  ������������������������������������������  ��\n");
    printf("             ��               ��[0]����                      ��\n"); 
    printf("             ��                                              ��\n");
    printf("             ��               ��[1]��ʱ������                ��\n");
    printf("             ��                                              ��\n");
    printf("             ��               ��[2]���۸�����                ��\n");
    printf("             ��                                              ��\n");
    printf("             ��               ��[3]���������                ��\n");
    printf("             ��������������������������������������������������\n");
    printf("                               ��ѡ��:");
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
		printf("\n\n\n\n             �������� ����������������룡��������      \n\n\n ");
		system("pause");
		system("cls");
		n++;
		if(n==3)
		{
			printf(" \n\n\n          ����������������  ��������̫�࣬�Զ��˳�! ����������������\n\n\n");
			printf("           ����������������  ��лʹ��ͼ�����ϵͳ  ����������������\n\n\n");
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
		printf("�������š���Ҫ����ͼ����Ϣ¼�룬������'#'��\n");
		scanf("%s",p1->num);
		if(strcmp(p1->num,"#")==0)
			i=1;
		while(i!=1)
		{
			printf("�������������� ���� ������ ��� ������� �۸�:\n");
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
	printf("\n\n\n\t\t\tͼ����Ϣ���������\n\n\n");
	system("pause");
    system("cls");
	printf("\n\n\n\t\t\t�Ƿ񱣴�ͼ����Ϣ����1.��/2.�񣩣�");
	scanf("%d",&x); 
	if(x==1) 
		fprint(head);
	else
	{
	 system("cls");
		printf("\n\n\n\t\t\t �ļ�û�б����棡\n\n\n\n");
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
		printf("û��ͼ�鱣�棡\n");
		system("pause");
		system("cls");
		menu();
	}
	for(p1=head;p1!=NULL;p1=p1->next) /*����*/
		fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*��ͼ����Ϣд���ļ�*/ 
	fclose(fp);
	system("cls");
	printf("\n ͼ����Ϣ�ѳɹ����浽�ļ�tushu_list.txt �У�\n");
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
	printf("�������㱣����ļ���\n");
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
	 printf("û��ͼ�飡\n");
	 system("pause");
	 system("cls");
	 menu();
 }	
 for(p1=head;p1!=NULL;p1=p1->next)
	 fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*��ͼ����Ϣд���ļ�*/
 fclose(fp);
 system("cls");
 printf("\n ͼ����Ϣ�ѳɹ����浽�ļ� %s �У�\n",a);
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
		printf("û�л��飡\n");
		xmenu();
	}
	for(p1=head;p1!=NULL;p1=p1->next) /*����*/
		fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*��ͼ����Ϣд���ļ�*/ 
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
		fprintf(fp,"%-10s  %-30s  %-20s  %-20s  %-20s  %.0lf    %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price );/*��ͼ����Ϣд���ļ�*/
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
	if((fp=fopen("tushu_list.txt","r"))==NULL)/*�Ȱ�ȫ��Ŀ¼�ļ�*/ 
	{
		printf("File open error!\n");
		system("pause");
		exit(0); 
	}
	while(!feof(fp))/*��ȡ����������*/ 
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
	 printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
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
	 printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	 for(p1=head;p1!=NULL;p1=p1->next)
	 {
         printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p1->num,p1->name,p1->writer,p1->press,p1->kind,p1->time,p1->price);
	 }
	 system("pause");
	 system("cls");
	 xmenu();
 }
//-----------------------------
 void count(struct tushu *head) /*ͳ��ͼ����Ŀ*/
 {
	 int n=0;
	 struct tushu *p1; 
	 for(p1=head;p1!=NULL;p1=p1->next)
		 n++;
	 printf("\n��ϵͳͳ�����ڵ�ͼ�鹲�� %d �ᡣ\n",n);/*���㲢�� ��ͼ����Ŀ*/ 
	 system("pause");
	 system("cls");
	 menu();
}
//----------------------------
void Findofname(struct tushu *head) /*��������ѯͼ��*/ 
{ 
	int i=0,n;
	char b[31];
	struct tushu *p;
	p=head;
	printf("\n������Ҫ��ѯ��ͼ�����ƣ�");
	scanf("%s",b);
	while(p!=NULL)
	{
		if(strcmp(p->name,b)==0)
		{ 
	        printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	 		printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			i++;
		}
		p=p->next;
	}
	if(i==0) 
	{
		system("cls");
		printf("\n �Բ���û���ҵ���Ϊ��%s����ͼ�飡\n",b);
	    system("pause");
	}
	printf("\n\n\n\t\t\t�Ƿ��������ͼ����Ϣ����1.��/����.���أ���");
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
	 printf("\n������Ҫ��ѯ��ͼ������������");
	 scanf("%s",b);
	 while(p!=NULL)
	 { 
		 if(strcmp(p->writer,b)==0)
		 {
			 printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			 i++;
		 }
		 p=p->next;
	 }
	 if(i==0)
	 {
		 system("cls");
		 printf("\n �Բ���û���ҵ�' %s '���������ͼ�飡\n",b);
		 system("pause");
	 }
	 printf("\n\n\n\t\t\t�Ƿ��������ͼ����Ϣ����1.��/����.���أ���");
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
	 printf("\n��������Ҫ��ѯ��ͼ�����");
	 scanf("%s",b); 
	 while(p!=NULL)
	 {
		 if(strcmp(p->kind,b)==0)
		 {
			 printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price); 
			 i++;
		 } 
		 p=p->next; 
	 }
	 if(i==0)
	 {
		system("cls");
		printf("\n �Բ���û���ҵ����Ϊ' %s '��ͼ�飡\n",b);
		system("pause");
	}
	 printf("\n\n\n\t\t\t�Ƿ��������ͼ����Ϣ����1.��/����.���أ���");
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
 void xFindofname(struct tushu *head) /*��������ѯͼ��*/ 
 { 
	 int i=0,n;
	 char b[31];
	 struct tushu *p;
	 p=head;
	 printf("\n������Ҫ��ѯ��ͼ�����ƣ�");
	 scanf("%s",b);
	 while(p!=NULL)
	 {
		 if(strcmp(p->name,b)==0)
		 { 
			 printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			 i++;
		 }
		 p=p->next; 
	 }
	 if(i==0) 
	 {
		 system("cls");
		 printf("\n �Բ���û���ҵ���Ϊ��%s����ͼ�飡\n",b);
		 system("pause");
	 }
	 printf("\n\n\n\t\t\t�Ƿ��������ͼ����Ϣ����1.��/����.���أ���");
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
	 printf("\n������Ҫ��ѯ��ͼ������������");
	 scanf("%s",b);
	 while(p!=NULL)
	 { 
		 if(strcmp(p->writer,b)==0)
		 {
			 printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	 		 printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			 i++;
		 }
		 p=p->next;
	 }
	 if(i==0)
		 system("cls");
	 printf("\n �Բ���û���ҵ�' %s '���������ͼ�飡\n",b);
	 system("pause");
	 printf("\n\n\n\t\t\t�Ƿ��������ͼ����Ϣ����1.��/����.���أ���");
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
	printf("\n��������Ҫ��ѯ��ͼ�����");
	scanf("%s",b); 
	while(p!=NULL)
	{
		if(strcmp(p->kind,b)==0)
		{
			printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	 		printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p->num,p->name,p->writer,p->press,p->kind,p->time,p->price);
			i++;
		} 
		p=p->next;
	}
	if(i==0)
		system("cls");
		printf("\n �Բ���û���ҵ����Ϊ' %s '��ͼ�飡\n",b);
		system("pause");
		printf("\n\n\n\t\t\t�Ƿ��������ͼ����Ϣ����1.��/����.���أ���");
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
	printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	for(p5=p1;p5!=NULL;p5=p5->next)  
	printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p5->num,p5->name,p5->writer,p5->press,p5->kind,p5->time,p5->price);
	system("pause");
	system("cls");
	printf("\n\n\n\t\t\t�Ƿ񱣴�ͼ����Ϣ����1.��/2.��(����)����");
	scanf("%d",&x); 
	if(x==1)
		fprint_(p1);
	else
		system("cls");
	printf("\n\n\n\t\t\t û�б����浽�ļ���\n\n\n\n");
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
	printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	for(p5=p1;p5!=NULL;p5=p5->next)  
	printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p5->num,p5->name,p5->writer,p5->press,p5->kind,p5->time,p5->price);
	system("pause");
	system("cls");
	printf("\n\n\n\t\t\t�Ƿ񱣴�ͼ����Ϣ����1.��/2.��(����)����");
	scanf("%d",&x); 
	if(x==1)
		fprint_(p1);
	else
		system("cls");
	printf("\n\n\n\t\t\t û�б����浽�ļ���\n\n\n\n");
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
	//��������дӴ�С����������ð�ݷ���
	//p1ʹ֮����ָ��ͷ��㣬p4ʹ֮����ָ��������õ���ǰ��Ľ��
	//p3��Ϊ�н飬����p2����һ�����
	{
		for(p2=p1;p2->next!=p4;)
		{
			if(strcmp(p2->num,p2->next->num)>0)//p2��ֵ����p2->next��ֵ������			
			{
				if(p2==p1)//ͷ���Ҫ����
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
			else//����Ҫ��������p2��p3ǰ��1λ
			{
				p3=p2;
				p2=p2->next;
			}
		}
		p4=p2;
	}
	printf("���        ����                            ����                  ������                ���                  ����ʱ��    �۸�\n");
	for(p5=p1;p5!=NULL;p5=p5->next)  
	printf("%-10s  %-30s  %-20s  %-20s  %-20s  %-10.0lf  %.2lf\n", p5->num,p5->name,p5->writer,p5->press,p5->kind,p5->time,p5->price);
	system("pause");
	system("cls");
	printf("\n\n\n\t\t\t�Ƿ񱣴�ͼ����Ϣ����1.��/2.��(����)����");
	scanf("%d",&x); 
	if(x==1)
		fprint_(p1);
	else
		system("cls");
	printf("\n\n\n\t\t\t û�б����浽�ļ���\n\n\n\n");
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
		printf("ɾ���ɹ���\n");
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
		printf("����ͼ����Ϣ��\n"); 
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
		printf("û��ɾ����Ҫɾ����ͼ�飡\n");
		system("pause");
		system("cls");
		menu();
		return;
	}
	else
		printf("\n ���Ϊ' %s 'Ŀ��ͼ���ѱ�ɾ�������������ļ���\n",m); 
	printf("\n\n\n\t\t\t�Ƿ񱣴�ͼ����Ϣ����1.��/2.��(����)����");
	scanf("%d",&x); 
	if(x==1)
		fprint_(head);
	else
		system("cls");
		printf("\n\n\n\t\t\t ��û�б����浽�ļ���\n\n\n\n");
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
	printf("������Ҫ�޸��鱾�ı��:");
	scanf("%s",m);
	while(p!=NULL)
	{
		if(strcmp(p->num,m)==0)
		{
			printf("�������������� ���� ������ ��� ������� �۸�\n");
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
		printf("\n                      ��������  û��ͼ���¼!  ��������\n\n");
		system("pause");
		system("cls");
		menu();
	}
	else	
		printf("\n ���Ϊ' %s 'Ŀ��ͼ���ѱ��޸ģ�\n",m); 
	printf("\n\n\n\t\t\t�Ƿ񱣴�ͼ����Ϣ����1.��/2.��(����)����");
	scanf("%d",&x); 
	if(x==1)
		fprint_(head);
	else
		system("cls");
		printf("\n\n\n\t\t\t û�б����浽�ļ���\n\n\n\n");
		system("pause");
		system("cls");
		menu();
		return;
}
//-------------------------------
void borrow(struct tushu *head)//���� 
{ 
	struct tushu *ptr1,*ptr2;
	struct jieshu *xinxi=NULL;
	char m[11];
	int n=0;
	system("cls");
	printf("������������ͼ��ı��:\n");
	scanf("%s",m);
    if((strcmp(head->num,m)==0)&&head->next==NULL)
	{
		xinxi=borrowcreate(head,xinxi);
		printf("\n\n\n����ɹ���\n\n\n\n");
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
		printf("��ͼ����Ϣ��\n");
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
		printf("��ͼ����Ϣ��\n");
		system("pause");
		system("cls");
		xmenu();
	}
	else
		printf("\n\n\n����ɹ���\n\n\n\n");
	
	system("pause");
	system("cls");
	jsprint(xinxi);
	jfprint_(head);
}
//------------------------------
void huanshu(struct tushu *head)	//��дһ��jsdelete����ɾ��jieshu_list.txt�ļ����ݺ�һ��putin������������д��tushu_list.txt 
{
	system("cls");
	struct jieshu *jsinfo,*p,*p1;
	char booknum[11];
	jsinfo=jcreate();
	if (jsinfo==NULL)
	{
		printf("\n\n\n\t\tû�н����¼���޷����л������!\n\n\n\n");
		system("pause");
		system("cls");
	}
	else
	{
		printf("����������Ҫ������ı�ţ�����ȡ���������������'#':\n");
		scanf("%s",booknum);
		printf("\n\n\n");
		if(strcmp(booknum,"#")==0)
		{
			printf("û�н��л������!\n\n\n");
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
				printf("�������ͼ���������޷����л������!\n\n\n");
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
				printf("����ɹ���\n\n\n");
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
	printf("���������ʺ�(������20���ַ�)����Enter����\n");
	scanf("%s",zhanghao);
	printf("������������(������10���ַ�)����Enter������\n");
	scanf("%s",pa);
	system("cls");
	printf("�Ƿ�ȷ���޸ģ�1��/���������أ���\n");
    scanf("%d",&i);
	if(i==1)
	{
		system("cls");
		printf("�˺ż������޸ĳɹ������μǣ�\n");
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
	printf("��������ʾ���㹲�����������˺�����Ļ��ᣡ\n");
	there:
	printf("������ѧ�ţ���Enter������\n");
	scanf("%d",&zhanghao);
	printf("����������(������10���ַ�)����Enter��������ʼ����Ϊ123456\n");
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
		printf("�������ѧ�Ų����ڻ�����������������룡\n\n");
		system("pause");
		system("cls");
		goto there;
	}
	else
	{
		system("cls");
		printf("�������ѧ�Ų����ڻ��������\n");
		printf("\n\n\n\t\t���Ѵﵽ����������ޣ������Զ��������˵���\n\n\n\n");
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
	printf("���������ԭ����(������10���ַ�)����Enter������\n");
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
			printf("������������(������10���ַ�)��\n");
            scanf("%s",pb);
            printf("���ٴ�����������(������10���ַ�)��\n");
            scanf("%s",pc);
			if(strcmp(pb,pc)==0)
			{

				system("pause");
				system("cls");          
				printf("�Ƿ�ȷ���޸ģ�1��/���������أ���\n");
				scanf("%d",&i);
				if(i==1)
				{
					printf("�����޸ĳɹ������μǣ�\n");
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
					printf("����û���޸ģ�\n");
					xmenu();
				}
			}
			else
			{
				system("cls");
				printf("��������������벻һ�£����������룡\n\n");
				system("pause");
				system("cls");
				printf("�Ƿ�����޸ģ�1��/���������أ���\n");
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
		printf("�����ԭ�������\n");
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
	printf("                     ��ӭ����ͼ�����ϵͳ\n");
	printf("*******************************************************************\n\n\n");
	system("pause");
	system("cls");
	printf("\t    [���ڽ���Ȩ�޺˲�]\n�������ѣ��㹲�����������˺ź�����Ļ��ᣡ\n");
	printf("��ʼ����Ա�˺ź�����ֱ�Ϊguanliyuan,123456\n\n\n\n");
	system("pause");
	system("cls");
there:		
	if(n==2||n==1)
	{
		system("cls");
		printf("ע�⣺�����������%d��,ʣ�����%d\n�������ʺ�(������20���ַ�),��Enter����:\n",3-n,n);
	}
	if(n==3)
		printf("ʣ�����:%d\n�������ʺ�(������20���ַ�)����Enter����:\n",n);
	scanf("%s",zhanghao);
	printf("����������(������10���ַ�),��Enter����:\n");
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
			printf("\n\n�Բ������������������������û��ʹ�ù���Աϵͳ��Ȩ�ޣ�\n�����������˵���\n\n\n");
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
	printf("             ��������������������������������������������������\n");  
	printf("             ��  ��         ��ӭʹ��ͼ�����ϵͳ         ��  ��\n");
	printf("             ��  ������������������������������������������  ��\n");
	printf("             ��                                              ��\n");
	printf("             ��              �����ˣ����                    ��\n");
	printf("             ��                                              ��\n");
	printf("             ��              �������ڣ�2016.12               ��\n");
	printf("             ��                                              ��\n");
	printf("             ��                                              ��\n");
	printf("             ��������������������������������������������������\n");
	printf("��Enter������......\n");
	getchar();
there:
	fflush(stdin);
	system("cls");
	printf("\n\n\n1 :����Ա��½ϵͳ\n\n2 :ѧ����½ϵͳ\n\n0 :�˳�\n\n\n\n");
    printf("��ѡ��:");
	scanf("%d",&i);
	if(i==0)
	{
		system("cls");
		printf("\n\n\n\n*********************************************************************************\n");
		printf("                           ��лʹ��ͼ�����ϵͳ\n");
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
			printf("��û��ѧ����Ϣ��ѧ�����ܵ�¼!\n");
			system("pause");
			system("cls");
			main();
		}
        xsecret(head1);
	}
	else
	{
		printf("\n\n����������������룡\n\n\n");
		system("pause");
		system("cls"); 
		j++;
		if(j==3)
		{
			system("cls");
			printf("\n\n\n*************************************************************************\n\n");
			printf("\n\n\t\t������Ĵ������࣬�Զ��˳���ллʹ�ã�\n\n");
			printf("\n\n*************************************************************************\n\n");
			system("pause");
			exit(0);
		}
		goto there;
	}
}
