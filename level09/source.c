#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

typedef struct	s_struct_message
{
	char	message[140];
	char	username[40];
	size_t	size;
}				t_struct_message;

void secret_backdoor(void)
{
	char	command[128];

	fgets(command, 128, stdin);
	system(command);
	return;
}

void set_msg(t_struct_message *struct_message)
{
	char	*msg_buffer[1024];

	bzero(msg_buffer, 1024);

	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets((char *)msg_buffer, 1024, stdin);
	strncpy(struct_message->message, (char *)msg_buffer, struct_message->size);
	return;
}

void set_username(t_struct_message *struct_message)
{
	char	*username[160];

	bzero(username, 160);

	puts(">: Enter your username");
	printf(">>: ");
	fgets(username, 128, stdin);

	for (int i = 0; i <= 40 && struct_message->username[i] != '\0'; i++)
	{
		struct_message->username[i] = username[i];
	}

	printf(">: Welcome, %s", struct_message->username);
}

void handle_msg(void)
{
	t_struct_message	*struct_message;

	struct_message->size = 140;
	bzero(struct_message->username, 40);
	set_username(struct_message);
	set_msg(struct_message);
	puts(">: Msg sent!");
}

int main(void)
{
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n- -------------------------------------------");
	handle_msg();
	return 0;
}
