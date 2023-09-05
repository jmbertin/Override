#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <stdbool.h>

int decrypt(unsigned int key)
{
	char			*encryptedStr = "Q}|u`sfg~sf{}|a3";
	char			*expectedStr = "Congratulations!";
	unsigned int	len = strlen(encryptedStr);
	unsigned int	idx = 0;

	while (idx < len)
	{
		encryptedStr[idx] = key ^ encryptedStr[idx]; // XOR operation
		idx++;
	}

	if (strncmp(encryptedStr, expectedStr, 17) == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");

	return (17);
}

void test(unsigned int password, unsigned int decrypt_seed)
{
	if (decrypt_seed - password <= 21)
		decrypt(decrypt_seed - password);
	else
		decrypt(rand());
}

int main(void)
{
	unsigned int password;

	password = time(NULL);
	srand(password);
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%u", password);
	test(password, 322424845);
	return (0);
}
