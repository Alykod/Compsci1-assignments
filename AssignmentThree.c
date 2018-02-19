// Aly Abdelrahman
//COP assignment 3

#include <stdio.h>
#include <stdlib.h>

void readDataFile();
void ExchangeCharachters(char str[], int i, int j);
void RecursivePermute(char str[], int k);

int main ()
{
	readDataFile();
	printf("Processed input and wrote output. \n");
	system("pause");
	return 0;
}

void readDataFile ()
{
	const LENGTH = 50;
	char data[LENGTH];
	char fileName[]= "AssignmentThreeInput.txt";
	FILE *filePointer;

	printf("Trying to open file %s\n", fileName);
	filePointer = fopen(fileName, "r");

	if (filePointer == NULL);
	{

		perror("Error opening file\n");
		exit(0);
	}


	while (fgets(data, LENGTH, filePointer) != NULL)
	{
	    strtok(data, "\n");
		printf("Permuting %s\n", data);
		RecursivePermute(data, 0);
	}

	fclose;

}
void RecursivePermute(char str[], int k)
{
	int j;
	char fileName = "AssignmentThreeOutput.txt";
	FILE *filePointer;

	filePointer = fopen(fileName, "w");

	if( filePointer == NULL)
	{
		perror("Error while opening the file.\n" );
		exit(0);
	}


	if (k == strlen(str))
	{
		printf("not our base case.\n");
		fprintf(filePointer, "%s\n", str);
	}
	else
	{

		for (j = k; j < strlen(str); j++)
		{
			//printf("Calling first charachters.");
			ExchangeCharachters(str, k, j );

			RecursivePermute(str, k + j);

			printf("??");
			ExchangeCharachters(str, j, k);
		}
	}
	fclose(filePointer);
}
void ExchangeCharachters(char str[], int i, int j)
{
	char temp = str[i];
	str[i] = str[j];
	str[j] = temp;
}
