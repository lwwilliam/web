#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <map>
#include <vector>
#include <fstream>
#include <exception>

// #include "../Networking/hdenetworking.hpp"

# define RESET		"\033[0m"
# define BLACK		"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::vector;

namespace conf
{
	class ServerLocation
	{
		public:

		private:
			std::map<string, std::vector<string> >	rules;
	};

	class ServerConfig
	{
		public:
			ServerConfig();
			ServerConfig(const ServerConfig &server_config);
			ServerConfig &operator = (const ServerConfig &server_config);
			~ServerConfig();


		private:
			std::vector<string>					listen;
			std::string							root;
			std::string							index;
			std::string							server_name;

			std::map<string, string>			error;
			std::map<string, string>			cgi;
			// stuff

			std::map<string, ServerLocation>	locations;

	};

	class Error : public std::exception
	{
		private:
			const char* message;

		public:
			Error(const char* msg) : message(msg) {}

			virtual const char* what() const throw()
			{
				return message;
			}
	};

	class Config
	{
		public:
			Config();
			// Construtor to handle the whole config file
			Config(std::string filename);
			// Config(const Config &config);
			// Config &operator = (const Config &config);
			// ~Config();
		private:
			// std::vector<ServerConfig>	servers;
	};
}

#endif