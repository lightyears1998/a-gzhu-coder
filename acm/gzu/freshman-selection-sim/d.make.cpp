#include <iostream>
#include <string>
using namespace std;

void simplify(string str)
{
    if (str.length() <= 3) cout << str << endl;
    else if (str.length() % 2)
    {
        string nxt = str.substr(0, str.length() - 1);
        simplify(nxt);
    }
    else
    {
        string nxt;
        for (int i = 0; i < str.length(); i += 2)
        {
            int sum = ((int)str[i] + (int)str[i + 1]) % 26;
            nxt += char('a' + sum);
        }
        simplify(nxt);
    }
}

int main()
{
    string a = string("jtkhaprkcwgioyddqrkhxfdkafqefolqnklztsmqiablgjonzcbtbswsywaorcwqxrvpkckcdqkillfnrfnyntkvxdohpzpijoem");
    simplify(a);
}
