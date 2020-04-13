#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include"Token.h"
#include <bitset>
using namespace std;

const char let = 'L'; // Let is used for declaration of variables
const char quit = 'Q'; // Quit is used to exit the program
const char print = '\n'; // Prints the result of calculation
const char number = '8'; // Indicates that this is a number
const char name = 'a'; // Indicates that this is a variable
const char sqrts = 's'; // Indicates that this is a square root
const char pows = 'p'; // Indicates that this is a exponentiation
const char cnst = '2'; // Indicates that this is a constant
const char lg = '3'; // Indicates that this is a decimal logarithm
const char help = '?'; // Indicates that this is help
const string prompt = "> "; // Prompt used at the beginning of every line
const string result = "= "; // = used to before the result
const char bit = '0'; //"Word bit"
const char bits = '1'; //value of bits

struct Variable   // Holds variables names and values
{								
	string name; // Variable name
	double value; // Variable value
	bool constant;// Variable value
	Variable(string n, double v, bool c) :name(n), value(v), constant(c) { }
};

struct Token   // Token holds operators, operands and names of variables
{
	char kind;
	double value;
	string name;
	vector<bool> vb;
	Token(const char& ch) :kind(ch) { } // Operator
	Token(const char& ch, const double& val) :kind(ch), value(val) { } // Operand
	Token(const char& ch, const string& n) :kind(ch), name(n) { } // Name of variable
	Token(const char& ch, const vector<bool> vec) :kind(ch),vb (move(vec)) { } // Operator
};

class Token_stream {
	bool full;
	Token buffer; // Holds a symbol that wasn't used by specific function
public:
	Token_stream() :full(0), buffer(0) { }
	Token get();
	Token get_b();
	void putback(Token t) { buffer = t; full = true; } // Returns symbol to buffer. If 'full' = true, get() will use symbol from buffer
	void ignore(char c); // Ignores all characters before specific symbol
};  // Stream of tokens

vector<Variable> var_table;
Token_stream ts; // Holds all Tokens

Token Token_stream::get() // Get characters from cin
{
	if (full) // If buffer is not empty, return value from it
	{ 
		full = false; 
		return buffer; 
	} 
	char ch = cin.get(); // Otherwise start looking for characters in input stream
	switch (ch)
	{
		case '(':	case ')':	case '+':	case '-':	case '*':
		case '/':	case '%':	case '=':	case '!':	case ',':
			return Token(ch); // If it is an operator or comma then return it
		case '.': 	case '0':	case '1':	case '2':	case '3':
		case '4':	case '5':	case '6':	case '7':	case '8':
		case '9':
		{
			cin.unget(); // If it is a number then return it to the stream
			double val;
			cin >> val; // Read the complete value
			return Token(number, val);
		}
		case '#': // If user declares the variable then return 'let'
			if (!isspace(cin.get())) cin.unget(); // check the next symbol
			return Token(let);
		case print:
			return Token(print);
		case help:
			return Token(help);
		default:
		if (isalpha(ch)) // If it is a letter
		{ 
			string s;
			s += ch; // Put the letter in 's' because it has been already read
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) // Continue to read in 's'
				s += ch; 
			cin.unget(); // Return the character into the stream
			if (s == "sqrt") 
				return Token(sqrts);
			if (s == "pow") 
				return Token(pows);
			if (s == "help" || s == "Help") 
				return Token(help);
			if (s == "lg") 
				return Token(lg);
			if (s == "const")
			{
				if (!isspace(cin.get())) // check the next symbol
					cin.unget(); 
				return Token(cnst);
			}
			if (s == "bit" || s == "Bit" || s == "BIT")
				return Token(bit);
			if (s == "exit" || s == "quit" || s == "Exit" || s == "Quit")  // Close the program
				return Token(quit); 
			return Token(name, s); // Return name of variable
		}
		if (isspace(ch)) 
			return Token(print);
		throw runtime_error("Bad token");
	}
}

void Token_stream::ignore(char c) // Ignores all characters before specific symbol
{
	if (full && c == buffer.kind) { // If 'c' is already in buffer then just discard it
		full = false;
		return;
	}
	full = false; // Otherwise discard value in buffer and look for it further
	char ch;
	while (ch = cin.get()) // Read all values before 'c'
		if (ch == c) return; // Return when 'c' is found
}

template<class R, class A> R narrow_cast(const A& a)  // run-time checked narrowing cast (type conversion)
{
	R r = R(a);
	if (A(r) != a) throw runtime_error(string("info loss"));
	return r;
}

double get_value(const string& s) // Gets variable's value
{
	for (Variable i : var_table) {
		if (i.name == s) return i.value;
	}
	throw runtime_error("get: undefined name "+s);
}

double expression(); // Declaration of expression()

