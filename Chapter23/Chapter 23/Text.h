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
	Text(){};

	bool get_data(const std::string&);
	void get_data(std::istream& );
	
	void print(std::ostream&);
	void print_replaced(std::ostream& os);

	bool save_replaced(const std::string&);
		
	void replace_date();

	void set_pattern(const std::regex& ptrn) { pattern=ptrn ; }

private:
	std::vector<std::string> text;
	std::vector<std::string> replaced;
	std::regex pattern{ R"((\d{4}[.]\d{2}[.]\d{2})|(\d{2}\D\d{2}\D\d{4}))" };
	
	std::string replace_date(const std::string&);
	std::string replace(const std::string&);
};