#include <iostream>
#include <vector>
#include <string>

void input_text(std::vector<std::string>& text)
{
    std::string s;
    while (std::cin >> s)
    {
        if (s == "Quit")
            return;
        text.push_back(s);
    } 
}

void print_vector(const std::vector<std::string>& text)
{
    if (text.size() == 0) throw std::runtime_error("Vector for print is empty");
    for (auto i : text)
        std::cout << i << std::endl;
}

const std::string* compare_string_max(const std::string* a, const std::string* b)
{
    int min;
    ((*a).size() > (*b).size()) ? min = (*b).size() : min = (*b).size();
    for (int i = 0; i < min; i++)
    {
        if (tolower((*a).at(i)) > tolower((*b).at(i)))
            return a;
        if (tolower((*a).at(i)) < tolower((*b).at(i)))
            return b;
    }
    if ((*a).size() >= (*b).size()) return a;
    return b;
}

const std::string* maximum(const std::vector<std::string>& text)
{
    if (text.size() == 0) throw std::runtime_error("Vector for calculation is empty");
    const std::string* ptr_max = &text.at(0);
    for (int i=0; i<text.size();i++)
        ptr_max = compare_string_max(&text.at(i), ptr_max);
    return ptr_max;
}

int main()
{
    try 
    {
        std::vector <std::string> text;
        std::cout << "Please, input some strings. To exit input Quit" << std::endl;
        input_text(text);
        std::cout << "Your text is:" << std::endl;
        print_vector(text);
        std::cout << "Maximum string is:" << std::endl << *maximum(text);
    }
    catch (const std::exception& e)
    {
        std::cout << " an exception was caught, with message '"
            << e.what() << "'\n";
    }
}

