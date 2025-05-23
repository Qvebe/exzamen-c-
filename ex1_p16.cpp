#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double calculateYFormula(double x) {
    // arcsin((sqrt(x)/(sqrt(x)+1))^5)
    double term1 = asin(pow(sqrt(x) / (sqrt(x) + 1), 5));
    
    // (x^2 + 1)^(1/5)
    double term2 = pow(x * x + 1, 0.2);
    
    // log2(2^sinx + |x|^cosx)
    double term3 = log2(pow(2, sin(x)) + pow(fabs(x), cos(x))));
    
    return term1 + term2 + term3;
}

bool isInDomain(double x, double y) {
    return (y >= 0) && (x * x + y * y <= 25);
}

int main() {
    double x;
    cout << "Введите значение x: ";
    cin >> x;
    
    double y_formula = calculateYFormula(x);
    
    cout << fixed << setprecision(6);
    cout << "Результат вычисления по формулам: y = " << y_formula << endl;
    
    bool inDomain = isInDomain(x, y_formula);
    cout << "Точка (x, y) принадлежит области D: " << boolalpha << inDomain << endl;
    
    return 0;
}
