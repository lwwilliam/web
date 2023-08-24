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
// using std::map;
// using std::vector;

namespace conf
{
	class ServerLocation
	{
		public:
			typedef std::map<string, std::vector<string> > rules_map;
			ServerLocation(std::ifstream *file);
			ServerLocation(const ServerLocation &L);
			ServerLocation &operator = (const ServerLocation &L);
			~ServerLocation();

			//getter
			const std::map<string, std::vector<string> > &get_rules() const;
		private:
			std::map<string, std::vector<string> >	rules;
	};

	std::ostream &operator << (std::ostream &outs, const ServerLocation &server_location);

	class ServerConfig
	{
		public:
			typedef	std::vector<string>::iterator		portIter;
			typedef std::map<string, ServerLocation>	locationMap;

			ServerConfig(std::ifstream *file);
			ServerConfig(const ServerConfig &server_config);
			ServerConfig &operator = (const ServerConfig &server_config);
			~ServerConfig();

			//setter
			void	set_port(string text);
			void	set_root(string text);
			void	set_index(string text);
			void	set_server_name(string text);
			void	set_client_max(string text);
			void	set_error(string text);
			void	set_cgi(string text);
			void	location_name(string text, std::ifstream *file);

			//getter
			string	get_root() const;
			string	get_index() const;
			string	get_server_name() const;
			string	get_client_max() const;
			const std::vector<string>			&get_port() const;
			const std::map<string, string>	&get_error() const;
			const std::map<string, string>	&get_cgi() const;
			const std::map<string, ServerLocation>	&get_locations() const;

		private:
			std::vector<string>					port;
			string								root;
			string								index;
			string								server_name;
			string								client_max;

			std::map<string, string>			error;
			std::map<string, string>			cgi;
			// stuff

			std::map<string, ServerLocation>	locations;

	};

	std::ostream &operator << (std::ostream &outs, const ServerConfig &server_config);

	class Config
	{
		public:
			Config();
			// Construtor to handle the whole config file
			Config(std::string filename);
			Config(const Config &config);
			Config &operator=(const Config &config);
			~Config();
			void	config_handle(std::ifstream *file);

			//getter
			const std::vector<ServerConfig> &get_servers() const;
		private:
			std::vector<ServerConfig>	servers;
	};

	std::ostream &operator << (std::ostream &outs, const Config &config);

	class Error : public std::exception
	{
		public:
			Error(const char* msg) : message(msg) {}

			virtual const char* what() const throw()
			{
				return message;
			}
		private:
			const char* message;
	};
}

#endif