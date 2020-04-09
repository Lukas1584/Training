#pragma once
#include"Text.h"

Text::Text(const std::string& filename)
{
	Text::get_data(filename);
	replaced=text;
}

bool Text::get_data(const std::string& file_name)
{
	std::ifstream file{ file_name };
	if (!file) return false;
	for (std::string line; std::getline(file, line);)
		text.push_back(line);
	return true;
}

bool Text::save_replaced(const std::string& file_name)
{
	std::ofstream file{ file_name };
	if (!file) return false;
	for (const auto& line : replaced)
		file << line << std::endl;
	return true;
}

void Text::print_replaced(std::ostream& os)
{
	for (const auto& line : replaced)
		os << line << std::endl;
}

void Text::print_original(std::ostream& os)
{
	for (const auto& line : text)
		os << line << std::endl;
}

std::string Text::replace(const std::string& date)
{
	std::string result;
	if (isdigit(date[2])) //2020x04x09
		result = date.substr(0, 4) + '-' + date.substr(5, 2) + '-' + date.substr(8, 2); //2020-04-09
	if (isdigit(date[7])) //09x04x2020
		result = date.substr(6, 4) + '-' + date.substr(3, 2) + '-' + date.substr(0, 2); //2020-04-09
	return result;
}

std::string Text::replace_date(const std::string& line)
{
	std::regex pattern{ R"((\d{4}[.]\d{2}[.]\d{2})|(\d{2}\D\d{2}\D\d{4}))" };
	std::smatch matches;
	std::string result = line;
	while (std::regex_search(result, matches, pattern))
		result = matches.prefix().str() + Text::replace(matches[0]) + matches.suffix().str();
	return result;
}

void Text::replace_date()
{
	for (std::string& line : replaced)
		line = Text::replace_date(line);
}


