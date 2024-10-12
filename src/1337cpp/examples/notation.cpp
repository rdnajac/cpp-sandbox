#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Example values
    double A = 100.345;
    double B = 2006.008;
    double C = 2331.41592653498;

    // Output for A: hexadecimal representation (truncated to int)
    cout << "0x" << hex << static_cast<int>(A) << endl;

    // Output for B: formatted to 2 decimal places, right justified
    cout << setw(15) << fixed << setprecision(2) << (B >= 0 ? "+" : "") << B << endl;

    // Output for C: scientific notation with 9 decimal places
    cout << scientific << uppercase << setprecision(9) << C << endl;

    return 0;
}
