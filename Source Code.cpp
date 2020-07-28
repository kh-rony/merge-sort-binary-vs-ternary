//Merge Sort (Binary Split vs Ternary Split)
//
//Sample Output:
//ARRAY_SIZE = 500000
//Time spent in merge sort for binary split: 203 milliseconds.
//Time spent in merge sort for ternary split: 172 milliseconds.

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

#define ARRAY_SIZE 500000

void assignSerialNumbersIntoArray(int myArray[])
{
    for( int i = 0; i < ARRAY_SIZE; i++ )
    {
        myArray[i] = i;
    }
}

void assignSerialNumbersReverselyIntoArray(int myArray[])
{
    for( int i = 0; i < ARRAY_SIZE; i++ )
    {
        myArray[i] = (ARRAY_SIZE - i - 1);
    }
}

void assignRandomNumbersIntoArray(int myArray[])
{
    srand(time(0));
    for( int i = 0; i < ARRAY_SIZE; i++ )
    {
        myArray[i] = rand();
    }
}

void printArrayContents(int myArray[])
{
    for( int i = 0; i < ARRAY_SIZE; i++ )
    {
        cout << myArray[i] << " ";
    }
}

void mergeSortWithBinarySplit(int myArray[], int firstIndex, int lastIndex)
{
    if( firstIndex == lastIndex )
    {
        return;
    }
    
    int middleIndex;
    int splittedSize1;
    int splittedSize2;
    int *splittedArray1;
    int *splittedArray2;
    int index1;
    int index2;
    
    middleIndex = firstIndex + (int) ((lastIndex - firstIndex) / 2);
    
    mergeSortWithBinarySplit(myArray, firstIndex, middleIndex);
    mergeSortWithBinarySplit(myArray, (middleIndex + 1), lastIndex);
    
    splittedSize1 = (middleIndex - firstIndex + 1);
    splittedSize2 = (lastIndex - middleIndex);
    
    splittedArray1 = new int[splittedSize1];
    splittedArray2 = new int[splittedSize2];
    
    for( index1 = 0; index1 < splittedSize1; index1++ )
    {
        *(splittedArray1 + index1) = myArray[firstIndex + index1];
    }
    for( index2 = 0; index2 < splittedSize2; index2++ )
    {
        *(splittedArray2 + index2) = myArray[middleIndex + 1 + index2];
    }
    
    index1 = 0;
    index2 = 0;
    
    for( int i = firstIndex; i <= lastIndex; i++ )
    {
        if( index1 < splittedSize1 && index2 < splittedSize2 &&
            *(splittedArray1 + index1) <= *(splittedArray2 + index2))
        {
            myArray[i] = *(splittedArray1 + index1);
            index1++;
        }
        else if( index1 < splittedSize1 && index2 < splittedSize2 &&
                 *(splittedArray2 + index2) <= *(splittedArray1 + index1))
        {
            myArray[i] = *(splittedArray2 + index2);
            index2++;
        }
        else if( index1 == splittedSize1 )
        {
            while( index2 < splittedSize2 )
            {
                myArray[i] = *(splittedArray2 + index2);
                i++;
                index2++;
            }
            break;
        }
        else if( index2 == splittedSize2 )
        {
            while( index1 < splittedSize1 )
            {
                myArray[i] = *(splittedArray1 + index1);
                i++;
                index1++;
            }
            break;
        }
    }
    
    delete[] splittedArray1;
    delete[] splittedArray2;
}


