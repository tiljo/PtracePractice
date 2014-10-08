#include"ptrchdr.h"
main()
{
	ptrace(PTRACE_TRACEME,0,0,0);
	while(1);
}
