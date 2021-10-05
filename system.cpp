#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#define SIZE 10
typedef struct Order{
	int Table_ID;
	int Dish_ID[10];
	int Dish_Num;
	struct Order *nextPtr;
}ORDER;
typedef struct Table{
	int Table_ID;//桌子编号
	int Capacity;//餐桌最多能容纳的人数
	int Table_State;//1.有人在用 0.无人在用
}TABLE;
typedef struct Dish {
	int Dish_ID;  //菜的编号
	char Dish_Name[30];  //菜名
	float Dish_Price;  //价格
}DISH;
//struct


TABLE table_menu[5] = {{1,4,0},{2,5,0},{3,6,0},{4,7,0},{5,8,0}};//桌子信息
DISH DishMenu[10] = {{ 1, "葱花炒鸡蛋", 4.000000 },{ 2, "红烧鲤鱼", 66.000000 },{ 3, "麻辣豆腐", 4.000000 },
                         { 4, "东坡肘子", 33.000000 },{ 5, "北京烤鸭", 108.000000 },{ 6, "鲤鱼跃龙门", 666.000000 },
                         { 7, "南京叫花鸡", 77.000000 },{ 8, "白菜炖粉条", 10.000000 },{ 9, "四喜丸子", 88.000000 },
                         { 10, "羊肉泡馍", 20.000000 }};//菜品单信息
int GLOBAL = 1;
//初始化
//global variables

int Highpopular(int dishpopular[], size_t size);
int Pass_Word(int ke);//密码验证
void List_Management(int key);//同上
void ListMenu(void);//账目管理界面打印
void Dish_Menu(void);//菜品单界面打印
void CreateBill(ORDER** headPtrPtr,int tableNum,int a[],int dishNum);//创建节点并插入链表
ORDER *search(ORDER** headPtrPtr,int choice);//按桌号查找节点
void deleted(ORDER** headPtrPtr,ORDER** aPtr);//删除节点
//function declare


