#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void vulnerable_function() {
    unsigned int size;
    char *buffer;

    printf("Enter size of your input: ");
    scanf("%u", &size);

    // Integer Overflow 취약점
    size = size * 4;  // 일부러 부풀림 처리

    buffer = (char *)malloc(size);
    if (buffer == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter your data: ");
    // Buffer Overflow 취약점
    gets(buffer);

    printf("Your data: %s\n", buffer);
    free(buffer);
}

int main() {
    vulnerable_function();
    return 0;
}
