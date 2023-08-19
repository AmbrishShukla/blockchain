#include <bits/stdc++.h>
using namespace std;
#define ull unsigned long long int

string decimalToBinary(int n)
{

    string s = bitset<64>(n).to_string();

    const auto loc1 = s.find('1');

    if (loc1 != NULL)
        return s.substr(loc1);

    return "0";
}

ull allxor(ull num)
{
    ull ans = num % 10;
    num = num / 10;
    while (num != 0)
    {
        ull rem = num % 10;
        ans = ans ^ rem;
        num = num / 10;
    }
    return ans;
}

ull hashfunction(ull n)
{

    ull ans = 0;
    ull k = 0;

    while (n != 0)
    {
        // cout << "this is the si " << n % 10 << endl;
        ull bin = n % 10;
        cout << "this is the bin " << bin << endl;
        string nm = decimalToBinary(bin + 48);

        int num = stoi(nm);
        cout << "this is the num " << num << endl;

        ull finalnum = allxor(num);
        cout << "this is the finalnum " << finalnum << endl;

        ans = (finalnum * pow(2, k)) + ans;
        cout << "this is the ans " << ans << endl;

        k++;
        n = n / 10;
        cout << endl;
    }

    return ans;
}

int main()
{
    cout << "enter a number between 0 - 999" << endl;
    // ull s;
    // cin >> s;

    ull hashans = hashfunction(230);

    cout << hashans << endl;
    // cout << numReverse(234) << endl;
    // cout << tobinary(12) << endl;
    // cout << decimalToBinary(52) << endl;
    cout << bitset<8>(9) << endl;
}

// ull binarytodecimal(ull n)
// {
//     ull ans = 0;
//     ull i = 0;
//     while (n != 0)
//     {
//         ull digit = n % 10;
//         ans = pow(2, i) + ans;
//         n = n / 2;
//         i++;
//     }
//     return ans;
// }

// ull numReverse(ull n)
// {
//     ull ans = 0;
//     ull i = 0;
//     while (n != 0)
//     {
//         ull rem = n % 10;
//         ans = (ans * 10) + rem;
//         n = n / 10;
//     }
//     return ans;
// }

// ull tobinary(ull n)
// {
//     ull ans = 0;
//     ull i = 0;
//     while (n != 0)
//     {
//         ull bit = n % 2;
//         cout << "this is the bit ans i and pow " << bit << " " << i << " " << bit * pow(10, i) + ans << endl;
//         ull c = pow(10, i);
//         ans += bit * c;
//         cout << "this is the ans " << ans << endl;
//         n = n / 2;
//         i++;
//     }
//     // cout << ans << endl;
//     ull finalans = numReverse(ans);
//     return finalans;
// }