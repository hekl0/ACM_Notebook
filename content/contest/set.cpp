#include <bits/stdc++.h>
using namespace std;

bool lexical_compare(int a, int b) {
    return to_string(a) < to_string(b);
};

int main() {
    set<int, decltype(&lexical_compare)> s(&lexical_compare);
    // set<int> s;
    s.insert(10000);
    s.insert(20);
    s.insert(11);
    s.insert(100);

    for (int x : s)
        cout << x << ' ';

    return 0;
}