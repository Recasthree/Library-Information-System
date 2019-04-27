#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>			//for the sleep()
#include "head.h"
#include "manager.h"
#include "id.h"
#include "file.h"
#include "ui.h"

extern int identity;
extern student preStudent;
extern char libPassword[11];

int main() {
	identity = 0;		//Initialize the identity variable
	strcpy(libPassword, "123");			//Initialize the password of the librarian, you can change it by replacing "123" with the password you like
	userface();
	return 0;
}

