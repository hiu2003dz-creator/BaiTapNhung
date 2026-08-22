#include <stdio.h>
#include <string.h>
#include<stdlib.h>
void memory_leak(void)
{
    size_t allocation_count = 0;

    while (1)
    {
        void *block = malloc(1024);

        if (block == NULL)
        {
            printf("Out of Memory!\n");
            printf("So lan cap phat thanh cong: %zu\n",
                   allocation_count);
            return;
        }

        allocation_count++;

        if (allocation_count % 1000 == 0)
        {
            printf("Da cap phat: %zu KB\n",
                   allocation_count);
        }
    }
}
void stack_overflow(size_t depth)
{
    char stack_block[1024];

    printf("Do sau hien tai: %zu, dia chi Stack: %p\n", depth,(void *)stack_block);
    stack_overflow(depth + 1);
}
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Cach dung: %s <che_do>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "stack_overflow") == 0)
    {
        printf("Ban da chon Stack Overflow\n");
        stack_overflow(1);
    }
    else if (strcmp(argv[1], "memory_leak") == 0)
    {
    printf("Bat dau tao Memory Leak\n");
    memory_leak();
    }
    else if (strcmp(argv[1], "out_of_memory") == 0)
    {
        printf("Ban da chon Out of Memory\n");
    memory_leak();
    }
    else
    {
        printf("Che do khong hop le: %s\n", argv[1]);
        return 1;
    }

    return 0;
}