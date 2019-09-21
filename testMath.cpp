#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

double factorial(int k) 
{
    double result = 1;
    for (int i = 1; i <= k; i++)
    {
        result *= i;
    }
    return result;
}

double possion(int k, int lamda) 
{
    return pow(lamda,k) * exp(-lamda) / factorial(k);
}

int  main()
{   
    int i;
    cin >> i;
    int lamda;
    cin >> lamda;
    cout << factorial(i) << endl;
    cout << possion(i,lamda) << endl;
}