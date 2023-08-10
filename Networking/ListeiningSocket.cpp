#include "ListeiningSocket.hpp"

namespace HDE
{
	ListeiningSocket::ListeiningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog) : 
		BindingSocket(domain, service, protocol, port, interface)
	{
		this->backlog = backlog;
	}
	
	ListeiningSocket::~ListeiningSocket()
	{
	}

	void ListeiningSocket::startlisten()
	{
		this->listening = listen(get_connection(), backlog);
	}
}