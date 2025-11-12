#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mini5phone.h"

struct PHONE_NODE *head;

struct PHONE_NODE *addRecord(struct PHONE_NODE *ptr, char name[], char birth[], char phone[])
{
	struct PHONE_NODE *temp = (struct PHONE_NODE *)malloc(sizeof(struct PHONE_NODE));
	if (temp == NULL)
		return NULL;

	strcpy(temp->name, name);
	strcpy(temp->birthdate, birth);
	strcpy(temp->phone, phone);

	if (ptr == NULL)
		temp->next = NULL;
	else
		temp->next = ptr;

	return temp;
}

int loadCSV(char *filename)
{
	FILE *p = fopen(filename, "rt");
	char buffer[1000];
	int i, j, errorCode = 0;

	if (p == NULL)
	{
		return 1;
	}

	// otherwise, the file is open, read CSV

	fgets(buffer, 999, p); // skip the CSV header

	fgets(buffer, 999, p);
	while (!feof(p))
	{
		char name[50];
		char birthdate[12];
		char phone[15];
		// parse the CSV record

		for (j = 0, i = 0; i < 999 && buffer[i] != '\0' && buffer[i] != ','; i++, j++)
			name[j] = buffer[i];

		name[j] = '\0';
		i++;

		for (j = 0; i < 999 && buffer[i] != '\0' && buffer[i] != ','; i++, j++)
			birthdate[j] = buffer[i];

		birthdate[j] = '\0';
		i++;

		for (j = 0; i < 999 && buffer[i] != '\0' && buffer[i] != '\n'; i++, j++)
			phone[j] = buffer[i];

		phone[j] = '\0';

		head = addRecord(head, name, birthdate, phone);

		if (errorCode == 1)
		{
			fclose(p);
			return 1;
		}

		// Get the next record
		fgets(buffer, 999, p);
	}

	fclose(p);

	return 0;
}

int saveCSV(char *filename)
{
	FILE *p = fopen(filename, "wt");
	struct PHONE_NODE *cur = head;

	if (p == NULL)
		return 1;

	fprintf(p, "name,birthdate,phone\n");

	while (cur != NULL)
	{
		fprintf(p, "%s,%s,%s\n", cur->name, cur->birthdate, cur->phone);
		cur = cur->next;
	}

	fclose(p);

	return 0;
}

struct PHONE_NODE *findRecord(struct PHONE_NODE *ptr, char name[])
{
	while (ptr != NULL)
	{
		if (strcmp(ptr->name, name) == 0)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

// helper function for listRecords()
void printHeading()
{
	printf("---- NAME ---- ---- BIRTH DATE ---- ---- PHONE ----\n");
}

// helper function for listRecords()
void printContent(char *name, char *birth, char *phone)
{
	printf("%-14s %-20s %-15s\n", name, birth, phone);
}

// no input, calls helper functions to print all nodes in phonebook (formatted)
int listRecords()
{
	struct PHONE_NODE *ptr = head;
	int i;
	char *n;
	char *b;
	char *p;

	if (ptr == NULL)
		return 1;

	printHeading();

	while (ptr != NULL)
	{
		n = ptr->name;
		b = ptr->birthdate;
		p = ptr->phone;
		printContent(n, b, p);
		ptr = ptr->next;
	}

	return 0;
}

struct PHONE_NODE *delete(struct PHONE_NODE *ptr, char name[], int *deleted)
{
	struct PHONE_NODE *temp = NULL;
	struct PHONE_NODE *current = ptr;

	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
		{
			if (temp == NULL)
				ptr = current->next;
			else
				temp->next = current->next;
			free(current);
			*deleted = 1;
			return ptr;
		}
		temp = current;
		current = current->next;
	}

	return ptr;
}

struct PHONE_NODE *clear(struct PHONE_NODE *head)
{
	struct PHONE_NODE *curr = head;

	while (curr != NULL)
	{
		struct PHONE_NODE *temp = curr;
		curr = curr->next;
		free(temp);
	}

	head = NULL;
	return head;
}
