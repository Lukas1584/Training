#include"Text.h"
#include <iostream>

int main()
{
	try
	{
		Text a("text.txt");
		a.print_original(std::cout);
		a.save_replaced("Result3.txt");
		a.print_replaced(std::cout);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}
}