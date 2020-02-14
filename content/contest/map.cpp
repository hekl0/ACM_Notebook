#include <bits/stdc++.h>

template<typename T1, typename T2>
struct Node
{
    T1 x;
    T2 y;
    
    Node(T1 x, T2 y): x(x), y(y) {}

    bool operator<(const Node &ob) const
    {
        return x > ob.x || (x == ob.x && y > ob.y);
    }
};

int main()
{
    std::map<Node<std::string,std::string>, int> map =
    {
        {{"C", "C99"}, 1999},
        {{"C", "C11"}, 2011},
        {{"C++", "C++14"}, 2014},
        {{"C++", "C++17"}, 2017},
        {{"Java", "Java SE 8"}, 2014},
        {{"Java", "Java SE 9"}, 2017}
    };

    for (const auto &entry: map)
    {
        auto key = entry.first;
        std::cout << "{" << key.x << "," << key.y << "}, "
                  << entry.second << '\n';
    }

    return 0;
}