#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf jump_buffer;

void vulnerable_function() {
    unsigned int size;
    char *buffer;

    printf("Enter number of elements: ");
    scanf("%u", &size);  // 사용자로부터 size 입력 받기

    // 정수 오버플로우 발생시키기 위해
    size = size - 1;  // 예를 들어 이 값을 4294967295로 설정해봐

    printf("Size after overflow correction: %u\n", size);  // 디버깅을 위한 출력

    // 의도적으로 작은 크기의 버퍼 할당
    size = 10;  // 버퍼 크기를 10으로 설정해버려

    // malloc에서 할당되는 버퍼 크기가 매우 작게 설정
    buffer = (char *)malloc(size * sizeof(char));

    if (!buffer) {
        printf("Memory allocation failed! Size: %u\n", size);
        longjmp(jump_buffer, 1);  // 메모리 할당 실패 시 예외 처리
    }

    printf("Memory allocated successfully. Enter your data: ");
    if (setjmp(jump_buffer) != 0) {
        printf("Buffer overflow detected! Program terminated.\n");
        free(buffer);  // 할당된 메모리 해제
        return;
    }

    // buffer 크기를 초과하는 데이터를 입력하도록 강제
    gets(buffer);  // 위험한 gets() 사용
    printf("Data you entered: %s\n", buffer);
    free(buffer);  // 할당된 메모리 해제
}

int main() {
    vulnerable_function();
    return 0;
}
