/* compile this program to 'child1'*/
#include"ptrchdr.h"
int main()
{
	ptrace(PTRACE_TRACEME,0,0,0);
	while(1) printf("hello\n");
	return 0;
}
