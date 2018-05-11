#include "stdafx.h"
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

static char log_buf[500] = {0,};
static int (* log_func)(void) = NULL;

int log_GET(void)
{
	printf("Logging : %s\n", log_buf);
	return 0;
}

int log_POST(void)
{
	printf("Logging : %s\n", log_buf);
	return 0;
}

int parse(SOCKET sock, char *buf)
{
	char url[1000] = {0,};
	char send_buf[2000]={0,};
	char * token = strtok(buf, " ");
	char * method = token;
	//if(strlen(token+(strlen(method)+1))>1000) exit(1);
	strcpy(url,token+(strlen(method)+1));
	printf("URL : %s ",url);

	if (strcmp(method,"GET") == 0)
	{
		sprintf(send_buf,
			"HTTP/1.1 200 OK\n"
			"Server: simple web server\n"
			"Content-Type: text/html\n\n"
			"<html>\n"
			"<body>\n"
			"Welcome To My WebServer !!\n"
			"</body>\n"
			"</html>"
		);
		send(sock, send_buf, sizeof(send_buf), 0);
		log_func = log_GET;
	} 
	else 
	{
		sprintf(send_buf,
			"HTTP/1.1 404 Not Found\n"
			"Server: simple web server\n"
			"Content-Type: text/html\n\n"
			"<html>\n"
			"<body>\n"
			"Page Not Found!!\n"
			"</body>\n"
			"</html>"
		);
		send(sock, send_buf, sizeof(send_buf), 0);
		log_func = log_POST;
	}

	printf("\nlog func ptr : 0x%x\n",log_func);
	printf("\nlog buf length : %d\n",strlen(url));
	memcpy(log_buf, url, strlen(url));
	printf("\nlog buf : 0x%x\n",&log_buf);
	printf("\nlog func ptr : 0x%x\n",log_func);
	log_func();
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsadata = {0};
	WSAStartup(WORD(2.0), &wsadata);

	sockaddr_in addr_server = {0,};
	sockaddr_in addr_client = {0,};
	SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_server.sin_port = htons(80);

	int addrlen_server = sizeof(sockaddr);
	int addrlen_clt = sizeof(sockaddr);
	char recv_buf[2000]={0,};

	printf("# Simple Web Server v0.1\n");
	printf("[+] Server Start !!\n");

	if (bind(server_sock, (sockaddr *)&addr_server, sizeof(sockaddr)) == SOCKET_ERROR) 
	{
		printf("Bind Error : %d\n", WSAGetLastError());
		exit(-1);
	} 

	if (listen(server_sock, 5) == SOCKET_ERROR) 
	{
		printf("Listen Error : %d\n", WSAGetLastError());
		exit(-1);
	}

	while (1) 
	{
		client_sock = accept(server_sock, (sockaddr *)&addr_client, &addrlen_clt);
	    if (client_sock == INVALID_SOCKET) 
		{
			printf("accept failed. Error No. %d\n", WSAGetLastError());	
		}
		//printf("Connected : %ld\n", client_sock);
		recv(client_sock, recv_buf, 2000, 0);
		parse(client_sock,recv_buf);
		closesocket(client_sock);
	}
	return 0;
}

