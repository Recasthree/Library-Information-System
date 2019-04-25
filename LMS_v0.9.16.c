#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>			//for the sleep()

//The Structure of Student Information and Book Information
struct BOOK{
	char number[11];		//Book number
	char name[16];			//Book name
	char author[21];		//The author(s) of the book
	int exist;				//The status of this book. [1]In the library [2]Be loaned out [3]Be damaged
	char stu_number[11];	//If the book is borrowed, it is the identity number of the student who borrow the book.
	int x; 
	struct BOOK *next;		//The point of the next book
};
typedef struct BOOK Book;
typedef Book *book;

struct STUDENT{
	char number[11];		//Student's identity number. The student use the number to sign in.
	char password[16];		//The password of the identity. The student use the number to sign in.
	char name[21];			//Student's namechar boo_number[10];	//If the student borrows a book, it is the number of the book that be borrowed by the student.
	int booknum;			//The number of books were borrowed by the stduent
	char firstBook[11]; 	//The number of the first book a student can borrow
	char secondBook[11]; 	//The number of the second book a student can borrow
	char thirdBook[11]; 	//The number of the third book a student can borrow
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
char libPassword[11] = "123";


void userface(){
	system("cls");    //Clean the screen
	printf("|  ------------------------------------------------------------------------------------------  |\n");
	printf("|                                  Library Information System                                  |\n");
	printf("|  ------------------------------------------------------------------------------------------  |\n");
	printf("|                                       [1] Book Access                                        |\n");
	printf("|                                       [2] Student Access                                     |\n");
	printf("|                                       [3] Librarian Access                                   |\n");
	printf("|                                       [4] Exit System                                        |\n");
	printf("|  ------------------------------------------------------------------------------------------  |\n");
	printf("Welcome to use Library Information System, you can enter the corresponding number of accesses into the subsystems.\n");
	printf("PS1: If you don't have the student identity, you can't borrow or return the books, only read the book list.\n");
	printf("PS2: You can register as a student through the Student Access.\n");
	char t = getch();    //It will not display the number on the screen.
	while(1) {
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
						continue;
				}
				break;
			default:
				continue;
		}
	}
};

