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
	
	void print_original(std::ostream&);
	void print_replaced(std::ostream&);

	bool save_replaced(const std::string&);

private:
	std::vector<std::string> text;
	std::vector<std::string> replaced;
	
	void replace_date();
	bool get_data(const std::string&);
	std::string replace_date(const std::string&);
	std::string replace(const std::string&);
};