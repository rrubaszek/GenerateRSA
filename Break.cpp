#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor.hpp>

#include "Setup.h"

using namespace boost::multiprecision;

template<typename T> 
T power(T a, T b, T n)
{
    T result = 1;
    while(b > 0) 
    {
        if(b % 2 == 1) 
        {
            result = (result*a) % n;
        }
        a = (a * a) % n;
        b = b / 2; 
    }

    return result;
};

void crack(int1024_t e, int1024_t d, int1024_t n, int1024_t& p, int1024_t& q)
{
    int1024_t t = (e * d - 1);
    int1024_t phi = t;
    while(t % 2 == 0)
    {
        t = t / 2;
    }

    int1024_t k, x;
    int1024_t temp = 1;
    int1024_t a = 2;
    while(a < 100)
    {
        k = t;
        while(k < phi)
        {
            x = power<int1024_t>(a, k, n);
            if(x != 1 && x != (n - 1) && (x*x) % n == 1)
            {
                temp = boost::math::gcd<int1024_t>(x-1, n);
                break;
            }

            k = k * 2;
        }

        a = a + 2;
    }
    
    q = n / temp;
    p = temp;

}

int main()
{
    int1024_t p, q;

    std::ifstream inputFile("keysAlice.txt");
    if (!inputFile) 
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::vector<int1024_t> numbers;
    int1024_t num;
    while (inputFile >> num) 
    {
        numbers.push_back(num);
    }

    int1024_t e, d, n;
    e = numbers.at(0);
    d = numbers.at(1);
    n = numbers.at(2);

    std::cout << "Cracking...\n";
    crack(e, d, n, p, q);
    std::cout << p << "\n" << q << "\n";

    return 0;
}