void mergeSortWithTernarySplit(int myArray[], int firstIndex, int lastIndex)
{
    if( firstIndex == lastIndex )
    {
        return;
    }
    
    int middleIndex1;
    int middleIndex2;
    int splittedSize1;
    int splittedSize2;
    int splittedSize3;
    int *splittedArray1;
    int *splittedArray2;
    int *splittedArray3;
    int index1;
    int index2;
    int index3;
    
    // if less than 3 elements are present in working portion of array,
    // then merge sort with ternary split can not be applied
    // so only in this case binary split will be applied
    if( (lastIndex - firstIndex) == 1 )
    {
        mergeSortWithBinarySplit(myArray, firstIndex, lastIndex);
        return;
    }
    
    // if at least 3 elements are present in working portion of array,
    // then merge sort with ternary split will be applied
    if( (lastIndex - firstIndex) > 1 )
    {
        middleIndex1 = firstIndex + (int) ((lastIndex - firstIndex) / 3);
        middleIndex2 = middleIndex1 + (int) ((lastIndex - middleIndex1) / 2);
        
        mergeSortWithTernarySplit(myArray, firstIndex, middleIndex1);
        mergeSortWithTernarySplit(myArray, (middleIndex1 + 1), middleIndex2);
        mergeSortWithTernarySplit(myArray, (middleIndex2 + 1), lastIndex);
        
        splittedSize1 = (middleIndex1 - firstIndex + 1);
        splittedSize2 = (middleIndex2 - (middleIndex1 + 1) + 1);
        splittedSize3 = (lastIndex - (middleIndex2 + 1) + 1);
        
        splittedArray1 = new int[splittedSize1];
        splittedArray2 = new int[splittedSize2];
        splittedArray3 = new int[splittedSize3];
        
        for( index1 = 0; index1 < splittedSize1; index1++ )
        {
            *(splittedArray1 + index1) = myArray[firstIndex + index1];
        }
        for( index2 = 0; index2 < splittedSize2; index2++ )
        {
            *(splittedArray2 + index2) = myArray[middleIndex1 + 1 + index2];
        }
        for( index3 = 0; index3 < splittedSize3; index3++ )
        {
            *(splittedArray3 + index3) = myArray[middleIndex2 + 1 + index3];
        }
        
        index1 = 0;
        index2 = 0;
        index3 = 0;
        
        for( int i = firstIndex; i <= lastIndex; i++ )
        {
            if( index1 < splittedSize1 && index2 < splittedSize2 && index3 < splittedSize3 &&
                *(splittedArray1 + index1) <= *(splittedArray2 + index2) &&
                *(splittedArray1 + index1) <= *(splittedArray3 + index3))
            {
                myArray[i] = *(splittedArray1 + index1);
                index1++;
            }
            else if( index1 < splittedSize1 && index2 < splittedSize2 && index3 < splittedSize3 &&
                     *(splittedArray2 + index2) <= *(splittedArray1 + index1) &&
                     *(splittedArray2 + index2) <= *(splittedArray3 + index3))
            {
                myArray[i] = *(splittedArray2 + index2);
                index2++;
            }
            else if( index1 < splittedSize1 && index2 < splittedSize2 && index3 < splittedSize3 &&
                     *(splittedArray3 + index3) <= *(splittedArray1 + index1) &&
                     *(splittedArray3 + index3) <= *(splittedArray2 + index2))
            {
                myArray[i] = *(splittedArray3 + index3);
                index3++;
            }
            
            else if( index1 == splittedSize1 )
            {
                if( index2 < splittedSize2 && index3 < splittedSize3 &&
                    *(splittedArray2 + index2) <= *(splittedArray3 + index3))
                {
                    myArray[i] = *(splittedArray2 + index2);
                    index2++;
                }
                else if( index2 < splittedSize2 && index3 < splittedSize3 &&
                         *(splittedArray3 + index3) <= *(splittedArray2 + index2))
                {
                    myArray[i] = *(splittedArray3 + index3);
                    index3++;
                }
                else if( index2 == splittedSize2 )
                {
                    while( index3 < splittedSize3 )
                    {
                        myArray[i] = *(splittedArray3 + index3);
                        i++;
                        index3++;
                    }
                    break;
                }
                else if( index3 == splittedSize3 )
                {
                    while( index2 < splittedSize2 )
                    {
                        myArray[i] = *(splittedArray2 + index2);
                        i++;
                        index2++;
                    }
                    break;
                }
            }
            
            else if( index2 == splittedSize2 )
            {
                if( index3 < splittedSize3 && index1 < splittedSize1 &&
                    *(splittedArray3 + index3) <= *(splittedArray1 + index1))
                {
                    myArray[i] = *(splittedArray3 + index3);
                    index3++;
                }
                else if( index3 < splittedSize3 && index1 < splittedSize1 &&
                         *(splittedArray1 + index1) <= *(splittedArray3 + index3))
                {
                    myArray[i] = *(splittedArray1 + index1);
                    index1++;
                }
                else if( index3 == splittedSize3 )
                {
                    while( index1 < splittedSize1 )
                    {
                        myArray[i] = *(splittedArray1 + index1);
                        i++;
                        index1++;
                    }
                    break;
                }
                else if( index1 == splittedSize1 )
                {
                    while( index3 < splittedSize3 )
                    {
                        myArray[i] = *(splittedArray3 + index3);
                        i++;
                        index3++;
                    }
                    break;
                }
            }
            
            else if( index3 == splittedSize3 )
            {
                if( index1 < splittedSize1 && index2 < splittedSize2 &&
                    *(splittedArray1 + index1) <= *(splittedArray2 + index2))
                {
                    myArray[i] = *(splittedArray1 + index1);
                    index1++;
                }
                else if( index1 < splittedSize1 && index2 < splittedSize2 &&
                         *(splittedArray2 + index2) <= *(splittedArray1 + index1))
                {
                    myArray[i] = *(splittedArray2 + index2);
                    index2++;
                }
                else if( index1 == splittedSize1 )
                {
                    while( index2 < splittedSize2 )
                    {
                        myArray[i] = *(splittedArray2 + index2);
                        i++;
                        index2++;
                    }
                    break;
                }
                else if( index2 == splittedSize2 )
                {
                    while( index1 < splittedSize1 )
                    {
                        myArray[i] = *(splittedArray1 + index1);
                        i++;
                        index1++;
                    }
                    break;
                }
            }
        }
        
        delete[] splittedArray1;
        delete[] splittedArray2;
        delete[] splittedArray3;
    }
}

int main()
{
    int myArray[ARRAY_SIZE];
    double startTime;
    double stopTime;
    double timeInterval;
    
    cout << "ARRAY_SIZE = " << ARRAY_SIZE << endl;
    
    assignSerialNumbersReverselyIntoArray(myArray);
    
    startTime = clock();
    mergeSortWithBinarySplit(myArray, 0, (ARRAY_SIZE - 1));
    stopTime = clock();
    timeInterval = (stopTime - startTime);
    cout << "Time spent in merge sort for binary split: " << timeInterval << " milliseconds." << endl;
    
    assignSerialNumbersReverselyIntoArray(myArray);
    
    startTime = clock();
    mergeSortWithTernarySplit(myArray, 0, (ARRAY_SIZE - 1));
    stopTime = clock();
    timeInterval = (stopTime - startTime);
    cout << "Time spent in merge sort for ternary split: " << timeInterval << " milliseconds." << endl;
    
    return 0;
}