int main(void){
	system("color f4");
	ORDER *headPtr=NULL;
	int i,j;//counter
	//一些指针和计数器的声明
	while(1){
		puts("*********************");
		puts("    餐厅服务系统");
		puts("*********************");
		puts("1.点菜");
		puts("2.客户结账");
		puts("3.账目管理");
		puts("4.餐馆统计");
		puts("5.退出");
		int choice;
		puts("请选择：");
		scanf("%d", &choice);//主菜单界面打印


		switch(choice){
			case 1:{
				printf("请输入来客数量（1-8）\n");
				int num;//来就餐的人数
				scanf("%d",&num);
				while(num <=0 || num >= 9){
					printf("输入错误，请重试：\n");
					scanf("%d",&num);
				}
				int i;//counter
				int tableNum;
				for(i = 0;i< 5;i++){
					if(num<= table_menu[i].Capacity && table_menu[i].Table_State == 0){
						printf("您和您的朋友可以到%d号桌用餐\n",i+1);
						tableNum=i+1;//tableNum
						table_menu[i].Table_State = 1;
						break;
					}
				}//桌号分配


				Dish_Menu();//菜品单界面打印

				FILE * cfPtr;
           		 if((cfPtr = fopen("client.txt", "a")) == NULL){
              		  puts("File couldn't be opened");
            	}
				else{


				int choice = -1;
				int a[10]={0};
				int dishNum=0;
			    for(i=0;choice != 0;i++){
			        printf("请输入菜的编号，按0结束输入:");
			        scanf("%d", &choice);
			        if(choice < 0 || choice > 10){
			            printf("输入错误，请重新输入！\n");
			        }
			        if(choice == 0){
			        	break;
					}
			        if(choice >= 0 && choice <= 10){
			        	fprintf(cfPtr, "%d ", DishMenu[choice - 1].Dish_ID);
			            a[i]=choice;
			            dishNum++;
			        }
			    }//点菜

				CreateBill(&headPtr,tableNum,a,dishNum);//创建节点并插入链表
				fclose(cfPtr);
				}
				break;
			}
			case 2:{
				printf("请输入需结账的餐桌号(1-5)\n");
				int choice;
				scanf("%d",&choice);
				ORDER *aPtr;
				aPtr=search(&headPtr,choice);//按桌号查找节点
				if(!aPtr){
					break;
				}
				int total=0;

				printf("编号			菜名			价格\n");
				for(i=0;i<=9;i++){
					for(j=0;j<=9;j++){
						if(aPtr->Dish_ID[i]==DishMenu[j].Dish_ID){
						printf("%d			%s			%f",DishMenu[j].Dish_ID,DishMenu[j].Dish_Name,DishMenu[j].Dish_Price);
						printf("\n");
						total=total+DishMenu[j].Dish_Price;
						}
					}
				}
				printf("您一共点了%d道菜\n",aPtr->Dish_Num);
				printf("共计%d元\n",total);
				printf("请交款\n");
				float money,change;
				int judge=0;
				while(judge==0){
					scanf("%f",&money);
					if(money>=total){
						change=money-total;
						printf("找您%.6f元\n",change);
						judge=1;
						FILE * CFptr;
						time_t timer;
						timer = time(NULL);
           				if((CFptr = fopen("accountbook.txt", "a")) == NULL){
              				  puts("File couldn't be opened");
            			}
						else{
							fprintf(CFptr, "%d\t%s\n", total, ctime(&timer));
						}
						fclose(CFptr);
					}
					else{
						printf("听说宁想吃霸王餐？\n");
					}
				}

				//打印账单

				deleted(&headPtr,&aPtr);//删除节点
				table_menu[choice-1].Table_State = 0;//桌子初始化
				break;
			}
			case 3:{
				int mima ;
				FILE *fpp;
				if((fpp = fopen("keyword.txt","r")) ==NULL){
					fclose(fpp);
					fopen("keyword.txt", "w");
					fpp = fopen("keyword.txt", "w");
					fprintf(fpp, "%d", 123456);
				}
				else{
					fscanf(fpp,"%d",&mima);
				}
				fclose(fpp);
				List_Management(mima);
				if(GLOBAL == 2){
					break;
				}
				if(GLOBAL == 1){

					int CHOICE;
					scanf("%d",&CHOICE);
					while (CHOICE != 3){
						if(CHOICE == 1){
							int newmima;
							printf("请输入新的密码\n");
							scanf("%d",&newmima);
							FILE *fppp;
							if((fppp = fopen("keyword.txt","w")) ==NULL){
								puts("无法打开文件\n");
							}
							else{
								fprintf(fppp,"%d",newmima);
							}
							fclose(fppp);
							system("pause");
							break;
						}
						if(CHOICE == 2){
							printf("欢迎来到账目管理系统,您的帐单如下\n");
							puts("消费金额\t消费时间\n");
							FILE * cfPTR;
							char str[25];
							int i = 0, j = 0;
							int pay;
	           				if((cfPTR = fopen("accountbook.txt", "r")) == NULL){
	              		  		puts("File couldn't be opened");
	            			}
							else{
								fscanf(cfPTR, "%d", &pay);
								while(!feof(cfPTR)){
									i = 0;
									j = 0;
									fscanf(cfPTR, "%d\n", &pay);
									while(i <= 5 && j < 25){
										fscanf(cfPTR, "%c", &str[j]);
										j++;
										if(str[j] == ' '){
											i++;
										}
									}
									fscanf(cfPTR, "\n\n");
									i = 0;
									j = 0;
									printf("%d\t", pay);
									while(i <= 5 && j < 25){
										printf("%c", str[j]);
										j++;
										if(str[j] == ' '){
											i++;
										}
									}
									printf("\n");
								}
								break;
							}
							fclose(cfPTR);
							break;
						}
						if(CHOICE == 3){
							system("pause");
							exit(0);
							printf("已退出账目管理系统\n");
						}
					}
				}
				break;
			}
			case 4:{
				FILE * CFPTR;
        	int num, k, l;
        	int dishpopular[10] = {0};
           	if((CFPTR = fopen("client.txt", "r")) == NULL){
           		 puts("File couldn't be opened");
          	}
         	else{
			 	fscanf(CFPTR, "%d", &num);
            	while(!feof(CFPTR)){
            		dishpopular[num - 1]++;
            		fscanf(CFPTR, "%d", &num);
            	}
            	fclose(CFPTR);
            	puts("菜的受欢迎程度如下：\n");
				for(k = 1; k <= 10; k++){
					printf("%d菜：", k);
					for(l = 0; l < dishpopular[k- 1]; l++){
						printf("* ");
					}
					printf("\n");
          		}
          		printf("比较受欢迎的四个菜是：\n");
          		int temp, k;
          		for(k = 1; k < 5; k++){
					temp = Highpopular(dishpopular, SIZE);
					printf("%s\n", DishMenu[temp].Dish_Name);
					dishpopular[temp] = 0;
				}
				fclose(CFPTR);
			}

			break;
			}
			case 5:{
				system("pause");
				exit(0)5;
				break;
			}
			default:
		 	printf("输入错误，请重新输入！\n");
		 	system("pause");
			break;
		}
		system("pause");//返回主菜单
		system("cls");//清屏
	}
	system("pause");
	return 0;
}
//main function


