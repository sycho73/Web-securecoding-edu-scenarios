#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_order(int quantity, char *special_request) {
    unsigned int price_per_item = 2000;  // 단가 1000원
    unsigned int total_price;

    // 🛑 Integer Overflow 취약점
    total_price = quantity * price_per_item;

    printf("Total price: %u\n", total_price);

    // 🛑 Buffer Overflow 취약점 (크기 계산 오류)
    char *buffer = (char *)malloc(total_price);  // 문제 발생 가능
    if (!buffer) {
        printf("Memory allocation failed!\n");
        return;
    }

    // 🛑 Special Request 입력 처리 (취약점)
    char request_buffer[50];  // 제한된 버퍼 크기
    strcpy(request_buffer, special_request);  // BOF 가능

    printf("Order received: %s\n", request_buffer);
    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <quantity> <special_request>\n", argv[0]);
        return 1;
    }

    int quantity = atoi(argv[1]);
    char *special_request = argv[2];

    process_order(quantity, special_request);
    return 0;
}