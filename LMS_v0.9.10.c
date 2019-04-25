#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//The Structure of Student Information and Book Information
struct BOOK{
	char number[10];		//Book number
	char name[15];			//Book name
	char author[20];		//The author(s) of the book
	int exist;				//The status of this book. [1]In the library [2]Be loaned out [3]Be damaged
	char stu_number[10];	//If the book is borrowed, it is the identity number of the student who borrow the book.
	int x; 
	struct BOOK *next;		//The point of the next book
};
typedef struct BOOK Book;
typedef Book *book;

struct STUDENT{
	char number[10];		//Student's identity number. The student use the number to sign in.
	char password[15];		//The password of the identity. The student use the number to sign in.
	char name[20];			//Student's namechar boo_number[10];	//If the student borrows a book, it is the number of the book that be borrowed by the student.
	int booknum;			//The number of books were borrowed by the stduent
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
void save_student_information();
student tt();
void register_identity();
void sign_in();
void sign_out();
void borrow_book();
void return_book();
void student_access();
void sign_in_lib();
void student_list();
void find_student();
void librarian_access();

//Created identity
int identity = 0;			//The type of the identity. [0]Guest(cannot borrow books) [1]student(can borrow and return books) [2]librarian(can manage books and students' information)
student preStudent;
char libPassword[10] = "connors123";


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
					break;
			}
			break;
		default:
			break;
	}
};

