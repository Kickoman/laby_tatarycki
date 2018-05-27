#include <iostream>
#include <cmath>

using namespace std;

double f(double x) // var 9
{
    return x * x * x + 10 * x * x - 50;
}

double findRoots(double a, double b, double eps, double h)
{
    double x0 = a, x1 = b;
    double x2 = 0, delta = 0;
    do {
        x2 = x1 - f(x1)*(x1 - x0)/(f(x1) - f(x0));
        delta = fabs(x1 - x2);
        x0 = x1; x1 = x2;
    } while (delta > eps);
    return x2;
}

int main()
{
    /* initial values */
    double a, b, h, eps;
    cout << "Computing roots for the function sin(x)^2 - 3*cos(x)\n"
            "Please, input the range.\n";
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "Please, input step size\n";
    cout << "h = ";
    cin >> h;
    cout << "Please, input the epsilon (for approximation)\n";
    cout << "eps = ";
    cin >> eps;

    for (double x = a; x <= b; x += h)
    {
        if (f(x) * f(x + h) < 0)
        {
            double y = findRoots(x, x + h, eps, h);
            cout << "Root: " << y << endl;
        }
    }
    return 0;
}
