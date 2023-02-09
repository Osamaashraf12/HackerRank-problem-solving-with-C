#include <stdio.h>
#include <stdlib.h>

void update(int *a,int *b) {
    int num1, num2;

    // assign the values to the variables
    num1 = *a + *b;
    num2 = abs(*a - *b);
    *a = num1;
    *b = num2;
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;

    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