//Read out the data of the file to the linked list and return the value as the header address
book ss() {
	FILE *fp;       //The pointer of the file
	int n = 0;
	book head = NULL;
	book p, p2, pr = NULL;
	fp=fopen("mybook", "ab+");     //Open files in a read-only manner
	if(fp == NULL) {
		printf("[Error] Cannot find or open file\n");
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


student tt() {
	FILE *fp;       //The pointer of the file
	int n = 0;
	student head = NULL;
	student p, p2, pr = NULL;
	fp=fopen("studentInformation", "ab+");     //Open files in a read-only manner
	if(fp == NULL) {
		printf("[Error] Cannot find or open file\n");
	}
	while( !feof(fp) ) {       //Determine whether the file location flag moves to the end of the file 
		n++;
		p = (student)malloc( sizeof(struct STUDENT) ); //Apply for a space in memory
		fread(p, sizeof(struct STUDENT), 1, fp);     //Assign the data of the file (number of data is 1) that fp refers to to to p
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
	if(fp == NULL)
	{
		printf("[Error] Cannot find or open file");
	}
	if(fwrite(p, sizeof(struct BOOK), 1, fp) != 1)   //Store a section of data pointed to by p in the file pointed to by fp
	{
		//If there is no successful write, the return value of fwrite is not 1
		printf("[Error] Write error");
	}
	fclose(fp);    //Close file and the pointer   
}


void input_book() {
	system("cls");
	book presentBook;
	presentBook = (book)malloc(sizeof(struct BOOK));     //Using malloc to allocate the memory
	//input the information of the book
	printf("Please input the book number (less than 10 digits)¡êo");    
	scanf("%s", presentBook->number);getchar();    //-> assigns members of a structure directly through a pointer to the structure, press any key to continue.
	printf("Please input the book name (less than 15 letters)¡êo");
	scanf("%s", presentBook->name);getchar();
	printf("Please input the author(s) of the book (less than 20 letters)¡êo");
	scanf("%s", presentBook->author);getchar();
	presentBook->exist = 1;
	printf("|  ------------------------------------  |\n");
	printf("|                                        |\n");
	printf("| Please confirm whether to save or not? |\n");
	printf("|       [1] Yes            [2] NO        |\n");
	printf("|                                        |\n");
	printf("|  ------------------------------------  |\n");
	do {
		char c = getch();
		if(c == '1') {
			save_book(presentBook);    //Store book information in files
			system("cls");
			printf("Saving....");
			sleep(1); 
			printf("\n|  -----------------------------------------  |\n");
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
	book head, p;
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
		sum++;  //Calculating the total amount of books
		p = p->next;
	}
	printf("|  --------------------------------------------------------------  |\n");
	printf("|  The total number of books is¡êo%d\n                              |\n",sum);
	printf("|  Press the following key to go directly to the corresponding     |\n");
	printf("|  interface.                                                      |\n");
	printf("|    [0] Return to the main interface                              |\n");
	printf("|    [1] Find books                                                |\n");
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
			break;
	}
};


void delete_book() {
	do {
		system("cls");
		FILE *fp;
		book head, p, pre = NULL; 
		int index = 0;
		int choose = 0;
		int x;
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
			gets(delName);
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
				printf("|   %5d   %15s   %s   %20s    [%d]    |\n",index,p->name,p->number,p->author,p->exist);
				p->x = index;
			}
			if(p != NULL && strcmp(p->number, delNum) == 0 && choose == 2) {
				index++;
				printf("|   %5d   %15s   %s   %20s    [%d]    |\n",index,p->name,p->number,p->author,p->exist);
				p->x = index;
			}
			p = p->next;
		}
		if(index == 0) {       //If index = 0, it does not enter the previous search cycle, which means that it does not find the corresponding information.
			printf("[Error] No corresponding information was found.\n");
			sleep(200);
			printf("|  -----------------------------------------  |\n");
			printf("|                                             |\n");
			printf("|      Do you want to continue searching?     |\n");
			printf("|         [1] Yes             [2] No          |\n");
			printf("|                                             |\n");
			printf("|  -----------------------------------------  |\n");
			while(1) {             //Dead loops are designed to prevent other key interference except 0 and 1.
				ch = getch();
				if(ch == '1')
					break;   
				else if(ch == '2') {
					userface();
					break;
				}      //Exit the dead loop
			}
			if(ch == '1')     //If ch equals 1, the search cycle is terminated and a new one is started
			   continue;
		}
		while(1) {
			printf("Please enter the index of the book you want to delete: ");
			scanf("%d", &x);
			getchar();
			if(x > index || x <= 0)
				printf("Error: Input the wrong index, please re-enter!\n");
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
				break;
		}
		p=head;
		while(p != NULL && p->x != x) {
			pre = p;
			p = p->next;
		}
		if(p != NULL) {
			if(pre == NULL)
				head = head->next;
			else
				pre->next = p->next;
		}
		free(p);
		fp = fopen("mybook","wb");
		if(fp == NULL)
			printf("Error: Cannot find or open file\n");
		if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
			printf("Error: Write error\n");
		fclose(fp);
		if(head != NULL) {
			p = head->next;
			fp = fopen("mybook","ab");
			if(fp == NULL)
				printf("Error: Cannot find or open file\n");
			while(p != NULL)
			{
				if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
					printf("Error: Write error\n");
				p = p->next;
			}
			fclose(fp);
		}
		system("cls");
		printf("Deleting, please wait a moment...\n");
		Sleep(500);
		system("cls");
		printf("|  ---------------------------------------------------  |\n");
		printf("|     Delete successfully. Do you want to continue?     |\n");
		printf("|               [1]Yes             [2]No                |\n");
		printf("|  ---------------------------------------------------  |\n");
		while(1) {
			c = getch();
			if(c == '1')
				break;
			else if(c == '2')
				userface();
		}
	}while(1);
}


void find_book() {
	do {
		system("cls");
		char information[20];
		char t;
		int choose = 0;
		book head, p;
		head = ss();
		p = head;
		printf("|  --------------------------------------------------------------  |\n");
		printf("|                           Book  Search                           |\n");
		printf("|  --------------------------------------------------------------  |\n");
		printf("|                               TIPS:                              |\n");
		printf("|  (1) There are two kinds of search methods, exact search and     |\n");
		printf("|  fuzzy search. Both search methods can search books by book      |\n");
		printf("|  number, title and author.                                       |\n");
		printf("|  (2) To use exact search, you have to input exactly the same     |\n");
		printf("|  information.                                                    |\n");
		printf("|  (3) To use fuzzy search, some information can be omitted, but   |\n");
		printf("|  it can't be mistyped.                                           |\n");
		printf("|  (4) The input character limits for both search methods are 20.  |\n");
		printf("|  --------------------------------------------------------------  |\n");
		printf("|                                                                  |\n");
		printf("|  Enter the numbers in parentheses below and select the search    |\n");
		printf("|  method.                                                         |\n");
		printf("|            [1]Exact Search            [2]Fuzzy Search            |\n");
		printf("|                                                                  |\n");
		printf("|  --------------------------------------------------------------  |\n");
		t = getch();
		while(1) {
			t = getch();
			if(t == '1') {
				choose = 1;
				break;
			} 
			else if(t == '2') {
				choose = 2;
				break;
			}
		}
		if(choose == 1) {
			system("cls");
			printf("Exact Search\n");
			printf("Please enter the important of the book you want to find: ");
			gets(information);
		}
		if(choose == 2) {
			system("cls");
			printf("Fuzzy Search\n");
			printf("Please enter the important of the book you want to find: ");
			gets(information);
		} 
		
		printf("|  --------------------------------------------------------------  |\n");
		printf("|         Name      |   Number   |        Author        | Status   |\n");
		printf("|  --------------------------------------------------------------  |\n");
		while(p != NULL) {
			if(p != NULL && (strcmp(p->name, information) == 0 || strcmp(p->author, information) == 0 || strcmp(p->number, information) == 0) && choose == 1) {
				printf("|   %15s   %s   %20s    [%d]    |\n",p->name,p->number,p->author,p->exist);
			}
			if(p != NULL && (strstr(p->name, information) != NULL || strstr(p->author, information) != NULL || strstr(p->number, information) != NULL) && choose == 2) {
				printf("|   %15s   %s   %20s    [%d]    |\n",p->name,p->number,p->author,p->exist);
			}
			p = p->next;
		}
		printf("|  --------------------------------------------------------------  |\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}while(1);
};


void save_student_information(student p) {
	FILE *fp;    //The pointer of the file
	fp = fopen("studentInformation", "ab");   //Open a binary file named mybook by additional opening file and writing data at the end of the file
	if(fp == NULL)
	{
		printf("[Error] Cannot find or open file");
	}
	if(fwrite(p, sizeof(struct STUDENT), 1, fp) != 1)   //Store a section of data pointed to by p in the file pointed to by fp
	{
		//If there is no successful write, the return value of fwrite is not 1
		printf("[Error] Write error");
	}
	fclose(fp);    //Close file and the pointer
};


void register_identity() {
	system("cls");
	char c, t;
	student head, p;
	head = tt();
	p = head;
	student newStudent;
	char information[10];
	newStudent = (student)malloc(sizeof(struct STUDENT));     //Using malloc to allocate the memory
	//input the information of the book
	printf("Please input the number you like (equal to 10 digits)¡êo");    
	scanf("%s", information);getchar();
	if( strlen(information) != 10 ) {
		printf("Sorry, this number does not contain 10 digits.\n");
		sleep(200);
		printf("[Press any key to return]\n");
		getch();
		register_identity();
	}
	else {
		while(p != NULL) {
			if(p != NULL && strcmp(p->number, information) == 0) {
				printf("Sorry, this number has already been used.\n");
				sleep(200);
				printf("[Press any key to return]\n");
				getch();
				register_identity();
				break;
			}
			p = p->next;
		}
		strcpy(newStudent->number, information);
	}
	
	printf("Please input the password (less than or equal to 15 letters)¡êo");
	scanf("%s", newStudent->password);getchar();
	printf("Please input your name (less than or equal to 20 letters)¡êo");
	scanf("%s", newStudent->name);getchar();
	newStudent->booknum = 0;
	printf("|  ------------------------------------  |\n");
	printf("|                                        |\n");
	printf("| Please confirm whether to save or not? |\n");
	printf("|       [1] Yes            [2] No        |\n");
	printf("|                                        |\n");
	printf("|  ------------------------------------  |\n");
	do {
		c = getch();
		if(c == '1') {
			save_student_information(newStudent);    //Store book information in files
			system("cls");
			printf("Saving....");
			Sleep(500); 
			printf("|  -----------------------------------------  |\n");
			printf("|                                             |\n");
			printf("| Save successfully! Do you want to sign in?  |\n");
			printf("|         [1] Yes             [2] No          |\n");
			printf("|                                             |\n");
			printf("|  -----------------------------------------  |\n");
			while(1) {
			t = getch();
				if(t == '1') {
					sign_in();
					break;
				}
				else if(t == '2') {
				 	userface();
				 	break;
				}
			}while(1);
		}
		else if(c == '2')
			break;
	}while(1);
};


void sign_in() {
	if( identity == 0 ) {
		do {
			system("cls");
			FILE *fp;
			student head, p, stu;
			char inNum[10];
			char inPassword[15];
			head = tt();    //Return the header address
			p = head;
			printf("Please input your number: ");
			scanf("%s", inNum);
			if( strlen(inNum) != 10 ) {
				printf("Sorry, this number does not contain 10 digits.\n");
				sleep(200);
				printf("[Press any key to return]\n");
				getch();
				sign_in();
				break;
			}
			else {
				while(p != NULL) {
					if(p != NULL && strcmp(p->number, inNum) == 0) {
						stu = p;
						break;
					}
					p = p->next;
				}
				if(p != NULL) {
					printf("Sorry, this number is not registered.\n");
					sleep(200);
					printf("[Press any key to return the main userface]\n");
					getch();
					userface();
					break;
				}
	
				printf("Please input your password: ");
				scanf("%s", inPassword);
				if(strcmp(stu->password, inPassword) == 0) {
					printf("Signing in...\n");
					sleep(400);
					identity = 1;
					preStudent = stu;
					printf("Sign in successfully.\n");
					printf("[Press any key to return the main userface]\n");
					getch();
					userface();
				}
				else {
					printf("Sorry, your password is wrong.\n");
					sleep(200);
					printf("[Press any key to return the main userface]\n");
					getch();
					userface();
				}
			}
		}while(1);
	}
	else if( identity == 1 ) {
		printf("Sorry, the last student has not been signed out yet. You can't sign in.\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 2 ) {
		printf("Sorry, you are now a librarian. You can't sign in to the student identity again.\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}	
};


void sign_out() {
	if( identity == 0 ) {
		printf("Sorry, you are now a guest. You can't sign out.\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 1 ) {
		system("cls");
		student head, p;
		char c;
		FILE *fp;
		head = tt();
		p = head;
		while(p != NULL) {
			if(p != NULL && strcmp(p->number, preStudent->number) == 0) {
				p = preStudent;
			}
			p = p->next;
		}
		
		printf("Signing out...\n");
		sleep(100);
		fp = fopen("studentInformation","wb");
		if(fp == NULL)
			printf("[Error] Cannot find or open file\n");
		if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
			printf("[Error] Write error\n");
		fclose(fp);
		if(head != NULL) {
			p = head->next;
			fp = fopen("studentInformation","ab");
			if(fp == NULL)
				printf("[Error] Cannot find or open file\n");
			while(p != NULL) {
				if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
					printf("[Error] Write error\n");
				p = p->next;
			}
			fclose(fp);
		}
		printf("Sign out successfully.\n");
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 2 ) {
		system("cls");
		char c;
		printf("|  -----------------------------------------  |\n");
		printf("|                                             |\n");
		printf("|      Confirm to sign out the identity?      |\n");
		printf("|         [1] Yes             [2] No          |\n");
		printf("|                                             |\n");
		printf("|  -----------------------------------------  |\n");
		while(1) {
			c = getch();
			if(c == '1') {
				printf("Signing out...\n");
				sleep(400);
				identity = 0;
				printf("Sign out successfully.\n");
				printf("[Press any key to return the main userface]\n");
				getch();
				userface();
				break;
			}
			else if(c == '2') {
				userface();
				break;
			}
		}
	}
};


void borrow_book() {
	if( identity == 0 ) {
		char c;
		printf("Sorry, you are now a guest and have no right to borrow books.\n");
		sleep(200);
		printf("|  -----------------------------------------  |\n");
		printf("|                                             |\n");
		printf("|    Do you want to register as a student?    |\n");
		printf("|         [1] Yes             [2] NO          |\n");
		printf("|                                             |\n");
		printf("|  -----------------------------------------  |\n");
		while(1) {
			c = getch();
			if(c == '1') {
				register_identity();
				break;
			} 
			else if(c == '2') {
				userface();
				break;
			}
		}
	}
	else if( identity == 2 ) {
		printf("Sorry, you are now a librarian and have no right to borrow books.\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 1 ) {
		do {
			system("cls");
			book head, p;
			int index = 0;
			int choose = 0;
			int x;
			char borName[15];
			char borNum[10];
			char q, ch, t, c;
			FILE *fp;
			head = ss();
			printf("|  ---------------------------------------  |\n");
			printf("|                                           |\n");
			printf("|  Select different ways to borrow books    |\n");
			printf("|    [1] Borrow books by book name          |\n");
			printf("|    [2] Borrow books by book number        |\n");
			printf("|                                           |\n");
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
				printf("Please enter the name of the book you want to borrow: ");
				gets(borName);
			}
			if(choose == 2) {
				system("cls");
				printf("Please enter the number of the book you want to borrow: ");
				scanf("%s", borNum);
			}
			p = head;
			while(p!=NULL) {
				p->x = 0;
				p = p->next;
			}
			p=head;
			printf("|                            Operating Book List                           |\n");
			printf("|  ----------------------------------------------------------------------  |\n");
			printf("|   Index |       Name      |   Number   |        Author        | Status   |\n");
			printf("|  ----------------------------------------------------------------------  |\n");
			while(p != NULL) {
				if(p != NULL && strcmp(p->name, borName) == 0 && choose == 1) {       //strcmp() is a string comparison function
					index++;
					printf("|   %5d   %15s   %s   %20s    [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				if(p != NULL && strcmp(p->number, borNum) == 0 && choose == 2) {
					index++;
					printf("|   %5d   %15s   %s   %20s    [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				p = p->next;
			}
			if(index == 0) {       //If index = 0, it does not enter the previous search cycle, which means that it does not find the corresponding information.
				printf("[Error] No corresponding information was found.\n");
				sleep(200);
				printf("|  -----------------------------------------  |\n");
				printf("|                                             |\n");
				printf("|      Do you want to continue searching?     |\n");
				printf("|         [1] Yes             [2] No          |\n");
				printf("|                                             |\n");
				printf("|  -----------------------------------------  |\n");
				while(1) {             //Dead loops are designed to prevent other key interference except 0 and 1.
					ch = getch();
					if(ch == '1')
						break;   
					else if(ch == '2') {
						userface();
						break;
					}      //Exit the dead loop
				}
				if(ch == '1')     //If ch equals 1, the search cycle is terminated and a new one is started
				   continue;
			}
		
			while(1) {
				printf("Please enter the index of the book you want to borrow: ");
				scanf("%d", &x);
				getchar();
				if(x > index || x <= 0)
					printf("[Error] Input the wrong index, please re-enter!\n");
				else
					break;
			}
			printf("|  ----------------------------------  |\n");
			printf("|                                      |\n");
			printf("|     Confirm to borrow this book?     |\n");
			printf("|        [1]Yes        [2]No           |\n");
			printf("|                                      |\n");
			printf("|  ----------------------------------  |\n");
			while(1) {
				t = getch();
				if(t == '1')
					break;
				else if(t == '2')
					userface();
					break;
			}
			p=head;
			while(p != NULL && p->x != x)
				p = p->next;
			if(p && p->exist == 1 ) {
				if( preStudent->firstBook == NULL || preStudent->secondBook == NULL || preStudent->thirdBook == NULL ) {
					p->exist = 2;
					strcpy(p->stu_number, preStudent->number);
					while(1) {
						if( preStudent->firstBook == NULL ) {
							preStudent->firstBook = p;
							break;
						}
						if( preStudent->secondBook == NULL ) {
							preStudent->secondBook = p;
							break;
						}
						if( preStudent->thirdBook == NULL ) {
							preStudent->thirdBook = p;
							break;
						}
					}
				} else if( preStudent->firstBook != NULL && preStudent->secondBook != NULL && preStudent->thirdBook != NULL ) {
					printf("Sorry, you have borrowed three books(Up to the borrowing limit) and have no right to borrow books.\n");
					sleep(200);
					printf("[Press any key to return the main userface]\n");
					getch();
					userface();
					break;
				}
			} else if(p && p->exist != 1 ) {
				printf("Sorry, the book has been lent out or damaged.\n");
				sleep(200);
				printf("[Press any key to return the main userface]\n");
				getch();
				userface();
				break;
			}
		
			fp = fopen("mybook","wb");
			if(fp == NULL)
				printf("[Error] Cannot find or open file\n");
			if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
				printf("[Error] Write error\n");
			fclose(fp);
			if(head != NULL) {
				p = head->next;
				fp = fopen("mybook","ab");
				if(fp == NULL)
					printf("[Error] Cannot find or open file\n");
				while(p != NULL)
				{
					if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
						printf("[Error] Write error\n");
					p = p->next;
				}
				fclose(fp);
			}
			system("cls");
			printf("Borrowing, please wait a moment...\n");
			Sleep(500);
			system("cls");
			printf("|  ---------------------------------------------------  |\n");
			printf("|                                                       |\n");
			printf("|     Borrow successfully. Do you want to continue?     |\n");
			printf("|               [1]Yes             [2]No                |\n");
			printf("|                                                       |\n");
			printf("|  ---------------------------------------------------  |\n");
			while(1) {
				c = getch();
				if(c == '1')
					break;
				else if(c == '2')
					userface();
			}
		}while(1);
	}
};


void return_book() {
	if( identity == 0 ) {
		char c;
		printf("Sorry, you are now a guest and have no right to return books.\n");
		sleep(200);
		printf("|  -----------------------------------------  |\n");
		printf("|                                             |\n");
		printf("|    Do you want to register as a student?    |\n");
		printf("|         [1] Yes             [2] NO          |\n");
		printf("|                                             |\n");
		printf("|  -----------------------------------------  |\n");
		while(1) {
			c = getch();
			if(c == '1') {
				register_identity();
				break;
			} 
			else if(c == '2') {
				userface();
				break;
			}
		}
	}
	else if( identity == 2 ) {
		printf("Sorry, you are now a librarian and have no right to return books.\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 1 ) {
		do {
			system("cls");
			book head,p;
			int index = 0;
			int choose = 0;
			int x;
			char reName[15];
			char reNum[10];
			char q, ch, t, c;
			FILE *fp;
			head = ss();
			printf("|  ---------------------------------------  |\n");
			printf("|                                           |\n");
			printf("|  Select different ways to borrow books    |\n");
			printf("|    [1] Return books by book name          |\n");
			printf("|    [2] Return books by book number        |\n");
			printf("|                                           |\n");
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
				printf("Please enter the name of the book you want to return: ");
				gets(reName);
			}
			if(choose == 2) {
				system("cls");
				printf("Please enter the number of the book you want to return: ");
				scanf("%s", reNum);
			}
			p = head;
			while(p!=NULL) {
				p->x = 0;
				p = p->next;
			}
			p = head;
			printf("|                            Operating Book List                           |\n");
			printf("|  ----------------------------------------------------------------------  |\n");
			printf("|   Index |       Name      |   Number   |        Author        | Status   |\n");
			printf("|  ----------------------------------------------------------------------  |\n");
			while(p != NULL) {
				if(p != NULL && strcmp(p->name, reName) == 0 && choose == 1) {       //strcmp() is a string comparison function
					index++;
					printf("|   %5d   %15s   %s   %20s    [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				if(p != NULL && strcmp(p->number, reNum) == 0 && choose == 2) {
					index++;
					printf("|   %5d   %15s   %s   %20s    [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				p = p->next;
			}
			if(index == 0) {       //If index = 0, it does not enter the previous search cycle, which means that it does not find the corresponding information.
				printf("[Error] No corresponding information was found.\n");
				sleep(200);
				printf("|  -----------------------------------------  |\n");
				printf("|                                             |\n");
				printf("|      Do you want to continue searching?     |\n");
				printf("|         [1] Yes             [2] No          |\n");
				printf("|                                             |\n");
				printf("|  -----------------------------------------  |\n");
				while(1) {             //Dead loops are designed to prevent other key interference except 0 and 1.
					ch = getch();
					if(ch == '1')
						break;   
					else if(ch == '2') {
						userface();
						break;
					}      //Exit the dead loop
				}
				if(ch == '1')     //If ch equals 1, the search cycle is terminated and a new one is started
				   continue;
			}
		
			while(1) {
				printf("Please enter the index of the book you want to return: ");
				scanf("%d", &x);
				getchar();
				if(x > index || x <= 0)
					printf("[Error] Input the wrong index, please re-enter!\n");
				else
					break;
			}
			printf("|  ----------------------------------  |\n");
			printf("|                                      |\n");
			printf("|     Confirm to return this book?     |\n");
			printf("|        [1]Yes        [2]No           |\n");
			printf("|                                      |\n");
			printf("|  ----------------------------------  |\n");
			while(1) {
				t = getch();
				if(t == '1')
					break;
				else if(t == '2')
					userface();
					break;
			}
			p = head;
			while(p != NULL && p->x != x)
				p = p->next;
			if(p) {
				if( preStudent->firstBook == p || preStudent->secondBook == p || preStudent->thirdBook == p ) {
					p->exist = 1;
					strcpy(p->stu_number, "\0");
					while(1) {
						if( preStudent->firstBook == p ) {
							preStudent->firstBook = NULL;
							break;
						}
						if( preStudent->secondBook == p ) {
							preStudent->secondBook = NULL;
							break;
						}
						if( preStudent->thirdBook == p ) {
							preStudent->thirdBook = NULL;
							break;
						}
					}
				} else if( (preStudent->firstBook != p && preStudent->secondBook != p  && preStudent->thirdBook != p) || p->exist != 2 ) {
					printf("Sorry, you haven't borrowed this book.\n");
					sleep(200);
					printf("[Press any key to return the main userface]\n");
					getch();
					userface();
					break;
				}
			}
		
			fp = fopen("mybook","wb");
			if(fp == NULL)
				printf("[Error] Cannot find or open file\n");
			if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
				printf("[Error] Write error\n");
			fclose(fp);
			if(head != NULL) {
				p = head->next;
				fp = fopen("mybook","ab");
				if(fp == NULL)
					printf("[Error] Cannot find or open file\n");
				while(p != NULL)
				{
					if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
						printf("[Error] Write error\n");
					p = p->next;
				}
				fclose(fp);
			}
			system("cls");
			printf("Returning, please wait a moment...\n");
			Sleep(500);
			system("cls");
			printf("|  ---------------------------------------------------  |\n");
			printf("|                                                       |\n");
			printf("|     Return successfully. Do you want to continue?     |\n");
			printf("|               [1]Yes             [2]No                |\n");
			printf("|                                                       |\n");
			printf("|  ---------------------------------------------------  |\n");
			while(1) {
				c = getch();
				if(c == '1')
					break;
				else if(c == '2')
					userface();
			}
		}while(1);
	}
};


void student_access() {
	system("cls");
	printf("|  --------------------------------------------------------------  |\n");
	printf("|                          Student Access                          |\n");
	printf("|  --------------------------------------------------------------  |\n");
	printf("|  Press the following key to go directly to the corresponding     |\n");
	printf("|  interface.                                                      |\n");
	printf("|    [0] Return to the main interface                              |\n");
	printf("|    [1] Register Identity                                         |\n");
	printf("|    [2] Sign in                                                   |\n");
	printf("|    [3] Sign out                                                  |\n");
	printf("|    [4] Borrow books                                              |\n");
	printf("|    [5] Return books                                              |\n");
	printf("|  --------------------------------------------------------------  |\n");
	char e = getch();
	switch(e)
	{
		case '0':
			userface();
			break;
		case '1':
			register_identity();
			break;
		case '2':
			sign_in();
			break;
		case '3':
			sign_out();
			break;
		case '4':
			borrow_book();
			break;
		case '5':
			return_book();
			break;
		default:
			break;
	}
};


void sign_in_lib() {
	if( identity == 0 ) {
		system("cls");
		char inPassword[15];
		printf("Please input your password: ");
		scanf("%s", inPassword);
		if(strcmp(libPassword, inPassword) == 0) {
			printf("Signing in...\n");
			sleep(400);
			identity = 2;
			printf("Sign in successfully.\n");
			printf("[Press any key to return the main userface]\n");
			getch();
			userface();
		}
	}
	else if( identity == 1 ) {
		printf("Sorry, you are now a student. You can't sign in to the librarian identity again.\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	} else if( identity == 2 ) {
		printf("Sorry, you have signed in as a librarian and do not need to sign in.\n");
		sleep(200);
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
};


void student_list() {
	system("cls");    //Clean the screen
	student head, p;
	int sum = 0;
	head = tt();
	if(head == NULL)
	{
		printf("\n\nSorry, there are no student in the library for the time being. \n");
		printf("[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	printf("|                                               Student List                                               |\n");
	printf("|  ------------------------------------------------------------------------------------------------------  |\n");
	printf("|                                                  TIPS:                                                   |\n");
	printf("|  (1) Librarian also have no authority to manipulate student data.                                        |\n");
	printf("|  (2) Booknum means the number of books borrowed.                                                         |\n");
	printf("|  (3) The first book, the second book and the third book show the number of the book borrowed by the      |\n");
	printf("|  student.                                                                                                |\n");
	printf("|  ------------------------------------------------------------------------------------------------------  |\n");
	printf("|     Number   |        Name         |    Password     | Booknum | First book | Second book | Third book   |\n");
	printf("|  ------------------------------------------------------------------------------------------------------  |\n");
	p = head;
	while(p != NULL)
	{
		printf("|   %10s   %20s   %15s    %d   %10s   %10s   %10s   |\n",p->number,p->name,p->password,p->booknum,p->firstBook->number,p->secondBook->number,p->thirdBook->number);
		sum++;  //Calculating the total amount of books
		p = p->next;
	}
	printf("|  ------------------------------------------------------------------------------------------------------  |\n");
	printf("|  The total number of students is¡êo%d\n                                                                   |\n",sum);
	printf("|  Press the following key to go directly to the corresponding interface.                                  |\n");
	printf("|    [0] Return to the main interface                                                                      |\n");
	printf("|    [1] Find student                                                                                      |\n");
	printf("|  ------------------------------------------------------------------------------------------------------  |\n");
	char e = getch();
	switch(e)
	{
		case '0':
			userface();
			break;
		case '1':
			find_student();
			break;
	}
};


void find_student() {
	do {
		system("cls");
		char information[20];
		char t;
		int choose = 0;
		student head, p;
		head = tt();
		p = head;
		printf("|  --------------------------------------------------------------  |\n");
		printf("|                           Book  Search                           |\n");
		printf("|  --------------------------------------------------------------  |\n");
		printf("|                               TIPS:                              |\n");
		printf("|  (1) There are two kinds of search methods, exact search and     |\n");
		printf("|  fuzzy search. Both search methods can search student by number  |\n");
		printf("|  name, the number of the book borrowed by the student.           |\n");
		printf("|  (2) To use exact search, you have to input exactly the same     |\n");
		printf("|  information.                                                    |\n");
		printf("|  (3) To use fuzzy search, some information can be omitted, but   |\n");
		printf("|  it can't be mistyped.                                           |\n");
		printf("|  (4) The input character limits for both search methods are 20.  |\n");
		printf("|  --------------------------------------------------------------  |\n");
		printf("|                                                                  |\n");
		printf("|  Enter the numbers in parentheses below and select the search    |\n");
		printf("|  method.                                                         |\n");
		printf("|            [1]Exact Search            [2]Fuzzy Search            |\n");
		printf("|                                                                  |\n");
		printf("|  --------------------------------------------------------------  |\n");
		t = getch();
		while(1) {
			t = getch();
			if(t == '1') {
				choose = 1;
				break;
			} 
			else if(t == '2') {
				choose = 2;
				break;
			}
		}
		if(choose == 1) {
			system("cls");
			printf("Exact Search\n");
			printf("Please enter the important of the student you want to find: ");
			gets(information);
		}
		if(choose == 2) {
			system("cls");
			printf("Fuzzy Search\n");
			printf("Please enter the important of the student you want to find: ");
			gets(information);
		} 
		
		printf("|                                               Student List                                               |\n");
		printf("|  ------------------------------------------------------------------------------------------------------  |\n");
		printf("|     Number   |        Name         |    Password     | Booknum | First book | Second book | Third book   |\n");
		printf("|  ------------------------------------------------------------------------------------------------------  |\n");
		while(p != NULL) {
			if(p != NULL && (strcmp(p->name, information) == 0 || strcmp(p->number, information) == 0 || strcmp(p->firstBook->number, information) == 0 || strcmp(p->secondBook->number, information) == 0 || strcmp(p->thirdBook->number, information) == 0) && choose == 1) {
				printf("|   %10s   %20s   %15s    %d   %10s   %10s   %10s   |\n",p->number,p->name,p->password,p->booknum,p->firstBook->number,p->secondBook->number,p->thirdBook->number);
			}
			if(p != NULL && (strstr(p->name, information) != NULL || strstr(p->number, information) != NULL || strstr(p->firstBook->number, information) != NULL || strstr(p->secondBook->number, information) != NULL || strstr(p->thirdBook->number, information) != NULL) && choose == 2) {
				printf("|   %10s   %20s   %15s    %d   %10s   %10s   %10s   |\n",p->number,p->name,p->password,p->booknum,p->firstBook->number,p->secondBook->number,p->thirdBook->number);
			}
			p = p->next;
		}
		printf("|  ------------------------------------------------------------------------------------------------------  |\n");
		sleep(200);
		printf("\n\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}while(1);
};


void librarian_access() {
	system("cls");
	printf("|  --------------------------------------------------------------  |\n");
	printf("|                         Librarian Access                         |\n");
	printf("|  --------------------------------------------------------------  |\n");
	printf("|  Press the following key to go directly to the corresponding     |\n");
	printf("|  interface.                                                      |\n");
	printf("|    [0] Return to the main interface                              |\n");
	printf("|    [1] Sign in                                                   |\n");
	printf("|    [2] Sign out                                                  |\n");
	printf("|    [3] Check out the book list                                   |\n");
	printf("|    [4] Input book                                                |\n");
	printf("|    [5] Delete book                                               |\n");
	printf("|    [6] Check out the student list                                |\n");
	printf("|  --------------------------------------------------------------  |\n");
	char e = getch();
	switch(e)
	{
		case '0':
			userface();
			break;
		case '1':
			sign_in_lib();
			break;
		case '2':
			sign_out();
			break;
		case '3':
			book_access();
			break;
		case '4':
			input_book();
			break;
		case '5':
			delete_book();
			break;
		case '6':
			student_list();
			break;
		default:
			break;
	}
};


int main() {
	userface();
	return 0;
}
