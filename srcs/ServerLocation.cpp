#include "webserv.hpp"

namespace conf
{
	ServerLocation::ServerLocation(std::ifstream *file)
	{
		string text, var1, var2, key, value;
		std::vector<string> tmp, value_vec;

		while (std::getline(*file, text))
		{
			if (text[1] == '}')
				break;
			if (text.find('#') == std::string::npos)
			{
				if (text.empty())
						continue;
				text.resize(text.size() - 1);
				std::stringstream ss(text);
				if (text.find("return") == std::string::npos)
				{
					while (std::getline(ss, key, '	'))
					{
						if (key.empty())
							continue;
						else
							tmp.push_back(key);
					}
				}
				else
				{
					std::istringstream iss(text);
					iss >> var1 >> var2;
					tmp.push_back(var1);
					tmp.push_back(var2);
				}
				std::stringstream v(tmp[1]);
				while (std::getline(v, value, ' '))
					value_vec.push_back(value);
				this->rules[tmp[0]] = value_vec;
				value_vec.clear();
				tmp.clear();
			}
		}
	}

	ServerLocation::ServerLocation(const ServerLocation &L)
	{
		*this = L;
	}

	ServerLocation	&ServerLocation::operator=(const ServerLocation &L)
	{
		if (this != &L)
		{
			this->rules = L.rules;
		}
		return (*this);
	}

	ServerLocation::~ServerLocation()
	{}

	std::map<string, std::vector<string> > ServerLocation::get_rules()
	{
		return(this->rules);
	}
}