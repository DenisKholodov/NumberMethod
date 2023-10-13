#include <fstream>
#include <iostream>
#include <memory>

#define _USE_MATH_DEFINES
#include <cmath>

double Func(double x)
{
    return pow(x, 3) / (1 - pow(x, 4));
}

double Func_(double x)
{
    return -0.25 * log(abs(1 - pow(x, 4)));
}

double IntagrateRectangle(double func(double), double a, double b, int n)
{
    double I = 0.;
    double h = (b - a) / (n - 1);

    for (int i = 0; i < n; i++)
    {
        I += Func(a + h * (i + 0.5));
    }

    return I * h;
}

double IntagrateTrapezoid(double func(double), double a, double b, int n)
{
    double I = 0.;
    double h = (b - a) / (n - 1);

    for (int i = 0; i < n; i++)
    {
        I += Func(a + h * (i + 1)) + Func(a + h * i);
    }

    return I * h / 2;
}

double IntagrateSimpson(double func(double), double a, double b, int n)
{
    double I = 0.;
    double h = (b - a) / (n - 1);

    for (int i = 1; i < n; i++)
    {
        I += Func(a + h * (i - 1)) + 4 * Func(a + h * i) + Func(a + h * (i + 1));
    }

    return I * h / 6;
}

int main()
{
    int n = 1000000; // n - кол-во узлов
    double a = 2., b = 4.;

    std::cout << Func_(b) - Func_(a) << '\n';
    std::cout << IntagrateRectangle(Func, a, b, n) << '\n';
    std::cout << IntagrateTrapezoid(Func, a, b, n) << '\n';
    std::cout << IntagrateSimpson(Func, a, b, n) << '\n';

    std::cout << "errorRectangle = " << fabs(IntagrateRectangle(Func, a, b, n) - Func_(b) + Func_(a)) << '\n';
    std::cout << "errorTrapezoid = " << fabs(IntagrateTrapezoid(Func, a, b, n) - Func_(b) + Func_(a)) << '\n';
    std::cout << "errorSimpson   = " << fabs(IntagrateSimpson(Func, a, b, n) - Func_(b) + Func_(a)) << '\n';

    return 0;
}