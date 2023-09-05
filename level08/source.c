#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void log_wrapper(FILE *log_file, char *prefix, char *message)
{
	char	buffer[264];
	size_t	newline_position;

	strcpy(buffer, prefix);
	strcat(buffer, message);

	newline_position = strcspn(buffer, "\n");
	buffer[newline_position] = '\0';

	fprintf(log_file, "LOG: %s\n", buffer);
}

int main(int argc, char **argv)
{
	FILE	*log_file;
	FILE	*source_file;
	int		dest_fd;
	char	char_read;
	char	dest_path[100] = "./backups/";

	if (argc != 2)
		printf("Usage: %s filename\n", argv[1]);

	log_file = fopen("./backups/.log", "w");
	if (log_file == NULL)
	{
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(log_file, "Starting back up ", argv[1]);
	source_file = fopen(argv[1], "r");
	if (source_file == NULL)
	{
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}

	strncat(dest_path, argv[1], 99 - strlen(dest_path));

	dest_fd = open(dest_path, O_CREAT | O_WRONLY, 432);
	if (dest_fd < 0)
	{
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}

	while (1)
	{
		char_read = fgetc(source_file);
		if (char_read == EOF)
			break;
		write(dest_fd, &char_read, 1);
	}

	log_wrapper(log_file, "Finished back up ", argv[1]);

	fclose(source_file);
	close(dest_fd);
	fclose(log_file);

	return (0);
}
