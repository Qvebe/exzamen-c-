#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void fillArray(vector<vector<int>>& arr, int rows, int cols, int minVal, int maxVal) {
    srand(time(0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            arr[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
}

void printArray(const vector<vector<int>>& arr) {
    for (const auto& row : arr) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << endl;
    }
}

void findElements(const vector<vector<int>>& arr, int threshold) {
    int count = 0;
    cout << "\nЭлементы, удовлетворяющие условию (неотрицательные и сумма индексов > " << threshold << "):\n";
    
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = 0; j < arr[i].size(); ++j) {
            if (arr[i][j] >= 0 && (i + j) > threshold) {
                cout << "Элемент [" << i << "][" << j << "] = " << arr[i][j] << endl;
                count++;
            }
        }
    }
    
    cout << "\nОбщее количество таких элементов: " << count << endl;
}

int main() {
    int rows, cols;
    cout << "Введите количество строк массива: ";
    cin >> rows;
    cout << "Введите количество столбцов массива: ";
    cin >> cols;
    
    vector<vector<int>> array(rows, vector<int>(cols));
    
    fillArray(array, rows, cols, -10, 10);
    
    cout << "\nСгенерированный массив:\n";
    printArray(array);
    
    int threshold;
    cout << "\nВведите пороговое значение суммы индексов: ";
    cin >> threshold;
    
    findElements(array, threshold);
    
    return 0;
}
