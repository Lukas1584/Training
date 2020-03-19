#include <iostream>

void to_lower(char* s)
{
    for (char* ptr = s;*ptr!=0;ptr++)
         if (*ptr >= 'A' && *ptr <= 'Z')
            *ptr += 'a' - 'A';       
 }

int size_s(const char* s)
{
    int count = 0;
    for (const char* ptr = s; *ptr != 0 ; ptr++)
        count++;
    return count;
}

char* strdup1(const char* s)
{
    int sz = size_s(s);
    char* str = new char[sz];
    for (int i=0; i< sz;i++)
        str[i] = s[i];
    str[sz] = 0;
    return str;
}


int main()
{
    std::cout << "Please, input text (max 200 symbols)\n";
    char str[200];
    std::cin >> str;
    to_lower(str);
    std::cout << "In lower case:" << std::endl << str << std::endl << 
        "New string:" <<std::endl<<strdup1(str);
}


