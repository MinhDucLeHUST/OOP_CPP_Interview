#include "bits/stdc++.h"

using namespace std;

class Bank
{
public:
    void Calculate(int time)
    {
        money *= time;
        cout << "money: " << money << endl;
    }
    void Calculate(int indebit, string name)
    {
        if (name != "President")
        {
            money -= indebit;
            cout << "money: " << money << endl;
        }
        else
        {
            money -= 3 * indebit;
            cout << "money: " << money << endl;
        }
    }

private:
    int money = 10;
};

int main()
{
    Bank bank;
    bank.Calculate(3);
    bank.Calculate(1, "President");
    return 0;
}