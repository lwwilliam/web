#ifndef SIMPLESERVER_HPP
#define SIMPLESERVER_HPP

#include <unistd.h>
#include <iostream>
#include "../hdenetworking.hpp"

namespace HDE
{
	class SimpleServer
	{
	private:
		ListeningSocket *socket;
		virtual void accepter() = 0;
		virtual void handler() = 0;
		virtual void responder() = 0;
	public:
		SimpleServer(int domain, int service, int protocol, int port, u_long interface, int backlog);
		~SimpleServer();

		virtual void launch() = 0;
		ListeningSocket *get_socket();
	};
}

#endif