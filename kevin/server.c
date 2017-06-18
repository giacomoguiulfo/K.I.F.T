#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>








#include <string.h>

int ft_putendl_fd(char *str, int fd)
{
	return (write(fd, str, strlen(str)));
}


int main()
{
	int create_socket;
	int new_socket;
	socklen_t addrlen;
	int bufsize = 1024;
	char *buffer = malloc(bufsize);
	struct sockaddr_in address;

	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){
		printf("The socket was created\n");
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);

	if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){
		printf("Binding Socket\n");
	}


	while (1)
	{
		if (listen(create_socket, 10) < 0)
		{
			perror("server: listen");
			exit(1);
		}

		if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {
			perror("server: accept");
			exit(1);
		}

		if (new_socket > 0){
			printf("The Client is connected...\n");
		}

		recv(new_socket, buffer, bufsize, 0);
		printf("%s\n", buffer);
		//write(new_socket, "hello world\n", 12);
		write(new_socket, "Kevin lights on\n", 16);
		write(new_socket, "Ok, I've turned the lights on.\n", 31);
		//ft_putendl_fd("Kevin: lights on\n", new_socket);
		//ft_putendl_fd("Ok, I've turned the lights on.\n", new_socket);
		close(new_socket);
	}
	close(create_socket);
	return 0;
}
