/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 00:57:46 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/12 01:43:02 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUFFER 1024

int main()
{
	int				count;
	int				clientSocket;
	int				fd;
	int				file_size;
	char			buffer[BUFFER];
	char			temp[BUFFER];
	struct			sockaddr_in serverAddr;
	socklen_t		addr_size;
	struct stat		stat;

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number, using htons function to use proper byte order */
	serverAddr.sin_port = htons(7891);
	/* Set IP address to localhost */
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/* Set all bits of the padding field to 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

	/*---- Connect the socket to the server using the address struct ----*/
	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	/*----Open File and get the size of file----*/
	fd = open("test.wav", O_RDONLY);
	fstat(fd, &stat);
	file_size = stat.st_size;
	printf("File_size = %d\n", file_size);
	sprintf(buffer,"%d", file_size);

	/*---- Send message to the socket of the incoming connection ----*/
	//strcpy(buffer, itoa(file_size));
	send(clientSocket, buffer, 10, 0);
	bzero(temp, BUFFER);
	while ((count = read(fd, temp, BUFFER)) != 0)
	{
	//	sendto(sid, send_data, 1024, 0, (struct sockaddr *)&client_socket, size);
		send(clientSocket, temp, BUFFER, 0);
		bzero(temp, BUFFER);
	}
	return 0;
}
