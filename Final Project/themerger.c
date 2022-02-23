#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 128
#define NUMBER 10000


int main(int argc, char * argv[])
{
    char * filename = argv[1]; //optional filename arg
    //printf("%s\n", filename);

    char ** arr1;
    char ** arr2;
    char line[MAXSTRING];

    if((arr1 = (char **)malloc(NUMBER * sizeof(char *))) == NULL)
    {
        printf("Malloc error\n");
        fflush(stdout);
        exit(1);
    }

    if((arr2 = (char **)malloc(NUMBER * sizeof(char *))) == NULL)
    {
        printf("Malloc error\n");
        fflush(stdout);
        exit(1);
    }

    int strings = 0;
    int count1 = 0;
    int count2 = 0;

    while((fgets(line, MAXSTRING, stdin)) != NULL) //read data from stdin until EOF
    {
        arr1[strings] = (char *)malloc(strlen(line)*sizeof(char));
        arr2[strings] = (char *)malloc(strlen(line)*sizeof(char));

        if(strstr(line, "1"))
        {
            strcpy(arr1[strings], line);
            count1++;

        }
        if(strstr(line, "2"))
        {
            strcpy(arr2[strings], line);
            count2++;
        }
        strings++;
    }

    int sum;
    sum = strings + strings;
    int sum2;
    sum2 = count1 + count2;
    char * arr3[sum];

    int i;

    for(i = 0; i < strings; i++) //merge 
    {
        arr3[i] = arr1[i];
        arr3[i+strings] = arr2[i];
    }

    if (argc == 2)
    {
        FILE * f1;
        f1 = fopen(filename, "w");

        for(i=0; i < sum; i++)
        {
            fprintf(f1,"%s", arr3[i]); //print arr3 to stdout
        }
    }
    else
    {
        /*printf("\nArray 1: \n");
        for(i=0; i < strings; i++)
        {
            printf("%s", arr1[i]); // print arr1 to stdout
        }

        printf("\nArray 2: \n");
        for(i=0; i < strings; i++)
        {
            printf("%s", arr2[i]); // print arr2 to stdout
        }*/

        printf("\nArray 3: \n");
        for(i=0; i < sum; i++)
        {
            printf("%s", arr3[i]); // print arr3 to stdout
        }
        exit(0);
    }

    free(arr1);
    free(arr2);

    exit(0);

    return 0;
}
