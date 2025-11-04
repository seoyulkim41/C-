#define _CRT_SECURE_NO_WARNINGS
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

    printf("재고수량: ");
    for (int i = 0; i < a; i++) {
        printf("%d ", remain[i]);
    }
    printf("\n");

    int total_out = 0, total_in = 0;
    for (int i = 0; i < a; i++) {
        total_out += out[i];
        total_in += in[i];
    }

    double rate = ((double)total_out / total_in) * 100.0;
    printf("총 판매량: %d (판매율 %.2f%%)\n", total_out, rate);

    int max_idx = 0, min_idx = 0;
    for (int i = 1; i < a; i++) {
        if (out[i] > out[max_idx]) max_idx = i;
        if (out[i] < out[min_idx]) min_idx = i;
    }
    printf("가장 많이 판매된 상품: ID %d, 판매량 %d\n", max_idx + 1, out[max_idx]);
    printf("가장 적게 판매된 상품: ID %d, 판매량 %d\n", min_idx + 1, out[min_idx]);

    for (int i = 0; i < a; i++) {
        if (remain[i] <= 2) {
            printf("상품 ID %d : 재고부족(%d)\n", i + 1, remain[i]);
        }
    }

    return 0;
}
