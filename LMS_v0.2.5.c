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

struct STUDENT{
	char number[10];		//Student's identity number. The student use the number to sign in.
	char password[20];		//The password of the identity. The student use the number to sign in.
	char name[15];			//Student's name
	int identity;			//The type of the identity. [0]Guest(cannot borrow books) [1]student(can borrow and return books) [2]librarian(can manage books and students' information)
	char boo_number[10];	//If the student borrows a book, it is the number of the book that be borrowed by the student.
	struct BOOK *firstBook; //The point of the first book a student can borrow
	struct BOOK *secondBook; //The point of the second book a student can borrow
	struct BOOK *thirdBook; //The point of the third book a student can borrow
	struct STUDENT *next;	//The point of the next student
};
typedef struct STUDENT Student;
typedef Student *student;

//Created functions
void userface();
void input_book();
void book_access();
void student_access();
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
					exit();
					break;
				case '2':
					userface();
					break;
				default:
					printf("Sorry, please enter the correct number.\n");
					printf("Press any key to return to the main interface of the system.\n");
					getch();  //Press any key to continue
					userface();
			}
			break;
		default:
			printf("Sorry, please enter the correct number.\n");
			printf("Press any key to return to the main interface of the system.\n");
			getch();
			userface();
	}
	return 0;
};

void input_book() {
	system("cls");
	book presentBook;
	p=(book)malloc(sizeof(struct BOOK));     //Using malloc to allocate the memory
	//input the information of the book
	printf("Please input the book number (less than 10 digits)£º");    
	scanf("%s",presentBook->number);getchar();
	printf("Please input the book name (less than 15 letters)£º");
	scanf("%s",presentBook->name);getchar();
	printf("Please input the author(s) of the book (less than 20 letters)£º");
	scanf("%s",presentBook->author);getchar();
	printf("Please input the status of this book([1]In the library [2]Be loaned out [3]Be damaged): ");
	scanf("%d",&presentBook->exist);
	printf("|  ------------------------------------  |\n");
	printf("|                                        |\n");
	printf("| Please confirm whether to save or not? |\n");
	printf("|       [1] Yes            [2] NO        |\n");
	printf("|                                        |\n");
	printf("|  ------------------------------------  |\n");
	while(1) {
		char t = getch();
		if(c == '1') {
			save_book(presentBook);
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
				 	//mgfhfhd();
			}while(1);
		}
		else if(c == '2')
			break;
	}while(1);
};






void book_access() {
	system("cls");    //Clean the screen
	printf("|                        Book List                       |\n");
	printf("|  ----------------------------------------------------  |\n");
	printf("|       Name      |   Number   |    author    |  status  |\n");
	printf("|  ----------------------------------------------------  |\n");
	
};






