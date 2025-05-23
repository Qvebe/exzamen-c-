#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculateY(double x) {
    if (x < -1.0) {
        // y(x) = x^6 * lg|6^x - |x-5|^x|
        double term1 = pow(6.0, x);
        double term2 = pow(fabs(x - 5.0), x);
        return pow(x, 6) * log10(fabs(term1 - term2));
    } 
    else if (x >= -1.0 && x < 1.0) {
        // y(x) = sin(x / (1 - 2x^2))
        return sin(x / (1.0 - 2.0 * pow(x, 2)));
    } 
    else {
        // y(x) = arcsin(1 / x^4)
        return asin(1.0 / pow(x, 4));
    }
}

int main() {
    double x;
    cout << "Введите значение x: ";
    cin >> x;

    if (x >= 1.0 && fabs(1.0 / pow(x, 4)) > 1.0) {
        cout << "Ошибка: для x = " << x << " значение 1/x^4 выходит за область определения arcsin (должно быть [-1, 1])" << endl;
        return 1;
    }

    if (x >= -1.0 && x < 1.0 && (1.0 - 2.0 * pow(x, 2)) == 0.0) {
        cout << "Ошибка: для x = " << x << " знаменатель равен нулю" << endl;
        return 1;
    }

    double y = calculateY(x);

    cout << fixed << setprecision(6);
    cout << "y(" << x << ") = " << y << endl;

    return 0;
}
