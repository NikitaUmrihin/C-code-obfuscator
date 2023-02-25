#include "VarObfuscator.h"
#include "LineObfuscator.h"
#include "CommentObfuscator.h"


using namespace std;

int main()
{
    srand(time(0));
    Obfuscator* obfs[3];
    obfs[0] = new VarObfuscator();
    obfs[1] = new LineObfuscator();
    obfs[2] = new CommentObfuscator();
    
    
    obfs[0]->obfuscate("example_code.c");

    for(int i=1; i<3; i++)
        obfs[i]->obfuscate(obfs[i-1]->OUT);
    
    
    
    for(int i=0; i<3;i++)
        delete obfs[i];
    

    return 0;
}


