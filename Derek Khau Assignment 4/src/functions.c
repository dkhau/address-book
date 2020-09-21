#include "prototype.h"

/*this function counts the number of contacts*/
int numContact()
{
	FILE* fp;
	int num = 0;
	struct contact* address;

	fp = fopen("myContactList.db", "ab+");

	address = malloc(sizeof(struct contact)*1);

	/*starts at beginning of file*/
	fseek(fp,0,SEEK_SET);
	fread(address,sizeof(struct contact),1,fp);

	while(feof(fp) == 0)
	{
		num++;
		if(num > 1)
		{
			address = realloc(address, sizeof(struct contact)*num+1);
		}
		fseek(fp,address->next,SEEK_SET);
		fread(address,sizeof(struct contact),1,fp);
	}	

	free(address);
	fclose(fp);

	return num;
}

/*this function adds a contact to the list*/
void createContact(char action[9])
{
	struct contact* address;
	char* first = " ";
	char* last = " ";
	char* comp = " ";
	char* email = " ";
	int i = 0;
	int emailCounter = 0;
	int phoneNumCheck = 0;
	char buffer[52];
	int length = 0;
	char* ptr;
	FILE* fp;

	fp = fopen("myContactList.db", "ab+");

	/*starts at end of file*/
	fseek(fp , 0, SEEK_END);

	address = malloc(sizeof(struct contact));
	address->phone_number = 0;
	address->first_name_posn = 0;
	address->last_name_posn = 0;
	address->company_name_posn = 0;
	address->email_posn = 0;
	address->next = 0;

	/*user input*/
	printf("\n");
	printf("First Name: ");
	fgets(buffer,52,stdin);
	length = strlen(buffer);
	buffer[length-1] = '\0';
	first = malloc(sizeof(char)*length+1);
	strcpy(first, buffer);

	if(strcmp(buffer,"\0") == 0)
	{
		address->first_name_posn = 0;
		address->last_name_posn = ftell(fp) + sizeof(struct contact);
	}

	else
	{
		address->first_name_posn = ftell(fp) + sizeof(struct contact);
		address->last_name_posn = address->first_name_posn + length;
	}
	length = 0;

	printf("Last Name: ");
	fgets(buffer,52,stdin);
	length = strlen(buffer);
	buffer[length-1] = '\0';
	last = malloc(sizeof(char)*length+1);
	strcpy(last, buffer);

	if(strcmp(buffer,"\0") == 0)
	{
		address->company_name_posn = address->last_name_posn;
		address->last_name_posn = 0;
	}

	else
	{
		address->company_name_posn = address->last_name_posn + length;
	}
	length = 0;

	/*this loops makes user enter a company name if they did not enter a last name*/
	do
	{
		printf("Company Name: ");
		fgets(buffer,52,stdin);
		length = strlen(buffer);
		buffer[length-1] = '\0';
		comp = malloc(sizeof(char)*length+1);
		strcpy(comp, buffer);

	}while(strcmp(last,"\0") == 0 && strcmp(comp, "\0") == 0);


	if(strcmp(buffer,"\0") == 0)
	{
		address->email_posn = address->company_name_posn;
		address->company_name_posn = 0;
	}

	else
	{
		address->email_posn = address->company_name_posn + length;
	}
	length = 0;

	printf("Phone Number (enter only numbers): ");
	fgets(buffer, 52,stdin);
	length = strlen(buffer);
	buffer[length-1] = '\0';

	/*checks for digits for phone number*/
	for (i = 0; i < strlen(buffer); i++)
	{
		if(isdigit(buffer[i]) == 0)
		{
			phoneNumCheck = 1;
			break;
		}

		else
		{
			phoneNumCheck = 0;

		}
	}

	/*checks for length of phone number*/
	while((strlen(buffer) < 7) || (strlen(buffer) > 7 && strlen(buffer) < 10) || (strlen(buffer) > 10) || phoneNumCheck == 1) 
	{
		printf("Phone Number (enter only numbers): ");
		fgets(buffer, 52,stdin);
		length = strlen(buffer);
		buffer[length-1] = '\0';

		/*checks for digits again*/
		for (i = 0; i < strlen(buffer); i++)
		{
			if(isdigit(buffer[i]) == 0)
			{
				phoneNumCheck = 1;
				break;
			}

			else
			{
				phoneNumCheck = 0;

			}
		}
	}
	address->phone_number = strtol(buffer,&ptr,10);
	length = 0;

	printf("Email: ");
	fgets(buffer,52,stdin);
	length = strlen(buffer);
	buffer[length-1] = '\0';

	/*counts number of @ and .*/
	for(i = 0; i < length-1; i++)
	{
		if(buffer[i] == '@' || buffer[i] == '.')
		{
			emailCounter++;
		}
	}

	/*allows user to re enter email*/
	while(emailCounter < 2)
	{
		emailCounter = 0;
		printf("Email: ");
		fgets(buffer,52,stdin);
		length = strlen(buffer);
		buffer[length-1] = '\0';

		for(i = 0; i < length-1; i++)
		{
			/*checks for valid TLD*/
			if((buffer[i] == '@' && buffer[i+1] != '.') ||(buffer[i] == '.' && buffer[i+1] != '\0'))
			{
				emailCounter++;
			}
		}


		if(emailCounter == 2)
		{
			break;
		}
	}

	email = malloc(sizeof(char)*length+1);
	strcpy(email, buffer);

	if(strcmp(buffer,"\0") == 0)
	{
		address->next = address->email_posn;
		address->email_posn = 0;
	}

	else
	{
		address->next = address->email_posn + length;
	}
	length = 0;

	/*asks for next action*/
	printf("Action: ");
	fgets(action,9,stdin);
	strtok(action,"\n");

	/*error message*/
	while(action[0] != 'S' && action[0] != 'R')
	{
		printf("Action: ");
		fgets(action,9,stdin);
		strtok(action,"\n");
	}

	/*saves the contacts*/
	if(action[0] == 'S')
	{
		fwrite(address, sizeof(struct contact), 1,fp);
		if(strcmp(first,"\n") != 0)
		{
			fwrite(first, sizeof(char),strlen(first) + 1,fp);
		}

		if(strcmp(last,"\n") != 0)
		{
			fwrite(last,sizeof(char),strlen(last) + 1,fp);
		}

		if(strcmp(comp,"\n") != 0)
		{
			fwrite(comp,sizeof(char),strlen(comp) + 1 ,fp);
		}

		if(strcmp(email,"\n") != 0)
		{
			fwrite(email,sizeof(char),strlen(email) + 1, fp);
		}

		action[0] = 'R';
	}

	free(first);
	free(last);
	free(comp);
	free(email);
	free(address);

	first = NULL;
	last = NULL;
	comp = NULL;
	email = NULL;
}

