#include "Setup.h"
#include <iostream>
#include <random>
#include <boost/multiprecision/random.hpp>

using namespace boost::multiprecision;

Setup::Setup(){}

template<typename T> 
T Setup::power(T a, T b, T n)
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

bool Setup::millerTest(int512_t d, int512_t n)
{
    int512_t a = 2 + rand() % (n - 4);
 
    int512_t x = power<int512_t>(a, d, n);
 
    if (x == 1  || x == n-1)
    {
        return true;
    }
 
    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)
        {
            return false;
        }      
            
        if (x == n-1)
        {
            return true;
        }    
            
    }
 
    return false;
}
 
bool Setup::isPrime(int512_t number, int k)
{
    if (number <= 1 || number == 4) 
    {
        return false;
    }
        
    if (number <= 3) 
    {
        return true;
    }
 
    int512_t d = number - 1;
    while (d % 2 == 0)
    {
        d /= 2;
    }
      
    for(int i = 0; i < k; i++)
    {
        if (!millerTest(d, number))
        {
            return false;
        }       
    }  
 
    return true;
}

std::pair<int512_t, int512_t> Setup::findPrimes(int512_t a, int512_t b, int1024_t& n)
{
    std::cout << "Generating...\n";

    int k = 100;

    int512_t p, q;
    auto mt = boost::random::mt19937(std::random_device()());
    auto ui = boost::random::uniform_int_distribution<cpp_int>(a, b);
    do
    {
        p = static_cast<int512_t>(ui(mt));

    } while (!isPrime(p, k));
    
    do
    {
        q = static_cast<int512_t>(ui(mt));

    } while (!isPrime(q, k));
	
	//n = (int1024_t)(p * q);

    //another version
    n = (int1024_t)((p-1) * (q-1));

    return std::make_pair(p, q);
}