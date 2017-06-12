/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkalia <jkalia@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 18:00:39 by jkalia            #+#    #+#             */
/*   Updated: 2017/06/12 00:51:20 by jkalia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>

void set_socket(struct sockaddr_in *socket, int type, int host_short)
{
	socket -> sin_family = type;
	socket -> sin_port = htons(host_short);
}

void deserialize(char *buffer, int *size, char *data)
{
	int i=0, j=0;
	char temp1[20];

	while(buffer[i] != ' ')
	{
		temp1[j++] = buffer[i++];
	}
	temp1[j] = '\0';
	printf("\nINT : %s\n", temp1);
	*size = atoi(temp1);

	i++;
	j=0;

	while(buffer[i] != '\0')
	{
		data[j++] = buffer[i++];
	}
	data[j++] = '\0';
}

int main()
{
	int sid = 0, bid = 0, con = 0;
	char *send_data = (char *)malloc(1024*sizeof(char));
	char *receive_data = (char *)malloc(1024*sizeof(char));
	char *temp = (char *)malloc(1024*sizeof(char));
	struct hostent *host;
	struct sockaddr_in server_socket;
	int size = sizeof(server_socket);

	if((sid = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		printf("Connection error at client side..\n");
		exit(1);
	}

	set_socket(&server_socket, AF_INET, 6000);

	if (inet_aton("127.0.0.1", &server_socket.sin_addr)==0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	printf("Enter the name of the file you want to see : ");
	scanf("%s", send_data);
	int fd = open("sanket.mp3", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IXUSR);
	sendto(sid, send_data, 1024, 0, (struct sockaddr *)&server_socket, size);
	printf("================= Contents of the File =====================\n");
	while(1)
	{
		int size;
		recvfrom(sid, temp, 1024, 0, (struct sockaddr *)&server_socket, (socklen_t *)&size);
		printf("Deserialize it : %s\n",temp);
		deserialize(temp, &size, receive_data);
		if(!strcmp(receive_data, "ENDOFFILE"))
		{
			printf("============================================================\n");
			break;
		}
		else
			write(fd, receive_data, size);
	}
//	fcloseall();
	close(sid);

	return 0;
}
