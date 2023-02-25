#include "VarObfuscator.h"



void VarObfuscator::obfuscate(string fileName)
{
    
    string *arr =  parseFile(fileName);
    int count=0;
    string again="";
    
    
    
    //  count int variables
    for(int i=0; i<size; i++)
    {
        if(arr[i].find("int ")<INT_MAX && arr[i].find(";")<INT_MAX)
        {
            count++;
            //  found a fucntion call, not a variables
            if(arr[i].find("(")<INT_MAX)
            {
                //  substring to check functions input
                again= arr[i].substr( arr[i].find("(")+1, arr[i].length());
                count--;
            }
            
            //  found array of ints
            if(arr[i].find("[")<INT_MAX)
                count--;   
            
            //  check functions input
            if(again.find("int ")<INT_MAX)
            {
                count++;
                again= again.substr( again.find("int ")+3, arr[i].length());
                
                while(again.find("int ")<INT_MAX)
                {
                    count++;
                    again= again.substr( again.find("int ")+3, arr[i].length());
                }
            }
            
        }
    }
    
    //  create array
    string vars[count];

    //  go through array and fill it up with int variables from source code
    for(int v=0; v<count; v++)
    {
        //  go through the code
        for(int i=0; i<size; i++)
        {
            //  if previous element in variables array is empty, go back
            if((v>0) && (vars[v-1]==""))
                v--;
                
            //  if an int variable is found    
            if(arr[i].find("int")<INT_MAX && arr[i].find(";")<INT_MAX )
            {
                //  indexes to find name of the variable
                int start = arr[i].find("int")+3;
                int end = arr[i].find(';');
                
                
                string again="";
                
                if(arr[i].at(start)==' ')
                {
                    //  go through string to find name of variable
                    for(int j=start;j<=end;j++)
                    {
                        //  append legitimate chars
                        if(arr[i].at(j)!=' ' && arr[i].at(j)!='=' && arr[i].at(j)!='(' && arr[i].at(j)!=')' && arr[i].at(j)!=';'  && arr[i].at(j)!=',' && v<count)
                            vars[v]+=arr[i].at(j);
                        
                        //  if we got to end of line or '='
                        if(arr[i].at(j)==';' || arr[i].at(j)=='=' )
                        {
                            //  we found the name
                            j=end; v++; 
                        }
                        
                        //  if it's a function or an array
                        if(arr[i].at(j)=='('|| arr[i].at(j)=='['|| arr[i].at(j)==']')
                        {
                            //  clean name
                            vars[v]="";
                             
                            //  make a substring from the rest of the line
                            again = arr[i].substr( j, arr[i].length());
                            
                            //  check again if an int is found
                            if (again.find("int")<INT_MAX)
                            j+=again.find("int")+3;
                        }
                        
                        //  variables found in function declarations
                        if(arr[i].at(j)==')'|| arr[i].at(j)==',')
                        {
                            //  we found the name
                            v++;
                            //  make substring of rest of the line
                            again= arr[i].substr( j, arr[i].length());
                            
                            
                            //  check again if any ints are found
                            if (again.find("int")<INT_MAX)
                                j+=again.find("int")+3;
                        }
                        
                        
                        //  go through variables array
                        for(int chck=v-2; chck>=0 ; chck--)
                        {
                            //  if we got the same variable twice, delete one
                            if(vars[v-1]==vars[chck])
                                    vars[v-1]="";
                       }
                        
                       
                    }
                }
            }
        }   
    }



    //  pick the variable we wish to change
    string oldv="";
    int varlen=0;
    while(oldv=="")
    {
        int pick = rand()%count;
        oldv = vars[pick];    
        varlen = oldv.length();
    }

    //  generate new random variable name
    string newname="";
    while(newname.length()!=varlen)
        newname = generateRandomVar();

    //  go through array
    for(int i=0; i<size-1; i++)
    {
        //  search for our old variable
        while(arr[i].find(oldv)<INT_MAX)
        {
            int found = 0 ;
            //  if found - replace with new variable
            if(arr[i].at(arr[i].find(oldv)+varlen)=='=' || arr[i].at(arr[i].find(oldv)+varlen)=='+' ||arr[i].at(arr[i].find(oldv)+varlen)==' '|| arr[i].at(arr[i].find(oldv)+varlen)=='-' || arr[i].at(arr[i].find(oldv)+varlen)=='*' || arr[i].at(arr[i].find(oldv)+varlen)==';'|| arr[i].at(arr[i].find(oldv)+varlen)=='/'|| arr[i].at(arr[i].find(oldv)+varlen)=='%'|| arr[i].at(arr[i].find(oldv)+varlen)==')'|| arr[i].at(arr[i].find(oldv)+varlen)==','|| arr[i].at(arr[i].find(oldv)+varlen)==']')
                arr[i].replace(arr[i].find(oldv), varlen, newname);
            //  else - need to check further
            else found=arr[i].find(oldv);
            
            
            if(found!=0 || arr[i].find(oldv)==0)
            {
                //  get substring to check further
                string sub = arr[i].substr(arr[i].find(oldv), arr[i].length());
                
                //  keep searching
                while (sub.find(oldv)<INT_MAX)
                {
                    //  cut when needed
                    int cut = sub.find(oldv);
                    found+=cut;
                    
                    //  if we found our old variable
                    if(arr[i].at(found+varlen)=='=' || arr[i].at(found+varlen)=='+' || arr[i].at(found+varlen)=='-' || arr[i].at(found+varlen)=='*' || arr[i].at(found+varlen)==';'|| arr[i].at(found+varlen)=='/'|| arr[i].at(found+varlen)=='%'|| arr[i].at(found+varlen)==')' || arr[i].at(found+varlen)=='>' || arr[i].at(found+varlen)=='<'|| arr[i].at(found+varlen)==','|| arr[i].at(found+varlen)==' '|| arr[i].at(found+varlen)==']')
                    {
                        //  replace him with new variable
                        arr[i].replace(found, varlen, newname);
                        
                        //  make substring to keep searching
                        sub = sub.substr(cut+varlen, arr[i].length());
                        found=found+varlen;
                            
                    }
                    else 
                    {
                        //  make substring to keep searching
                        sub = sub.substr(cut+varlen, arr[i].length());
                        found=found+varlen;
                    }
                }
            i++;
            }        
        }
    }
    
    writeToFile(arr);
    
    
}