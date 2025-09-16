#include <stdio.h>

int main() {
    int a;
    int id;
    int in[100]; 
    int out[100];
    int remain[100];

    printf("상품 개수: ");
    scanf("%d", &a);

    printf("상품별 입고 수량: ");
    for (int i = 0; i < a; i++) {
        scanf("%d", &in[i]);
    }
    printf("상품별 판매 수량: ");
    for (int i = 0; i < a; i++) {
        scanf("%d", &out[i]);
    }
    for (int i = 0; i < a; i++) {
        remain[i] = in[i] - out[i];
    }

    printf("상품 ID: ");
    scanf("%d", &id);

    printf("%d\n", remain[id - 1]);
    for (int i = 0; i < a; i++) {
        printf("%d ", remain[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}