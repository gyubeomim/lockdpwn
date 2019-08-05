#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
    cout << "Enter number of elements." << endl;
    int n, i, x; double avg, var = 0, skewness = 0, S, k = 0;
    cin >> n;
    cout << "Enter elements." << endl;
    vector<int> v;

    int a[] = {2, 11, 8, 10, 1, 13, 9, 5, 9, 2, 10, 3, 8, 6, 17, 2, 10, 15, 14, 5};

    for (i = 0; i < n; i++)
    {
        x = a[i];
        v.push_back(x);
    }

    sort(v.begin(), v.end());
    for (i = 0; i < n; i++)
        cout << v[i] << " ";
   int sum = accumulate(v.begin(), v.end(), 0);
   avg = (double)sum/n;
   cout << "\nMean = " << avg << endl;
   vector<int>::iterator it;
    if (n % 2 != 0)
    {
       x = (n+1)/2;
       it = v.begin() + x;
       nth_element(v.begin(), it, v.end());
       cout << "Median = " << *(v.begin() + x -1) << endl;
    }
    else
    {
        float m;
        x = (n)/2 - 3;
        it = v.begin() + x;
        m = (*(v.begin()+ x - 1) + (*(v.begin() + x - 2 )))/2;
        cout << "Median = " << m << endl;
    }
    for (i = 0; i < n; i++)
    {
        var += (v[i] - avg)*(v[i] - avg);
    }
    var = (double)(var)/(n - 1);
    cout << "Variance = " << var << endl;
    S = (double)sqrt(var);
    for (i = 0; i < n; i++)
        skewness += (v[i] - avg)*(v[i] - avg)*(v[i] - avg);
    skewness = skewness/(n * S * S * S);
    cout << "Skewness = " << skewness << endl;
    for (i = 0; i < n; i++)
        k += (v[i] - avg)*(v[i] - avg)*(v[i] - avg)*(v[i] - avg);
    k = k/(n*S*S*S*S);
    k -= 3;
    cout << "Kurtosis = " << k << endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
