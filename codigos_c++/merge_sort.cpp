#include <iostream>

using namespace std;

void merge_sort(int arr[], int inicio, int meio, int fim){
    int n = fim - inicio;
    int tam_a = meio - inicio + 1;
    int tam_b = fim - meio;
    int a[tam_a], b[tam_b];
    for (int i = 0; i < tam_a; i++){
        a[i] = arr[inicio + i];
    }
    for (int i = 0; i < tam_b; i++){
        b[i] = arr[meio + 1 + i];
    }
    int i = 0, j = 0;
    for (int k = inicio; k <= fim; k++){
        if (i < tam_a && (a[i] <= b[j] || j >= tam_b)){
            arr[k] = a[i];
            i++;
        }
        else {
            arr[k] = b[j];
            j++;
        }
    }
    return;
}

void recursao(int arr[], int inicio, int fim){
    if (inicio >= fim){
        return;
    }
    int meio = inicio + (fim - inicio)/2;
    recursao(arr, inicio, meio);
    recursao(arr, meio+1, fim);
    merge_sort(arr, inicio, meio, fim);
}

int main(){

    int arr[] = {6, 7, 34, 2, 2, 3, 6, 1, 65, 23, 34, 7, 9, 12};
    int n = sizeof(arr)/sizeof(arr[0]);
    recursao(arr, 0, n - 1);
    for ( int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    return 0;
}