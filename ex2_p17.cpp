#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double V1, t1, V2, t2;
    
    cout << "Введите объем первой жидкости (V1 в литрах): ";
    cin >> V1;
    
    cout << "Введите температуру первой жидкости (t1 в градусах): ";
    cin >> t1;
    
    cout << "Введите объем второй жидкости (V2 в литрах): ";
    cin >> V2;
    
    cout << "Введите температуру второй жидкости (t2 в градусах): ";
    cin >> t2;
    
    double V_mix = V1 + V2;
    
    double t_mix = (V1 * t1 + V2 * t2) / V_mix;
    
    cout << fixed << setprecision(2);
    cout << "\nРезультаты расчета смеси:\n";
    cout << "Объем смеси: " << V_mix << " л\n";
    cout << "Температура смеси: " << t_mix << " градусов\n";
    
    return 0;
}
