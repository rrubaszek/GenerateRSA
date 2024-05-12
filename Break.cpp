#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/math/common_factor.hpp>
#include <boost/integer/mod_inverse.hpp>

using namespace boost::multiprecision;

template<typename T>
T power(T a, T b, T n)
{
    T result = 1;

    a = a % n;

    if(a == 0)
    {
        return 0;
    }

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
}

std::pair<int1024_t, int1024_t> crack(int1024_t e, int1024_t d, int1024_t n, int1024_t& p, int1024_t& q)
{
    int1024_t phi = ((e * d) - 1);
    int1024_t t = phi;
    while(t % 2 == 0)
    {
	std::cout << t << "\n";
        t = t / 2;
    }

    std::cout << "T: " << t << "Phi: " << phi << "\n";

    int1024_t k, x;
    int1024_t a = 2;
    while(true)
    {
        k = t;
        while(k < phi)
        {
            x = power<int1024_t>(a, k, n);
            if(x != 1 && x != (n - 1) && (x*x) % n == 1)
            {
                p = boost::math::gcd<int1024_t>(x-1, n);
		        q = n / p;
		        return std::make_pair(p, q);
            }

            k = k * 2;
        }

        a = a + 1;
    }
    return std::make_pair(0, 0);
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

    std::ifstream inputFile1("keysBob.txt");
    if (!inputFile1) 
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    while(inputFile1 >> num)
    {
        numbers.push_back(num);
    }

    int1024_t e, e2, d, n;
    e = numbers.at(0);
    d = numbers.at(1);
    n = numbers.at(2);
    e2 = numbers.at(3);

    std::cout << "Cracking...\n";
    auto res = crack(e, d, n, p, q);
    std::cout << res.first << "\n" << res.second << "\n";
    std::cout << "d = " << boost::integer::mod_inverse(e2, n) << " e = " << e2;

    return 0;
}
