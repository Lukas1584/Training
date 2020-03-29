#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

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
    for (unsigned int i=0; i<text.size();i++)
        ptr_max = compare_string_max(&text.at(i), ptr_max);
    return ptr_max;
}

void copy_list_to_doube(const std::list<int>* ptr_list, std::vector <double>* ptr_vector)
{
    for (auto x:*ptr_list)
        ptr_vector->push_back(x);
}

void print_vector(std::vector<double> print_copy)
{
    if (print_copy.size() == 0) throw std::runtime_error("Vector for print is empty");
    sort(print_copy.begin(), print_copy.end());
    for (auto i : print_copy)
        std::cout << i << std::endl;
}

void task11()
{
    std::list<int> list = { 1,10,2,9,3,8,4,7,5,6,6,5,7,4,8,3,9,2,10,1 };
    std::vector <double> vector;
    copy_list_to_doube(&list, &vector);
    print_vector(vector);
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
        task11();
    }
    catch (const std::exception& e)
    {
        std::cout << " an exception was caught, with message '"
            << e.what() << "'\n";
    }
}

