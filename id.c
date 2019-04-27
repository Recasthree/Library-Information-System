#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "head.h"
#include "manager.h"
#include "file.h"
#include "id.h"
#include "ui.h"

//Declare global variables
extern int identity;
extern student preStudent;
extern char libPassword[11];

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







