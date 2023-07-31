#ifndef  HTTP_LINUX_HPP
#define HTTP_LINUX_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>

using std::string;
using std::cout;
using std::endl;


namespace http
{
	class TcpServer
	{
	public:
		TcpServer(string ip_address, int port);
		~TcpServer();
	private:
		string m_ip_address;
		int	m_port;
		int m_socket;
		int m_new_socket;
		long m_incomingMessage;
		struct sockaddr_in m_socketAddress;
		unsigned int m_socketAddress_len;
		string m_serverMessage;

		int startServer();
		void clostServer();
		string buildResponse();
	};
}

#endif


//https://osasazamegbe.medium.com/showing-building-an-http-server-from-scratch-in-c-2da7c0db6cb7