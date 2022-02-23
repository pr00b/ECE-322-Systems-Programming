#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef DEBUG
#define PDEBUG 1
#else
#define PDEBUG 0
#endif

#define DPRINT(fmt, ...) do { if (PDEBUG) fprintf(stderr, "%s:%d:%s(): "fmt,\
		__FILE__, __LINE__, __func__, ##__VA_ARGS__); } while (0)
#define BUFFSIZE 128

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("Entered more than 1 or less than 1 argument.\n");
        exit(0);
    }
    
    
    DPRINT("Sleeping for 5 seconds...\n");
    sleep(5);

    char * filename = argv[1];
    //printf("%s\n", filename);


    FILE * f1;
    f1 = fopen(filename, "r");

    int fsize;
    //char * str = (char *)malloc(fsize); 

    fseek(f1,0,SEEK_END);
    fsize = ftell(f1);
    rewind(f1);

    char * str = (char *)malloc(fsize); 

    if (f1 == NULL)
    {
        printf("Error opening file.\n");
        exit(0);
    }

    //printf("%s\n", str);
    while(fgets(str, sizeof(str), f1) != NULL)
    {
        //printf("%s", str);
        fputs(str, stdout);
        //fprintf(stdout, "%s", str);
    }

    //while(fgets(str, sizeof(str), f1) == NULL)
    //{
        fclose(f1);
        free(str);
        exit(0);
    //}
    
    //fflush(stdout);
    //exit(0);
    
    return 0;
}
