#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
	int pid1, pid2, pid3, pid4, pid5;
	int p1[2], p2[2], p3[2];

	DPRINT("parent start\n");
	
	DPRINT("parent: starting child\n");

	char * fr = argv[1]; //filereader name
	//DPRINT("child 1/2: %s\n", fr);
	char * fname1= argv[2]; //file1 name
	//DPRINT("child 1 arg: %s\n", fname1);
	char * fname2 = argv[3]; //file 2 name
	//DPRINT("child 2 arg: %s\n", fname2);
	char * asorter = argv[4]; //asorter name
	//DPRINT("child 3/4: %s\n", asorter);
	char * merger = argv[5]; //merger name
	//DPRINT("child 5: %s\n", merger);
	char * fname3 = argv[6]; //file 3 name
	//DPRINT("child 5 arg: %s\n", fname3);

	pipe(p1); //create pipe1
	pid1 = fork(); //create child1

	if (pid1 == 0) //code for child 1
    {     
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 1(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]); // close pipe1 read end
		dup2(p1[1],STDOUT_FILENO); //write stdout to pipe

		execlp(fr, fr, fname1, NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)

		DPRINT("child 1(%d): end\n",mypid);
		exit(0);
	}

	pipe(p2); //create pipe2
	pid2 = fork(); //create child 2

	if(pid2 == 0) //code for child 2
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 2(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);

		dup2(p2[1],STDOUT_FILENO); //write stdout to pipe
		execlp(fr, fr, fname2, NULL);  //exec filereader2 (remember to remove ./ when testing on rabbit)

		DPRINT("child 2(%d): end\n",mypid);
		exit(0);
	}

	pipe(p3); //create pipe1
	pid3 = fork(); //create child 3

	if (pid3 == 0) //code for child 3
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 3(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);
	
		dup2(p1[0],STDIN_FILENO); //read stdin to pipe
		dup2(p3[1],STDOUT_FILENO); //write stdout to pipe

		execlp(asorter, asorter, "1", NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)
		
		DPRINT("child 3(%d): end\n",mypid);
		exit(0);
	}

	pid4 = fork(); //create child 4

	if(pid4 == 0) //code for child 4
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 4(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[1]);

		close(p3[0]);

		dup2(p2[0],STDIN_FILENO); //read stdin to pipe
		dup2(p3[1],STDOUT_FILENO); //read stdin to pipe

		execlp(asorter, asorter, "2", NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)

		DPRINT("child 4(%d): end\n",mypid);
		exit(0);
	}

	pid5 = fork(); //create child 5

	if(pid5 == 0)
	{	
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 5(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[1]);	

		dup2(p3[0],STDIN_FILENO); //read stdin to pipe
		execlp(merger, merger, fname3, NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)
	
		DPRINT("child 5(%d): end\n",mypid);
		exit(0);
	}

	int mypid = getpid();
	DPRINT("parent(%d):continue\n",mypid);

	close(p1[0]);
	close(p1[1]);

	close(p2[0]);
	close(p2[1]);
	
	close(p3[0]);
	close(p3[1]);

	waitpid(pid5,NULL,0); //always wait for last process after closing all pipes

	DPRINT("parent(%d): end\n",mypid);

	return 0;
}
