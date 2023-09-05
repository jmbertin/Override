#include <stdbool.h>


char	a_user_name[];

int	verify_user_pass(char *password)
{
	char	*correct_password = "admin";
	int		return_value;

	return_value = strcmp(password, correct_password);

	return (return_value);
}

int	verify_user_name(void)
{
	char	*correct_username = "dat_wil";
	int		return_value;

	puts("verifying username....\n");
	return_value = strncmp(a_user_name, correct_username, 7);

	return (return_value);
}

int	main(void)
{
	int		return_value;
	char	buffer[16];

	bzero(buffer, 16);
	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");
	fgets(&a_user_name, 0x100, 0); 
	if (verify_user_name() == 0) 
	{
		puts("Enter Password: ");
		fgets(buffer, 100, 0);
		if ((verify_user_pass(buffer) == 0) || (verify_user_pass(buffer) != 0))
		{
			puts("nope, incorrect password...\n");
			return_value = 1;
		}
		else
			return_value = 0;
	}
	else
	{
		puts("nope, incorrect username...\n");
		return_value = 1;
	}
	return (return_value);
}
