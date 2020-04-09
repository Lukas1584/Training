#include <iostream>
#include <vector>
#include <fstream>
#include<string>
#include<regex>
#include"Text.h"

std::vector<std::string> get_data(std::istream& is)
{
	std::vector<std::string> text;
	for (std::string line; std::getline(is, line);)
		text.push_back(line);
	return text;
}

void print(const std::vector<std::string>& text, std::ostream& os)
{
	for (const auto& line : text)
		os << line << std::endl;
}

std::string replace(const std::string& date)
{
	std::string result;
	if (isdigit(date[2])) //2020x04x09
		result = date.substr(0, 4) + '-' + date.substr(5, 2) + '-' + date.substr(8, 2); //2020-04-09
	if (isdigit(date[7])) //09x04x2020
		result = date.substr(6, 4) + '-' + date.substr(3, 2) + '-' + date.substr(0, 2); //2020-04-09
	return result;
}

std::string find_date_replace(const std::string& line)
{
	std::regex pattern{  R"((\d{4}[.]\d{2}[.]\d{2})|(\d{2}\D\d{2}\D\d{4}))" };
	std::smatch matches;
	std::string result=line;
	while (std::regex_search(result, matches, pattern))
		result = matches.prefix().str()+ replace(matches[0])+matches.suffix().str();
	return result;
}

std::vector<std::string> find_date_replace(const std::vector<std::string>& original)
{
	std::vector<std::string> replaced = original;
	for (std::string& line : replaced)
		line = find_date_replace(line);
	return replaced;
}

std::ifstream open_read(const std::string& file_name)
{
	std::ifstream file{ file_name };
	if (!file) throw std::runtime_error("File doesn't exist");
	return file;
}

std::ofstream open_save(const std::string& file_name)
{
	std::ofstream file{ file_name };
	if (!file) throw std::runtime_error("Can't create file");
	return file;
}

int main()
{
	try
	{
	/*
		std::ifstream is{ open_read("text.txt") };
		std::vector<std::string> text{ get_data(is) };
		std::cout << "	Original file: " << std::endl;
		print(text,std::cout);
		std::cout << "	Modified file: " << std::endl;
		std::ofstream os{ open_save("result.txt") };
		print(find_date_replace(text),os);
	*/

		Text a("text.txt");
		a.print(std::cout);
		a.print("result2.txt", a.find_date_replace());
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}