#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include<string>
#include<regex>
#include<map>

std::vector<std::string> get_data(std::istream& is)
{
	std::vector<std::string> text;
	for (std::string line; std::getline(is, line);)
		text.push_back(line);
	return text;
}

void print(const std::vector<std::string>& text)
{
	for (auto line : text)
		std::cout << line << std::endl;
}



void print(const std::map<std::string, std::string>& match)
{
	for (auto line : match)
		std::cout << line.first << std::endl << line.second << std::endl;
}

std::map<std::string, std::string> find_date(const std::vector<std::string>& text)
{
	std::regex pattern { ("(\\d{4}-\\d{2}-\\d{2})|\\d{2}-\\d{2}-\\d{4}|\\d{2}[.]\\d{2}[.]\\d{4}|\\d{4}[.]\\d{2}[.]\\d{2}") };
	
	std::map<std::string, std::string> match;
	for (auto line : text)
	{
		std::smatch matches;
		if (std::regex_search(line, matches, pattern))
			match.insert(std::make_pair(matches[0], line));
	}
			//std::cout<<"String number:"<< line+1 <<std::endl<<text.at(line)<<std::endl;
	return match;
}



int main()
{
	try
	{
		std::ifstream file{ "text.txt" };
		if (!file)throw std::runtime_error("File doesn't exist");
		std::vector<std::string> text = std::move(get_data(file));
		print(text);
		std::cout << "		Strings with date:" << std::endl;
		print(find_date(text));

	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


}