#include <stdio.h>

int main() {
    int a;
    int id;
    int in[100]; 
    int out[100];
    int remain[100];

    printf("��ǰ ����: ");
    scanf("%d", &a);

    printf("��ǰ�� �԰� ����: ");
    for (int i = 0; i < a; i++) {
        scanf("%d", &in[i]);
    }
    printf("��ǰ�� �Ǹ� ����: ");
    for (int i = 0; i < a; i++) {
        scanf("%d", &out[i]);
    }
    for (int i = 0; i < a; i++) {
        remain[i] = in[i] - out[i];
    }

    printf("��ǰ ID: ");
    scanf("%d", &id);

    printf("%d\n", remain[id - 1]);
    for (int i = 0; i < a; i++) {
        printf("%d ", remain[i]);
        printf(" ");
    }
    printf("\n");
    return 0;
}