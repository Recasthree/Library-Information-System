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

//Write the pointer of p into the file
void save_book(book p) {
	FILE *fp;    //The pointer of the file
	fp = fopen("data\\bookInformation.dat", "ab");   //Open a binary file named bookInformation by additional opening file and writing data at the end of the file
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


//Read out the data of the file to the linked list and return the value as the header address
book ss() {
	FILE *fp;       //The pointer of the file
	int n = 0;
	book head = NULL;
	book p, p2, pr = NULL;
	fp = fopen("data\\bookInformation.dat", "ab+");     //Open files in a read-only manner
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
	fp = fopen("data\\studentInformation.dat", "ab+");     //Open files in a read-only manner
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


void save_student_information(student p) {
	FILE *fp;    //The pointer of the file
	fp = fopen("data\\studentInformation.dat", "ab");   //Open a binary file named studentInformation by additional opening file and writing data at the end of the file
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