void check_next(const char& c) { //check the next char
	Token t = ts.get();
	string s;
	s += c; s += t.kind;
	switch (c) 
	{
		case '+':
		case '-':
		case '/':
		case '*':
			switch (t.kind) 
			{
				case '+':
				case ')':
				case '-':
				case '*':
				case '/':
				case '%':
				case print:
				case '=':
				case ',':
				case '!':
					throw runtime_error("Error: wrong operation "+s);
				default:
					ts.putback(t);
					return;
			}
		case '!':
			switch (t.kind) 
			{
				case '(':
				case '!':
				case number:
				case ',':
					throw runtime_error("Error: wrong operation "+s);
			default:
				ts.putback(t);
				return;
			}
		case '%':
			switch (t.kind) 
			{
				case '!':
				case '+':
				case ')':
				case '-':
				case '*':
				case '/':
				case '%':
				case print:
				case '=':
				case ',':
					throw runtime_error("Error: wrong operation "+s);
				default:
					ts.putback(t);
					return;
			}
		default:
			ts.putback(t);
			return;
	}
}

double primary() // Processes semicolons, numbers, square roots,exponentiations and returns variables
{
	Token t = ts.get(); // Get a character
	switch (t.kind) 
	{
		case '(':
		{	
			double d = expression(); // Perform calculations in semicolons
			t = ts.get(); // Get a ')' closing character
			if (t.kind != ')') throw runtime_error("')' expected"); // If there wasn't any ')' return an error
			return d;
		}
		case sqrts: // Calculate square root of number or group of numbers
		{
			double d = expression();
			if (d < 0) throw runtime_error("square root of negative number was detected"); // Print error message if negative number was thrown to sqrt
			return sqrt(d);
		}
		case lg: // Calculate decimal logarithm
		{
			double d = expression();
			if (d < 0) throw runtime_error("decimal logarithm of negative number was detected"); // Print error message if negative number was thrown to ecimal logarithm
			return log10(d);
		}
		case pows: //Calculate exponentiation
		{
			t = ts.get();
			if (t.kind == '(') 
			{
				double lval = expression();
				int rval = 0;
				t = ts.get();
				if (t.kind == ',') rval = narrow_cast<int>(expression());
				else throw runtime_error("Second argument is not provided");
				double result = 1;
				if (rval < 0) //if negative degree
				{ 
					lval = 1 / lval;
					rval = 0 - rval;
				}
				for (double i = 0; i < rval; ++i) 
					result *= lval;
				t = ts.get();
				if (t.kind != ')') throw runtime_error("')' expected"); // If there wasn't any ')' return an error
				return result;
			}
			else throw runtime_error("'(' expected"); // If there wasn't any ')' return an error
		}
		case '-': // For negative digits
			check_next('-'); //check the next character
			return -primary(); // Return negative digit
		case number:  // If Token is a number
			return t.value; // Return the number
		case name: // If Token is a name of variable
			return get_value(t.name); // Return the value of the variable
		case '+': // For positive digits
			check_next('+'); //check the next character
			return primary();
		default:
			throw runtime_error("primary expected"); // Return an error if an inappropriate character was provided
	}
}

double term() // Performs '*', '/', '!', '%' and @(sqrt) operations
{
	double left = primary(); // Get the number or the variable
	while (true) 
	{
		Token t = ts.get(); // Get a new character
		switch (t.kind) 
		{
			case '*': // Multiplication
				check_next('*'); //check the next character
				left *= primary();
				break;
			case '/': // Division
			{	
				check_next('/'); //check the next character
				double d = primary();
				if (d == 0) throw runtime_error("division by zero"); // Division by zero is prohibited
				left /= d;
				break;
			}
			case '!': // Factorial
			{
				check_next('!'); //check the next character
				int x = (int)left;
				for (int i = 1; i < left; i++)  // Get a multiplication of all numbers before x (including x)
					x *= i;
				if (x == 0) left = 1;
				else left = x;
				break;
			}
			case '%': // Modulo
			{
				check_next('%'); //check the next character
				double d = primary();
				if (d == 0) throw runtime_error("division by zero");
				left = fmod(left, d); // Use fmod to divide floating-point numbers with remainder
				break;
			}
			default:
				ts.putback(t); // If nothing was done return character to the stream
				if (left == -0) return 0; // Change -0 to 0 when it was multiplied or divided by negative digit
				return left; // Return new or unchanged value of 'left'
		}
	}
}

double expression() // Performs '+' and '-' operations
{
	double left = term(); // Get the number or the result of calculations in term
	while (true) 
	{
		Token t = ts.get();
		switch (t.kind) 
		{
			case '+':
				check_next('+');
				left += term(); // Addition
				break;
			case '-':
				check_next('-');
				left -= term(); // Subtraction
				break;
			default:
				ts.putback(t); // If nothing was done return character to the stream
				return left; // Return the new or unchanged value of 'left'
		}
	}
}

