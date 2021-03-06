// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};
	char a[2000];
	int i = 0;
	usleep(500000);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	while (1)
	{
		// write your code!
		while (1)
		{
			scanf("%c", &a[i]);
			if (a[i] == '\n')
				break;
			else
				i++;
		}
		memset(buffer, '\0', sizeof(buffer) / sizeof(char));
		a[i] = '\0';
		i = 0;
		send(sock, a, strlen(a), 0);
		if (!strcmp(a, "kill"))
		{
			break;
		}
		else
		{
			valread = read(sock, buffer, 1024);
			printf("%s\n", buffer);
		}
	}

	return 0;
}
