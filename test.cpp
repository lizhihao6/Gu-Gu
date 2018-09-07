#include <iostream>
#include <algorithm>
using namespace std;

class Bint
{
  public:
    int *num = new int[200];
    Bint();
    Bint(const Bint &bint);
    Bint(const int &a);
    Bint operator+(const int &a);
    Bint operator+(const Bint &bint);
    Bint &operator=(const int &a);
    Bint &operator-=(const Bint &bint);
    bool operator==(const int &a);
    Bint change(const int &a);
    void print();
};

Bint::Bint()
{
    for (int i = 0; i < 200; i++)
        num[i] = 0;
}

Bint::Bint(const Bint &bint)
{
    for (int i = 0; i < 200; i++)
        num[i] = bint.num[i];
}

Bint::Bint(const int &a)
{
    for (int i = 0; i < 200; i++)
        num[i] = change(a).num[i];
}

Bint Bint::operator+(const int &a)
{
    return *this + change(a);
}

Bint Bint::operator+(const Bint &bint)
{
    int plus = 0;
    Bint a;
    for (int i = 0; i < 200; i++)
    {
        int temp = num[i] + bint.num[i] + plus;
        a.num[i] = temp % 10;
        if (temp >= 10)
            plus = 1;
        else
            plus = 0;
    }
    return a;
}

Bint &Bint::operator=(const int &a)
{
    Bint bint = change(a);
    for (int i = 0; i < 200; i++)
        num[i] = bint.num[i];
    return *this;
}

Bint &Bint::operator-=(const Bint &bint)
{
    int get = 0;
    for (int i = 0; i < 200; i++)
    {
        num[i] -= get + bint.num[i];
        if (num[i] < 0)
        {
            num[i] += 10;
            get = 1;
        }
        else
            get = 0;
    }
    return *this;
}

bool Bint::operator==(const int &a)
{
    Bint bint = change(a);
    for (int i = 0; i < 200; i++)
        if (bint.num[i] != num[i])
            return false;
    return true;
}

void Bint::print()
{
    for (int i = 199; i >= 0; i--)
        if (num[i] != 0)
        {
            for (; i >= 0; i--)
                cout << num[i];
            return;
        }
    cout << 0;
}

Bint Bint::change(const int &a)
{
    int temp = a;
    int length = 0;
    Bint bint;
    for (; temp > 0; length++, temp /= 10)
        bint.num[length] = temp % 10;
    return bint;
}

int get_max(int k)
{
    int n = 1;
    for (int i = 0; i < k; i++)
        n *= 2;
    return n - 1;
}

Bint *next_bit(int trees_num, Bint &counter, Bint *list, int bits)
{
    Bint *_list = new Bint[trees_num + 1];
    for (int i = bits - 1; i < trees_num; i++)
    {
        _list[i] = _list[i - 1] + list[i - 1];
        counter = counter + _list[i];
    }
    delete list;
    return _list;
}

Bint cut(int k, int W, int n, int max_bits)
{
    int head_max = get_max(W % k);
    Bint cut_count;
    Bint *list = new Bint[n];
    for (int cut_num = head_max; cut_num < n - 1; cut_num++)
        list[cut_num].num[0] = 1;

    Bint counter;
    for (int bits = 2; bits <= max_bits; bits++)
    {
        counter = 0;
        list = next_bit(n, counter, list, bits);
        if (list[n - 2] == 0)
        {
            if (bits != max_bits)
                counter = 0;
            break;
        }
    }
    cut_count = cut_count + counter;

    return cut_count;
}

void count(int k, int W)
{
    int n = get_max(k), max_bits = W / k;
    Bint counter = 0;
    if (W % k != 0)
        max_bits++;

    Bint *list = new Bint[n];
    for (int i = 0; i < n; i++)
        list[i].num[0] = 1;

    for (int bits = 2; bits <= max_bits; bits++)
    {
        list = next_bit(n, counter, list, bits);
        if (list[n - 2] == 0)
            break;
    }

    if (W % k != 0)
        counter -= cut(k, W, n, max_bits);

    counter.print();
    cout << endl;
}

int main()
{
    int k, W;
    cin >> k >> W;
    count(k, W);
    return 0;
}