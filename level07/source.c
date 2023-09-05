#include <stdio.h>
#include <string.h>

int	store_number(int *data_array)
{
	int	number, index;

	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();

	if (index % 3 == 0 || number >> 0x18 == 0xb7)
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	else
	{
		data_array[index] = number;
		return (0);
	}
}

int	get_unum(void)
{
	int input_num = 0;

	fflush(stdout);
	scanf("%u", &input_num);
	clear_stdin();

	return (input_num);
}

int	read_number(int *data_array)
{
	int	index;

	printf(" Index: ");
	index = get_unum();

	printf(" Number at data[%u] is %u\n", index, data_array[index]);

	return (0);
}



void print_welcome_message()
{
	puts(
		"----------------------------------------------------\n"
		"  Welcome to wil's crappy number storage service!   \n"
		"----------------------------------------------------\n"
		" Commands:                                           \n"
		"    store - store a number into the data storage    \n"
		"    read   - read a number from the data storage     \n"
		"    quit  - exit the program                         \n"
		"----------------------------------------------------\n"
		"   wil has reserved some storage :>                  \n"
		"----------------------------------------------------\n");
}

int	main(int argc, char **argv, char **envp)
{
	char car;
	int intVar, longueur;
	int uintVar;
	unsigned int *ptrVar;
	char *charPtrVar;
	char *bytePtrVar;
	int in_GS_OFFSET;
	char **argCopy1;
	char **argCopy2;
	unsigned int local_storage[100];
	unsigned int userInput[7];
	int local_14;

	argCopy1 = argv;
	argCopy2 = envp;
	local_14 = *(int *)(in_GS_OFFSET + 0x14);
	memset(userInput, 0, sizeof(userInput));
	memset(local_storage, 0, sizeof(local_storage));

	while (*argCopy1 != NULL)
	{
		memset(*argCopy1, 0, strlen(*argCopy1));
		argCopy1++;
	}

	while (*argCopy2 != NULL)
	{
		memset(*argCopy2, 0, strlen(*argCopy2));
		argCopy2++;
	}

	print_welcome_message();

	while (1)
	{
		printf("Input command: ");
		fgets((char *)userInput, 0x14, stdin);
		longueur = strlen((char *)userInput);
		userInput[longueur] = 0;

		if (strncmp((char *)userInput, "store", 5) == 0)
			userInput[0] = store_number(local_storage);
		else if (strncmp((char *)userInput, "read", 4) == 0)
			userInput[0] = read_number(local_storage);
		else if (strncmp((char *)userInput, "quit", 4) == 0)
		{
			if (local_14 == *(int *)(in_GS_OFFSET + 0x14))
				return 0;
			__stack_chk_fail();
		}
		if (userInput[0] == 0)
			printf("Completed %s command successfully\n", userInput);
		else
			printf("Failed to do %s command\n", userInput);

		memset(userInput, 0, sizeof(userInput));
	}
}
