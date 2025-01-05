#include <stdio.h>

int sobrevivente(int n, int k){
    if(n == 1)  return 0;
    return (sobrevivente(n - 1, k) + k) % n;
}

int main(){
    int n, casos, k, t;
    scanf("%d", &casos);
    t = 1;
    while(t <= casos){
        scanf("%d %d", &n, &k);
        printf("Case %d: %d\n", t, sobrevivente(n, k) + 1);
        t++;
    }
    return 0;
}