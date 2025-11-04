#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_STOCK 5

// 전역 변수
int stock = MAX_STOCK;           // 상품 개수 5개 고정
int in[MAX] = { 0 };               // 입고 수량
int out[MAX] = { 0 };              // 판매 수량
int nam[MAX] = { 0 };              // 남은 재고
char stockName[MAX][50] = { 0 };   // 상품명 저장
int price[MAX] = { 0 };            // 상품 가격
int totalSales[MAX] = { 0 };       // 총 판매금액
int totalin = 0, totalout = 0;   // 총 입고, 총 판매

// 함수 선언
int commandMenu(void);
void stockIn(void);
void stockOut(void);
void pronaw(void);
void pronawone(void);
void inputProductNames(void);

// 메인 함수
int main(void) {
    inputProductNames();

    while (1) {
        int menu = commandMenu();

        if (menu == 1) stockIn();
        else if (menu == 2) stockOut();
        else if (menu == 3) pronawone();
        else if (menu == 4) pronaw();
        else if (menu == 5) {
            printf("프로그램 종료\n");
            break;
        }
        else {
            printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }
    return 0;
}

// 메뉴 출력
int commandMenu(void) {
    int menu;
    printf("\n[쇼핑몰 재고 관리 프로그램]\n");
    printf("1. 입고\n");
    printf("2. 판매\n");
    printf("3. 개별현황\n");
    printf("4. 전체현황\n");
    printf("5. 종료\n");
    printf("> 선택: ");
    scanf("%d", &menu);
    return menu;
}

// 상품명 입력
void inputProductNames(void) {
    for (int i = 0; i < stock; i++) {
        printf("ID%d 상품명: ", i);
        scanf("%s", stockName[i]);
    }
}

// 입고 처리
void stockIn(void) {
    int sub, id, qty;
    printf("입고수량 입력: 전체 1, 개별 2 선택 > ");
    scanf("%d", &sub);

    if (sub == 1) {
        printf("전체 상품 입고수량 입력: ");
        for (int i = 0; i < stock; i++) {
            scanf("%d", &qty);
            in[i] += qty;
            nam[i] += qty;
            totalin += qty;

            if (price[i] == 0) {
                printf("ID %d(%s)의 판매가격 입력: ", i, stockName[i]);
                scanf("%d", &price[i]);
            }
        }
    }
    else if (sub == 2) {
        printf("상품 ID 입력(0~%d): ", stock - 1);
        scanf("%d", &id);
        if (id < 0 || id >= stock) {
            printf("잘못된 ID입니다.\n");
            return;
        }
        printf("입고 수량 입력: ");
        scanf("%d", &qty);
        in[id] += qty;
        nam[id] += qty;
        totalin += qty;

        if (price[id] == 0) {
            printf("판매가격 입력: ");
            scanf("%d", &price[id]);
        }
    }
}

// 판매 처리
void stockOut(void) {
    int sub, id, qty;
    printf("판매수량 입력: 전체 1, 개별 2 선택 > ");
    scanf("%d", &sub);

    if (sub == 1) {
        printf("전체 상품 판매수량 입력: ");
        for (int i = 0; i < stock; i++) {
            scanf("%d", &qty);
            if (nam[i] < qty) {
                printf("ID %d(%s): 재고부족(%d)\n", i, stockName[i], nam[i]);
                continue;
            }
            out[i] += qty;
            nam[i] -= qty;
            totalout += qty;
            totalSales[i] += qty * price[i];
        }
    }
    else if (sub == 2) {
        printf("상품 ID 입력(0~%d): ", stock - 1);
        scanf("%d", &id);
        if (id < 0 || id >= stock) {
            printf("잘못된 ID입니다.\n");
            return;
        }
        printf("판매 수량 입력: ");
        scanf("%d", &qty);
        if (nam[id] < qty) {
            printf("재고부족! 현재 재고: %d\n", nam[id]);
            return;
        }
        out[id] += qty;
        nam[id] -= qty;
        totalout += qty;
        totalSales[id] += qty * price[id];
    }
}

// 전체현황
void pronaw(void) {
    printf("\n[전체 상품 현황]\n");
    printf("ID\t상품명\t가격\t입고\t판매\t재고\t총판매금액\n");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < stock; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
            i, stockName[i], price[i], in[i], out[i], nam[i], totalSales[i]);
    }

    if (totalin > 0) {
        double rate = (double)totalout / totalin * 100;
        printf("총판매량: %d (판매율 %.2f%%)\n", totalout, rate);
    }

    int max = out[0], min = out[0];
    int maxId = 0, minId = 0;

    for (int i = 1; i < stock; i++) {
        if (out[i] > max) { max = out[i]; maxId = i; }
        if (out[i] < min) { min = out[i]; minId = i; }
    }

    printf("가장 많이 판매된 상품: ID %d(%s) 판매량 %d\n", maxId, stockName[maxId], max);
    printf("가장 적게 판매된 상품: ID %d(%s) 판매량 %d\n", minId, stockName[minId], min);

    for (int i = 0; i < stock; i++) {
        if (nam[i] <= 2) {
            printf("⚠️  상품 ID %d(%s): 재고부족(%d)\n", i, stockName[i], nam[i]);
        }
    }
}

// 개별현황
void pronawone(void) {
    int id;
    printf("상품 ID 입력(0~%d): ", stock - 1);
    scanf("%d", &id);
    if (id < 0 || id >= stock) {
        printf("잘못된 ID입니다!\n");
        return;
    }

    printf("\n[개별 상품 현황]\n");
    printf("ID\t상품명\t가격\t입고\t판매\t재고\t총판매금액\n");
    printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
        id, stockName[id], price[id], in[id], out[id], nam[id], totalSales[id]);
}
