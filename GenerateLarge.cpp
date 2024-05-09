#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/random.hpp>
#include <boost/integer/mod_inverse.hpp>
#include <boost/math/common_factor_rt.hpp>

using namespace boost::multiprecision;

static int1024_t n;

auto mt = boost::random::mt19937(std::random_device()());

int512_t power(int512_t a, int512_t b, int512_t n)
{
    int512_t result = 1;
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

int1024_t power1(int1024_t a, int1024_t b, int1024_t n)
{
    int1024_t result = 1;
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

bool millerTest(int512_t d, int512_t n)
{
    int512_t a = 2 + rand() % (n - 4);
 
    int512_t x = power(a, d, n);
 
    if (x == 1  || x == n-1)
       return true;
 
    while (d != n-1)
    {
        x = (x * x) % n;
        d *= 2;
 
        if (x == 1)      
            return false;
        if (x == n-1)    
            return true;
    }
 
    return false;
}
 
bool isPrime(int512_t number, int k)
{
    if (number <= 1 || number == 4) 
        return false;
    if (number <= 3) 
        return true;
 
    int512_t d = number - 1;
    while (d % 2 == 0)
        d /= 2;

    for(int i = 0; i < k; i++)
        if (!millerTest(d, number))
            return false;
 
    return true;
}

std::pair<int512_t, int512_t> findPrimes(int512_t a, int512_t b)
{
    std::cout << "Generating...\n";

    int k = 100;

    int512_t p, q;
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

std::pair<int1024_t, int1024_t> generate(int512_t a, int512_t b)
{
    int1024_t e;
    auto ui = boost::random::uniform_int_distribution<cpp_int>(1, n - 1);
	do
	{
		e = static_cast<int1024_t>(ui(mt));

	} while (boost::math::gcd<int1024_t>(n, e) != 1);

	int1024_t d = boost::integer::mod_inverse(e, n);

    return std::make_pair(e, d);
}

int1024_t encryption(int1024_t m, int1024_t key, int1024_t n)
{
    return (m * key) % n;
    //return power1(m, key, n);
}

int main()
{
    int512_t a = 1;
    int512_t b = 1;

    int bits;
    std::cin >> bits;

    std::cout << "Initializing...\n";
    for(int i = 0; i < bits; i++)//256-bits keys -> i < 128
    {
        a = a * 2;
        b = b * 2;
    }

    a = a / 2;//Range for finding primes

    std::pair<int512_t, int512_t> primes = findPrimes(a, b);

    std::cout << primes.first << " " << primes.second << "\n";

	std::pair<int1024_t, int1024_t> res1 = generate(primes.first, primes.second);
    std::pair<int1024_t, int1024_t> res2 = generate(primes.first, primes.second);

    std::cout << "e = " << res1.first << "\nd = " << res1.second << "\n";
    std::cout << "e = " << res2.first << "\nd = " << res2.second << "\n";
    std::cout << "n = " << n << "\n";    
    
    int1024_t message = 15;

    int1024_t encrypted = encryption(message, res1.first, n);

    std::cout << "encrypted message: " << encrypted << "\n";

    int1024_t dec = encryption(encrypted, res1.second, n);

    std::cout << "decrypted message: " << dec % n << "\n";

    std::ofstream myfile;
    myfile.open ("keys.txt");
    myfile << res1.first << "\n" << res1.second << "\n" << res2.first << "\n" << res2.second << "\n" << n;
    myfile.close();

	return 0;
}
