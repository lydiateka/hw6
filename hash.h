#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        unsigned long long w[5] = {0}; 
        int index = k.size(); 
        int count = 4; 
        while (index >= 6) { 
            for (int i = index - 6; i < index; i++) { 
                int digit = letterDigitToNumber(k[i]); 
                w[count] = w[count] * 36 + digit; 
            }
            index -= 6; 
            count -=1; 
        }

        if (index > 0 && index < 6) { 
            for (int i = 0; i < 6; i++) { 
                int digit = 0; 
                if (i >= 6 - index) { 
                    digit = letterDigitToNumber(k[i - (6 - index)]); 
                }
                w[count] = w[count] * 36 + digit; 
            }
        }

        unsigned long long hash = 0; 
        for (int i = 0; i < 5; i++) { 
           hash += rValues[i]*w[i];   
        }

        return hash; 

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        letter = tolower(letter); 
        if (letter >= 'a' && letter <= 'z') { 
            return letter - 'a'; 
        }
        else { 
          return (letter -'0') + 26;   
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
