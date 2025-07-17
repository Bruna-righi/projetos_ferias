#include <iostream>
#include <vector>
#include <math.h>
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
    vector<pair<pair<int, int>, int>> probabilidades;
    for (auto intervalo : intervalos){
        int mediana = ceil((intervalo.second + intervalo.first)/2);
        bool continuar = true;
        if (intervalo.first == intervalo.second){
            cout << "1\n";
            continue;
        }
        int i = mediana;
        while (arr[i] == arr[mediana]){
            i--;
            if (i == intervalo.first && arr[i] == arr[mediana]){
                cout << "1\n";
                continuar = false;
                break;
            }
        }
        if(continuar){
            if(i >= 0 && arr[i] != arr[i+1] && i < mediana && i >= intervalo.first){
                cout << arr[i] + 1 << endl;
            } 
            else cout << arr[mediana] +1 << endl;
        }
    }
    return 0;
}
