#ifndef BINDINGSOCKET_HPP
#define BINDINGSOCKET_HPP

#include "SimpleSocket.hpp"

namespace HDE
{
	class BindingSocket : public SimpleSocket
 	{
	private:
		/* data */
	public:
		BindingSocket(int domain, int service, int protocol, int port, u_long interface);
		~BindingSocket();
		int connect_to_network(int sock, struct sockaddr_in address);
	};
	
}

#endif