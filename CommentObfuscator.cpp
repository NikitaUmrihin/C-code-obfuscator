#include "CommentObfuscator.h"



void CommentObfuscator::obfuscate(string fileName)
{
    string *arr =  parseFile(fileName);
    
    //  generate array of comments
    string cmnts[10];
    for(int i=0; i<10; i++)
        cmnts[i]=generateComment();
        
    //  find comments, and randomly choose which ones to replace
    for(int i=0; i<size; i++)
    {
        if(arr[i].find("// ")<INT_MAX)
        {
            if(rand() % 10000 >= 5000)
                arr[i]=cmnts[rand()%10];
            else arr[i]="";
        }
    } 
    
    
    writeToFile(arr);
}


string CommentObfuscator::generateComment()
{
    //  array of keywords to be used in obfusated comments
    string keywords[]={ "initialize","merge","pivot", "default","sum","is","variables","calculate","next", "cast",
    "of","input","new","delete","constructor", "set", "insert","average", "count", "nodes","if", "error", "while",
    "equals","in", "list", "binary", "sort", "array", "print", "search", "to", "string", "compare", "for", "if",
    "check", "from", "thread", "image", "copy", "change", "edit", "my", "method", "private", "get", "function",
    "struct", "set", "display", "replace", "hexadecimal", "update", "store", "length", "find", "last", "first" };

    //  length of the comment
    int len = rand()%15 +4 ;
    string newComm="// ";
    
    //  choose our keywords
    for(int i=1; i< len; i++)
    {
        int num = rand()% (sizeof(keywords)/sizeof(keywords[0]));
        newComm += keywords[num]+" ";
        
        if(i%6==0)
        newComm+=",";
        
    }
    
    return newComm;
}






