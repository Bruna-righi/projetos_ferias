#include <bits/stdc++.h>

using namespace std;

string tumba;

int main(){
    //primeiro, leitura
    string senha;
    cin >> tumba;
    int tam = 1;

    senha.push_back(tumba[0]);
    for(size_t i = 0; i < tumba.length()*2; i++){

        if(senha[i%tam] != tumba[i%tumba.length()]){

            for(int j = senha.size(); j <= i; j++){
                if(i-tam >= tumba.length()/2){
                    cout << "-1\n";
                    return 0;
                }
                senha.push_back(tumba[j]);
                tam++;
                if(senha[i%tam] == tumba[i]) break;
            }
        }
    }

    if(senha.size() > tumba.length()/2){
        cout << "-1\n";
        return 0;
    }

    int maior_div = 0;
    for(size_t i = 1; i <= tumba.length()/2; i++){
        if(i%senha.size() == 0 && tumba.length()%i == 0){
            maior_div = (int) i;
        }
    }

    if(maior_div == 0){
        cout << "-1\n";
        return 0;
    }

    for(int n = 0; n < maior_div; n++){
        cout << senha[n%senha.size()];
    }
    cout << endl;

    return 0;
}