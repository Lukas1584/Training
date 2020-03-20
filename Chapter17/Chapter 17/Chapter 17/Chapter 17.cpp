#include <iostream>

void to_lower(char* s)
{
    for (; *s; s++)
        if (*s >= 'A' && *s <= 'Z')
            *s += 'a' - 'A';
}

int size_s(const char* s)
{
    int count = 0;
    for(; *s; s++)
        count++;
    return count;
}

char* strdup1(const char* s)
{
    char* str = new char[size_s(s)];
    while(*s)
        *(str++) = *(s++);
    //*(str+1) = '\0';
    str = str-(size_s(s) - 1)* sizeof(char);
    std::cout << *str;
    return str;
}

char* strdup2(const char* s)
{
    int sz = size_s(s);
    char* str = new char[sz];
    for (int i = 0; i <= sz; i++)
        str[i] = s[i];
    
    return str;
}

const char* findx(const char* s, const char* x)
{
    while (*s)
    {
        if(*s==*x)
        {
            const char* tmpx = x;
            const char* tmps = s;
            while (*tmpx)
            {
                if (*tmps == *tmpx)
                {
                    tmps++; tmpx++;
                }
                else break;
            }
            if (!(*tmpx)) return s;
        }
        s++;
    }
    return s;
}


int main()
{
    /*std::cout << "Please, input text (max 200 symbols)\n";
    char str[200];
    std::cin >> str;
    to_lower(str);
    std::cout << "In lower case:" << std::endl 
        << str << std::endl
        << "New string:" <<std::endl
        << strdup1(str);*/
    const char* str1 = "Hello world";
    const char* str2 = "lo";
    std::cout << *(findx(str1,str2));
    
}