/*this function displays the contacts, sorting does not work*/
void displayContact()
{
	struct contact* address;
	struct person* person;
	char buffer[52];
	int length = 0;
	FILE* fp;
	int numOfContacts = 0;

	fp = fopen("myContactList.db", "ab+");

	address = malloc(sizeof(struct contact)*1);
	person = malloc(sizeof(struct person)*1);

	/*start at beginning of file*/
	fseek(fp,0,SEEK_SET);
	fread(address,sizeof(struct contact),1,fp);

	while(feof(fp) == 0)
	{
		numOfContacts++;

		if(numOfContacts > 1 && feof(fp) == 0)
		{
			address = realloc(address,sizeof(struct contact)*(numOfContacts+1));
			person = realloc(address,sizeof(struct person)*(numOfContacts+1));
		}

		/*gets all contact info from the file*/
		fseek(fp,address->first_name_posn, SEEK_SET);
		length = address->last_name_posn - address->first_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].firstName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].firstName,buffer);
		length = 0;

		fseek(fp,address->last_name_posn, SEEK_SET);
		length = address->company_name_posn - address->last_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].lastName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].lastName,buffer);
		length = 0;

		fseek(fp,address->company_name_posn, SEEK_SET);
		length = address->email_posn - address->company_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].companyName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].companyName,buffer);
		length = 0;

		fseek(fp,address->email_posn, SEEK_SET);
		length = address->next - address->email_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].email = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].email,buffer);
		length = 0;

		/*prints out every contact, sorting does not work*/
		printf("%d. %s %s\n", numOfContacts,person[numOfContacts-1].firstName, person[numOfContacts-1].lastName);

		fseek(fp,address->next,SEEK_SET);
		fread(address,sizeof(struct contact),1,fp);
	}
	free(person);
	free(address);
	fclose(fp);
	
}

/*this function displays a contact's full information*/
void selectContact(int num, char action[9])
{
	struct contact* address;
	struct person* person;
	char buffer[52];
	int length = 0;
	FILE* fp;
	int numOfContacts = 0;

	fp = fopen("myContactList.db", "ab+");

	address = malloc(sizeof(struct contact)*1);
	person = malloc(sizeof(struct person)*1);

	fseek(fp,0,SEEK_SET);
	fread(address,sizeof(struct contact),1,fp);

	while(feof(fp) == 0)
	{
		numOfContacts++;

		if(numOfContacts > 1)
		{
			address = realloc(address,sizeof(struct contact)*numOfContacts+1);
			person = realloc(address,sizeof(struct person)*numOfContacts+1);
		}

		/*gets all contact information in a file*/
		fseek(fp,address->first_name_posn, SEEK_SET);
		length = address->last_name_posn - address->first_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].firstName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].firstName,buffer);
		length = 0;

		fseek(fp,address->last_name_posn, SEEK_SET);
		length = address->company_name_posn - address->last_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].lastName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].lastName,buffer);
		length = 0;

		fseek(fp,address->company_name_posn, SEEK_SET);
		length = address->email_posn - address->company_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].companyName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].companyName,buffer);
		length = 0;

		fseek(fp,address->email_posn, SEEK_SET);
		length = address->next - address->email_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].email = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].email,buffer);
		length = 0;

		fseek(fp,address->next,SEEK_SET);
		fread(address,sizeof(struct contact),1,fp);

		/*displays a contact's full information*/
		if(numOfContacts == num)
		{
			printf("\n");
			printf("First Name: %s\n", person[numOfContacts-1].firstName);
			printf("Last Name: %s\n", person[numOfContacts-1].lastName);
			printf("Company Name: %s\n", person[numOfContacts-1].companyName);
			printf("Phone Number: %ld\n", address[numOfContacts-1].phone_number);
			printf("Email: %s\n", person[numOfContacts-1].email);
		}
	}
	free(person);
	free(address);
	fclose(fp);

	/*asks for action*/
	printf("Action: ");
	fgets(action,9,stdin);
	strtok(action,"\n");
}

