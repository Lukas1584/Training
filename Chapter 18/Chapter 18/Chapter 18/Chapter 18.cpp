#include <iostream>

int str_size(const char* s)
{
    int count = 0;
    for(;*s;s++)
        count++;
    return count;
}

void str_copy(char *str, const char* s)
{
    for (; *s; str++, s++)
        *str = *s;
    *str++ = '\0';
}

char* strdup1(const char* s)
{
    int size = str_size(s);
    char* str = new char[size];
    str_copy(str, s);
    return str;
}

int main()
{   
    const char* string = "Hello, world!";
    std::cout << string << std::endl << strdup1(string);
}