#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

/**
 * @brief функция для вывода в формате правильных чисел 
 * 
 * @param vec значение перевернутого результируещего числа
 * @param sz размер вектора
 */
void print(std::vector <int> vec, int sz) { 
    for (int i = sz - 1; i >= 0; --i) {
        std::cout << vec[i];
    }
    std::cout << '\n';
}

/**
 * @brief Функция проверка на то, что первое число > второго и можно вычитать
 * 
 * @param vec1 первое число вектор
 * @param vec2 второе число вектор
 * @return true если можно вычитать
 * @return false нельзя вычитать
 */

bool test(std::vector <int> vec1, std::vector <int> vec2) { 
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

/**
 * @brief функция для избавления от незначащих нулей
 * 
 * @param vec вектор число
 * @return std::vector <int> "чистый" вектор
 */
std::vector <int> cleaner(std::vector <int> vec) { 
    for (int i = vec.size() - 1; i >= 0; --i) {
        if (vec[i] == 0) vec.pop_back();
        else break;
        if (vec.size() == 1) break;
    }
    return vec;
}

/**
 * @brief функция суммирования для возведения в степень 
 * 
 * @param vec1 вектор 1
 * @param vec2 вектор 2
 * @param sz размер вектора
 * @return std::vector <int> результирующий вектор в степени
 */
std::vector <int> vecsum(std::vector <int> vec1, std::vector <int> vec2, int sz) { 
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

/**
 * @brief функция для нахождения разности вектором
 * 
 * @param vec1 число вектор в степени
 * @param vec2 число вектор в степени
 * @param maxs максимальный размер бОльшего вектора
 * @param mins минимальный размер меньшего вектора
 * @return std::vector <int> разность векторов
 */

std::vector <int> vecsub(std::vector <int> vec1, std::vector <int> vec2, int maxs, int mins) {  
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