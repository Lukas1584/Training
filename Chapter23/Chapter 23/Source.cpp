#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include<string>
#include<regex>

void get_data(std::vector<std::string>& text)
{
	std::ifstream file{ "text.txt" };
	if (!file)throw std::runtime_error("File doesn't exist");
	for (std::string line; std::getline(file, line);)
		text.push_back(line);
}

void print(const std::vector<std::string>& text)
{
	for (auto line : text)
		std::cout << line << std::endl;
}

void find_date(const std::vector<std::string>& text)
{
	std::regex pattern{ ("(\\d{4}-\\d{2}-\\d{2})|\\d{2}-\\d{2}-\\d{4}|\\d{2}[.]\\d{2}[.]\\d{4}|\\d{4}[.]\\d{2}[.]\\d{2}") };
	std::smatch matches;
	for (size_t line=0; line < text.size(); line++)
		if(std::regex_search(text.at(line), matches, pattern))
			std::cout<<"String number:"<< line+1 <<std::endl<<text.at(line)<<std::endl;
}

int main()
{
	try
	{
		std::vector<std::string> text;
		get_data(text);
		print(text);
		std::cout << "		Strings with date:" << std::endl;
		find_date(text);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}


}