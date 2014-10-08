#include"ptrchdr.h"
int main()
{
	int i=0;
   	int status =0, pid;
	struct user_regs_struct uregs;

	if((pid = fork())==0){
		ptrace(PTRACE_TRACEME,0,0,0);
		execl("/home/tiljo/Documents/myunexpriments/ptrace/child3","child3",(char *)0);
		printf("execl error..\n");
	}else{
		wait(&status);
		ptrace(PTRACE_CONT,pid,0,0);
		sleep(1);
		//child should have got into the loop by this time
		kill(pid,SIGINT);
		wait(&status);
		ptrace(PTRACE_GETREGS,pid,0,&uregs);
		printf("ebx = %ld\n",uregs.ebx);
		uregs.ebx =245;
		ptrace(PTRACE_SETREGS,pid,0,&uregs);
		ptrace(PTRACE_CONT,pid,0,0);
		wait(&status);
		printf("parent: out of wait: %d..\n",WIFSTOPPED(status));
		sleep(20);
	}
	return 0;
}
