#include "LineObfuscator.h"



void LineObfuscator::obfuscate(string fileName)
{
    string *arr =  parseFile(fileName);
    
        int mainstart=INT_MAX;
        int sogercount=0;
        int mainend;
        int check=0;
        
        //  go through code array
        for(int i=0; i<size; i++)
        {
            //  found main
            if(arr[i].find("main")<INT_MAX)
                mainstart=i;
                
            //  count curly braces to find where main ends
            if( (i>=mainstart) && (arr[i].find("{")<INT_MAX))
            {
                check++;
                sogercount++;
            }
        
            if( (i>=mainstart) && (arr[i].find("}")<INT_MAX))
            sogercount--;
            
            //  all curly braces gone, main ends here
            if(sogercount==0 && mainstart!=INT_MAX && check!=0)
            {
                mainend=i;
                i=size;
            }
        
    }
    
    //  generate random variable name
    string randv=generateRandomVar();
    int edits = 0;

    //  go through main code    
    for(int i=mainstart+1; i<mainend; i++)
    {   
        //  add our variable to the code
        if((i%2==0) && edits==0)
        {
            arr[i]+="\nint "+randv+";";
            i++;
            edits++;
            size++;
        }
        
        //  find random position for next line we want to add
        int pos = rand()%(mainend - mainstart) + mainstart ;
        
        //  add another line to code
        if(edits==1)
        {
            arr[pos]+="\n"+randv+" = "+to_string(rand()%2000)+" + "+to_string(rand()%1000)+" ;";
            edits++;
            size++;
        }
    }
    
    
    writeToFile(arr);
}