// Aly Abderahman
// assignment 1 linklists

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//struct
struct node
{
    int id;
    char name[50];
    struct node *next;
}*head;

//Function prototypes
int delID(int num);
int delname(char * delname);
void insert(char * namein, char * inId);
void display(struct node * displayNode);
void ReadText();

//main function
int  main()
{
//string variables & integer variables
    char nameDelete[50];
    char NameIN[50];
    int id[10];

    int idDelete;
    int i;

    struct node *n;

    head = NULL;

    //input data from text function
    ReadText();

    while(1)
    {

        //User menu
        printf("\n\nMenu\n");
        printf("-------------\n");
        printf("1.Insert\n");
        printf("2.Display\n");
        printf("3.Delete by ID\n");
        printf("4.Delete by Name\n");
        printf("5.Exit\n\n");
        printf("Enter your choice : ");

        if(scanf("%d", &i)<=0)
        {
            printf("Enter only an Integer\n");

            return 0;
        }
        else
        {
            //Switch statements of menu
            switch(i)
            {
                case 1:
                    printf("Enter the name to insert: ");
                    scanf(" %s\n",NameIN);

                    printf("What is the id number for %s? ",NameIN);
                    scanf(" %s\n",id);

                    printf("\n");
                    //Function insert student name and id number
                    insert(NameIN , id);
                    break;
                case 2:
                    //Checks if link list is valid
                    if(head == NULL)
                    {
                        printf("List is Empty\n");
                    }
                    else
                    {
                        printf("Element(s) in the list are : ");
                        //display all students
                        display(n);
                    }
                    break;
                case 3:
                    //Checks if linked list is empty
                    if(head == NULL)
                        printf("List is Empty\n");
                    //If not deletes student data
                    else
                    {
                        printf("Enter the ID number to delete : ");
                        scanf("%d",&idDelete);

                        //Call to function to delete by ID
                        if( (delID(idDelete)) == 1)
                            printf("%d deleted successfully\n",idDelete);
                        else
                            printf("%d not found in the list\n",idDelete);
                    }
                    break;
                case 4:
                    if(head == NULL)
                        printf("List is Empty\n");
                    else
                    {
                        printf("Enter the name to delete : ");
                        scanf(" %s\n",&nameDelete);

                        //Call to function to delete by name
                        if( (delname(nameDelete)) == 1)
                            printf("%s deleted\n",nameDelete);
                        else
                            printf("%s not in the list\n",nameDelete);
                    }
                    break;
                case 5:
                    return 0;
                default:
                    printf("Invalid input please retry\n");
            }
        }
    }
    return 0;
}


void  display(struct node *displayNode)
{
     displayNode = head;

     if(displayNode == NULL)
     {
         return;
     }

    while(displayNode!= NULL)
    {
        printf("Student %s has id %d\n", displayNode->name, displayNode->id);

        displayNode = displayNode->next;
    }

    printf("\n");
}

//Inserts student data in link list nodes
void insert(char * namein, char * inId)
{
    struct node *temp, *helper;

    temp= (struct node *)malloc(sizeof(struct node));

    int intId = atoi(inId);

    //Copies student name to node
    strcpy(temp->name, namein);
    //copies student id to node
    temp->id = intId;
    temp->next = NULL;

    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        helper = head;

        while(helper->next != NULL)
        {
            helper =helper->next;
        }

        helper->next= temp;
    }

    printf("Added student %s with id number %s",namein,inId);
}

//accepts student id
int delID(int num)
{
    struct node *temp, *prev;

    temp = head;

    printf("checking for id %d....\n",num);

    while(temp != NULL)
    {
        if(temp->id == num)
        {
            if(temp == head)
            {
                head = temp->next;
                free(temp);

                //Returns truth value to main
                return 1;
            }
            else
            {
                prev->next = temp->next;
                free(temp);

                //Returns truth value to main
                return 1;
            }
        }
        else
        {
            prev = temp;
            temp = temp->next;
        }
    }

    return 0;
}

int delname(char *name)
{
    struct node *temp, *prev;

    temp = head;

    printf("checking name %s\n",name,name);

    while(temp != NULL)
     {
            if(strcmp(temp->name,name) == 0)
            {
                printf("found %s\n",name);

                if(temp == head)
                {
                    head = temp->next;
                    free(temp);

                    return 1;
                }
                else
                {

                    prev->next = temp->next;
                    free(temp);

                    return 1;
                }
            }

            else
            {
                prev = temp;

                temp = temp->next;
            }
    }

    return 0;
}


//Reads in input text file
void ReadText()
{
    //Variables to store names and id's from input text file
    const LENGTH = 50;
    const char comma[2] = ",";
    char *name;
    char *id;
    char datainfo[LENGTH];

    // file location
    char fileName[] = "AssignmentOneInput.txt";

    //Initializing file pointer
    FILE * filePointer;
    filePointer = fopen(fileName,"r");

    if (filePointer == NULL)
    {
        printf("Error while opening the file.\n");
        exit(0);
    }

    while ((fgets(datainfo, LENGTH, filePointer)) !=NULL)
    {
        //Assigns student name & id  to variable
        name = strtok(datainfo,comma);

        id = strtok(NULL,comma);

        if(name == NULL)
            return;

        //variables in node
        insert(name,id);
    }

      fclose(filePointer);
}
