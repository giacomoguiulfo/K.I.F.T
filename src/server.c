/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 18:00:55 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/12 00:51:25 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

void set_socket(struct sockaddr_in *socket, int type, int host_short, int addr_type)
{
	socket -> sin_family = type;
	socket -> sin_port = htons(host_short);
	socket -> sin_addr.s_addr = htonl(addr_type);
}

void serialize(char *buffer, int count, char *data)
{
	int i=0, j=0;
	char temp1[20];

	sprintf(temp1, "%d", count);
	while(temp1[i] != '\0')
	{
		buffer[j++] = temp1[i++];
	}
	buffer[j++]=' ';

	for(i=0; data[i] != '\0'; i++)
	{
		buffer[j++] = data[i];
	}
	buffer[j] = '\0';
	printf("BUFFER =%ld\n", sizeof(buffer));
}

int main()
{
	int sid = 0, bid = 0, fp;
	char *send_data = (char *)malloc(1024*sizeof(char));
	char temp[1024];
	char *receive_data = (char *)malloc(1024*sizeof(char));
	int fd, count, cnt=0;
	struct sockaddr_in server_socket, client_socket;
	int size = sizeof(client_socket);

	if((sid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Connection error..\n");
		exit(1);
	}

	set_socket(&server_socket, AF_INET, 6000, INADDR_ANY);

	if((bid = bind(sid, (struct sockaddr *)&server_socket, sizeof(struct sockaddr))) == -1)
	{
		printf("Binding error..\n");
		exit(1);
	}

	printf("I am waiting for client..\n");

	recvfrom(sid, receive_data, 1024, 0,(struct sockaddr *)&client_socket, (socklen_t *)&size);
	printf("received data is : %s\n", receive_data);
	fd = open(receive_data, O_RDONLY);
	printf("size = %ld\n", sizeof(send_data));

	while((count=read(fd, temp, 500)) != 0)
	{
		printf("I am inside the loop : %d\n", cnt++);
		serialize(send_data, count, temp);
		printf("Serialized : %s\n", send_data);
		sendto(sid, send_data, 1024, 0, (struct sockaddr *)&client_socket, size);
	}
	printf("I am outside the loop : %d\n", count);
	strcpy(temp, "ENDOFFILE");
	serialize(send_data, sizeof(temp), temp);
	sendto(sid, send_data, 1024, 0, (struct sockaddr *)&client_socket, size);

//	fcloseall();
	close(sid);
	close(fd);
	return 0;
}
