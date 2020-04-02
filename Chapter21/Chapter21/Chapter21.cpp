#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <list>

std::string ENDLINE = "EndLine";

class Purchase
{
    std::string name;
    double price;
    int count;
public:
    Purchase(std::string n, double p, int c) :
        name(n), price(p), count(c) {}
    void print(std::ostream& os);
    void save(std::ostream& os);
};

class Order
{
    std::string clientName;
    std::string clientAdress;
    std::string clientBirthDate;
    std::vector<Purchase> clientPurchase;
public:
    Order(std::string n, std::string a, std::string b, std::vector<Purchase> v) :
        clientName(n), clientAdress(a), clientBirthDate(b),clientPurchase(v) {}
    
    void print(std::ostream& os);
    void save(std::ostream& os);
    bool operator<(const Order& a) const { return clientName < a.clientName; }
    std::string get_adress() const { return clientAdress; }
 };

Purchase input_purchase()
{
    std::cout << "Input product name:" << std::endl;
    std::string name;
    std::cin >> name;
    std::cout << "Input unit price:" << std::endl;
    double price;
    std::cin >> price;
    std::cout << "Input quantity:" << std::endl;
    int count;
    std::cin >> count;
    return Purchase(name, price, count);
}

void input_purchases(std::vector<Purchase>& purchases)
{
    while (true)
    {
        purchases.push_back(input_purchase());
        std::cout << "Do you want to input one more purchase? (Y/N)" << std::endl;
        char choice;
        std::cin >> choice;
        if (choice != 'Y' && choice != 'y') break;
    }
}

Order input_order()
{
    std::cout << "Input client name:" << std::endl;
    std::string clientName;
    std::cin >> clientName;
    std::cout << "Input client adress:" << std::endl;
    std::string clientAdress;
    std::cin >> clientAdress;
    std::cout << "Input client birth date:" << std::endl;
    std::string clientBirthDate;
    std::cin >> clientBirthDate;
    std::vector<Purchase> purchases; 
    input_purchases(purchases);
    return Order(clientName, clientAdress, clientBirthDate,purchases);
}

void input_orders(std::vector<Order>& orders)
{
    while (true)
    {
        orders.push_back(input_order());
        std::cout << "Do you want to input one more order? (Y/N)" << std::endl;
        char choice;
        std::cin >> choice;
        if (choice != 'Y' && choice != 'y') break;
    }
    return;
}

void Purchase::print(std::ostream& os)
{
    os << "Product name: " << name << std::endl
        << "Price: " << price << std::endl
        << "Quantity: " << count << std::endl;
}

void Order::print(std::ostream& os)
{
    os << "Client name: " << clientName << std::endl
        << "Client adress: " << clientAdress << std::endl
        << "Client birth date: " << clientBirthDate << std::endl;
    for (auto purchase : clientPurchase)
        purchase.print(os);
    os << std::endl;
}

template <typename In,typename Stream>
void print_orders(Stream& os, const In& orders)
{
    for (auto order : orders)
        order.print(os);
}

template <typename In>
void print_to_file(const In& orders,std::string fileName)
{
    std::ofstream file(fileName);
    print_orders(file, orders);
}

void Purchase::save(std::ostream& os)
{
    os << name << " " << price << " " << count << " ";
}

void Order::save(std::ostream& os)
{
    os << std::endl << clientName << " " << clientAdress << " " << clientBirthDate << std::endl;
    for (auto purchase : clientPurchase)
        purchase.save(os);
    os << ENDLINE;
}

template <typename In>
void save(const In& orders, const std::string fileName)
{
    std::ofstream file(fileName);
    for (auto order : orders)
        order.save(file);
}


void read_purchases(std::istream& is,std::vector<Purchase>& clientPurchase)
{
    std::string name;
    double price;
    int count;
    while (true)
    {
        is >> name;
        if (name == ENDLINE) return;
        is >> price >> count;
        clientPurchase.push_back(Purchase(name, price, count));
    }
}

Order read_order(std::istream& is)
{
    std::string clientName;
    std::string clientAdress;
    std::string clientBirthDate;
    is >> clientName >> clientAdress >> clientBirthDate;
    std::vector<Purchase> clientPurchase;
    read_purchases(is, clientPurchase);
    return Order(clientName, clientAdress, clientBirthDate, clientPurchase);
}

template <typename In>
void read_orders(In& orders,const std::string fileName)
{
    std::ifstream file(fileName);
    while (!file.eof())
         orders.push_back(read_order(file));
 }

int main()
{
    std::vector<Order> orders;
    input_orders(orders);
    print_orders(std::cout,orders);
    print_to_file(orders, "Report.txt");
    sort(orders.begin(), orders.end());
    save(orders, "Orders.txt");
    std::vector<Order> ordersRead;
    read_orders(ordersRead, "Orders.txt");
    print_orders(std::cout, ordersRead);
    std::list<Order> orderList;
    read_orders(orderList, "Orders.txt");
    orderList.sort([](const Order& a, const Order& b) {return (a.get_adress())<(b.get_adress());});
    print_orders(std::cout, orderList);
    std::vector<Order> bigOrders;
    merge(orderList.begin(), orderList.end(), ordersRead.begin(), ordersRead.end(), std::back_inserter(bigOrders));
    print_to_file(orders, "ReportBig.txt");
}

