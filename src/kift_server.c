/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 00:57:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/18 02:56:23 by gguiulfo         ###   ########.fr       */
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

int	g_new_socket;

int		client_out(t_server *server)
{
	int		i;
	char	*out;

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

int		recieve_wav(t_server *server, char *inbuffer)
{
	char	buffer[BUFFER];
	int		file_size;
	int		count;
	int		fd;

	fd = open("out.wav", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR);
	if (fd < 0)
		LOG("ERROR");
	file_size = atoi(inbuffer);
	count = 0;
	printf("fd = %d\nRecieved File_Size: %d\n", fd, file_size);
	bzero(buffer, BUFFER);
	while (1)
	{
		recv(g_new_socket, buffer, 1024, 0);
		count += write(fd, buffer, BUFFER);
		if (count >= file_size)
			break ;
		bzero(buffer, BUFFER);
	}
	init_pocketsphinx(server);
	run_commands(server->recognized, server);
	client_out(server);
	printf(ASC_BRED"Server send: %s\n"ASC_EOC, server->send);
	return (0);
}

int		begin(t_server *server)
{
	char	buffer[BUFFER];

	bzero(server, sizeof(t_server));
	bzero(buffer, BUFFER);
	CHK1(read(g_new_socket, buffer, BUFFER) == -1, printf("ERROR READ"), -1);
	printf("%s\n", buffer);
	if (ISDIGIT(buffer[0]))
		recieve_wav(server, buffer);
	else
	{
		printf("ERROR!");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int		main(int ac, char **av)
{
	struct sockaddr_storage	server_storage;
	struct sockaddr_in		server_addr;
	socklen_t				addr_size;
	t_server				server;
	int						welcome_socket;

	bzero(&server, sizeof(server));
	welcome_socket = socket(PF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
	bind(welcome_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
	listen(welcome_socket, 5) == 0 ? printf("Listening\n") : printf("Error\n");
	addr_size = sizeof(server_storage);
	while (1)
	{
		g_new_socket = accept(welcome_socket,
					(struct sockaddr *)&server_storage, &addr_size);
		printf("%s:%d connected\n", inet_ntoa(server_addr.sin_addr),
					ntohs(server_addr.sin_port));
		begin(&server);
	}
	return (0);
}
