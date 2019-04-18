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

//Read out the data of the file to the linked list and return the value as the header address
book ss() {
	FILE *fp;       //The pointer of the file
	int n = 0;
	book head = NULL;
	book p,p2,pr = NULL;
	fp=fopen("mybook", "ab+");     //Open files in a read-only manner
	if(fp == NULL) {
		printf("Error: Cannot find or open file\n");
	}
	while( !feof(fp) ) {       //Determine whether the file location flag moves to the end of the file 
		n++;
		p=(book)malloc( sizeof(struct BOOK) ); //Apply for a space in memory
		fread(p, sizeof(struct BOOK), 1, fp);     //Assign the data of the file (number of data is 1) that fp refers to to to p
		if(n == 1) {
			//When n == 1, p points to the header
			head = p;
			p2 = p;
		} else {
			//Create linked list
			pr = p2;
	    	p2->next = p;
	    	p2 = p;
		}
    }
    if(pr != NULL)
       pr->next = NULL;
    else
       head = NULL;
    fclose(fp);    //Close file and the pointer 
    return head;   //Return header pointer
}

//Write the pointer of p into the file
void save_book(book p) {
	FILE *fp;    //The pointer of the file
	fp = fopen("mybook", "ab");   //Open a binary file named mybook by additional opening file and writing data at the end of the file
	if(fp==NULL)
	{
		printf("Error: Cannot find or open file");
	}
	if(fwrite(p, sizeof(struct BOOK), 1, fp) != 1)   //Store a section of data pointed to by p in the file pointed to by fp
	{
		//If there is no successful write, the return value of fwrite is not 1
		printf("Error: Write error");
	}
	fclose(fp);    //Close file and the pointer   
}


void input_book() {
	system("cls");
	book presentBook;
	presentBook = (book)malloc(sizeof(struct BOOK));     //Using malloc to allocate the memory
	//input the information of the book
	printf("Please input the book number (less than 10 digits)£º");    
	scanf("%s", presentBook->number);getchar();    //-> assigns members of a structure directly through a pointer to the structure, press any key to continue.
	printf("Please input the book name (less than 15 letters)£º");
	scanf("%s", presentBook->name);getchar();
	printf("Please input the author(s) of the book (less than 20 letters)£º");
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
	printf("|  The total number of books is£º%d\n                              |\n",sum);
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


void delete_book() {
	do {
		system("cls");
		FILE *fp;
		book head, p, pre = NULL; 
		int index = 0;
		int choose = 0;
		int x, i = 11;
		char delName[15];
		char delNum[10];
		char q, t, c, ch;
		head = ss();    //Return the header address
		printf("|  ---------------------------------------  |\n");
		printf("|  Select different ways to delete books    |\n");
		printf("|    [1] Delete books by book name          |\n");
		printf("|    [2] Delete books by book number        |\n");
		printf("|  ---------------------------------------  |\n");
		while(1) {
			q = getch();
			if(q == '1') {
				choose = 1;
				break;
			} 
			else if(q == '2') {
				choose = 2;
				break;
			}
		}
		if(choose == 1) {
			system("cls");
			printf("Please enter the name of the book you want to delete: ");
			scanf("%s", delName);
		}
		if(choose == 2) {
			system("cls");
			printf("Please enter the number of the book you want to delete: ");
			scanf("%s", delNum);
		}
		p = head;
		while( p != NULL ) {
			p->x = 0;
			p = p->next;
		}
		p = head;
		printf("|                            Operating Book List                           |\n");
		printf("|  ----------------------------------------------------------------------  |\n");
		printf("|   Index |       Name      |   Number   |        Author        | Status   |\n");
		printf("|  ----------------------------------------------------------------------  |\n");
		while(p != NULL) {
			if(p != NULL && strcmp(p->name, delName) == 0 && choose == 1) {       //strcmp() is a string comparison function
				index++;
				printf("|   %15s   %s   %20s    [%d]    |\n",p->name,p->number,p->author,p->exist);
				p->x = index;
				i++;
			}
			if(p != NULL && strcmp(p->number, delNum) == 0 && choose == 2) {
				index++;
				printf("|   %5d   %15s   %s   %20s    [%d]    |\n",j,p->name,p->number,p->author,p->exist);
				p->x = index;
				i++;
			}
			p = p->next;
		}
		if(index == 0) {       //If index = 0, it does not enter the previous search cycle, which means that it does not find the corresponding information.
			printf("Error: No corresponding information was found.\n");
			printf(Return the main menu by 0 and search by 1)
			while(1) {             //Dead loops are designed to prevent other key interference except 0 and 1.
				ch = getch();
				if(ch == '0') {
					menu();
					break;
				}
				else if(ch == '1')
					break;         //Exit the dead loop
			}
			if(ch == '1')     //If ch equals 1, the search cycle is terminated and a new one is started
			   continue;
		}
		while(1) {
			printf("Please enter the index of the book you want to delete: ");
			scanf("%d", &x);
			getchar();
			if(x > index || x <= 0)
				printf("Error: Input the wrong index, please re-enter!");
			else
				break;
		}
		printf("|  ----------------------------------  |\n");
		printf("|     Confirm to delete this book?     |\n");
		printf("|        [1]Yes        [2]No           |\n");
		printf("|  ----------------------------------  |\n");
		while(1) {
			t = getch();
			if(t == '1')
				break;
			else if(t == '2')
				userface();
		}
		p=head;
		while(p != NULL && p->x != x) {
			pre = p;
			p = p->next;
		}
		if(p != NULL) {
			if(pre == NULL)
				head=head->next;
			else
				pre->next = p->next;
		}
		free(p);
		fp = fopen("mybook","wb");
		if(fp == NULL)
			printf("Error: Cannot find or open file");
		if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
			printf("Error: Write error");
		fclose(fp);
		if(head != NULL) {
			p = head->next;
			fp = fopen("mybook","ab");
			if(fp == NULL)
				printf("Error: Cannot find or open file");
			while(p != NULL)
			{
				if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
					printf("Error: Write error");
				p = p->next;
			}
			fclose(fp);
		}
		system("cls");
		printf("ÕýÔÚÉ¾³ý£¬ÇëÉÔºó....");
		Sleep(500);
		system("cls");
		printf("|  ---------------------------------------------------  |\n");
		printf("|     Delete successfully. Do you want to continue?     |\n");
		printf("|               [1]Yes             [2]No                |\n");
		printf("|  ---------------------------------------------------  |\n");
		while(1) {
			c=getch();
			if(c == '1')
				break;
			else if(c == '2')
				userface();
		}
	}while(1);
}


void register_identity() {
};


void borrow_book() {
	
	
};


