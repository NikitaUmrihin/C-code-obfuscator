


//      exercise 2 
    
//      Question 1:     adding big numbers using arrays
    
//      Question 2:     bubble sort array of big numbers    
    



#include <stdio.h>
#include <string.h>



void addBigNumbers(char first[], char second[], char result[]);

void sortBigNumbers(char* bigNumbers[], int N);

int main()
{
    //  QUESTION 1 TESTER
    char a[100], b[100], c[200];
    printf("ENTER 1st NUMBER\n");
    scanf("%s", a);
    
    printf("ENTER 2nd NUMBER\n");
    scanf("%s", b);

    addBigNumbers(a,b,c);
    printf("The sum is : %s\n", c);

    
    
    //  QUESTION 2 TESTER
    char *bigNumbers[7] = {"3214", "12433536", "3","10734790300", "987654", "235", "2342222", };
    
    printf("Lets sort this array : \n");
    for(int i=0; i<7; i++)
        printf("%s,",bigNumbers[i]);
    printf("\n");
      
        
    sortBigNumbers(bigNumbers, 7);
    
    printf("sorted : \n");
    for(int i=0; i<7; i++)
        printf("%s, ",bigNumbers[i]);
    return 0;
}


//          question 1

void addBigNumbers(char first[], char second[], char result[])
{
    //  initialize indexes, error flag and "error" string
    int i=0, j=0, errorFlag=0;
    char stop[] = "error";
    
    //  count digits in first number 
    while(first[i]!='\0')
    {
        //  verify digits
        if ( (first[i]<'0') || (first[i]>'9') )
            errorFlag ++;
        i++;
    }
    
    //  count digits in second number
    while(second[j]!='\0')
    {
        //  verify digits
        if ( (second[j]<'0') || (second[j]>'9') )
            errorFlag ++;
    
        j++;        
    }
    
    //  if input is invalid 
    if (errorFlag!=0)
    {
        //  return "error"
        for(int k=0; k<5; k++)
            result[k] = stop[k];
        return;
    }
    
    int size;
    
    //  define end of result string
    if(i>=j)
    {
        result[i+1]='\0';
        size=i+1;
    }
    else
    {
        result[j+1]='\0';
        size=j+1;
    }
    
    
    //  correct indexes, initiate carry flag
    i--; j--;
    int carry = 0;
    
    //  go through both inputs (from least significant digit to most significant)
    while ((i>=0)||(j>=0))
    {
        //  initialize intergers
        int digitOne = (first[i]-'0');
        int digitTwo = (second[j]-'0');
        int res = 0;
            
            
        //  sum two corresponding digits , if needed
            
        if((i>=0))
            res = digitOne;
        
        if(j>=0)
            res = digitTwo;   
        
        if((i>=0) && (j>=0))
            res = digitOne + digitTwo;
        
        
        //  check carry flag
        
        if (carry==1)
        {
            res++;
            carry = 0 ;
        }
        
        if (res>=10)
        {
            res-=10;
            carry++;
        }
            
            
        //  put result digit in our array (as a char)
            
        if(i>=j)
            result[i]= res+'0';
        
        else
            result[j]= res+'0';
        
        
        
        //  check MSD carry
        if (carry==1 && i==0 && j==0)
        {
            for(int k=size; k>0; k--)
            {
                result[k] = result[k-1];
            }
            result[0] = 1+'0';
        }
        
        
        //  keep going
        j--;
        i--;
    }

}




//          question 2


void sortBigNumbers(char* bigNumbers[], int N)
{
    //  initialize indexes
    int i, j ;

    //  bubble sort
    for(i=0; i<N-1; i++)
    {
        for (j=i+1; j<N; j++)
        {   
            //  compare strings length
            if(strlen(bigNumbers[i]) > strlen(bigNumbers[j]))
            {   
                //  change pointers
                char* temp = bigNumbers[i];
                bigNumbers[i] = bigNumbers[j];
                bigNumbers[j] = temp;
            }
        }
    }


}