#pragma once
#include"Text.h"

Text::Text(const std::string& filename)
{
	std::ifstream file{ open_read(filename) };
	get_data(file);
}

std::ifstream Text::open_read(const std::string& file_name)
{
	std::ifstream file{ file_name };
	if (!file) throw std::runtime_error("File doesn't exist");
	return file;
}

std::ofstream Text::open_save(const std::string& file_name)
{
	std::ofstream file{ file_name };
	if (!file) throw std::runtime_error("Can't create file");
	return file;
}

void Text::get_data(std::istream& is)
{
	for (std::string line; std::getline(is, line);)
		text.push_back(line);
}

void Text::print(const std::string& filename, const std::vector<std::string>& print)
{
	std::ofstream os{ Text::open_save(filename) };
	for (const auto& line : print)
		os << line << std::endl;
}

void Text::print(std::ostream& os)
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

std::string Text::find_date_replace(const std::string& line)
{
	std::regex pattern{ R"((\d{4}[.]\d{2}[.]\d{2})|(\d{2}\D\d{2}\D\d{4}))" };
	std::smatch matches;
	std::string result = line;
	while (std::regex_search(result, matches, pattern))
		result = matches.prefix().str() + Text::replace(matches[0]) + matches.suffix().str();
	return result;
}

std::vector<std::string> Text::find_date_replace()
{
	std::vector<std::string> replaced = text;
	for (std::string& line : replaced)
		line = Text::find_date_replace(line);
	return replaced;
}

