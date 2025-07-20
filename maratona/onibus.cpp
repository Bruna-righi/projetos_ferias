#include <bits/stdc++.h>
#define BUS "+------------------------+"
#define LINHA_3_OCUPADA "|O.......................|"
#define LINHA_3_VAZIA "|#.......................|"

using namespace std;

int main(){
    int passageiros;
    cin >> passageiros;
    if (passageiros <= 2){
        cout << BUS << endl;
        if (passageiros == 0){
            cout << "|#.#.#.#.#.#.#.#.#.#.#.|D|)" << endl;
        }
        else cout << "|O.#.#.#.#.#.#.#.#.#.#.|D|)" << endl;
        if ( passageiros == 2){
            cout << "|O.#.#.#.#.#.#.#.#.#.#.|.|" << endl;
        }
        else cout << "|#.#.#.#.#.#.#.#.#.#.#.|.|" << endl;
        cout << LINHA_3_VAZIA << endl;
        cout <<  "|#.#.#.#.#.#.#.#.#.#.#.|.|)" << endl;
        cout << BUS << endl;
        return 0;
    }
    char matriz[3][11];
    int cont = 0;
    for (int i = 0; i<11; i++){
        for (int j = 0; j < 3; j++){
            if ( cont < passageiros - 1) matriz[j][i] = 'O';
            else matriz[j][i] = '#';
            cont++;
        }
    }
    cout << BUS << endl;
    for (int i = 0; i<2; i++){
        for (int j = 0; j < 11; j++){
            if ( j == 0) cout << "|";
            cout << matriz[i][j] << ".";
            if(j == 10 && i == 0) cout << "|D|)";
            else if (j == 10 && i == 1) cout << "|.|";
            if (j == 10) cout << endl;
        }
    }
    cout << LINHA_3_OCUPADA << endl;
    for (int i = 0; i<11; i++){
        for (int j = 2; j <3; j++){
            if ( i == 0) cout << "|";
            cout << matriz[j][i] << ".";
            if(i == 10 ) cout << "|.|)" << endl;
        }
    }
    cout << BUS << endl;
    return 0;
}