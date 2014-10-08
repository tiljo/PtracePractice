#include"ptrchdr.h"
int main()
{
	int pid,data,status = 0;

	if((pid = fork())==0){
		ptrace(PTRACE_TRACEME,0,0,0);
		execl("/home/tiljo/Documents/myunexpriments/ptrace/child4","child4",(char *)0);
		printf("execl error...\n");
	}else{
		wait(&status);
		data = ptrace(PTRACE_PEEKDATA,pid,0x601040,0);
		printf("data = %d\n",data);
		data = 245;
		ptrace(PTRACE_POKEDATA,pid,0x601040,data);
		ptrace(PTRACE_CONT,pid,0,0);
		wait(&status);
		printf("parent: out of wait: %d...\n",WIFSTOPPED(status));
		sleep(20);
	}
	return 0;
}


