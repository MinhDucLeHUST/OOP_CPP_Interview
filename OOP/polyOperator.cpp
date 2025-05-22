#include "bits/stdc++.h"

using namespace std;

class Math
{
private:
public:
    int n1, n2;
    string name, s2;
    Math(int n1 = 10, int n2 = 0) : n1(n1), n2(n2) {}
    Math(string name, int n, int age) : name(name), n1(n), n2(age) {}
    Math operator+(const Math &param)
    {
        return Math(n1 + param.n1, n2 + param.n2);
    }
    Math operator-(const Math &param)
    {
        return Math(n1 - param.n1, n2 - param.n2);
    }
    void Cout(int x, int y)
    {
        cout << "x: " << x << ", y: " << y << endl;
        cout << "x+y: " << x + y << endl;
    }
};

int main()
{
    Math math(110, 11);
    cout << "n1: " << math.n1 << ", n2: " << math.n2 << endl;

    Math b;
    cout << "n1: " << b.n1 << ", n2: " << b.n2 << endl;
    Math c = b + math;
    cout << "n1: " << c.n1 << ", n2: " << c.n2 << endl;

    Math m = c - math;
    cout << "n1: " << m.n1 << ", n2: " << m.n2 << endl;

    Math newmath("MinhDuc", 100, 25);
    cout << "name: " << newmath.name << ", n: " << newmath.n1 << ", age: " << newmath.n2 << endl;
    Math x = math + newmath;
    cout << "math_x:\n";
    cout << "n1: " << x.n1 << ", n2: " << x.n2 << endl;
    // c.Cout(4, 6);
}