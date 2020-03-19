#include <iostream>

void to_lower(char* s)
{
    char* ptr = s;
    for (char* ptr = s;*ptr!=0;ptr++)
         if (*ptr >= 'A' && *ptr <= 'Z')
            *ptr += 'a' - 'A';       
 }

int main()
{
    std::cout << "Please, input text (max 200 symbols)\n";
    char str[200];
    std::cin >> str;
    to_lower(str);
    std::cout << "In lower case:" << std::endl << str;
}


