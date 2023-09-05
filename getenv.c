#include <stdio.h>

int main(void)
{
	extern char** environ;
	int i = 0;
	while (environ[i])
	{
			printf("%p - %s\n", environ[i], environ[i]);
			i++;
	}
}
