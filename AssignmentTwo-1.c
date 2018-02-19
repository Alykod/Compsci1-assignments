// Aly Abdelrahman
// assignment  two

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 80
#define TRUE 1


// struct
struct produceItem
{
    char produce[20];
    char type[20];
    char soldBy[20];
    float price;
    int quantityInStock;
    struct produceItem *next;
};

// Function prototypes
void addProduceItem(struct produceItem **, char *, char *, char *, float, int);
void count();
void display(struct produceItem *);
void readDataFile(struct produceItem **);
void recursiveReverse(struct produceItem **);
char * trim(char *c);
void writeDataFile(struct produceItem *);

//* Function to push
void addProduceItem(struct produceItem **headRef, char *produce, char *type, char*soldBy, float price, int quantity)

{
    //node
    struct produceItem* temp = (struct produceItem*) malloc(sizeof(struct produceItem));

    // add data
    strcpy(temp->produce, produce);
    strcpy(temp->type, type);
    strcpy(temp->soldBy, soldBy);
    temp->price = price;
    temp->quantityInStock = quantity;

    //old list to new list linking
    temp->next = (*headRef);

    // move the head.
    (*headRef) = temp;
}

 // Function to print linked list
 void display(struct produceItem *headRef)
 {
     struct produceItem *helper = headRef;

     if(helper == NULL)
     {
         return;
     }
     else
     {
         printf("==========================================================================");
         printf(" Item #   Produce       Type             Sold By         Price    In Stock");
         printf("==========================================================================");

         int counter = 1;

         while(helper != NULL)
         {
             printf("%5d %3s %-16s %-13s %6.2f %8d \n",
                    counter++, " ", helper->produce, helper->type,
                    helper->soldBy, helper->price, helper->quantityInStock);

                helper = helper ->next;
         }
     }

     printf("\n");
 }

 // Function to read in the data file
 void readDataFile(struct produceItem **headRef)
 {
     const char comma[2] = ",";
     char dataLine[LENGTH];
     char *produce;
     char *type;
     char *soldBy;
     float price;
     int quantityInStock;

     //File name and location
     char *fileName = "AssignmentTwoInput.txt";
     FILE *filePointer;
    //checking for file
     printf("Trying to open file %s\n", fileName);
     filePointer = fopen(fileName, "r"); //Read node
     if ( filePointer != NULL)
     printf("Successfully opened file %s\n", fileName);

     if( filePointer == NULL )
     {
         perror("Error while opening the file.\n");
         exit(0);
     }

     // Loop until find end of file
     while( ( fgets(dataLine, LENGTH, filePointer) ) != NULL)
     {
         // String tokenize the data line to get the individual fields
         produce = trim(strtok(dataLine, ","));
         type = trim(strtok(NULL, ","));
         soldBy = trim(strtok(NULL, ","));
         price = atof(trim(strtok(NULL, ",")));
         quantityInStock = atoi(trim(strtok(NULL, ",")));

         addProduceItem(headRef, produce, type, soldBy, price, quantityInStock);

     }


     fclose(filePointer);
 }

void recursiveReverse(struct produceItem** head_ref)
{
    struct produceItem* first;
    struct produceItem* rest;

    //* Empty List
    if (*head_ref == NULL)
        return;


    first = *head_ref;
    rest = first->next;

    /* List has only one node */
    if (rest == NULL)
        return;

    // Reverse the rest of the list and put the first element at the end
    recursiveReverse(&rest);
    first->next->next = first;

    first->next = NULL;

    // Fix the head pointer
    *head_ref = rest;
}

char * trim(char *c)
{
    char * e = c + strlen(c) - 1;

    while(*c && isspace(*c))
        c++;

    while(e > c && isspace(*e))
        *e-- = '\0';

    return c;
}
//Write Function
//Writes inventory to an export text file
void writeDataFile(struct produceItem *headRef)
{
    char *fileName = "AssignmentTwoOutput.txt";
    FILE *filePointer;
    int counter = 1;
    struct produceItem *helper = headRef;


    printf("Trying to create file %s\n", fileName);
    filePointer = fopen(fileName, "w"); //Write node

    if( filePointer == NULL )
    {
        perror("Error while opening the file.\n");
        exit(0);
    }

    if(helper == NULL)
    {
        return;
    }
    else
    {
        fprintf(filePointer, "==========================================================================");
        fprintf(filePointer, " Item #   Produce       Type             Sold By         Price    In Stock");
        fprintf(filePointer, "==========================================================================");

    while(helper != NULL)
    {
        fprintf(filePointer,"%5d %3s %-13s %-16s %-13s %6.2f %8d \n",
                counter++, " ", helper->produce, helper->type,
                helper->soldBy, helper->price, helper->quantityInStock);

            helper = helper->next;
    }
  }

    fclose(filePointer);
    printf("Successfully wrote out file %s", fileName);
}

int main()
{
    /* Start with the empty list */
    struct produceItem* head = NULL;
    int choice;

    // Loop until the user wants to exit
    while(TRUE)
    {
        printf("\nList Operations\n");
        printf("===============\n");
        // This option reads in the data file...
        printf("1. Stock Produce Department\n");
        // This option displays to the ...
        printf("2. Display Produce Inventory\n");
        // This option recursively reverses this inventory
        printf("3. Reverse Order of Produce Inventory\n");
        // This option writes to a file the produce inventory
        printf("4. Export Produce Inventory\n");
        // This option exits the program
        printf("5. Exit Program\n");
        printf("Enter your choice : ");

        if (scanf("%d", &choice) <= 0)
        {
            printf("Enter only an Integer\n");
            exit(0);
        }
        else
        {
            switch(choice)
        {
            case 1:
            readDataFile(&head);
            break;
            case 2:
                    display(head);
            break;
            case 3:
                    recursiveReverse(&head);
            break;
            case 4:
                    writeDataFile(head);
            break;
            case 5:
            return 0;
            default:
            printf("Invalid option\n");
            printf("Please enter an integer corresponding to the following menu options");

        }

    }
 }
 return 0;
}
