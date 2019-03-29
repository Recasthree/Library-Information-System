#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N sizeof(struct BOOK)

//The Structure of Student Information and Book Information
struct BOOK{
	char number[10];		//Book number
	char name[15];			//Book name
	char author[20];		//The author(s) of the book
//	char time[10];			//The publication time of the book
//	int type;				//The type of books. The different books have different types.
	int exist;				//The status of this book. [1]In the library [2]Be loaned out [3]Be damaged
	char stu_number[10];	//If the book is borrowed, it is the identity number of the student who borrow the book.
	struct BOOK *next;		//The point of the next book
};
typedef struct BOOK Book;
typedef Book *book;

int identity = 0;			//The type of the identity. [0]Guest(cannot borrow books) [1]student(can borrow and return books) [2]librarian(can manage books and students' information)
struct STUDENT{
	char number[10];		//Student's identity number. The student use the number to sign in.
	char password[20];		//The password of the identity. The student use the number to sign in.
	char name[15];			//Student's namechar boo_number[10];	//If the student borrows a book, it is the number of the book that be borrowed by the student.
	struct BOOK *firstBook; //The point of the first book a student can borrow
	struct BOOK *secondBook; //The point of the second book a student can borrow
	struct BOOK *thirdBook; //The point of the third book a student can borrow
	struct STUDENT *next;	//The point of the next student
};
typedef struct STUDENT Student;
typedef Student *student;

//Created functions
void userface();
void save_book();
void input_book();
void delete_book();
void find_book();
book ss();
void book_access();
void register_identity();
void borrow_book();
void return_book();
void student_access();
void student_list();
void librarian_access();




void userface(){
	system("cls");    //Clean the screen
	printf("|     Library Information System     |\n");
	printf("|  --------------------------------  |\n");
	printf("|         [1] Book Access            |\n");
	printf("|         [2] Student Access         |\n");
	printf("|         [3] Librarian Access       |\n");
	printf("|         [4] Exit System            |\n");
	printf("|  --------------------------------  |\n");
	printf("Welcome to use Library Information System, you can enter the corresponding number of accesses into the subsystems.\n");
	printf("PS1: If you don't have the student identity, you can't borrow or return the books, only read the book list.\n");
	printf("PS2: You can register as a student through the Student Access.\n");
	char t = getch();    //It will not display the number on the screen.
	switch(t)
	{
		case '1':
			book_access();
			break;
		case '2':
			student_access();
			break;
		case '3':
			librarian_access();
			break;
		case '4':
			system("cls");	
			printf("|  ---------------------------------------  |\n");
			printf("|                                           |\n");
			printf("| Are you sure you want to exit the system? |\n");
			printf("|       [1] Yes              [2] NO         |\n");
			printf("|                                           |\n");
			printf("|  ---------------------------------------  |\n");
			char e = getch();
			switch(e)
			{
				case '1':
					exit(0);
					break;
				case '2':
					userface();
					break;
				default:
					printf("[Error] Sorry, please enter the correct number.\n");
					printf("[Press any key to return the main userface]\n");
					getch();  //Press any key to continue
					userface();
			}
			break;
		default:
			printf("[Error] Sorry, please enter the correct number.\n");
			printf("[Press any key to return the main userface]\n");
			getch();
			userface();
	}
};

//将文件中的内容读出到链表中，返回值为表头地址 
book ss() {
	FILE *fp;       //文件指针 
	int n=0;
	book head=NULL;
	book p2,p,pr=NULL;
	fp=fopen("mybook","ab+");     //以只读的方式打开文件 
	if(fp==NULL)
	{
		printf("cannot open file\n");
	}
	while(!feof(fp))        //判断文件位置标志是否移动到文件末尾 
	{
	   n++;
	   	p=(book)malloc(N); //向内存申请一段空间 
	   fread(p,N,1,fp);     //将fp所指向的文件中的内容赋给p 
	   if(n==1)
	   {
	      head=p;
	      p2=p;
	    }
	    else             //创建链表 
	    {
	    	pr=p2;
	    	p2->next=p;
	    	p2=p;
		}
    }
    if(pr!=NULL)
       pr->next=NULL;
    else
       head=NULL;
    fclose(fp);    //关闭文件 
    return head;   //返回头指针 
}

