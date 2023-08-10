#ifndef LISTENINGSOCKET_HPP
#define LISTENINGSOCKET_HPP

#include "BindingSocket.hpp"

namespace HDE
{
	class ListeiningSocket : public BindingSocket
	{
	private:
		int backlog;
		int listening;
	public:
		ListeiningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog);
		~ListeiningSocket();
		void startlisten();
	};
}

#endif