/*this function edit's a contacts information*/
void edit(char action[9], int contactNum)
{
	struct contact* address;
	struct person* person;
	char buffer[52];
	int length = 0;
	FILE* fp;
	int numOfContacts = 0;
	int i = 0;
	int phoneNumCheck = 0;
	char* ptr;
	int emailCounter = 0;

	fp = fopen("myContactList.db", "ab+");

	address = malloc(sizeof(struct contact)*1);
	person = malloc(sizeof(struct person)*1);

	fseek(fp,0,SEEK_SET);
	fread(address,sizeof(struct contact),1,fp);

	while(feof(fp) == 0)
	{
		numOfContacts++;

		if(numOfContacts > 1)
		{
			address = realloc(address,sizeof(struct contact)*numOfContacts+1);
			person = realloc(address,sizeof(struct person)*numOfContacts+1);
		}

		fseek(fp,address->first_name_posn, SEEK_SET);
		length = address->last_name_posn - address->first_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].firstName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].firstName,buffer);
		length = 0;

		fseek(fp,address->last_name_posn, SEEK_SET);
		length = address->company_name_posn - address->last_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].lastName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].lastName,buffer);
		length = 0;

		fseek(fp,address->company_name_posn, SEEK_SET);
		length = address->email_posn - address->company_name_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].companyName = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].companyName,buffer);
		length = 0;

		fseek(fp,address->email_posn, SEEK_SET);
		length = address->next - address->email_posn;
		fread(buffer,length,1,fp);
		person[numOfContacts-1].email = malloc(sizeof(char)*length);
		strcpy(person[numOfContacts-1].email,buffer);
		length = 0;

		fseek(fp,address->next,SEEK_SET);
		fread(address,sizeof(struct contact),1,fp);
	}
	free(address);
	free(person);

	fclose(fp);

	/*lets user edit contact*/
	printf("First Name: %s\n", person[contactNum-1].firstName);
	printf("Last Name: %s\n", person[contactNum-1].lastName);
	printf("Company Name: %s\n", person[contactNum-1].companyName);
	printf("Phone Number: ");
	fgets(buffer, 52,stdin);
	length = strlen(buffer);
	buffer[length-1] = '\0';
	for (i = 0; i < strlen(buffer); i++)
	{
		if(isdigit(buffer[i]) == 0)
		{
			phoneNumCheck = 1;
			break;
		}

		else
		{
			phoneNumCheck = 0;

		}
	}

	while((strlen(buffer) < 7) || (strlen(buffer) > 7 && strlen(buffer) < 10) || (strlen(buffer) > 10) || phoneNumCheck == 1) 
	{
		printf("Phone Number: ");
		fgets(buffer, 52,stdin);
		length = strlen(buffer);
		buffer[length-1] = '\0';

		for (i = 0; i < strlen(buffer); i++)
		{
			if(isdigit(buffer[i]) == 0)
			{
				phoneNumCheck = 1;
				break;
			}

			else
			{
				phoneNumCheck = 0;

			}
		}
	}
	person[contactNum-1].phoneNum = strtol(buffer,&ptr,10);
	length = 0;

	printf("Email: ");
	fgets(buffer,52,stdin);
	length = strlen(buffer);
	buffer[length-1] = '\0';

	for(i = 0; i < length-1; i++)
	{
		if(buffer[i] == '@' || buffer[i] == '.')
		{
			emailCounter++;
		}
	}

	while(emailCounter < 2)
	{
		emailCounter = 0;
		printf("Email: ");
		fgets(buffer,52,stdin);
		length = strlen(buffer);
		buffer[length-1] = '\0';

		for(i = 0; i < length-1; i++)
		{
			if((buffer[i] == '@' && buffer[i+1] != '.') ||(buffer[i] == '.' && buffer[i+1] != '\0'))
			{
				emailCounter++;
			}
		}


		if(emailCounter == 2)
		{
			break;
		}
	}
	person[numOfContacts-1].email = malloc(sizeof(char)*length+1);
	strcpy(person[contactNum-1].email, buffer);
	contactNum = 0;


	printf("Action: ");
	fgets(action,9,stdin);
	strtok(action,"\n");

	while(action[0] != 'S' && action[0] != 'R' && action[0] != 'D')
	{
		printf("Action: ");
		fgets(action,9,stdin);
		strtok(action,"\n");
	}

	/*does not save properly*/
	if(action[0] == 'S')
	{
		action[0] = 'R';
	}

}

/*this function deletes a contact, does not work*/
void deleteContact(char action[9])
{
	
	action[0] = 'R';
}

