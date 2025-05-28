#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

void reset_memory(char *ptr, size_t size) {
    if (ptr && size > 0) {
        memset(ptr, 0, size);
    }
}

void process_order(int quantity, int special_count, char *special_request) {
    unsigned int price_per_item = 2000;
    unsigned int total_price;

    // total_price의 값이 Integer Overflow가 발생되는 경우
    if (quantity > 0 && price_per_item > UINT_MAX / quantity) {
        printf("Integer Overflow 발생!(총 가격에서 발생)\n");
        fflush(stdout);
    }

    total_price = quantity * price_per_item;

    printf("요청 수량: %d\n", quantity);
    printf("단가: %u원\n", price_per_item);
    printf("총 가격: %u원\n", total_price);

    // Integer Overflow로 인해 실제 처리된 수량 확인
    unsigned int corrupted_quantity = total_price / price_per_item;
    if (corrupted_quantity != (unsigned int)quantity) {
        printf("Integer Overflow로 인해 실제 계산된 수량: %u (원래 입력: %d)\n", corrupted_quantity, quantity);
        fflush(stdout);
    }

    // 특별상품 처리
    char *special_buffer = (char *)malloc(corrupted_quantity);
    if (!special_buffer) {
        printf("메모리 할당 실패!\n");
        return;
    }

    // 특별상품 ID 채우기 (의도적 Buffer Overflow 유도)
    if (special_count > 0) {
        memset(special_buffer, 'S', corrupted_quantity);
        if (special_count > corrupted_quantity) {
            printf("Buffer Overflow 발생 가능성! (특별상품 버퍼 크기보다 더 많이 저장 시도)\n");
            fflush(stdout);
        }
        printf("특별상품 ID 저장 완료 (요청된 수량: %u, 특별상품 저장된 개수: %d)\n",
               corrupted_quantity, special_count < corrupted_quantity ? special_count : corrupted_quantity);
        fflush(stdout);
    }

    // 기존 요청사항 처리
    if (strlen(special_request) > 20) {
        printf("추가 요구사항 입력 길이 초과 (Buffer Overflow 가능성)\n");
        fflush(stdout);
    }

    char request_buffer[20];
    strcpy(request_buffer, special_request);  // Buffer Overflow 가능 지점

    printf("추가 요구사항: %s\n", request_buffer);
    fflush(stdout);

    reset_memory(special_buffer, corrupted_quantity);
    free(special_buffer);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <quantity> <special_count> <special_request>\n", argv[0]);
        return 1;
    }

    errno = 0;
    unsigned long long raw_quantity = strtoull(argv[1], NULL, 10);
    int special_count = atoi(argv[2]);
    char *special_request = argv[3];

    // quantity 값 자체가 Integer Overflow가 발생되는 경우
    if (errno != 0 || raw_quantity > UINT_MAX) {
        printf("Integer Overflow 발생!(주문 수량에서 발생)\n");
        fflush(stdout);
    }

    int quantity = (int)raw_quantity;  // 어쨌든 이 값으로 처리하긴 해야 하니까 강제 변환
    process_order(quantity, special_count, special_request);
    return 0;
}
