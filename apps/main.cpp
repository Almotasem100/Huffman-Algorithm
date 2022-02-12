#include <iostream>
#include "helpers.hpp"
#include <bits/stdc++.h> 
#include "Operations.hpp"
using namespace std;


int main(int argc, char **argv)
{
    if (argc == 2)
    {
        string dna = getFileFirstLine(argv[1]);
        Compress(dna);
        vector<string> stratic = BiCompress(dna);
        Decompress(stratic,dna);
    }        
    return 0;
}
