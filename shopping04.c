#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 함수 선언
void input_stock(int a, int in[], int remain[]);
void sell_product(int a, int out[], int remain[]);
void show_status(int a, int in[], int out[], int remain[], char name[][50]);
void input_product_name(int a, char name[][50]);  

int main() {
    int a;
    int id;
    int in[100];
    int out[100];
    int remain[100];
    char name[100][50]; //상품명 2차원 배열
    int menu;

    printf("쇼핑몰 재고 관리 프로그램\n");
    printf("상품 개수를 입력하세요: ");
    scanf("%d", &a);
    getchar(); 

    for (int i = 0; i < a; i++) {
        in[i] = 0;
        out[i] = 0;
        remain[i] = 0;
        strcpy(name[i], "미등록"); 
    }

    while (1) {
        printf("\n--- 메뉴 선택 ---\n");
        printf("1. 입고\n");
        printf("2. 판매\n");
        printf("3. 현황 출력\n");
        printf("4. 상품명 입력\n");
        printf("5. 종료\n");
        printf("번호를 선택하세요: ");
        scanf("%d", &menu);

        if (menu == 1) {
            input_stock(a, in, remain);
        }
        else if (menu == 2) {
            sell_product(a, out, remain);
        }
        else if (menu == 3) {
            show_status(a, in, out, remain, name);
        }
        else if (menu == 4) { 
            input_product_name(a, name);
        }
        else if (menu == 5) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}

//상품명 입력 기능
void input_product_name(int a, char name[][50]) {
    printf("\n상품명 입력을 시작합니다.\n");
    for (int i = 0; i < a; i++) {
        printf("상품 ID %d의 이름을 입력하세요: ", i + 1);
        scanf("%s", name[i]);
    }
    printf("상품명 입력이 완료되었습니다.\n");
}

//입고 함수
void input_stock(int a, int in[], int remain[]) {
    printf("상품별 입고 수량 입력: ");
    for (int i = 0; i < a; i++) {
        int temp;
        scanf("%d", &temp);
        in[i] += temp;
        remain[i] += temp;
    }
    printf("입고가 완료되었습니다.\n");
}

//판매 함수
void sell_product(int a, int out[], int remain[]) {
    printf("상품별 판매 수량 입력: ");
    for (int i = 0; i < a; i++) {
        int temp;
        scanf("%d", &temp);
        out[i] += temp;
        remain[i] -= temp;
        if (remain[i] < 0) remain[i] = 0;
    }
    printf("판매가 완료되었습니다.\n");
}

// 상품명,현황 출력
void show_status(int a, int in[], int out[], int remain[], char name[][50]) {
    printf("\n--- 상품 현황 ---\n");
    printf("재고수량: ");
    for (int i = 0; i < a; i++) {
        printf("%d ", remain[i]);
    }
    printf("\n");

    int total_in = 0, total_out = 0;
    for (int i = 0; i < a; i++) {
        total_in += in[i];
        total_out += out[i];
    }

    double rate = 0.0;
    if (total_in > 0)
        rate = ((double)total_out / total_in) * 100.0;

    printf("총 판매량: %d (판매율 %.2f%%)\n", total_out, rate);

    // 가장 많이,적게 판매된 상품 찾기
    int max_idx = 0, min_idx = 0;
    for (int i = 1; i < a; i++) {
        if (out[i] > out[max_idx]) max_idx = i;
        if (out[i] < out[min_idx]) min_idx = i;
    }

    printf("가장 많이 판매된 상품: ID %d (%s), 판매량 %d\n", max_idx + 1, name[max_idx], out[max_idx]);
    printf("가장 적게 판매된 상품: ID %d (%s), 판매량 %d\n", min_idx + 1, name[min_idx], out[min_idx]);

    // 재고 부족 경고
    for (int i = 0; i < a; i++) {
        if (remain[i] <= 2) {
            printf("상품 ID %d (%s): 재고부족(%d)\n", i + 1, name[i], remain[i]);
        }
    }
}
