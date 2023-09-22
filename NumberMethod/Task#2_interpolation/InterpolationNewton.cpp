#include <fstream>
#include <iostream>
#include <memory>

#define _USE_MATH_DEFINES
#include <cmath>

double func12(double x)
{
    return 5 / (2 + x + std::cos(x) * std::log(1 + x));
}

void InterpolationNode_Uniform(int a, int b, int n, double* pa)
{   
    double h = ((double) b - a) / (n - 1);

    for (int i = 0; i < n; i++)
    {
        *(pa + i) = i * h;
    }
}

void InterpolationNode_Chebyshev(int a, int b, int n, double* pa)
{
    for (int i = 0; i < n; i++)
    {
        *(pa + i) = (a + b)/2. + (b - a)/2. * std::cos((2. * (n - 1 - i) + 1.) / (2. * n) * M_PI);
        //std::cout << *(pa + i) << '\n';
    }
}

double DividedDiff (int n, double* pa)
{
    double sum = 0.;
    double subsum = 1.;
    for (int i = 0; i <= n; i++)
    {
        subsum = 1.;
        for (int j = 0; j <= n; j++)
        {
            if (j != i)
            {
                //std::cout << *(pa + i) << " -- \n";
                 subsum *= (*(pa + i) - *(pa + j));
            }
        }
        sum += func12(*(pa + i)) / subsum;
        //std::cout << sum << "!!\n";
    }
    
        //std::cout << "--------------  " << sum << "!!\n";
    return sum;
}

double NewtonInterpolant(double x, int n, double* pa)
{
    double* divDiff;
    double func_N = 0.;
    double subfunc_N = 1.;

    divDiff = (double *) malloc(n * sizeof (double));

    *divDiff = func12(*pa);
    //std::cout << *(pa + 1) << "!--!!\n";
    //std::cout << *divDiff << "!!!!!!\n";
    
    
    func_N = DividedDiff(n - 1, pa);
    for (int i = n - 2; i >= 0; i--)
    {
        //std::cout << i << ' ' << func_N << " ()()() ";
        func_N = func_N * (x - *(pa + i)) + DividedDiff(i, pa);
        //std::cout << x << " ===  " << *(pa + i) << ' ' << func_N << '\n';
    }
    //std::cout << DividedDiff(0, pa) << "!!!!!!!!@&#*#&@\n";
    free(divDiff);
    return func_N;
}

int main()
{
    int n = 4, N = 8; // n - кол-во узлов, N - кол-во значений интерполянта 
    int a = 0, b = 10;
    double* arrNode_Uni;
    double* arrNode_Cheb;

    arrNode_Uni = (double *) malloc(n * sizeof (double));
    arrNode_Cheb = (double *) malloc(n * sizeof (double));

    InterpolationNode_Uniform(a, b, n, arrNode_Uni);
    InterpolationNode_Chebyshev(a, b, n, arrNode_Cheb);
    /*
    for (int i = 0; i < n; i++)
    {
        std::cout << *(arrNode_Cheb + i) << ' ' << *(arrNode_Uni + i) << '\n';
    }*/

    const char csv_file_name[64] = "data_Newton.csv"; // имя файла для вывода
    std::ofstream csv_file;
    csv_file.open(csv_file_name);
    csv_file << "x,NewtonPolynom_Uni,NewtonPolynom_Cheb\n"; // записать заголовки колонок

    for (int i = 0; i <= N; i++){
        double I = 1. * i * (b - a) / N;
        csv_file << I << "," << NewtonInterpolant(I, n, arrNode_Uni) << "," << NewtonInterpolant(I, n, arrNode_Cheb) << "\n";
        
    }
    csv_file.close();

    free(arrNode_Cheb);
    free(arrNode_Uni);
    std::cout << "Final!\n";
    return 0;
}