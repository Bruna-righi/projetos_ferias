#include <bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b) { 
   while (b > 0) { 
      a = a % b; 
      a ^= b;    b ^= a;    a ^= b;  
   }  
   return a; 
} 

int main(){

    int k, x;
    vector<long long> arr;
    cin >> k >> x;
    for (int i = 0; i < k; i++){
        int temp;
        cin >> temp;
        arr.push_back(temp);
    }
    long long mdc = arr[0];
    for (int i = 1; i < arr.size(); i++){
        mdc = gcd(mdc, arr[i]);
    }
    if (x % mdc == 0){
        cout << "YES" << endl;
    }
    else cout << "NO" << endl;
    return 0;
}   