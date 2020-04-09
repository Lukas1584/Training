#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include<string>
#include<regex>

class Text
{
public:
	Text(const std::string&);
	std::ifstream open_read(const std::string&);
	std::ofstream open_save(const std::string&);
	void print(const std::string&, const std::vector<std::string>& );
	void print(std::ostream&);
	std::vector<std::string> find_date_replace();
private:
	void get_data(std::istream&);
	std::vector<std::string> text;
	std::string find_date_replace(const std::string&);
	std::string replace(const std::string&);
};