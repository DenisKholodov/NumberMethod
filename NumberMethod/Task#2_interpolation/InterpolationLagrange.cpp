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
        std::cout << *(pa + i) << '\n';
    }
}

double LagrangeInterpolant(double x, int n, double* pa)
{
    long double func_L = 0.;
    long double subfunc_L = 1.;

    for(int i = 0; i < n; i++)
    {
        //double a = *(pa + i);
        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                subfunc_L *= (x - *(pa + j))/(*(pa + i) - *(pa + j));
                
            }
        }
        
       // std::cout << *(pa + i) << "! " << subfunc_L << "! ";
        func_L += func12(*(pa + i)) * subfunc_L;
        //std::cout << func_L << "!\n";
        subfunc_L = 1.;
    }
    return func_L;
}

int main()
{
    int n = 5, N = 9; // n - кол-во узлов, N - кол-во значений интерполянта 
    int a = 0, b = 10;
    double* arrNode_Uni;
    double* arrNode_Cheb;

    arrNode_Uni = (double *) malloc(n * sizeof (double));
    arrNode_Cheb = (double *) malloc(n * sizeof (double));

    InterpolationNode_Uniform(a, b, n, arrNode_Uni);
    InterpolationNode_Chebyshev(a, b, n, arrNode_Cheb);
    
    for (int i = 0; i < n; i++)
    {
        std::cout << *(arrNode_Cheb + i) << ' ' << *(arrNode_Uni + i) << '\n';
    }

    const char csv_file_name[64] = "data_Lagrange.csv"; // имя файла для вывода
    std::ofstream csv_file;
    csv_file.open(csv_file_name);
    csv_file << "x,LagrangePolynom_Uni,LagrangePolynom_Cheb\n"; // записать заголовки колонок

    for (int i = 0; i < N; i++){
        double I = 1. * i * (b - a) / (N - 1);
        std::cout << I << '\n';
        csv_file << I << "," << LagrangeInterpolant(I, n, arrNode_Uni) << "," << LagrangeInterpolant(I, n, arrNode_Cheb) << "\n";
        
    }
    csv_file.close();

    free(arrNode_Cheb);
    free(arrNode_Uni);
    return 0;
}