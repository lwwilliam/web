#include "http_linux.hpp"

namespace 
{
	void log(const string &message)
	{
		cout << message << endl;
	}
	void exitWithError(const string &errorMessage)
	{
		log("Error: " + errorMessage);
		exit(1);
	}
} // namespace 


namespace http
{
	TcpServer::TcpServer(string ip_address, int port) : 
	m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(), 
	m_incomingMessage(), m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)), 
	m_serverMessage(buildResponse())
	{
		startServer();
	}
	TcpServer::~TcpServer()
	{
		clostServer();
	}

	int TcpServer::startServer()
	{
		m_socket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_socket < 0)
		{
			exitWithError("Cannot create socket");
			return 1;
		}
		return 0;
	}

	void TcpServer::clostServer()
	{
		close(m_socket);
		close(m_new_socket);
		exit(0);
	}

	string TcpServer::buildResponse()
	{
		string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
		std::ostringstream ss;
		ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
			<< htmlFile;

		return ss.str();
	}

	void TcpServer::startListen()
	{
		if (listen(m_socket, 20) < 0)
		{
			exitWithError("Socket listen failed");
		}
		std::ostringstream ss;
		ss << "\n*** Listening on ADDRESS: " 
			<< inet_ntoa(m_socketAddress.sin_addr) 
			<< " PORT: " << ntohs(m_socketAddress.sin_port) 
			<< " ***\n\n";
		log(ss.str());
	}

	void TcpServer::acceptConnection(int &new_socket)
	{
		new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
		if (new_socket < 0)
		{
			std::ostringstream ss;
			ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
			exitWithError(ss.str());
		}
	}
} // namespace http

