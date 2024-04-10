#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

void print(std::vector <int> vec, int sz) { // Для вывода в формате правльных чисел 
    for (int i = sz - 1; i >= 0; --i) {
        std::cout << vec[i];
    }
    std::cout << '\n';
}

void printRight(std::vector <int> vec, int sz) { // Для проверки вывода в том в формате, в которои вектор лежит в программе
    for (int i = 0; i < sz; ++i) {
        std::cout << vec[i];
    }
    std::cout << '\n';
}

bool test(std::vector <int> vec1, std::vector <int> vec2) { // Проверка на то, что первое число > второго и можно вычитать
    if (vec1.size() > vec2.size()) return true;
    else if (vec1.size() < vec2.size()) return false;
    else {
        for (int i = vec2.size() - 1; i >= 0; --i) {
            if (vec2[i] < vec1[i]) return true;
            else if (vec2[i] > vec1[i]) return false;
        }
    }
    return true;
}

std::vector <int> cleaner(std::vector <int> vec) { // Для избавления от незначащих нулей
    //printRight(vec, vec.size());
    for (int i = vec.size() - 1; i >= 0; --i) {
        if (vec[i] == 0) vec.pop_back();
        else break;
        if (vec.size() == 1) break;
    }
    return vec;
}
std::vector <int> vecsum(std::vector <int> vec1, std::vector <int> vec2, int sz) { // Сумма число-векторов для возведения 2 в нужную степень
    std::vector <int> resultvector; // Число-вектор с результатом
    resultvector.push_back(0);
    resultvector[0] = (vec1[0] + vec2[0]) % 10;
    int md = (vec1[0] + vec2[0]) / 10; // Переменная остатка
    for (int i = 1; md > 0 || i < sz; ++i) {
        vec1.push_back(0);
        vec2.push_back(0);
        resultvector.push_back(0);
        resultvector[i] = (vec1[i] + vec2[i] + md) % 10;
        md = (vec1[i] + vec2[i] + md) / 10;
    }
    return resultvector;
}


std::vector <int> vecsub(std::vector <int> vec1, std::vector <int> vec2, int maxs, int mins) { // Разность число-векторов 
    std::vector <int> resultvector; // Число-вектор с результатом
    resultvector.push_back(0);
    if (test(vec1, vec2)) {
        for (int i = 0; i < mins; ++i) { // Вычитаем из 1-ого числа 2-е 
            resultvector.push_back(0);
            resultvector[i] = (vec1[i] - vec2[i]);
            if (resultvector[i] < 0) {
                for (int j = i + 1; j < maxs; j++) {
                    if (vec1[j] > 0) {
                        vec1[j] -= 1;
                        for (int k = j - 1; k > i; --k) {
                            vec1[k] += 9;
                        }
                        resultvector[i] += 10;
                        break;
                    }
                }
            }
        }
        resultvector = cleaner(resultvector);
        for (int i = mins; i < maxs; i++) { // Переписываем элементы 1-го числа, которые не задело вычитание
            resultvector.push_back(vec1[i]);
        }
        return cleaner(resultvector);
    }
    else {
        resultvector[0] = -1;
        return resultvector;
    }
}


int main() {
    setlocale(LC_ALL, "russian");
    std::cout << "Введите x и y: ";
    int x, y; // Две степени из исходных данных
    std::cin >> x >> y;
    std::cout << "\n";
    std::vector <int> vec1 = { 2 }, vec2 = { 2 };
    for (int i = 0; i < x - 1; ++i) {
        vec1 = vecsum(vec1, vec1, vec1.size());
    }
    print(vec1, vec1.size());
    std::cout << "\n";
    for (int i = 0; i < y - 1; ++i) {
        vec2 = vecsum(vec2, vec2, vec2.size());
    }
    print(vec2, vec2.size());
    std::cout << "\n";
    std::vector <int> vecanswer = vecsub(vec1, vec2, std::max(vec1.size(), vec2.size()), std::min(vec1.size(), vec2.size()));
    print(vecanswer, (int)vecanswer.size());
    return 0;
}