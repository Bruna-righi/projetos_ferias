#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

// quero buscar o menor nó que esse nó consegue chegar
int dfs(int node, vector<vector<int>>& graph, vector<int>& menor) {
    if (menor[node] == -3){
        return node;
    }
    if (menor[node] >= 0){
        return menor[node];
    }
    menor[node]--;
    int menorQueEuChego = node;
    for (int i = 0; i < graph[node].size(); i++){
        int child = graph[node][i];
        int menorQueMeuFilhoChega = dfs(child, graph, menor);
        if(menorQueMeuFilhoChega < menorQueEuChego){
            menorQueEuChego = menorQueMeuFilhoChega;
        }
        menor[node] = menorQueEuChego;
    }
    return menorQueEuChego;
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> graph(n);   // graph[n] = int
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        graph[i].push_back(temp-1);
    }
    vector<pair<int, int>> intervalos(q);
    for (int i = 0; i < q; ++i) {
        cin >> intervalos[i].first >> intervalos[i].second;
        intervalos[i].first--;
        intervalos[i].second--;
    }
    vector<int> menor(n,-1);
    int arr[n];
    for (int i = 0; i<n; i++) {
        arr[i] = dfs(i, graph, menor);
    }
    vector<int> subarr;
    for (auto intervalo : intervalos){
        for (int i = intervalo.first; i <= intervalo.second; i++) {
            subarr.push_back(arr[i]);
        }
        sort(subarr.begin(), subarr.end());
        int mediana = ceil(subarr.size()/2);
        bool continuar = true;
        if (intervalo.first == intervalo.second){
            cout << "1\n";
            continue;
        }
        int i = mediana;
        // int j = mediana, tam = 0, maximum = 0, indice_longest;
        // while (j < intervalo.second - 1){
        //     if (arr[j] == arr[j+1]){
        //         tam++;
        //     }
        //     else {
        //         maximum = max(maximum, tam);
        //         indice_longest = j - tam;
        //         tam = 0;
        //     }
        //     j++;
        // }
        while (i >= 0 && subarr[i] == subarr[mediana]){
            i--;
        }
        if (i < 0){
            cout << "1\n";
            continuar = false;
        }
        if(continuar){
            // if (tam > mediana - i){
            //     cout << arr[indice_longest - 1] + 1 << endl;
            // }
            if (i >= 0 && subarr[i] != subarr[i+1]){
                cout << subarr[i] + 1 << endl;
            } 
            else cout << subarr[mediana] +1 << endl;
        }
    }
    return 0;
}
