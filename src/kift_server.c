/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 00:57:43 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/14 07:09:40 by jkalia           ###   ########.fr       */
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
	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number, using htons function to use proper byte order */
	serverAddr.sin_port = htons(8500);
	/* Set IP address to localhost */
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/* Set all bits of the padding field to 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*---- Bind the address struct to the socket ----*/
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*---- Listen on the socket, with 5 max connection requests queued ----*/
	if (listen(welcomeSocket, 5) == 0)
		printf("Listening\n");
	else
		printf("Error\n");

	/*---- Accept call creates a new socket for the incoming connection ----*/
	addr_size = sizeof serverStorage;
	newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

	/*---- Read the message from the server into the buffer ----*/
	recv(newSocket, buffer, 1024, 0);
	int fd = open("out.wav", O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
	printf("Testing: %s\n", buffer);

	/*---- Print the received message ----*/
	file_size = atoi(buffer);
	count = 0;
	printf("Recieved File_Size: %d\n", file_size);
	bzero(buffer, BUFFER);
	while(1)
	{
		//printf("Data\n");
		recv(newSocket, buffer, 1024, 0);
		//write(1, buffer, BUFFER);
		count += write(fd, buffer, BUFFER);
		if (count >= file_size)
			break;
		bzero(buffer, BUFFER);

	}
	return 0;
	init_pocketsphinx(&server);
	printf("Server out: = %s\n", server.reply);
}
