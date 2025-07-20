#include <bits/stdc++.h>

using namespace std;


char tabuleiro[100][100];
int distancias[100][100];
bool visitados[100][100];


bool flood_fill_guria(pair<int, int> posicaoSally, int n, int m){
    deque<pair<pair<int,int>, int>> fila;
    fila.push_back(make_pair(posicaoSally, 0));
    bool cheguei;
    while (!fila.empty()){
        int x = fila.front().first.first;
        int y = fila.front().first.second;
        visitados[x][y] = true;
        int distancia = fila.front().second;
        if (tabuleiro[x][y] == 'X'){
            return true;
        }
        fila.pop_front();
        if (x < n - 1 && !visitados[x+1][y] && distancias[x+1][y] <=distancia+1){
            fila.push_back(make_pair(make_pair(x+1, y), distancia + 1));
        }
        if (x > 0 && !visitados[x-1][y] && distancias[x-1][y] <=distancia+1){
            fila.push_back(make_pair(make_pair(x-1, y), distancia + 1));
        }
        if (y < m - 1 && !visitados[x][y+1] && distancias[x][y+1] <=distancia+1){
            fila.push_back(make_pair(make_pair(x, y+1), distancia + 1));
        }
        if (y > 0 && !visitados[x][y-1] && distancias[x][y-1] <=distancia+1){
            fila.push_back(make_pair(make_pair(x, y-1), distancia + 1));
        }
    }
    return false;
}

//montar flood fill
void flood_fill(vector<pair<int,int>>& buracos, int n, int m){
    deque<pair<int,int>> fila;
    for (size_t i = 0; i < buracos.size(); i++){
        distancias[buracos[i].first][buracos[i].second] = 0;
        fila.push_back(buracos[i]);
    }
    while(!fila.empty()){
        int x = fila.front().first;
        int y = fila.front().second;
        fila.pop_front();
        if (x < n-1 && tabuleiro[x+1][y] != '#' && distancias[x+1][y] == -1){
            fila.push_back(make_pair(x+1, y));
            distancias[x+1][y] = distancias[x][y] + 1;
        }
        if (x > 0 && tabuleiro[x-1][y] != '#' && distancias[x-1][y] == -1){
            fila.push_back(make_pair(x-1, y));
            distancias[x-1][y] = distancias[x][y] + 1;
        }
        if (y < m-1 && tabuleiro[x][y+1] != '#' && distancias[x][y+1] == -1){
            fila.push_back(make_pair(x, y+1));
            distancias[x][y+1] = distancias[x][y] + 1;
        }
        if (y > 0 && tabuleiro[x][y-1] != '#' && distancias[x][y-1] == -1){
            fila.push_back(make_pair(x, y-1));
            distancias[x][y-1] = distancias[x][y] + 1;
        }
    }
}


int main(){
    int testes, n, m;
    cin >> testes;
    while(testes--){
        cin >> n >> m;
        pair<int, int> posicaoSally;
        vector<pair<int, int>> buracos;
        for (int i = 0; i < n; i++) {
            for ( int j = 0; j < m; j++){
                cin >> tabuleiro[i][j];
                if (tabuleiro[i][j] == 'S'){
                    posicaoSally = make_pair(i, j);
                }
                if (tabuleiro[i][j] == '*'){
                    buracos.push_back(make_pair(i, j));
                }
            }
        }
        memset(distancias, -1, sizeof(distancias));
        memset(visitados, false, sizeof(visitados));
        
        flood_fill(buracos, n, m);
        
        memset(visitados, false, sizeof(visitados));
        // for(int x=0;x<n;x++){
        //     for(int y=0;y<m;y++){
        //         cout << distancias[x][y] << '\t';
        //     }
        //     cout << endl;
        // }
        bool deu = flood_fill_guria(posicaoSally, n, m);
        if(deu){
            cout <<"yes"<<endl;
        }
        else cout << "no" << endl;
    }
    return 0;
}