#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include "head.h"
#include "manager.h"
#include "ui.h"
#include "id.h"
#include "file.h"

//Declare global variables
extern int identity;
extern student preStudent;
extern char libPassword[11];

void input_book() {
	//Check your identity
	if( identity == 0 || identity == 1 ) {
		printf("Sorry, you have no right to input books.\n");
		sleep(1);
		printf("\n\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 2 ) {
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
	}
}


void delete_book() {
	//Check your identity
	if( identity == 0 || identity == 1 ) {
		printf("Sorry, you have no right to delete books.\n");
		sleep(1);
		printf("\n\n[Press any key to return the main userface]\n");
		getch();
		userface();
	}
	else if( identity == 2 ) {
		do {
			system("cls");
			FILE *fp;
			book head, p, d, pre = NULL; 
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
					if(ch == '1') {
						borrow_book();
						break; 
					}  
					else if(ch == '2') {
						userface();
						break;
					}      //Exit the dead loop
				}
			}
			
			while(1) {
				printf("Please enter the index of the book you want to delete: ");
				scanf("%d", &x);
				getchar();
				if(x > index || x <= 0) {
					printf("\n\n[Error] Input the wrong index, please re-enter!\n");
					continue;
				}
				else if( 0 < x <= index ) {
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
					
					//Write the data into the file
					fp = fopen("data\\bookInformation.dat","wb");
					d = head;
					while(1) {
						if( d != NULL ) {
							fwrite( d, sizeof(struct BOOK), 1, fp );
							d = d->next;
						}
						else
							break;
					}
					fclose(fp);
					break;
				}
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
		//Two different search methods
		if(choose == 1) {
			system("cls");
			printf("Exact Search\n");
			printf("\nPlease enter the information of the book you want to find: ");
			gets(information);getchar();
		}
		if(choose == 2) {
			system("cls");
			printf("Fuzzy Search\n");
			printf("\nPlease enter the information of the book you want to find: ");
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
}


void borrow_book() {
	//Check your identity
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
			student thead, tp, tq;
			int index = 0;
			int choose = 0;
			int x;
			char borName[16];
			char borNum[11];
			char q, ch, t, c;
			FILE *fp;
			head = ss();
			thead = tt();
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
							preStudent->booknum += 1;
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
				
					fp = fopen("data\\bookInformation.dat","wb");
					p = head;
					while(1) {
						if( p != NULL ) {
							fwrite( p, sizeof(struct BOOK), 1, fp );
							p = p->next;
						}
						else
							break;
					}
					fclose(fp);
					
					fp = fopen("data\\studentInformation.dat","wb");
					tp = thead;
					while(tp->next != NULL) {
						if( strcmp(thead->number, preStudent->number) == 0 ) {
							thead = preStudent;
							break;
						}
						else if( strcmp(tp->next->number, preStudent->number) == 0 ) {
							tq = preStudent;
							tp->next = tq;
							break;
						}
						else if( strcmp(p->next->number, preStudent->number) != 0 )
							p = p->next;
					}
					tp = thead;
					while(1) {
						if( tp != NULL ) {
							fwrite( tp, sizeof(struct STUDENT), 1, fp );
							tp = tp->next;
						}
						else
							break;
					}
					fclose(fp);
					
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
}


void return_book() {
	//Check your identity
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
			book head, p;
			student thead, tp, tq;
			int index = 0;
			int choose = 0;
			int x;
			char reName[16];
			char reNum[11];
			char q, ch, t, c;
			FILE *fp;
			head = ss();
			thead = tt();
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
			printf("|  ----------------------------------------------------------------------  |\n");
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
			printf("|  ----------------------------------------------------------------------  |\n");
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
				printf("\n\nPlease enter the index of the book you want to return: ");
				scanf("%d", &x);
				getchar();
				if( x > index || x <= 0 ) {
					printf("\n\n[Error] Input the wrong index, please re-enter!\n");
					continue;
				}
				else if( 0 < x <= index ) {
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
								preStudent->booknum -= 1;
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
								printf("\n[Press any key to return the main userface]\n");
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
				
					fp = fopen("data\\bookInformation.dat","wb");
					p = head;
					while(1) {
						if( p != NULL ) {
							fwrite( p, sizeof(struct BOOK), 1, fp );
							p = p->next;
						}
						else
							break;
					}
					fclose(fp);
					
					fp = fopen("data\\studentInformation.dat","wb");
					tp = thead;
					while(tp->next != NULL) {
						if( strcmp(thead->number, preStudent->number) == 0 ) {
							thead = preStudent;
							break;
						}
						else if( strcmp(tp->next->number, preStudent->number) == 0 ) {
							tq = preStudent;
							tp->next = tq;
							break;
						}
						else if( strcmp(p->next->number, preStudent->number) != 0 )
							p = p->next;
					}
					tp = thead;
					while(1) {
						if( tp != NULL ) {
							fwrite( tp, sizeof(struct STUDENT), 1, fp );
							tp = tp->next;
						}
						else
							break;
					}
					fclose(fp);
					
					system("cls");
					printf("Returning, please wait a moment...\n");
					sleep(1);
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
					break;
				}
			}
			
		}while(1);
	}
}


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
}


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
}

