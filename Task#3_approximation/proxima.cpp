#include <fstream>
#include <iostream>
#include <memory>

#define _USE_MATH_DEFINES
#include <cmath>

double func12(double x)
{
    return std::cosh(std::sin(x));
}

void func12_1_2(double a, double b, int n, double* func, double* derived)
{
    double h = (b - a) / (n - 1);

    *derived = (-3 * *(func) + 4 * *(func + 1) - *(func + 2)) / (2 * h);
    for (int i = 1; i < n - 1; i++)
    {
        *(derived + i) = (*(func + i + 1) - *(func + i - 1)) / (2 * h);
    }
    *(derived + n - 1) = (*(func + n - 3) - 4 * *(func + n - 2) + 3 * *(func + n - 1)) / (2 * h);
}

void func12_2_2(double a, double b, int n, double* func, double* derived)
{
    double h = (b - a) / (n - 1);

    *derived = (2 * *(func) - 5 * *(func + 1) + 4 * *(func + 2) - *(func + 3)) / (h * h);
    for (int i = 1; i < n - 1; i++)
    {
        *(derived + i) = (*(func + i - 1) - 2 * *(func + i) + *(func + i + 1)) / (h * h);
    }
    *(derived + n - 1) = (-1 * *(func + n - 4) + 4 * *(func + n - 3) - 5 * *(func + n - 2) + 2 * *(func + n - 1)) / (h * h);
}

void func12_2_4(double a, double b, int n, double* func, double* derived)
{
    double h = (b - a) / (n - 1);

    *derived = (45 * *(func) - 154 * *(func + 1) + 214 * *(func + 2) - 156 * *(func + 3) + 61 * *(func + 4) - 10 * *(func + 5)) / (12 * h * h);
    *(derived + 1) = (10 * *(func) - 15 * *(func + 1) - 4 * *(func + 2) + 14 * *(func + 3) - 6 * *(func + 4) + *(func + 5)) / (12 * h * h);
    for (int i = 2; i < n - 2; i++)
    {
        *(derived + i) = (-1 * *(func + i - 2) + 16 * *(func + i - 1) - 30 * *(func + i) + 16 * *(func + i + 1) - *(func + i + 2)) / (12 * h * h);
    }
    *(derived + n - 2) = (10 * *(func + n - 1) - 15 * *(func + n - 2) - 4 * *(func + n - 3) + 14 * *(func + n - 4) - 6 * *(func + n - 5) + *(func + n - 6)) / (12 * h * h);
    *(derived + n - 1) = (45 * *(func + n - 1) - 154 * *(func + n - 2) + 214 * *(func + n - 3) - 156 * *(func + n - 4) + 61 * *(func + n - 5) - 10 * *(func + n - 6)) / (12 * h * h);
}

void Node_Uniform(double a, double b, int n, double* pa)
{   
    double h = (b - a) / (n - 1);

    for (int i = 0; i < n; i++)
    {
        *(pa + i) = a + h * i;
    }
}

void DataCSV_creator(std::string fileName, int size, double* x_node, double* y_node)
{
    std::ofstream csv_file;
    csv_file.open(fileName);
    csv_file << "x,Func\n"; // записать заголовки колонок
    for (int i = 0; i < size; i++)
    {
        csv_file << *(x_node + i) << "," << *(y_node + i) << "\n";
    }
    csv_file.close();
}

int main()
{
    int n = 10; // n - кол-во узлов
    double a = -1.5, b = 1.5;
    double* arrNode_Uni;
    double* arrFunc_0_Uni;
    double* arrFunc_1_2_Uni;
    double* arrFunc_2_2_Uni;
    double* arrFunc_2_4_Uni;

    arrNode_Uni = (double *) malloc(n * sizeof (double));
    arrFunc_0_Uni = (double *) malloc(n * sizeof (double));
    arrFunc_1_2_Uni = (double *) malloc(n * sizeof (double));
    arrFunc_2_2_Uni = (double *) malloc(n * sizeof (double));
    arrFunc_2_4_Uni = (double *) malloc(n * sizeof (double));

    Node_Uniform(a, b, n, arrNode_Uni);

    for (int i = 0; i < n; i++)
    {
        *(arrFunc_0_Uni + i) = func12(*(arrNode_Uni + i));
    }

    func12_1_2(a, b, n, arrFunc_0_Uni, arrFunc_1_2_Uni);
    func12_2_2(a, b, n, arrFunc_0_Uni, arrFunc_2_2_Uni);
    func12_2_4(a, b, n, arrFunc_0_Uni, arrFunc_2_4_Uni);

    DataCSV_creator("data_Func.csv", n, arrNode_Uni, arrFunc_0_Uni);
    DataCSV_creator("data_DerFunc1_2.csv", n, arrNode_Uni, arrFunc_1_2_Uni);
    DataCSV_creator("data_DerFunc2_2.csv", n, arrNode_Uni, arrFunc_2_2_Uni);
    DataCSV_creator("data_DerFunc2_4.csv", n, arrNode_Uni, arrFunc_2_4_Uni);

    free(arrNode_Uni);
    free(arrFunc_0_Uni);
    free(arrFunc_1_2_Uni);
    free(arrFunc_2_2_Uni);
    free(arrFunc_2_4_Uni);
    return 0;
}