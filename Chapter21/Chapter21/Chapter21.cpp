#include <iostream>
#include <vector>
#include <set>

template <typename In,typename Pred,typename Out>
Out count_if(In first, In last,Pred pred, Out result)
{
    while (first != last)
    {
        if (pred(*first)) result++;
        first++;
    }
    return result;
}

template <typename In, typename T, typename Out>
Out count(In first, In last, const T& value, Out result)
{
    while (first != last)
    {
        if (*first == value) result++;
        first++;
    }
    return result;
}

int main()
{
    std::vector<int> vint = { 1,2,3,4,5,1,2,3,4,1,2,1,2,1 };
    std::set<int> sint = { 1,2,3,4,5,1,2,3,4,1,2,1,2,1 };
    int v = count(vint.begin(), vint.end(), 1, 0);
    int s = count(sint.begin(), sint.end(), 1, 0);
    int t = count_if(vint.begin(), vint.end(), [](int x) {return x > 2; }, 0);
    int u = count_if(sint.begin(), sint.end(), [](int x) {return x > 2; }, 0);
    std::cout << v << "  " << s << "  " << t << "  " << u;
}

