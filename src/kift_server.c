/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kift_server.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 00:57:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/28 08:54:58 by gguiulfo         ###   ########.fr       */
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
#include <netdb.h>
#include <sys/types.h>
#include <errno.h>

int	g_new_socket;

static int	client_out(t_server *server, int fd)
{
	int		i;
	char	*out;

	out = server->send;
	i = 0;
	strncpy(&out[i], server->recognized, server->recognized_len);
	i += server->recognized_len;
	out[i] = ';';
	++i;
	strncpy(&out[i], server->response, server->response_len);
	i += server->response_len;
	server->send_len = i;
	// close(fd);
	return (0);
}

static void	recieve_wav(t_server *server, char *inbuffer)
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
	client_out(server, fd);
	dprintf(g_new_socket, "Server send: %s\n", server->send);
	kift_log(server->recognized, server->response);
}

static int	begin(int filedes)
{
	t_server server;
	int		nbytes;
	char	buffer[BUFFER];
	static int flag = 0;

	bzero(&server, sizeof(t_server));
	bzero(buffer, BUFFER);
	nbytes = read(filedes, buffer, BUFFER);
	if (nbytes < 0)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", buffer);
	if (ISDIGIT(buffer[0]))
		recieve_wav(&server, buffer);
	else
	{
		printf("ERROR!");
		exit(EXIT_FAILURE);
	}
	system("rm -f out.wav");
	return (0);
}

static int	check_port(int argc, char **argv)
{
	int	tmp;

	if (argc < 2)
	{
		dprintf(STDERR_FILENO, "%s: Too few arguments\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	tmp = atoi(argv[1]);
	if (tmp < 1024 || tmp > 49151)
	{
		dprintf(STDERR_FILENO, "%s: Invalid port number\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

// int			main(int argc, char **argv)
// {
// 	struct sockaddr_storage	server_storage;
// 	struct sockaddr_in		server_addr;
// 	socklen_t				addr_size;
// 	t_server				server;
// 	int						welcome_socket;
//
// 	bzero(&server, sizeof(server));
// 	welcome_socket = socket(PF_INET, SOCK_STREAM, 0);
// 	server_addr.sin_family = AF_INET;
// 	server_addr.sin_port = htons(check_port(argc, argv));
// 	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
// 	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));
// 	bind(welcome_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
// 	listen(welcome_socket, 5) == 0 ? printf("Listening\n") : printf("Error\n");
// 	addr_size = sizeof(server_storage);
// 	while (1)
// 	{
// 		g_new_socket = accept(welcome_socket,
// 					(struct sockaddr *)&server_storage, &addr_size);
// 		printf("%s:%d connected\n", inet_ntoa(server_addr.sin_addr),
// 					ntohs(server_addr.sin_port));
// 		begin(&server);
// 	}
// 	return (0);
// }

#define PORT    4242
#define MAXMSG  512

int	make_socket (uint16_t port)
{
	int sock;
	struct sockaddr_in name;
	/* Create the socket. */
	sock = socket (PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror ("socket");
		exit (EXIT_FAILURE);
	}
	/* Give the socket a name. */
	name.sin_family = AF_INET;
	name.sin_port = htons(port);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	return (sock);
}

int
read_from_client (int filedes)
{
	char buffer[MAXMSG];
	int nbytes;

	nbytes = read (filedes, buffer, MAXMSG);
	if (nbytes < 0)
	{
		/* Read error. */
		perror ("read");
		exit (EXIT_FAILURE);
	}
	else if (nbytes == 0)
	/* End-of-file. */
	return -1;
	else
	{
		/* Data read. */
		fprintf (stderr, "Server: got message: `%s'\n", buffer);
		return 0;
	}
}

int	main(void)
{
	int sock;
	fd_set active_fd_set, read_fd_set;
	int i;
	struct sockaddr_in clientname;
	size_t size;
	/* Create the socket and set it up to accept connections. */
	sock = make_socket(PORT);
	if (listen (sock, 1) < 0)
	{
		perror ("listen");
		exit (EXIT_FAILURE);
	}
	/* Initialize the set of active sockets. */
	FD_ZERO (&active_fd_set);
	FD_SET (sock, &active_fd_set);
	while (1)
	{
		/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			perror ("select");
			exit (EXIT_FAILURE);
		}
		/* Service all the sockets with input pending. */
		for (i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd_set))
		{
			if (i == sock)
			{
				/* Connection request on original socket. */
				int new;
				size = sizeof (clientname);
				new = accept(sock, (struct sockaddr *) &clientname, &size);
				if (new < 0)
				{
					perror("accept");
					exit(EXIT_FAILURE);
				}
				fprintf(stderr,
					"Server: connect from host %s, port %hd.\n",
					inet_ntoa(clientname.sin_addr),
					ntohs(clientname.sin_port));
					FD_SET(new, &active_fd_set);
			}
			else
			{
				/* Data arriving on an already-connected socket. */
				// if (read_from_client (i) < 0)
				// {
					// bzero(&server, sizeof(t_server));
					begin(i);
					close(i);
					FD_CLR(i, &active_fd_set);
				// }
			}
		}
	}
}
