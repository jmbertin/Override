#include <stdio.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>

int main(void)
{
	unsigned int	exitStatus = 0;
	long			childInstructionPointer = 0;
	char			shellcode[32];
	__pid_t			forkid;

	forkid = fork();
	bzero(shellcode,32);

	if (forkid == 0)
	{
		prctl(1,1);
		ptrace(PTRACE_TRACEME, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(shellcode);					
	}
	else
	{
		while (childInstructionPointer != 11)
		{
			wait(&exitStatus);
			if (WIFEXITED(exitStatus) || WIFSTOPPED(exitStatus))
			{
				puts("child is exiting...");
				return (0);
			}
			childInstructionPointer = ptrace(PTRACE_PEEKUSER, forkid, 44, 0);
		}
		puts("no exec() for you");
		kill(forkid, 9);
	}
	return (0);
}
