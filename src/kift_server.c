/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 00:57:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/15 03:02:28 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <kift.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	newSocket;

int	client_out(t_server *server)
{ int	i; char	*out; 
	out = server->send;
	i = 0;
	out[i] = '{';
	++i;
	out[i] = '"';
	++i;
	strncpy(&out[i], server->recognized, server->recognized_len);
	i += server->recognized_len;
	out[i] = '"';
	++i;
	out[i] = '"';
	++i;
	strncpy(&out[i], server->response, server->response_len);
	i += server->response_len;
	out[i] = '"';
	++i;
	out[i] = '}';
	++i;
	server->send_len = i;
	return (0);
}

int	recieve_wav(t_server *server, char *inbuffer)
{
	int			file_size;
	int			count;
	char			buffer[BUFFER];

//	unlink("out.wav");
	//	int fd = open("out.wav", O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
	int fd = open("out.wav", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR);
	if (fd < 0)
		LOG("ERROR");
	printf("fd = %d\n", fd);
	file_size = atoi(inbuffer);
	count = 0;
	printf("Recieved File_Size: %d\n", file_size);
	bzero(buffer, BUFFER);
	while(1)
	{
		recv(newSocket, buffer, 1024, 0);
		count += write(fd, buffer, BUFFER);
		if (count >= file_size)
			break;
		bzero(buffer, BUFFER);

	}
	init_pocketsphinx(server);
	run_commands(server->recognized, server);
	client_out(server);
	ft_printf("%{red}Server send: %s\n%{eoc}", server->send);
	return (0);
}

int		begin(t_server *server)
{
	char		buffer[BUFFER];

	bzero(server, sizeof(t_server));
	bzero(buffer, BUFFER);
	CHK1(read(newSocket, buffer, BUFFER) == -1, printf("ERROR READ"), -1);
	printf("%s\n", buffer);
	if (buffer[0] == '#')
	{
		recieve_wav(server, &buffer[1]);
	}
	else 
	{
		printf("ERROR!");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main()
{
	t_server				server;
	static int				fileno;
	int					welcomeSocket;
	char					buffer[BUFFER];
	struct sockaddr_in			serverAddr;
	struct sockaddr_storage			serverStorage;
	socklen_t				addr_size;

	bzero(&server, sizeof(server));
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8300);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if (listen(welcomeSocket, 5) == 0)
		printf("Listening\n");
	else
		printf("Error\n");
	addr_size = sizeof(serverStorage);
	while (1)
	{
		newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
		printf("%s:%d connected\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));
		begin(&server);
		//close(newScocket);
	}
	return (0);
}
