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
	int pid1, pid2, pid3, pid4, pid5, pid6, pid7, pid8, pid9, pid10, pid11;
	int p1[2], p2[2], p3[2], p4[2], p5[2], p6[2], p7[2];

	DPRINT("parent start\n");
	
	DPRINT("parent: starting child\n");

	char * fr = argv[1]; //filereader name
	//DPRINT("child 1/2/3/4: %s\n", fr);
	char * fname1= argv[2]; //file1 name
	//DPRINT("child 1 arg: %s\n", fname1);
	char * fname2 = argv[3]; //file 2 name
	//DPRINT("child 2 arg: %s\n", fname2);
	char * fname3 = argv[4]; //file 3 name
	//DPRINT("child 3 arg: %s\n", fname3);
	char * fname4 = argv[5]; //file 4 name
	//DPRINT("child 4 arg: %s\n", fname4);
	char * asorter = argv[6]; //asorter name
	//DPRINT("child 5/6/7/8: %s\n", asorter);
	char * merger = argv[7]; //merger name
	//DPRINT("child 9/10: %s\n", merger);
	char * fname5 = argv[8]; //file 3 name
	//DPRINT("child 11 arg: %s\n", fname5);

	pipe(p1); //create pipe1
	pid1 = fork(); //create child 1

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

	pipe(p3); //create pipe3
	pid3 = fork(); //create child 3

	if(pid3 == 0) //code for child 3
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 3(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);

		dup2(p3[1],STDOUT_FILENO); //write stdout to pipe
		execlp(fr, fr, fname3, NULL);  //exec filereader2 (remember to remove ./ when testing on rabbit)

		DPRINT("child 3(%d): end\n",mypid);
		exit(0);
	}
	
	pipe(p4); //create pipe4
	pid4 = fork(); //create child 4

	if(pid4 == 0) //code for child 4
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 4(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);
		close(p3[1]);

		close(p4[0]);

		dup2(p4[1],STDOUT_FILENO); //write stdout to pipe
		execlp(fr, fr, fname4, NULL);  //exec filereader2 (remember to remove ./ when testing on rabbit)

		DPRINT("child 4(%d): end\n",mypid);
		exit(0);
	}

	pipe(p5); //create pipe5
	pid5 = fork(); //create child 5

	if (pid5 == 0) //code for child 5
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 5(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[1]); //working w p1

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);
		close(p3[1]);

		close(p4[0]);
		close(p4[1]);

		close(p5[0]); //working w p5
	
		dup2(p1[0],STDIN_FILENO); //read stdin to pipe
		dup2(p5[1],STDOUT_FILENO); //write stdout to pipe

		execlp(asorter, asorter, "1", NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)
		
		DPRINT("child 5(%d): end\n",mypid);
		exit(0);
	}

	pipe(p6); //create pipe6
	pid6 = fork(); //create child 6

	if(pid6 == 0) //code for child 6
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 6(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[1]); //working w p2

		close(p3[0]);
		close(p3[1]);

		close(p4[0]);
		close(p4[0]);

		close(p5[0]); //working w p5

		dup2(p2[0],STDIN_FILENO); //read stdin to pipe
		dup2(p5[1],STDOUT_FILENO); //write stdout to pipe

		execlp(asorter, asorter, "2", NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)

		DPRINT("child 6(%d): end\n",mypid);
		exit(0);
	}

	pipe(p7); //create pipe7
	pid7 = fork(); //create child 7

	if(pid7 == 0) //code for child 7
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 7(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[1]); //working w p3

		close(p4[0]);
		close(p4[0]);

		close(p5[0]);
		close(p5[1]);

		close(p6[0]); //working w p6

		dup2(p3[0],STDIN_FILENO); //read stdin to pipe
		dup2(p6[1],STDOUT_FILENO); //write stdout to pipe

		execlp(asorter, asorter, "1", NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)

		DPRINT("child 7(%d): end\n",mypid);
		exit(0);
	}

	pid8 = fork(); //create child 8

	if(pid8 == 0) //code for child 8
	{
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 8(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);
		close(p3[1]);

		close(p4[1]); //working w p4

		close(p5[0]);
		close(p5[1]);

		close(p6[0]); //working w p6

		dup2(p4[0],STDIN_FILENO); //read stdin to pipe
		dup2(p6[1],STDOUT_FILENO); //write stdout to pipe

		execlp(asorter, asorter, "2", NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)

		DPRINT("child 8(%d): end\n",mypid);
		exit(0);
	}

	pid9 = fork(); //create child 9

	if(pid9 == 0)
	{	
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 9(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);
		close(p3[1]);

		close(p4[0]);
		close(p4[1]);

		close(p5[1]); //working w p5

		close(p6[0]);
		close(p6[1]);

		close(p7[0]); //working w p7

		dup2(p5[0],STDIN_FILENO); //read stdin to pipe
		dup2(p7[1],STDOUT_FILENO); //write stdout to pipe

		execlp(merger, merger, NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)
	
		DPRINT("child 9(%d): end\n",mypid);
		exit(0);
	}

	pid10 = fork(); //create child 10

	if(pid10 == 0)
	{	
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 10(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);
		close(p3[1]);

		close(p4[0]);
		close(p4[1]);

		close(p5[0]);
		close(p5[1]);

		close(p6[1]); //working w p6

		close(p7[0]); //working w p7

		dup2(p6[0],STDIN_FILENO); //read stdin to pipe
		dup2(p7[1],STDOUT_FILENO); //write stdout to pipe

		execlp(merger, merger, NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)
	
		DPRINT("child 10(%d): end\n",mypid);
		exit(0);
	}
	
	pid11 = fork(); //create child 11

	if(pid11 == 0)
	{	
		int mypid = getpid();
		int myppid = getppid();
		DPRINT("child 11(%d) ppid(%d): started\n",mypid, myppid);

		close(p1[0]);
		close(p1[1]);

		close(p2[0]);
		close(p2[1]);

		close(p3[0]);
		close(p3[1]);

		close(p4[0]);
		close(p4[1]);

		close(p5[0]);
		close(p5[1]);

		close(p6[0]);
		close(p6[1]);

		close(p7[1]);	

		dup2(p7[0],STDIN_FILENO); //read stdin to pipe
		execlp(merger, merger, fname5, NULL);  //exec filereader1 (remember to remove ./ when testing on rabbit)
	
		DPRINT("child 11(%d): end\n",mypid);
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

	close(p4[0]);
	close(p4[1]);

	close(p5[0]);
	close(p5[1]);

	close(p6[0]);
	close(p6[1]);

	close(p7[0]);
	close(p7[1]);

	waitpid(pid11,NULL,0); //always wait for last process after closing all pipes

	DPRINT("parent(%d): end\n",mypid);

	return 0;
}