//将p中内容写入文件 
void save_book(book p) {
	FILE *fp;    //文件指针 
	fp=fopen("mybook","ab");   //以追加的方式打开名字为mybook的二进制文件 
	if(fp==NULL)
	{
		printf("cannot open file");
	}
	if(fwrite(p,N,1,fp)!=1)   //将p所指向的一段大小为N的内容存入fp所指向的文件中 
	{
		printf("write error");
	}
	fclose(fp);    //关闭文件  
}


void input_book() {
	system("cls");
	book presentBook;
	presentBook = (book)malloc(sizeof(struct BOOK));     //Using malloc to allocate the memory
	//input the information of the book
	printf("Please input the book number (less than 10 digits)：");    
	scanf("%s", presentBook->number);getchar();    //-> assigns members of a structure directly through a pointer to the structure, press any key to continue.
	printf("Please input the book name (less than 15 letters)：");
	scanf("%s", presentBook->name);getchar();
	printf("Please input the author(s) of the book (less than 20 letters)：");
	scanf("%s", presentBook->author);getchar();
	printf("Please input the status of this book([1]In the library [2]Be loaned out [3]Be damaged): ");
	scanf("%d", &presentBook->exist);
	printf("|  ------------------------------------  |\n");
	printf("|                                        |\n");
	printf("| Please confirm whether to save or not? |\n");
	printf("|       [1] Yes            [2] NO        |\n");
	printf("|                                        |\n");
	printf("|  ------------------------------------  |\n");
	while(1) {
		char c = getch();
		if(c == '1') {
			save_book(presentBook);    //Store book information in files
			system("cls");
			printf("Saving....");
			Sleep(500); 
			printf("|  -----------------------------------------  |\n");
			printf("|                                             |\n");
			printf("| Save successfully! Do you want to continue? |\n");
			printf("|         [1] Yes             [2] NO          |\n");
			printf("|                                             |\n");
			printf("|  -----------------------------------------  |\n");
			while(1) {
			char t = getch();
				if(t == '1')
					break;
				else if(t == '2')
				 	userface();
			}while(1);
		}
		else if(c == '2')
			break;
	}while(1);
};


void book_access() {
	system("cls");    //Clean the screen
	book head,p;
	int i = 11;
	int sum = 0;
	head = ss();
	if(head == NULL)
	{
		printf("\n\nSorry, there are no books in the library for the time being. \n");
		printf("Let's go and remind the librarian to add some. \n");
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	printf("|                             Book List                            |\n");
	printf("|  --------------------------------------------------------------  |\n");
	printf("|                               TIPS:                              |\n");
	printf("|  (1) If you encounter a favorite book that has not been lent     |\n");
	printf("|  out, you can write down the number of the book and borrow it    |\n");
	printf("|  at the Student Access (each student can borrow up to three      |\n");
	printf("|  books at the same time).                                        |\n");
	printf("|  (2) Status attributes represent the status of this book.        |\n");
	printf("|      [1]In the library  [2]Be loaned out  [3]Be damaged          |\n");
	printf("|  --------------------------------------------------------------  |\n");
	printf("|         Name      |   Number   |        Author        | Status   |\n");
	printf("|  --------------------------------------------------------------  |\n");
	p = head;
	while(p != NULL)
	{
		printf("|   %15s   %s   %20s    [%d]    |\n",p->name,p->number,p->author,p->exist);
		i++;
		sum++;  //Calculating the total amount of books
		p = p->next;
	}
	printf("|  --------------------------------------------------------------  |\n");
	printf("|  The total number of books is：%d\n                              |\n",sum);
	printf("|  Press the following key to go directly to the corresponding     |\n");
	printf("|  interface.                                                      |\n");
	printf("|    [0] Return to the main interface                              |\n");
	printf("|    [1] Borrow books                                              |\n");
	printf("|    [2] Borrow books                                              |\n");
	printf("|    [3] Return books                                              |\n");
	printf("|    [4] Management books (librarian status only)                  |\n");
	printf("|  --------------------------------------------------------------  |\n");
	char e = getch();
	switch(e)
	{
		case '0':
			userface();
			break;
		case '1':
			find_book();
			break;
		case '2':
			borrow_book();
			break;
		case '3':
			return_book();
			break;
		case '4':
			librarian_access();
			break;
		default:
			printf("[Error] Sorry, please enter the correct number.\n");
			printf("[Press any key to return]\n");
			getch();
			book_access();
	}
};






