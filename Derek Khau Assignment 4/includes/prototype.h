#ifndef _PROTOTYPEH_
#define _PROTOTYPEH_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct contact
{
	unsigned long phone_number;
	long first_name_posn;
	long last_name_posn;
	long company_name_posn;
	long email_posn;
	long next;
};

struct person
{
	unsigned long phoneNum;
	char* firstName;
	char* lastName;
	char* companyName;
	char* email;
};

void createContact(char [10]);
void displayContact();
void selectContact(int, char [10]);
void edit(char [10], int);
void deleteContact();
int numContact();

#endif


