#include "webserv.hpp"



namespace conf
{
	Config::Config()
	{}

	Config::Config(std::string filename)
	{
		std::ifstream config_filestream(filename.c_str());
		if (!config_filestream.fail())
		{
			config_handle(&config_filestream);
			config_filestream.close();
		}
		else
			throw conf::Error(RED "File not found" RESET);
	}

	Config::Config(const Config &config)
	{
		*this = config;
	}

	Config	&Config::operator=(const Config &config)
	{
		if (this != &config)
		{
			this->servers = config.servers;
		}
		return (*this);
	}

	Config::~Config()
	{}

	void	Config::config_handle(std::ifstream *file)
	{
		string text;
		int loop = 0, start = 0, end = 0;
		int c = 0;
		ServerConfig *tmp;

		while (std::getline(*file, text))
		{
			loop++;
			if (text.find("server {") < text.length() || text.find("server	{") < text.length())
			{
				start = loop;
				this->servers.push_back(ServerConfig(file, start, end));
				c++;
			}
		}
		cout << "server count: " << c << endl;
		// --> printing stored config
		for (size_t i = 0; i < servers.size(); ++i)
		{
			cout << "server : " << i << endl;
			std::vector<string> list = servers[i].get_listen();
			for (size_t a = 0; a < list.size(); ++a)
					cout << "port : " << list[a] << endl;
			cout << "root : " << servers[i].get_root() << endl;
			cout << "index : " << servers[i].get_index() << endl;
			cout << "server_name : " << servers[i].get_server_name() << endl;
			cout << "client_max : " << servers[i].get_client_max() << endl;
			std::map<string, string>::iterator it;
			std::map<string, string> tmp = servers[i].get_error();
			for (it = tmp.begin(); it != tmp.end(); it++)
				cout << "error : " << it->first << "   " << it->second << endl;
			tmp = servers[i].get_cgi();
			for (it = tmp.begin(); it != tmp.end(); it++)
				cout << "cgi : " << it->first << "   " << it->second << endl;
			cout << endl;
			std::map<string, ServerLocation>::iterator iter;
			std::map<string, ServerLocation> locate = servers[i].get_locations();
			for (iter = locate.begin(); iter != locate.end(); iter++)
			{
				cout << "location : " << iter->first << endl;
				std::map<string, std::vector<string> >::iterator	rules_it;
				std::map<string, std::vector<string> >	rule = iter->second.get_rules();
				for (rules_it = rule.begin(); rules_it != rule.end(); rules_it++)
				{
					cout << "key : " << rules_it->first;
					cout << "|	|value : ";
					for (size_t b = 0; b < rules_it->second.size(); ++b)
						cout << rules_it->second[b] << " ";
					cout << endl;
				}
				cout << endl;
			}
			cout << endl;
		}
		// <-- end
	}
}