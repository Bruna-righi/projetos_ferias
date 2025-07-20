#include <bits/stdc++.h>

using namespace std;

int main(){
    int casos, a, b;
    cin >> casos;
    while(casos--){
        cin >> a >> b;
        int passos;
        if (a < b){
            passos = b-a;
        }
        else passos = (b-(a%b))%b;
        cout << passos << endl;
    }
    return 0;
}