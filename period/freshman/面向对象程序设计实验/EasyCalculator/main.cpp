#include "scanner.h"
#include "calculator.h"
using namespace std;

void menu();
void help();
void credits();

int main()
{
    menu();

    string expression;
    while (input(expression))
    {
        if (expression == "exit") {
            exit(0);
        }
        if (expression == "help") {
            help(); continue;
        }
        if (expression == "credits") {
            credits(); continue;
        }
        if (resolve(expression)) {
            cout << calculate() << endl;
        }
        else cout << "Unable to resolve your input..." << endl;
    }
}

void menu()
{
    cout << "Easy Calculator v0.1.0" << endl;
    cout << R"(Type "help" or "credits" for more information.)" << endl;
}

void help()
{
    cout << "This calculator can only perform +-*/ ..." << endl;
    cout << "It doesn't support operators that accept one argument..." << endl;
    cout << endl;
    cout << "Availbe commands:" << endl;
    cout << "exit - Terminating this calculator" << endl;
}

void credits()
{
    cout << "Easy Calculator v0.1.0" << endl;
    cout << "Code by Jinhong Xie(1706300001)." << endl;
    cout << "Please contact 419246300@qq.com if you have any problem" << endl;
}
