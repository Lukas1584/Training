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

void str_to_lower(char* s)
{
    for (; *s; s++)
        if (*s >= 'A' && *s <= 'Z')
            *s += 'a' - 'A';
}

int strcmp(const char* s1, const char* s2)
{
    int sz_s1 = str_size(s1);
    int sz_s2 = str_size(s2);
    int min;
    (sz_s1 < sz_s2) ? min = sz_s1 : min = sz_s2;
    char* s1_low = strdup1(s1);
    char* s2_low = strdup1(s2);
    str_to_lower(s1_low);
    str_to_lower(s2_low);
    for (int i=0; i<=min; i++,s1_low++,s2_low++)
    {
        if (*s1_low < *s2_low)
            return -1;
        if (*s1_low > *s2_low)
            return 1;
    }
    if (sz_s1 == sz_s2) return 0;
    if (sz_s1 < sz_s2) return -1;
    else return 1;
}

int main()
{   
    const char* string = "Hello, world!";
    std::cout << string << std::endl << strdup1(string);
    char s1 []= "Hello";
    char s2 []= "hello";
    std::cout << std::endl << strcmp(s1,s2);
}