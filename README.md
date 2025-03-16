# RSA Key Generation with Boost Library

This repository contains a C++ implementation for **generating RSA keys**, utilizing the **Boost Multiprecision Library** for handling large numbers. The project consists of two main files:

- **Setup.cpp**: Contains helper functions for key generation.
- **GenerateLarge.cpp**: The main entry point, which generates the RSA key pair.

## Features
- Uses **Boost Multiprecision** for handling large prime numbers.
- Implements **RSA key pair generation**.
- Efficient and modular code structure.
- Uses Miller - Rabbin's test for efficient checking number's primality 

## Usage
1. Clone the repository:
   ```bash
   git clone https://github.com/rrubaszek/GenerateRSA.git
   cd GenerateRSA
   ```
2. Install Boost Library (if not already installed):
   ```bash
   sudo apt-get install libboost-all-dev  # Ubuntu/Debian
   brew install boost                     # macOS
   ```
3. Compile the project:
   ```bash
   g++ GenerateLarge.cpp S
   etup.cpp -o rsa_keygen -lboost_mp -lboost_random
   ```
4. Run the executable:
   ```bash
   ./rsa_keygen
   ```

## Dependencies
- **C++17 or later**
- **Boost Multiprecision Library**
- **Boost Random Library**

## License
This project is licensed under the MIT License.


