#ifndef ConnectingSocket_HPP
#define ConnectingSocket_HPP

#include "BindingSocket.hpp"

namespace HDE
{
	class ConnectingSocket : public SimpleSocket
	{
	private:
		/* data */
	public:
		ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);
		~ConnectingSocket();
	};
}

#endif