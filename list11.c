#include"ptrchdr.h"
int main()
{
	int pid,status,dat;
	unsigned int addr = 0x601044;
	if((pid = fork())==0){
		ptrace(PTRACE_TRACEME,0,0,0);
		execl("/home/tiljo/Documents/myunexpriments/ptrace/child5","child5",(char *)0);
		printf("execl error...\n");
	}else{
		wait(&status);
		while(1){
			//do just 1 instruction
			ptrace(PTRACE_SINGLESTEP,pid,0,0);
			wait(&status);
			if(WIFEXITED(status)) break;
			//'addr' is address of 'i' in child5 process
			dat = ptrace(PTRACE_PEEKDATA,pid,addr,0);
			if(dat == 10){
				ptrace(PTRACE_POKEDATA,pid,addr,2341);
				ptrace(PTRACE_CONT,pid,0,0);
				break;
			}
		}
		wait(&status);
		if(WIFEXITED(status))printf("child over\n");
	}
	return 0;
}
