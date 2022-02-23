#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 1024
#define NUMBER 1024

int main(int argc, char * argv[])
{

    if (argc != 2)
    {
        printf("Entered more than 1 argunent.\n");
        exit(0);
    }

    int num = atoi(argv[1]); // integer arg
    //printf("%d\n", num);

    char ** arr;
    char line[MAXSTRING];

    int i, j, strings, arraysize;

    if((arr=(char**)malloc(NUMBER*sizeof(char *)))==NULL)
    {
        printf("Error allocating memory.\n");
        fflush(stdout);
        exit(0);
    }

    strings = 0;
    arraysize = NUMBER;

    while((fgets(line, MAXSTRING, stdin)) != NULL)
    {
        arr[strings] = (char *)malloc(strlen(line)*sizeof(char));
        if(arr[strings]==NULL)
        {
            printf("Error allocating memory.");
            continue;
        }

        strcpy(arr[strings], line);
        strings++;
    }

    //after EOF

	for(int i = 0; i < strings; i++) //bsort
    {
		for(int j = 0; j < strings - i - 1; j++)
        {
			if (strcmp(arr[j], arr[j+1]) > 0)
            {
				char * tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
    		}
		}
	}

    //printf("\nAfter sorting: \n");
    for(i=0; i < strings; i++)
    {
        fprintf(stdout, "%d %s", num, arr[i]);
    }

    free(arr);
    exit(0);

    return 0;
}
