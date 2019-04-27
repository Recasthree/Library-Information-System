#ifndef __HEAD_H__
#define __HEAD_H__

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

//Created identity( define the global variables )
int identity;			//The type of the identity. [0]Guest(cannot borrow books) [1]student(can borrow and return books) [2]librarian(can manage books and students' information)
student preStudent;
char libPassword[11];

#endif