//Read out the data of the file to the linked list and return the value as the header address
book ss() {
	FILE *fp;       //The pointer of the file
	int n = 0;
	book head = NULL;
	book p, p2, pr = NULL;
	fp = fopen("bookInformation", "ab+");     //Open files in a read-only manner
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
	fp = fopen("studentInformation", "ab+");     //Open files in a read-only manner
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
	fp = fopen("bookInformation", "ab");   //Open a binary file named bookInformation by additional opening file and writing data at the end of the file
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
	printf("Please input the book number (less than 10 digits)£º");    
	scanf("%s", presentBook->number);getchar();    //-> assigns members of a structure directly through a pointer to the structure, press any key to continue.
	printf("Please input the book name (less than 15 letters)£º");
	scanf("%s", presentBook->name);getchar();
	printf("Please input the author(s) of the book (less than 20 letters)£º");
	scanf("%s", presentBook->author);getchar();
	presentBook->exist = 1;
	printf("\n|  ------------------------------------  |\n");
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
			printf("Saving....\n");
			sleep(1);
			system("cls");
			printf("|  -----------------------------------------  |\n");
			printf("|                                             |\n");
			printf("| Save successfully! Do you want to continue? |\n");
			printf("|         [1] Yes             [2] NO          |\n");
			printf("|                                             |\n");
			printf("|  -----------------------------------------  |\n");
			while(1) {
				char t = getch();
				if(t == '1') {
					input_book();
					break;
				}
				else if(t == '2') {
				 	userface();
					break;
				}
			}
		}
		else if(c == '2') {
				userface();
				break;
			}
	}
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
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	
	printf("|  --------------------------------------------------------------  |\n");
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
		printf("|   %-15s   %-10s   %-20s     [%d]    |\n",p->name,p->number,p->author,p->exist);
		sum++;  //Calculating the total amount of books
		p = p->next;
	}
	printf("|  --------------------------------------------------------------  |\n");
	printf("|  The total number of books is£º%-4d                              |\n",sum);
	printf("|  Press the following key to go directly to the corresponding     |\n");
	printf("|  interface.                                                      |\n");
	printf("|    [0] Return to the main interface                              |\n");
	printf("|    [1] Find books                                                |\n");
	printf("|    [2] Borrow books                                              |\n");
	printf("|    [3] Return books                                              |\n");
	printf("|    [4] Management books (librarian status only)                  |\n");
	printf("|  --------------------------------------------------------------  |\n");
	while(1) {
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
				continue;
		}
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
		char delName[16];
		char delNum[11];
		char q, t, c, ch;
		head = ss();    //Return the header address
		printf("|  ---------------------------------------  |\n");
		printf("|                                           |\n");
		printf("|   Select different ways to delete books   |\n");
		printf("|    [1] Delete books by book name          |\n");
		printf("|    [2] Delete books by book number        |\n");
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
			printf("Please enter the name of the book you want to delete: ");
			gets(delName);getchar();
		}
		if(choose == 2) {
			system("cls");
			printf("Please enter the number of the book you want to delete: ");
			scanf("%s", delNum);getchar();
		}
		
		p = head;
		while( p != NULL ) {
			p->x = 0;
			p = p->next;
		}
		p = head;
		printf("\n\n|  ----------------------------------------------------------------------  |\n");
		printf("|                            Operating Book List                           |\n");
		printf("|  ----------------------------------------------------------------------  |\n");
		printf("|   Index |       Name      |   Number   |        Author        | Status   |\n");
		printf("|  ----------------------------------------------------------------------  |\n");
		while(p != NULL) {
			if(p != NULL && strcmp(p->name, delName) == 0 && choose == 1) {       //strcmp() is a string comparison function
				index++;
				printf("|   %-5d   %-15s   %-10s   %-20s     [%d]    |\n",index,p->name,p->number,p->author,p->exist);
				p->x = index;
			}
			if(p != NULL && strcmp(p->number, delNum) == 0 && choose == 2) {
				index++;
				printf("|   %-5d   %-15s   %-10s   %-20s     [%d]    |\n",index,p->name,p->number,p->author,p->exist);
				p->x = index;
			}
			p = p->next;
		}
		if(index == 0) {       //If index = 0, it does not enter the previous search cycle, which means that it does not find the corresponding information.
			printf("[Error] No corresponding information was found.\n");
			sleep(1);
			printf("\n|  -----------------------------------------  |\n");
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
				printf("\n\n[Error] Input the wrong index, please re-enter!\n");
			else
				break;
		}
		printf("\n\n|  ----------------------------------  |\n");
		printf("|                                      |\n");
		printf("|     Confirm to delete this book?     |\n");
		printf("|        [1]Yes        [2]No           |\n");
		printf("|                                      |\n");
		printf("|  ----------------------------------  |\n");
		while(1) {
			t = getch();
			if(t == '1')
				break;
			else if(t == '2') {
				userface();
				break;
			}
		}
		
		p = head;
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
		fp = fopen("bookInformation","wb");
		if(fp == NULL)
			printf("[Error] Cannot find or open file\n");
		if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
			printf("[Error] Write error\n");
		fclose(fp);
		if(head != NULL) {
			p = head->next;
			fp = fopen("bookInformation","ab");
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
		printf("Deleting, please wait a moment...\n");
		sleep(1);
		system("cls");
		printf("|  ---------------------------------------------------  |\n");
		printf("|     Delete successfully. Do you want to continue?     |\n");
		printf("|               [1]Yes             [2]No                |\n");
		printf("|  ---------------------------------------------------  |\n");
		while(1) {
			c = getch();
			if(c == '1') {
				delete_book();
				break;
			}
			else if(c == '2') {
				userface();
				break;
			}
		}
	}while(1);
}


