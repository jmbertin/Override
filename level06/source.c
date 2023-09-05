#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ptrace.h>

unsigned int auth(char *inputString, unsigned int serial)
{
	size_t	inputLength;

	inputLength = strcspn(inputString, "\n");
	inputString[inputLength] = '\0';

	inputLength = strnlen(inputString, 32);

	if (inputLength < 6)
		return (1);

	if (ptrace(PTRACE_TRACEME) == -1)
	{
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m\'---------------------------\'");
		return (1);
	}

	unsigned int calculatedSerial = ((int)inputString[3] ^ 0x1337U) + 0x5eeded;
	for (int i = 0; i < inputLength; i++)
	{
		if (inputString[i] < ' ')
			return 1;
		calculatedSerial += (inputString[i] ^ calculatedSerial) % 0x539;
	}

	if (serial == calculatedSerial)
		return (0);
	return (1);
}

int	main(void)
{
	int				result;
	char			inputBuffer[32];
	unsigned int	serial;

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(inputBuffer, 32, stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &serial);

	result = auth(inputBuffer, serial);
	if (result == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
	}

	return result != 0;
}
