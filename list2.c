/* 'tracer' parent*/
#include"ptrchdr.h"

int main()
{
	char buf[100];
	getcwd(buf,sizeof(buf));
	int pid, status;
	if((pid = fork())== 0){
		execl("/home/tiljo/Documents/myunexpriments/ptrace/child1"/*buf*/,"child1",(char*)0);
		perror("exec:");
		printf("exec failed...\n");
	}else{
		sleep(1);
		kill(pid,SIGINT);
		wait(&status);//wait for child to stop
		if(WIFSTOPPED(status))
			printf("child has stopped..\n");
		sleep(3);
		ptrace(PTRACE_CONT, pid, 0, 0);
		/*will not come out of this wait because child does not terminate*/
		wait(&status);
	}
	return 0;
}
