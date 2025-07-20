#include <bits/stdc++.h>

using namespace std;

int quadrados[101];

void calcula_quadrados(){
    for (int i = 0; i < 101; i++){
        quadrados[i] = i*i;
    }
}

int main(){
    int n, m;
    cin >> n >> m;
    calcula_quadrados();
    int indice = floor(sqrt(n));
    int cont = 0;
    for (; indice >= 0; indice--){
        if (quadrados[n - quadrados[indice]] + indice == m) cont++;
    }
    cout << cont << endl;
}