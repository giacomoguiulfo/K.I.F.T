/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 00:57:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/14 18:57:43 by jkalia           ###   ########.fr       */
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




int main()
{
	t_server					server;
	static int				fileno;
	int						welcomeSocket;
	int						count;
	int						newSocket;
	char					buffer[BUFFER];
	int						file_size;
	struct sockaddr_in		serverAddr;
	struct sockaddr_storage	serverStorage;
	socklen_t				addr_size;

	bzero(&server, sizeof(server));
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8500);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
	if (listen(welcomeSocket, 5) == 0)
		printf("Listening\n");
	else
		printf("Error\n");
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	/*---- Read the message from the server into the buffer ----*/
	recv(newSocket, buffer, 1024, 0);
//	int fd = open("out.wav", O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
	int fd = open("out.wav", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR);
	file_size = atoi(buffer);
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
	init_pocketsphinx(&server);
	run_commands(server.recognized, &server);
	printf("Server out: %s\n", server.recognized);
	printf("Server reply: %s\n", server.response);
	return (0);
}
