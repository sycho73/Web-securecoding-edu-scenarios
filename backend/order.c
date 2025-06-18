#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#define MAX_SPECIAL_REQUEST_LEN 19  // +1 for null terminator

void reset_memory(char *ptr, size_t size) {
    if (ptr && size > 0) {
        memset(ptr, 0, size);
    }
}

void process_order(unsigned int quantity, unsigned int special_count, const char *special_request) {
    unsigned int price_per_item = 2000;
    unsigned int total_price;

    if (quantity > 0 && price_per_item > UINT_MAX / quantity) {
        printf("Integer Overflow 방지: 입력 수량이 너무 큽니다.\n");
        return;
    }

    total_price = quantity * price_per_item;

    printf("요청 수량: %u\n", quantity);
    printf("단가: %u원\n", price_per_item);
    printf("총 가격: %u원\n", total_price);

    unsigned int corrupted_quantity = total_price / price_per_item;
    if (corrupted_quantity != quantity) {
        printf("경고: 계산된 수량이 다릅니다. 처리 중단.\n");
        return;
    }

    if (corrupted_quantity == 0) {
        printf("경고: 처리할 수량이 0입니다.\n");
        return;
    }

    char *special_buffer = (char *)malloc(corrupted_quantity);
    if (!special_buffer) {
        printf("메모리 할당 실패!\n");
        return;
    }

    if (special_count > corrupted_quantity) {
        printf("Buffer Overflow 방지: 특별상품 수량이 버퍼 크기를 초과합니다. 잘라냅니다.\n");
        special_count = corrupted_quantity;
    }

    memset(special_buffer, 'S', corrupted_quantity);
    printf("특별상품 ID 저장 완료 (요청된 수량: %u, 저장된 개수: %u)\n",
           corrupted_quantity, special_count);

    if (strlen(special_request) > MAX_SPECIAL_REQUEST_LEN) {
        printf("추가 요구사항 입력 길이 초과. 최대 %d자까지 허용됩니다.\n", MAX_SPECIAL_REQUEST_LEN);
    }

    char request_buffer[MAX_SPECIAL_REQUEST_LEN + 1] = {0};  // +1 for null terminator
    strncpy(request_buffer, special_request, MAX_SPECIAL_REQUEST_LEN);  // 안전한 복사
    request_buffer[MAX_SPECIAL_REQUEST_LEN] = '\0';  // 널 종료 보장

    printf("추가 요구사항: %s\n", request_buffer);

    reset_memory(special_buffer, corrupted_quantity);
    free(special_buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <quantity> <special_count> <special_request>\n", argv[0]);
        return 1;
    }

    errno = 0;
    char *endptr;
    unsigned long long raw_quantity = strtoull(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || raw_quantity > UINT_MAX) {
        printf("잘못된 수량 입력입니다. 0 ~ %u 사이의 정수를 입력하세요.\n", UINT_MAX);
        return 1;
    }

    unsigned int quantity = (unsigned int)raw_quantity;

    int special_count = atoi(argv[2]);
    if (special_count < 0) {
        printf("특별상품 수량은 음수가 될 수 없습니다.\n");
        return 1;
    }

    const char *special_request = argv[3];

    process_order(quantity, (unsigned int)special_count, special_request);
    return 0;
}