int search(const string& s) { //search for an existing constant or variable
	for (unsigned int i = 0; i < var_table.size(); ++i) 
		if (var_table[i].name == s) return i + 1;
	return 0;
}

double declaration() // Declares a name of the variable
{
	Token t = ts.get();
	Token t2 = ts.get();
	Token t3 = ts.get();
	if ((t.kind != name && t2.kind != '=') && (t.kind != cnst && t2.kind != name && t3.kind != '=')) // check the correctness of the entries
		throw runtime_error("Declaration error");
	if (t.kind == cnst) //Declaration of a constant
	{ 
		int k = search(t2.name); //search for an existing constant or variable
		if (k && var_table[k-1].constant == true) throw runtime_error("You can't change constant "+ var_table[k-1].name);  //if a constant excist
		else if (k && var_table[k-1].constant == false) //if a variable excist
		{  
			double d = expression(); // Process the provided value
			var_table[k-1].value = d;
			var_table[k-1].constant = true;
			return d; // Return the value of a new variable
		}
		else //if nothing was found
		{ 
			double d = expression(); // Process the provided value
			var_table.push_back(Variable(t2.name, d, true)); // Add a new constant to a vector
			return d; // Return the value of a new constant   
		}
	}
	else //Declaration of a variable
	{ 
		ts.putback(t3);
		int k = search(t.name);
		if (k && var_table[k-1].constant == true) throw runtime_error("You can't change constant "+ var_table[k-1].name); // if a constant excist
		else if (k && var_table[k-1].constant == false) //if a variable excist
		{ 
			double d = expression(); // Process the provided value
			var_table[k-1] = (Variable(t.name, d, false));
			return d; // Return the value of new variable
		}
		else //if nothing was found
		{ 
			double d = expression(); // Process the provided value
			var_table.push_back(Variable(t.name, d, false)); // Add a new variable to a vector
			return d; // Return the value of a new variable   
		}
	}
}

void helps() { //information about program
	cout << "Для вычислений используются следующие операции: " << '\n';
	cout << "+ сложение; - вычитание; * умножение; / деление " << '\n';
	cout << "( и ) скобки; 5! факториал числа 5; 5%2 остаток от деления 5 на 2" << '\n';
	cout << "pow(2,3) возведение числа 2 в степень 3; sqrt(100) вычисление квадратного корня числа 100" << '\n';
	cout << "lg(10) вычисление десятичного логарифма по числу 10" << '\n';
	cout << "Работа с переменными: " << '\n';
	cout << "# const x=10 - объявление постоянной x и присвоение ей значения 10" << '\n';
	cout << "# x=10 - объявление переменной x и присвоение ей значения 10" << '\n';
	cout << "Предопределенные константы: k=1000; pi=3.1415926535; e=2.71828182845904523536 " << '\n';
	cout << "В программе реализована поддержка битовых операций &,|,^,~. "<<
		"Для этого перед началом выражения введите bit и через пробел введите выражение. " << '\n';
	cout << "В программе возможно вычисление нескольких выражений, для этого выражения нужно ввести через пробел" << '\n';
	cout << "Для старта вычиселния результата используется кнопка ввода (enter)" << '\n' << prompt;
	return;
}

double statement() // Distinguishes between declarations and expressions
{
	Token t = ts.get();
	switch (t.kind) 
	{
		case let: // User wants to declare the variable
			return declaration();
		case help: // User wants to see help
			helps();
			t = ts.get();
			return statement();
		default: // User wants another operation
			ts.putback(t);
			return expression();
	}
}

void clean_up_mess() // Ignores all characters before ';' if an exception was thrown
{
	ts.ignore(print);
}