void find_book() {
	do {
		system("cls");
		char information[21];
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
			printf("\nPlease enter the important of the book you want to find: ");
			gets(information);getchar();
		}
		if(choose == 2) {
			system("cls");
			printf("Fuzzy Search\n");
			printf("\nPlease enter the important of the book you want to find: ");
			gets(information);getchar();
		} 
		
		printf("|  --------------------------------------------------------------  |\n");
		printf("|                            Book List                             |\n");
		printf("|  --------------------------------------------------------------  |\n");
		printf("|         Name      |   Number   |        Author        | Status   |\n");
		printf("|  --------------------------------------------------------------  |\n");
		while(p != NULL) {
			if(p != NULL && (strcmp(p->name, information) == 0 || strcmp(p->author, information) == 0 || strcmp(p->number, information) == 0) && choose == 1) {
				printf("|   %-15s   %-10s   %-20s     [%d]    |\n",p->name,p->number,p->author,p->exist);
			}
			if(p != NULL && (strstr(p->name, information) != NULL || strstr(p->author, information) != NULL || strstr(p->number, information) != NULL) && choose == 2) {
				printf("|   %-15s   %-10s   %-20s     [%d]    |\n",p->name,p->number,p->author,p->exist);
			}
			p = p->next;
		}
		printf("|  --------------------------------------------------------------  |\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}while(1);
};


void save_student_information(student p) {
	FILE *fp;    //The pointer of the file
	fp = fopen("studentInformation", "ab");   //Open a binary file named bookInformation by additional opening file and writing data at the end of the file
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
}


void register_identity() {
	system("cls");
	char c, t;
	student head, p;
	head = tt();
	p = head;
	student newStudent;
	newStudent = (student)malloc(sizeof(struct STUDENT));     //Using malloc to allocate the memory
	//input the information of the book
	printf("Please input the number you like (equal to 10 digits)£º");    
	scanf("%s", newStudent->number);getchar();
	if( strlen(newStudent->number) != 10 ) {
		printf("Sorry, this number does not contain 10 digits.\n");
		sleep(1);
		printf("\n[Press any key to return]\n");
		getch();
		register_identity();
	}
	else {
		while(p != NULL) {
			if(p != NULL && strcmp(p->number, newStudent->number) == 0) {
				printf("Sorry, this number has already been used.\n");
				sleep(1);
				printf("\n[Press any key to return]\n");
				getch();
				register_identity();
				break;
			}
			p = p->next;
		}
	}
	
	printf("Please input the password (less than or equal to 15 letters)£º");
	scanf("%s", newStudent->password);getchar();
	printf("Please input your name (less than or equal to 20 letters)£º");
	scanf("%s", newStudent->name);getchar();
	newStudent->booknum = 0;
	strcpy(newStudent->firstBook, "\0");
	strcpy(newStudent->secondBook, "\0");
	strcpy(newStudent->thirdBook, "\0");
	printf("|  ----------------------------------------  |\n");
	printf("|                                            |\n");
	printf("|   Please confirm whether to save or not?   |\n");
	printf("|         [1] Yes            [2] No          |\n");
	printf("|                                            |\n");
	printf("|  ----------------------------------------  |\n");
	do {
		c = getch();
		if(c == '1') {
			save_student_information(newStudent);    //Store book information in files
			system("cls");
			printf("Saving....");
			sleep(1); 
			system("cls");
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
		else if(c == '2') {
			userface();
			break;
		}
	}while(1);
};


void sign_in() {
	if( identity == 0 ) {
		do {
			system("cls");
			FILE *fp;
			student head, p;
			char inNum[11];
			char inPassword[16];
			head = tt();    //Return the header address
			p = head;
			printf("Please input your number: ");
			scanf("%s", inNum);getchar();
			printf("Please input your password: ");
			scanf("%s", inPassword);getchar();
			if( strlen(inNum) != 10 ) {
				printf("\n\nSorry, this number does not contain 10 digits.\n");
				sleep(1);
				printf("\n[Press any key to return]\n");
				getch();
				sign_in();
				break;
			}
			else {
				p = head;
				while(p != NULL) {
					if( p != NULL && strcmp(p->number, inNum) == 0 && strcmp(p->password, inPassword) == 0 ) {
						system("cls");
						printf("Signing in...\n");
						sleep(1);
						identity = 1;
						preStudent = p;
						system("cls");
						printf("Sign in successfully.\n");
						printf("\n[Press any key to return the main userface]\n");
						getch();
						userface();
					}
					else if( p != NULL && strcmp(p->number, inNum) == 0 && strcmp(p->password, inPassword) != 0 ) {	
						printf("\n\nSorry, your password is wrong.\n");
						printf("\n[Press any key to return the main userface]\n");
						getch();
						userface();
					}
					p = p->next;
				}
				if(p != NULL) {
					printf("Sorry, this number is not registered.\n");
					sleep(1);
					printf("\n[Press any key to return the main userface]\n");
					getch();
					userface();
					break;
				}
			}
		}while(1);
	}
	else if( identity == 1 ) {
		printf("Sorry, the last student has not been signed out yet. You can't sign in.\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 2 ) {
		printf("Sorry, you are now a librarian. You can't sign in to the student identity again.\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}	
};


void sign_out() {
	if( identity == 0 ) {
		printf("Sorry, you are now a guest. You can't sign out.\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 1 ) {
		system("cls");
		student head, p, q;
		char c;
		FILE *fp;
		head = tt();
		q = (student)malloc( sizeof(struct STUDENT) );
		printf("|  -----------------------------------------  |\n");
		printf("|                                             |\n");
		printf("|      Confirm to sign out the identity?      |\n");
		printf("|         [1] Yes             [2] No          |\n");
		printf("|                                             |\n");
		printf("|  -----------------------------------------  |\n");
		while(1) {
			c = getch();
			if(c == '1') {
				p = head;
				while(p != NULL) {
					if( strcmp(p->number, preStudent->number) == 0 ) {
						p = preStudent;
						break;
					}
					else if( strcmp(p->number, preStudent->number) != 0 )
						p = p->next;
				}
				
				printf("Signing out...\n\n");
				sleep(1);
				fp = fopen("studentInformation","wb");
				if(fp == NULL)
					printf("[Error] Cannot find or open file\n");
				if( fwrite(head, sizeof(struct STUDENT), 1, fp) != 1 )
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
				preStudent = q;
				identity = 0;
				system("cls");
				printf("Sign out successfully.\n");
				printf("\n[Press any key to return the main userface]\n");
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
				sleep(1);
				identity = 0;
				printf("Sign out successfully.\n");
				printf("\n[Press any key to return the main userface]\n");
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
		system("cls");
		char c;
		printf("Sorry, you are now a guest and have no right to borrow books.\n");
		sleep(1);
		printf("\n|  -----------------------------------------  |\n");
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
		system("cls");
		printf("Sorry, you are now a librarian and have no right to borrow books.\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
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
			char borName[16];
			char borNum[11];
			char q, ch, t, c;
			FILE *fp;
			head = ss();
			printf("|  ---------------------------------------  |\n");
			printf("|                                           |\n");
			printf("|   Select different ways to borrow books   |\n");
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
			printf("|  ----------------------------------------------------------------------  |\n");
			printf("|                            Operating Book List                           |\n");
			printf("|  ----------------------------------------------------------------------  |\n");
			printf("|   Index |       Name      |   Number   |        Author        | Status   |\n");
			printf("|  ----------------------------------------------------------------------  |\n");
			while(p != NULL) {
				if(p != NULL && strcmp(p->name, borName) == 0 && choose == 1) {       //strcmp() is a string comparison function
					index++;
					printf("|   %-5d   %-15s   %-10s   %-20s     [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				if(p != NULL && strcmp(p->number, borNum) == 0 && choose == 2) {
					index++;
					printf("|   %-5d   %-15s   %-10s   %-20s     [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				p = p->next;
			}
			printf("|  ----------------------------------------------------------------------  |\n");
			if(index == 0) {       //If index = 0, it does not enter the previous search cycle, which means that it does not find the corresponding information.
				system("cls");
				printf("\n\n[Error] No corresponding information was found.\n");
				sleep(1);
				printf("\n|  -----------------------------------------  |\n");
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
					printf("\n\n[Error] Input the wrong index, please re-enter!\n");
				else if( 0 < x <= index ) {
					printf("\n\n|  ----------------------------------  |\n");
					printf("|                                      |\n");
					printf("|     Confirm to borrow this book?     |\n");
					printf("|        [1]Yes        [2]No           |\n");
					printf("|                                      |\n");
					printf("|  ----------------------------------  |\n");
					while(1) {
						t = getch();
						if(t == '1')
							break;
						else if(t == '2') {
							userface();
							break;
						} 
					}
					p = head;
					while(p != NULL && p->x != x)
						p = p->next;
					if(p && p->exist == 1 ) {
						if( strlen(preStudent->firstBook) == 0 || strlen(preStudent->secondBook) == 0 || strlen(preStudent->thirdBook) == 0 ) {
							p->exist = 2;
							strcpy(p->stu_number, preStudent->number);
							while(1) {
								if( strlen(preStudent->firstBook) == 0 ) {
									strcpy(preStudent->firstBook, p->number);
									break;
								}
								if( strlen(preStudent->secondBook) == 0 ) {
									strcpy(preStudent->secondBook, p->number);
									break;
								}
								if( strlen(preStudent->thirdBook) == 0 ) {
									strcpy(preStudent->thirdBook, p->number);
									break;
								}
							}
						}
						else if( strlen(preStudent->firstBook) != 0 && strlen(preStudent->secondBook) != 0 && strlen(preStudent->thirdBook) != 0 ) {
							printf("Sorry, you have borrowed three books(Up to the borrowing limit) and have no right to borrow books.\n");
							sleep(1);
							printf("\n[Press any key to return the main userface]\n");
							getch();
							userface();
							break;
						}
					}
					else if(p && p->exist != 1 ) {
						printf("Sorry, the book has been lent out or damaged.\n");
						sleep(1);
						printf("\n[Press any key to return the main userface]\n");
						getch();
						userface();
						break;
					}
				
					fp = fopen("bookInformation","wb");
					if(fp == NULL)
						printf("[Error] Cannot find or open file\n");
					if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
						printf("[Error] Write error\n");
					fclose(fp);
					if(head != NULL) {
						p = head->next;
						fp = fopen("bookInformation","ab");
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
					sleep(1);
					system("cls");
					printf("\n|  ---------------------------------------------------  |\n");
					printf("|                                                       |\n");
					printf("|     Borrow successfully. Do you want to continue?     |\n");
					printf("|               [1]Yes             [2]No                |\n");
					printf("|                                                       |\n");
					printf("|  ---------------------------------------------------  |\n");
					while(1) {
						c = getch();
						if(c == '1') {
							borrow_book();
							break;
						}
						else if(c == '2') {
							userface();
							break;
						}
					}
					break;
				}
			}
			
		}while(1);
	}
};


void return_book() {
	if( identity == 0 ) {
		system("cls");
		char c;
		printf("Sorry, you are now a guest and have no right to return books.\n");
		sleep(1);
		printf("\n|  -----------------------------------------  |\n");
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
		system("cls");
		printf("Sorry, you are now a librarian and have no right to return books.\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
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
			char reName[16];
			char reNum[11];
			char q, ch, t, c;
			FILE *fp;
			head = ss();
			printf("|  ---------------------------------------  |\n");
			printf("|                                           |\n");
			printf("|   Select different ways to return books   |\n");
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
					printf("|   %-5d   %-15s   %-10s   %-20s     [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				if(p != NULL && strcmp(p->number, reNum) == 0 && choose == 2) {
					index++;
					printf("|   %-5d   %-15s   %-10s   %-20s     [%d]    |\n",index,p->name,p->number,p->author,p->exist);
					p->x = index;
				}
				p = p->next;
			}
			if(index == 0) {       //If index = 0, it does not enter the previous search cycle, which means that it does not find the corresponding information.
				printf("\n[Error] No corresponding information was found.\n");
				sleep(1);
				printf("\n|  -----------------------------------------  |\n");
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
				system("cls");
				printf("Please enter the index of the book you want to return: ");
				scanf("%d", &x);
				getchar();
				if(x > index || x <= 0)
					printf("\n\n[Error] Input the wrong index, please re-enter!\n");
				else
					break;
			}
			printf("\n\n|  ----------------------------------  |\n");
			printf("|                                      |\n");
			printf("|     Confirm to return this book?     |\n");
			printf("|        [1]Yes        [2]No           |\n");
			printf("|                                      |\n");
			printf("|  ----------------------------------  |\n");
			while(1) {
				t = getch();
				if(t == '1') {
					return_book();
					break;
				}
				else if(t == '2') {
					userface();
					break;
				}
			}
			p = head;
			while(p != NULL && p->x != x)
				p = p->next;
			if(p) {
				if( p->exist == 2 ) {
					if( preStudent->firstBook == p->number || preStudent->secondBook == p->number || preStudent->thirdBook == p->number ) {
						p->exist = 1;
						strcpy(p->stu_number, "\0");
						while(1) {
							if( preStudent->firstBook == p->number ) {
								strcpy(preStudent->firstBook, "\0");
								break;
							}
							if( preStudent->secondBook == p->number ) {
								strcpy(preStudent->secondBook, "\0");
								break;
							}
							if( preStudent->thirdBook == p->number ) {
								strcpy(preStudent->thirdBook, "\0");
								break;
							}
						}
					}
					else if( (strlen(preStudent->firstBook) == 0 && strlen(preStudent->secondBook) == 0 && strlen(preStudent->thirdBook) == 0) || p->exist != 2 ) {
						printf("Sorry, you haven't borrowed this book. \n");
						sleep(1);
						printf("[Press any key to return the main userface]\n");
						getch();
						userface();
						break;
					}
				}
				else if( p->exist == 1 || p->exist == 3 ) {
					printf("Sorry, the book has not been lent out. \n");
					sleep(1);
					printf("[Press any key to return the main userface]\n");
					getch();
					userface();
					break;
				}
			}
		
			fp = fopen("bookInformation","wb");
			if(fp == NULL)
				printf("[Error] Cannot find or open file\n");
			if( fwrite(head, sizeof(struct BOOK), 1, fp) != 1 )
				printf("[Error] Write error\n");
			fclose(fp);
			if(head != NULL) {
				p = head->next;
				fp = fopen("bookInformation","ab");
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
			sleep(1);
			system("cls");
			printf("|  ---------------------------------------------------  |\n");
			printf("|                                                       |\n");
			printf("|     Return successfully. Do you want to continue?     |\n");
			printf("|               [1]Yes             [2]No                |\n");
			printf("|                                                       |\n");
			printf("|  ---------------------------------------------------  |\n");
			while(1) {
				c = getch();
				if(c == '1') {
					return_book();
					break;
				}
				else if(c == '2') {
					userface();
					break;
				}
			}
		}while(1);
	}
};


void student_access() {
	system("cls");
	char e;
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
	while(1) {
		e = getch();
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
				continue;
		}
	}
	
};


void sign_in_lib() {
	if( identity == 0 ) {
		system("cls");
		char inPassword[16];
		printf("Please input your password: ");
		scanf("%s", inPassword);getchar();
		if(strcmp(libPassword, inPassword) == 0) {
			system("cls");
			printf("Signing in...\n");
			sleep(1);
			identity = 2;
			system("cls");
			printf("Sign in successfully.\n");
			printf("\n[Press any key to return the main userface]\n");
			getch();
			userface();
		}
		else {
			printf("Sorry, the password is wrong.\n");
			printf("\n[Press any key to return the main userface]\n");
			getch();
			userface();
		}
	}
	else if( identity == 1 ) {
		printf("Sorry, you are now a student. You can't sign in to the librarian identity again.\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 2 ) {
		printf("Sorry, you have signed in as a librarian and do not need to sign in.\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
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
		printf("\nSorry, there are no student in the library for the time being. \n");
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	printf("|  ------------------------------------------------------------------------------------------------------  |\n");
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
		printf("|   %-10s   %-20s  %-15s      %-d      %-10s   %-10s    %-10s   |\n",p->number,p->name,p->password,p->booknum,p->firstBook,p->secondBook,p->thirdBook);
		sum++;  //Calculating the total amount of books
		p = p->next;
	}
	printf("|  ------------------------------------------------------------------------------------------------------  |\n");
	printf("|  The total number of students is£º%-4d                                                                   |\n",sum);
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
		char information[21];
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
			printf("\nExact Search\n");
			printf("\nPlease enter the important of the student you want to find: ");
			gets(information);
		}
		if(choose == 2) {
			system("cls");
			printf("\nFuzzy Search\n");
			printf("\nPlease enter the important of the student you want to find: ");
			gets(information);
		} 
		
		printf("|                                               Student List                                               |\n");
		printf("|  ------------------------------------------------------------------------------------------------------  |\n");
		printf("|     Number   |        Name         |    Password     | Booknum | First book | Second book | Third book   |\n");
		printf("|  ------------------------------------------------------------------------------------------------------  |\n");
		while(p != NULL) {
			if(p != NULL && (strcmp(p->name, information) == 0 || strcmp(p->number, information) == 0 || strcmp(p->firstBook, information) == 0 || strcmp(p->secondBook, information) == 0 || strcmp(p->thirdBook, information) == 0) && choose == 1) {
				printf("|   %-10s   %-20s  %-15s      %-d      %-10s   %-10s    %-10s   |\n",p->number,p->name,p->password,p->booknum,p->firstBook,p->secondBook,p->thirdBook);
			}
			if(p != NULL && (strstr(p->name, information) != NULL || strstr(p->number, information) != NULL || strstr(p->firstBook, information) != NULL || strstr(p->secondBook, information) != NULL || strstr(p->thirdBook, information) != NULL) && choose == 2) {
				printf("|   %-10s   %-20s  %-15s      %-d      %-10s   %-10s    %-10s   |\n",p->number,p->name,p->password,p->booknum,p->firstBook,p->secondBook,p->thirdBook);
			}
			p = p->next;
		}
		printf("|  ------------------------------------------------------------------------------------------------------  |\n");
		sleep(1);
		printf("\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}while(1);
};


void librarian_access() {
	system("cls");
	char e;
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
	while(1) {
		e = getch();
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
				continue;
		}
	}
};


int main() {
	userface();
	return 0;
}

