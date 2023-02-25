#include "Obfuscator.h"




string Obfuscator::generateRandomVar()
{
    //  length of variable
    int len = rand()%10 +1 ;
    
    //  pick first char of variable name
    int num = rand() % 123;
    while(!( (num>=65 && num<=90) || num==95 || (num>=97 && num<=122)  ))
        num = rand() % 123;
        
    string var;
    var.append(1, num);
    
    //  pick all other chars for variables name
    for(int i=1; i <len; i++)
    {
        num = rand() % 123;
        
        while(!( (num>=65 && num<=90) || num==95 || (num>=97 && num<=122) || (num>=48 && num<=57) ) )
            num = rand() % 123;
            
            
        var.append(1, num);
    }

    return var;
}




string* Obfuscator::parseFile(string fileName)
{
    ifstream read;
    read.open(fileName);

    //  count lines in our file
    string line;
    while(getline(read, line))
    {
        size++;
    }
    read.close();

    //  put lines from file to array
    string *arr = new string[size] ;
    int i=0;
    read.open(fileName);
    while(getline(read, line))
    {
        arr[i]=line;
        i++;
    }
    read.close();
   
    return arr;
   
    
}




void Obfuscator::writeToFile(string* codeArray)
{
    ofstream write;
    write.open(OUT);

    for(int i=0; i<size; i++)
    {
        write<< *(codeArray + i) << endl;
    }
    
    delete [] codeArray;
}

