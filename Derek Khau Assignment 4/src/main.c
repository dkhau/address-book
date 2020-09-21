#include "prototype.h"
int main(void)
{
	int numContacts = 0;
	int num = 0;
	char action[10];
	int editNum = 0;
	int deleteNum = 0;

	/*Calculates number of contacts*/
	numContacts = numContact();

	if(numContacts == 0)
	{
		printf("Error! Nothing is in the file!!!\n");
	}

	else
	{
		printf("Number of Contacts: %d\n", numContacts);
	}

	displayContact();
	printf("Action: ");
	fgets(action,9,stdin);
	strtok(action,"\n");
	num = atoi(action);

	/*error message*/
	while((action[0] != 'A' && action[0] != 'X') && (num > numContacts || num == 0))
	{
		printf("Action: ");
		fgets(action,9,stdin);
		strtok(action,"\n");
		num = atoi(action);
	}

	/*program keeps running until user enters X*/
	while(action[0] != 'X')
	{
		/*creates contact*/
		if(action[0] == 'A')
		{	
			createContact(action);
		}

		/*returns to contact list*/
		if(action[0] == 'R')
		{
			numContacts = numContact();
			printf("Number of Contacts: %d\n", numContacts);
			displayContact();
			printf("Action: ");
			fgets(action,9,stdin);
			strtok(action,"\n");
			num = atoi(action);

			/*error message*/
			while((action[0] != 'A' && action[0] != 'X') && (num > numContacts || num == 0))
			{
				printf("Action: ");
				fgets(action,9,stdin);
				strtok(action,"\n");
				num = atoi(action);
			}
		}

		/*contact selects a contact*/
		if(num <= numContacts && num != 0)
		{
			selectContact(num,action);
			editNum = num;
			deleteNum = num;
			num = 0;

			/*error message*/
			while(action[0] != 'R' && action[0] != 'E' && action[0] != 'D')
			{
				printf("Action: ");
				fgets(action,9,stdin);
				strtok(action,"\n");
			}
		}

		/*editing contact, does not work*/
		if(action[0] == 'E')
		{
			edit(action, editNum);
			editNum = 0;
		}

		/*deleting contact, does not work*/
		else if(action[0] == 'D')
		{
			deleteContact(action, deleteNum);
			deleteNum = 0;
		}
	}
	return 0;
}
