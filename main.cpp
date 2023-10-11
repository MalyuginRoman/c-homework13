#include "lib.h"

#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::vector<std::vector<double>> numbs;
    std::vector<double> numb;
    std::ifstream inputFile;
    int test_count = 18000;
    double correlation;
    int hit_number = 0;
    int class_object;
    std::vector<int> test_num;
    double calc_num = 0;
    std::vector<double> calc_hit;
    int calc_class_object = 0;

    inputFile.open("logreg_coef.txt");
    if (!inputFile.is_open()) {
        std::cout << "Ошибка при открытии файла!" << std::endl;
        return 0; }
    for (int j = 0; j < 10; j++)
    {
        numbs.push_back(numb);
        for (int i = 0; i < 785; i++)
        {
            long double number;
            inputFile >> number;
            numbs[j].push_back(number);
        }
    }
    inputFile.close();

    inputFile.open("test.csv");
    if (!inputFile.is_open()) {
        std::cout << "Ошибка при открытии файла!" << std::endl;
        return 0; }
    for (int i = 0; i < test_count; ++i)                    // i - номер строки с тестовыми данными
    {
        inputFile >> class_object;
        for (int j = 0; j < 10; j++)                        // j - номер рассчитываемого объекта
        {
            calc_num = numbs[j].at(0);
            for (int k = 0; k < 784; k++)                   // k - номер рассчитываемого коэффициента
            {
                int number;
                if (j == 0)
                {
                    char separator;
                    inputFile >> separator >> number;
                    test_num.push_back(number);
                }
                else
                    number = test_num.at(k);
                calc_num += numbs[j].at(k + 1) * number;
                if(k == 783)
                {
                    calc_hit.push_back(calc_num);
                    if(calc_num > calc_class_object)
                        calc_class_object = j;
                }
            }
        }
        if(calc_class_object == class_object)
        {
            hit_number++;
std::cout << i << "+" << std::endl;
        }
        calc_hit.clear();
        test_num.clear();
        calc_class_object = 0;
    }
    inputFile.close();

    correlation = 1.0 * hit_number / test_count;
std::cout << "correlation = " << hit_number << "/" << test_count << "=" << correlation << std::endl;

    return 0;
}
