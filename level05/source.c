#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void)
{
	unsigned char	currentByte;
	unsigned int	loopCounter;
	unsigned char	*bytePointer;
	unsigned char	fixedValue = 0;
	unsigned char	inputBuffer[100];
	unsigned int	charIndex = 0;

	fgets((char *)inputBuffer, 100, stdin);

	while (1)
	{
		loopCounter = 0xFFFFFFFF;
		bytePointer = inputBuffer;

		while (currentByte != 0 && loopCounter != 0)
		{
			loopCounter--;
			currentByte = *bytePointer;
			bytePointer = bytePointer + (unsigned int)fixedValue * -2 + 1;
		}

		if (~loopCounter - 1 <= charIndex)
		{
			printf(inputBuffer);
			exit(0);
		}

		if (inputBuffer[charIndex] >='A' && inputBuffer[charIndex] <= 'Z')
			inputBuffer[charIndex]  = tolower(inputBuffer[charIndex]);

		charIndex++;
	}
}
