#include <bits/stdc++.h>

bool lexical_compare(int a, int b) {
    return to_string(a) < to_string(b);
};

int main() {
    set<int, decltype(&lexical_compare)> s(&lexical_compare);
    s.insert(10000);
    s.insert(20);
}

struct Node {
    int x, y;
    bool operator<(const Node &ob) const {
        return x > ob.x || (x == ob.x && y > ob.y);
    }
};