Token Token_stream::get_b() // Get characters from cin
{
	if (full) // If buffer is not empty, return value from it
	{
		full = false;
		return buffer;
	}
	char ch = cin.get(); // Otherwise start looking for characters in input stream
	
	switch (ch)
	{
		case '(':	case ')':	case '&':	case '|':	case '^':	case '~':
			return Token(ch); // If it is an operator or comma then return it
		case '0':	case '1':
		{
			
			vector<bool> val;
			while (ch == '0' || ch == '1')
			{
				if(ch=='0')
					val.push_back(false);
				if(ch=='1')
					val.push_back(true);
				ch = cin.get();
			}
			cin.unget();
			
			return Token(bits, val);
			break;
		}
	case print:
		return Token(print);
	case help:
		return Token(help);
	default:
		if (isalpha(ch)) // If it is a letter
		{
			string s;
			s += ch; // Put the letter in 's' because it has been already read
			while (cin.get(ch) && isalpha(ch) ) // Continue to read in 's'
				s += ch;
			cin.unget(); // Return the character into the stream
			if (s == "exit" || s == "quit" || s == "Exit" || s == "Quit")  // Close the program
				return Token(quit);
		}
		if (isspace(ch))
			return Token(print);
		throw runtime_error("Bad bit token");
	}
}
void to_one_size(vector<bool>& left,vector<bool>& right)
{
	int l_sz = left.size();
	int r_sz = right.size();
	if (l_sz == r_sz) return;
	if (l_sz < r_sz)
	{
		for (int i = 0; i < (r_sz - l_sz); i++)
			left.insert(left.begin(), 0);
	}
	else
	{
		for (int i = 0; i < (l_sz - r_sz); i++)
			right.insert(right.begin(), 0);
	}
}
vector<bool> operator&(vector<bool> left,vector<bool> right)
{
	vector<bool> result;
	to_one_size(left, right);
	for (unsigned int i = 0; i < left.size(); i++)
		result.push_back(left[i] & right[i]);
	return result;
}
vector<bool> operator|(vector<bool> left,vector<bool> right)
{
	vector<bool> result;
	to_one_size(left, right);
	for (unsigned int i = 0; i < left.size(); i++)
		result.push_back(left[i] | right[i]);
	return result;
}
vector<bool> operator~(const vector<bool> right)
{
	vector<bool> result;
	for (unsigned int i = 0; i < right.size(); i++)
	{
		bool x;
		(right[i]) ? x = false : x = true;
		result.push_back(x);
	}
	return result;
}
vector<bool> operator^(vector<bool> left,vector<bool> right)
{
	vector<bool> result;
	to_one_size(left, right);
	for (unsigned int i = 0; i < left.size(); i++)
		result.push_back(left[i] & right[i]);
	return result;
}
vector<bool> expression_b();
vector<bool> primary_b() // Processes semicolons, numbers, square roots,exponentiations and returns variables
{
	Token t = ts.get_b(); // Get a character
	switch (t.kind)
	{
		case '(':
		{
			vector<bool> d = expression_b(); // Perform calculations in semicolons
			t = ts.get_b(); // Get a ')' closing character
			if (t.kind != ')') throw runtime_error("')' expected"); // If there wasn't any ')' return an error
			return d;
		}
		case bits:  // If Token is a number
			return t.vb; // Return the number
		case '~':
			return  ~ primary_b(); // Subtraction
		default:
			throw runtime_error("bit primary expected"); // Return an error if an inappropriate character was provided
	}
}
vector<bool> expression_b() // Performs '+' and '-' operations
{
	vector<bool> left = primary_b(); // Get the number or the result of calculations in term
	while (true)
	{
		Token t = ts.get_b();
		switch (t.kind)
		{
		case '&':
			left = left & primary_b(); // Addition
			break;
		case '|':
			left =left | primary_b(); // Subtraction
			break;
		case '^':
			left = left ^ primary_b(); // Subtraction
			break;
		default:
			ts.putback(t); // If nothing was done return character to the stream
			return left; // Return the new or unchanged value of 'left'
		}
	}
}
ostream& operator<<(ostream& os,const vector<bool>& vec)
{
	for (auto i : vec)
		os << i;
	os << endl;
	return os;
}




void calculate() // Performs calculations
{
	while (true)
		try
		{
			cout << prompt; // Output '>' symbol
			Token t = ts.get(); // Get a new character
			while (t.kind == print) // Read all '\n'
				t = ts.get(); 
			if (t.kind == quit) // Close the program if exit was entered
				return; 
			if (t.kind == bit)
			{
				ts.get_b();
				cout << result << expression_b() << endl;
			}
			else
			{
				ts.putback(t); // Return a character into the stream
				cout << result << statement() << endl; // Output the result
			}
		}
		catch (const runtime_error& e) {
			cerr << e.what() << endl; // Cout the error if the exception was thrown
			clean_up_mess(); // Ignores all characters till the ';'
		}
}

int main() {
	setlocale(LC_ALL, "rus");
	try {
		var_table.push_back(Variable("k", 1000, true)); // Pre-defined variable 'k'
		var_table.push_back(Variable("pi", 3.1415926535, true)); // Pre-defined variable 'pi'
		var_table.push_back(Variable("e", 2.71828182845904523536, true)); // Pre-defined variable 'e'
		cout << "Вас приветствует программа Калькулятор. Для подсказки о работе с программой введите 'help' или '?'" << '\n';
		cout << "Для выхода из программы введите 'exit' или 'quit'" << '\n';
		calculate(); // Performs calculations
		return 0;
	}
	catch (const exception& e) { // Throws an exception
		cerr << "Exception: " << e.what() << endl; // Describe the error
		char c;
		while (cin >> c && c != quit);
		return 1;
	}
	catch (...) { // Throws an exception
		cerr << "Exception\n";
		char c;
		while (cin >> c && c != quit);
		return 2;
	}
}





