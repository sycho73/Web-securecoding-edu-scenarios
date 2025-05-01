#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void reset_memory(char *ptr, size_t size) {
    if (ptr && size > 0) {
        memset(ptr, 0, size);
    }
}

void process_order(int quantity, char *special_request) {
    unsigned int price_per_item = 2000;
    unsigned int total_price;

    // Integer Overflow 검출
    if (quantity > 0 && price_per_item > UINT_MAX / quantity) {
        printf("⚠️ Integer Overflow 발생!\n");
    }

    total_price = quantity * price_per_item;
    printf("Total price: %u\n", total_price);

    char *buffer = (char *)malloc(total_price);
    if (!buffer) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Buffer Overflow 검출
    if (strlen(special_request) >= 20) {
        printf("⚠️ Buffer Overflow 가능성 있음! (입력 길이 초과)\n");
    }

    char request_buffer[20];
    strcpy(request_buffer, special_request);  // 의도된 BOF

    printf("Order received: %s\n", request_buffer);

    // 메모리 초기화 및 정리
    reset_memory(buffer, total_price);
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

    // 종료 직전에 전체 메모리 안정화 처리 (추가 작업 가능)
    fflush(stdout);
    return 0;
}
