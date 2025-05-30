#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class MathFunction {
private:
    double x;

public:
    MathFunction(double x_val) : x(x_val) {}

    double calculateY() {
        // arcsin((sqrt(x)/(sqrt(x)+1))^5)
        double term1 = asin(pow(sqrt(x) / (sqrt(x) + 1), 5));
        
        // (x^2 + 1)^(1/5)
        double term2 = pow(x * x + 1, 0.2);
        
        // log2(2^sinx + |x|^cosx)
        double term3 = log2(pow(2, sin(x)) + pow(fabs(x), cos(x))));
        
        return term1 + term2 + term3;
    }

    bool isInDomain(double y) {
        return (y >= 0) && (x * x + y * y <= 25);
    }

    double getX() const {
        return x;
    }
};

class DomainChecker {
private:
    double x;
    double y;

public:
    DomainChecker(double x_val, double y_val) : x(x_val), y(y_val) {}

    bool check() {
        return (y >= 0) && (x * x + y * y <= 25);
    }
};

class Application {
public:
    void run() {
        double x = getInput();
        MathFunction func(x);
        double y = func.calculateY();
        
        DomainChecker checker(x, y);
        bool inDomain = checker.check();
        
        displayResults(y, inDomain);
    }

private:
    double getInput() {
        double x;
        cout << "Введите значение x: ";
        cin >> x;
        return x;
    }

    void displayResults(double y, bool inDomain) {
        cout << fixed << setprecision(6);
        cout << "Результат вычисления по формулам: y = " << y << endl;
        cout << "Точка (x, y) принадлежит области D: " << boolalpha << inDomain << endl;
    }
};

int main() {
    Application app;
    app.run();
    return 0;
}
