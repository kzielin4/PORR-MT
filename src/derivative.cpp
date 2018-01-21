#include <boost/multiprecision/cpp_dec_float.hpp>

template<typename value_type, typename function_type>
value_type derivative(const value_type x, const value_type dx, function_type func) {
    const value_type dx1 = dx;
    const value_type dx2 = dx1 * 2;
    const value_type dx3 = dx1 * 3;

    const value_type m1 = (func(x + dx1) - func(x - dx1)) / 2;
    const value_type m2 = (func(x + dx2) - func(x - dx2)) / 4;
    const value_type m3 = (func(x + dx3) - func(x - dx3)) / 6;

    const value_type fifteen_m1 = 15 * m1;
    const value_type six_m2 = 6 * m2;
    const value_type ten_dx1 = 10 * dx1;

    return ((fifteen_m1 - six_m2) + m3) / ten_dx1;
}

double fun1(double x) {
    return (x == 0) ? 0 : sin(x) / x;
}

double fun2(double x) {
    return (x - 1.5) * (x - 1.5);
}

double fun3(double x) {
    return ((1 / 40) * x * x) + 1 - cos(x);
}

double fun4(double x) {
    return 5 * (sin(0.2 * x) + cos(0.7 * x));
}

double fun5(double x) {
    return sin(cos(x)) * x;
}

double dfun1(double a) {
    derivative(a, 1.0,
               [](const double &x) -> double {
                   return (x == 0) ? 1 : sin(x) / x;
               }
    );
}

double dfun2(double a) {
    derivative(a, 1.0,
               [](const double &x) -> double {
                   return (x - 1.5) * (x - 1.5);
               }
    );
}

double dfun3(double a) {
    derivative(a, 1.0,
               [](const double &x) -> double {
                   return ((1 / 40) * x * x) + 1 - cos(x);
               }
    );
}

double dfun4(double a) {
    derivative(a, 1.0,
               [](const double &x) -> double {
                   return 5 * (sin(0.2 * x) + cos(0.7 * x));
               }
    );
}


double dfun5(double a) {
    derivative(a, 1.0,
               [](const double &x) -> double {
                   return sin(cos(x)) * x;
               }
    );
}

double getL(double (*derivative)(double),double a,double b){
    double dMax = -9999999;
    double valueofdMax=-999999999;
    for(double x = a;x<=b;x=x+0.01) {
        double val = derivative(x);
        if (std::abs(val) > dMax) {
            valueofdMax = val;
            dMax = std::abs(val);
        }
    }
    return valueofdMax;
}