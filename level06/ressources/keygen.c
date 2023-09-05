#include <stdio.h>
#include <string.h>

unsigned int	generateSerialForString(char *inputString)
{
	unsigned int	calculatedSerial;
	size_t			inputLength = strlen(inputString);

	calculatedSerial = (inputString[3] ^ 0x1337U) + 0x5eeded;

	for (int i = 0; i < inputLength; i++)
		calculatedSerial += (inputString[i] ^ calculatedSerial) % 0x539;

	return (calculatedSerial);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s <string>\n", av[0]);
		return (1);
	}

	unsigned int	serial = generateSerialForString(av[1]);

	printf("Serial for %s is: %u\n", av[1], serial);
	return (0);
}
