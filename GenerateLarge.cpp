#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/random.hpp>
#include <boost/integer/mod_inverse.hpp>
#include <boost/math/common_factor_rt.hpp>

#include "Setup.h"

using namespace boost::multiprecision;

std::pair<int1024_t, int1024_t> generate(int512_t a, int512_t b, int1024_t n)
{
    int1024_t e;
    auto mt = boost::random::mt19937(std::random_device()());
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

    int1024_t n;

    int option, bits;
    std::cout << "Choose number of bits:\n1. 256\n2. 512\n";
    std::cin >> option;

    if(option == 1)
    {
        bits = 128;
    }
    else if(option == 2)
    {
        bits = 256;
    }
    else
    {
        std::cout << "Wrong input\n";
        return 0;
    }

    std::cout << "Initializing...\n";
    for(int i = 0; i < bits; i++)//256-bits keys -> i < 128
    {
        a = a * 2;
        b = b * 2;
    }

    a = a / 2;//Range for finding primes

    Setup* setup = new Setup();

    std::pair<int512_t, int512_t> primes = setup->findPrimes(a, b, n);

    std::cout << primes.first << " " << primes.second << "\n";

	std::pair<int1024_t, int1024_t> res1 = generate(primes.first, primes.second, n);
    std::pair<int1024_t, int1024_t> res2 = generate(primes.first, primes.second, n);

    std::cout << "e = " << res1.first << "\nd = " << res1.second << "\n";
    std::cout << "e = " << res2.first << "\nd = " << res2.second << "\n";
    std::cout << "n = " << n << "\n";    
    
    int1024_t message;

    std::cout << "Input message: ";
    std::cin >> message;

    int1024_t encrypted = encryption(message, res1.first, n);

    std::cout << "encrypted message: " << encrypted << "\n";

    int1024_t dec = encryption(encrypted, res1.second, n);

    std::cout << "decrypted message: " << dec % n << "\n";

    std::ofstream myfile;
    myfile.open("keysAlice.txt");
    myfile << res1.first << "\n" << res1.second << "\n" << n;
    myfile.close();

    myfile.open("keysBob.txt");
    myfile << res2.first << "\n" << res2.second << "\n" << n;
    myfile.close();

    delete(setup);

	return 0;
}
