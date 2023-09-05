#include <stdio.h>

int	main(void)
{
	size_t	bytes_read;
	char	*password [100];
	char	*flag [41];
	char	*username [100];
	FILE	*file;

	bzero(username, sizeof(username));
	bzero(flag, sizeof(flag));
	bzero(password, sizeof(password));

	file = fopen("/home/users/level03/.pass","r");
	if (file == NULL)
	{
		fprintf(stderr, "ERROR: failed to open password file\n");
		exit(1);
	}
	bytes_read = fread(flag, 1, 41, file);
	flag[strcspn(flag, "\n")] = 0;
	if (bytes_read != 41)
	{
		fprintf(stderr, "ERROR: failed to read password file\n");
		exit(1);
	}
	fclose(file);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");

	printf("--[ Username: ");
	fgets(username, 100, 0);
	username[strcspn(username, "\n")] = 0;

	printf("--[ Password: ");
	fgets(password, 100, 0);
	password[strcspn(password, "\n")] = 0;

	puts("*****************************************");

	if (strncmp(flag, password, 41) == 0)
	{
		printf("Greetings, %s!\n", username);
		system("/bin/sh");					// Target !
		return 0;
	}
	printf(username);				// security breach here !
	puts(" does not have access!");
	exit(1);
}
