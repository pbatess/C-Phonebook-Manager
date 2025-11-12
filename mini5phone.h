struct PHONE_NODE {
        char name[50];
        char birthdate[12];
        char phone[15];
        struct PHONE_NODE *next;
};

extern struct PHONE_NODE *head;

struct PHONE_NODE* addRecord(struct PHONE_NODE *ptr, char name[], char birth[], char phone[]);

int loadCSV(char *filename);

int saveCSV(char *filename);

struct PHONE_NODE* findRecord(struct PHONE_NODE *ptr, char name[]);

void printHeading();

void printContent(char *name, char *birth, char *phone);

int listRecords();

struct PHONE_NODE* delete(struct PHONE_NODE *ptr, char name[], int *deleted);

struct PHONE_NODE* clear(struct PHONE_NODE *head);
