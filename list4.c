#include"ptrchdr.h"
int main()
{
	int pid,status;
	if((pid = fork())== 0){
		ptrace(PTRACE_TRACEME,0,0,0);
		execl("/home/tiljo/Documents/myunexpriments/ptrace/child2","child2",(char *)0);
		printf("exec failed...\n");
	}else{
		wait(&status);
		if(WIFSTOPPED(status))
			printf("child has stopped...\n");
		sleep(10);
		ptrace(PTRACE_CONT,pid,0,0);
		wait(&status);
	}
	return 0;
}
