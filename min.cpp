#include <bits/stdc++h>
#include <chrono>
#include <omp.h>

using namespace std;

int minSequential(int arr[], int n)
{
    int mini = INT_MAX;
    for (int i = 0; i < n; i++){
        if (arr[i] < mini){
            mini = arr[i];
        }
    }
    return mini;
}

int maxSequential(int arr[], int n)
{
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++){
        if (arr[i] > maxi)
        {
            maxi = arr[i];
        }
    }
    return maxi;
}

int sumSequential(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int averageSequential(int arr[], int n)
{
    int sum = sumSequential(arr, n);
    return sum / n;
}

int minParallel(int arr[], int n)
{
    int mini = INT_MAX;
    #pragma omp parallel for reduction(min : mini)
    for (int i = 0; i < n; i++){
        if (arr[i] < mini)
        {
            mini = arr[i];
        }
    }
    return mini;
}

int maxParallel(int arr[], int n)
{
    int maxi = INT_MIN;
    #pragma omp parallel for reduction(max : maxi)
    for (int i = 0; i < n; i++){
        if (arr[i] > maxi){
            maxi = arr[i];
        }
    }
    return maxi;
}

int sumParallel(int arr[], int n)
{
    int sum = 0;
    #pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

int averageParallel(int arr[], int n)
{
    int sum = sumParallel(arr, n);
    return sum / n;
}

int main()
{
    int n;
    cout << "\nEnter total number of elements: ";
    cin >> n;

    
    vector<int>arr(n);
    for (int i = 0; i < n; i++){
        arr[i] = (rand() % n);
    }

    cout << "Generated array: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;

    // Sequential version
    auto startSeq = chrono::steady_clock::now();
    cout << "Sequential Min = " << minSequential(arr, n) << endl;
    auto endSeq = chrono::steady_clock::now();
    chrono::duration<double, micro> sqMin = endSeq - startSeq;
    cout << "Sequential Min Time: " << sqMin.count() << " microsec" << endl;

    auto startParallel = chrono::steady_clock::now();
    cout << "Parallel Min: " << minParallel(arr, n) << endl;
    auto endParallel = chrono::steady_clock::now();
    chrono::duration<double, micro> parrMin = endParallel - startParallel;
    cout << "Paralle Min Time: " << parrMin.count() << " microsec" << endl;
    
    cout<< "Speedup (min): "<< sqMin.count()/parrMin.count() <<endl;
    cout<<endl;
    
    
    startSeq = chrono::steady_clock::now();
    cout << "Sequential Max = " << maxSequential(arr, n) << endl;
    endSeq = chrono::steady_clock::now();
    chrono::duration<double, micro> sqMax = endSeq - startSeq;
    cout << "Sequential Max Time: " << sqMax.count() << " microsec" << endl;
    
    startParallel = chrono::steady_clock::now();
    cout << "Parallel Max = " << maxParallel(arr, n) << endl;
    endParallel = chrono::steady_clock::now();
    chrono::duration<double, micro> parrMax = endParallel - startParallel;
    cout << "Parallel Max Time: " << parrMax.count() << " microsecs" << endl;
    
    cout<< "Speedup (max): "<< sqMax.count()/parrMax.count() <<endl;
    cout<<endl;
    

    startSeq = chrono::steady_clock::now();
    cout << "Sequential Sum = " << sumSequential(arr, n) << endl;
    endSeq = chrono::steady_clock::now();
    chrono::duration<double, micro> sqSum = endSeq - startSeq;
    cout << "Sequential Sum Time: " << sqSum.count() << " microsecs" << endl;
    
    startParallel = chrono::steady_clock::now();
    cout << "Parallel Sum = " << sumParallel(arr, n) << endl;
    endParallel = chrono::steady_clock::now();
    chrono::duration<double, micro> parrSum = endParallel - startParallel;
    cout << "Parallel Sum Time: " << parrSum.count() << " microsecs" << endl;
    
    cout<< "Speedup (Sum): "<< sqSum.count()/parrSum.count() <<endl;
    
    cout<<endl;

    startSeq = chrono::steady_clock::now();
    cout << "Sequential Average = " << averageSequential(arr, n) << endl;
    endSeq = chrono::steady_clock::now();
    chrono::duration<double, micro> sqAvg = endSeq - startSeq;
    cout << "Sequential Average Time: " << sqAvg.count() << " microsec" << endl;

    startParallel = chrono::steady_clock::now();
    cout << "Parallel Average = " << averageParallel(arr, n) << endl;
    endParallel = chrono::steady_clock::now();
    chrono::duration<double, micro> parrAvg = endParallel - startParallel;
    cout << "Parallel Average Time: " << parrAvg.count() << " microsecs" << endl;
    
    cout<< "Speedup (Avg): "<< sqAvg.count()/parrAvg.count() <<endl;

    cout<<endl;
    delete[] arr; // Don't forget to release the allocated memory
    return 0;
}
