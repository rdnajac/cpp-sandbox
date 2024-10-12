#include <iostream>
#include <string>

using namespace std;

class Complex {
public:
    int a, b;

    void input(string s) {
        int v1 = 0, v2 = 0;
        int i = 0;
        while (s[i] != '+') {
            v1 = v1 * 10 + (s[i] - '0');
            i++;
        }
        i += 3; // Skip over '+i'
        while (i < s.length()) {
            v2 = v2 * 10 + (s[i] - '0');
            i++;
        }
        a = v1;
        b = v2;
    }
};

// Overload operator + for Complex
Complex operator+(const Complex& c1, const Complex& c2) {
    Complex result;
    result.a = c1.a + c2.a;
    result.b = c1.b + c2.b;
    return result;
}

// Overload operator << for Complex
ostream& operator<<(ostream& os, const Complex& c) {
    os << c.a << "+i" << c.b;
    return os;
}

int main() {
    Complex x, y;
    string s1, s2;
    cin >> s1 >> s2;
    x.input(s1);
    y.input(s2);
    Complex z = x + y;
    cout << z << endl;
    return 0;
}
