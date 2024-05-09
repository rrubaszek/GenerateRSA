#pragma once
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Setup
{
public:
    Setup();
    std::pair<int512_t, int512_t> findPrimes(int512_t a, int512_t b, int1024_t& n);
    template<typename T> static T power(T a, T b, T n);

private:
    bool millerTest(int512_t d, int512_t n);
    bool isPrime(int512_t number, int k);

};