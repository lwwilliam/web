#include "webserv.hpp"



namespace conf
{
	Config::Config()
	{}

	Config::Config(std::string filename)
	{
		string text;

		std::ifstream config_filestream(filename);
		if (!config_filestream.fail())
		{
			while (std::getline(config_filestream, text))
			{
				cout << text << endl;
			}
			config_filestream.close();
		}
		else
			throw conf::Error("File not found");
	}
}