#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "head.h"
#include "manager.h"
#include "id.h"
#include "ui.h"
#include "file.h"

//Declare global variables
extern int identity;
extern student preStudent;
extern char libPassword[11];

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
				char e;
				while(1) {
					e = getch();
					if( e == '1' ) {
						exit(0);
						break;
					}
					else if( e == '1' ) {
						userface();
						break;
					}
				}
				break;
			default:
				continue;
		}	
	}
}


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
		getch();		//Getch() accepts a character but does not display it
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
	
}


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




