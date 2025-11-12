#include<stdio.h>
#include<string.h>
#include "mini5phone.h"

// same as mini4 menu()
int menu() {
	int selection;
	char garbage[49];

	printf("Phonebook Menu: (1)Add, (2)Delete/Clear (3)Find, (4)List, (5)Quit>\n");
	scanf(" %d", &selection);
	fgets(garbage,48,stdin);

	return selection;
}

// same as mini4 main(), possibly different input parameters
int main() {
	int choice, record;
	char name[50], birth[50], phone[50];
	head = NULL;

	loadCSV("phonebook.csv");

	do {
		choice = menu();

		switch(choice) {
			case 1: 
				printf("Name:\n");  fgets(name,49,stdin);  name[strlen(name)-1]   = '\0';
				printf("Birth:\n"); fgets(birth,49,stdin); birth[strlen(birth)-1] = '\0';
				printf("Phone:\n"); fgets(phone,49,stdin); phone[strlen(phone)-1] = '\0';

				head = addRecord(head, name, birth, phone);
				if (head == NULL) printf("CSV if out of space\n");

				break;
			case 2:
				char response;
				
				char garbage[49];

				printf("(D)elete or (C)lear>\n");
				scanf(" %c", &response);
				fgets(garbage, 48, stdin);
	
				switch(response) {
					case 'D':
						printf("Delete name:\n");
						fgets(name,49,stdin);
						name[strlen(name)-1] = '\0';
						int deleted = 0;
    						head = delete(head, name, &deleted);
  						if (! deleted) printf("Sorry not found\n");
						break;
					case 'C':
 						char response;
                						
						char garbage[49];

               					printf("Are you sure (Y/N)>\n");
                				scanf(" %c", &response);
                				fgets(garbage,48,stdin);

               					switch(response) {
                      					case 'Y':
								head = clear(head);
									break;
                     					case 'N':
                              					break;
                       					default:
                               					printf("Invalid option\n");
           					}
						break;
					default:
						printf("Invalid option\n");
				}
				break;
			case 3:
				printf("Find name:\n"); fgets(name,49,stdin); name[strlen(name)-1] = '\0';
				
				struct PHONE_NODE *node;
				node = findRecord(head, name);

				if (node == NULL) printf("Does not exist\n");
				else {
					printHeading();
					printContent(node->name, node->birthdate, node->phone);
				}
				break;
			case 4:
				record = listRecords();

				if (record != 0) printf("Phonebook.csv does not exist\n");
				break;
			case 5:
				break;

			default:
				printf("Invalid menu selection\n");
		}
	} while (choice != 5);

	saveCSV("phonebook.csv");

	printf("End of phonebook program\n");

	return 0;
}
