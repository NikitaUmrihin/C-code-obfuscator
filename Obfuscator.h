#ifndef OBFUSCATOR
#define OBFUSCATOR

#include <array>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <climits>
#include <time.h>
using namespace std;



class Obfuscator
{
    public:
    const string OUT = "newcode.c";
    int size;

    virtual void obfuscate(string fileName) = 0;
    string generateRandomVar();
    string* parseFile(string fileName);
    void writeToFile(string* codeArray);
};





#endif