void Dish_Menu(void)
{
    int i;
	printf("**********欢迎选购本店菜************\n");
	puts("菜编号	菜名		菜单价");
	for (i = 0; i < 10; i++) {
        printf("%d\t%s\t%f\n", DishMenu[i].Dish_ID, DishMenu[i].Dish_Name, DishMenu[i].Dish_Price);
    }
}
//菜品单打印函数

void CreateBill(ORDER** headPtrPtr,int tableNum,int a[],int dishNum){
	ORDER *Ptr=(ORDER*)malloc(sizeof(ORDER));
	Ptr->Table_ID=tableNum;
	Ptr->nextPtr=NULL;
	Ptr->Dish_Num=dishNum;
	int i;
	for(i=0;i<=dishNum-1;i++){
		Ptr->Dish_ID[i]=a[i];
	}

	ORDER *lastPtr= *headPtrPtr;
	if(lastPtr){
		while(lastPtr->nextPtr){
			lastPtr=lastPtr->nextPtr;
		}
		lastPtr->nextPtr=Ptr;
	}
	else{
		*headPtrPtr=Ptr;
	}

}
//订单节点创建函数（链表插入）

ORDER *search(ORDER** headPtrPtr,int choice){
	ORDER *Ptr = NULL;
	int a=0,i;
	for(Ptr= *headPtrPtr;Ptr;Ptr=Ptr->nextPtr){
		if(Ptr->Table_ID==choice){
			a=1;
			break;
		}
	}
	if(!a){
		printf("NOT FOUND 404\n");
	}
	return Ptr;
}//按桌号查找节点

void ListMenu(void){
	puts("***************************");
	puts("   欢迎进入账目管理系统    ");
	puts("***************************");
	puts("1.修改密码");
	puts("2.查看账本");
	puts("3.返回");
	puts("请选择:");
}

int Pass_Word(int key){
	int a;
	scanf("%d",&a);
	if(a == key){
		return 1;
	}
	else{
		return 0;
	}
}

void List_Management(int key){
	printf("请输入密码（初始密码为123456）\n");
	int b;
	b = Pass_Word(key);
	if(b == 1){
		ListMenu();
		GLOBAL = 1;
	}
	if(b != 1){
		printf("输入错误，请重新输入，您还有两次机会：\n");
		Pass_Word(key);
		if(b == 1){
			ListMenu();
		}
		if(b != 1){
			printf("输入错误，请重新输入，您还有一次机会：\n");
			Pass_Word(key);
			if(b == 1){
				ListMenu();
			}
			if(b != 1){
				printf("输入错误，即将返回！");
				GLOBAL = 2;
				return;
			}
		}
	}
	return;
}

int Highpopular(int dishpopular[], size_t size){
	int i, max;
	max = 0;
	for(i = 0; i < 9; ++i){
		if(dishpopular[i] < dishpopular[i + 1]){
			max = i + 1;
		}
	}
	return max;
}

void deleted(ORDER** headPtrPtr,ORDER** aPtrPtr){
	ORDER *Ptr,*lastPtr;
	int a=0;
	for(Ptr= *headPtrPtr,lastPtr=NULL;Ptr;lastPtr=Ptr,Ptr=Ptr->nextPtr){
		if(Ptr== *aPtrPtr){
			if(lastPtr){
			lastPtr->nextPtr=Ptr->nextPtr;
			free(Ptr);
			a=1;
			break;
			}
			else{
				*headPtrPtr=Ptr->nextPtr;
				free(Ptr);
				a=1;
				break;
			}
		}
	}
}//删除节点
