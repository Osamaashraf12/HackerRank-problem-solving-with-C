#include <stdio.h>
int main()
{
	int n;
char* numbers[9] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

scanf("%d", &n);
if (n <= 9) {
	printf("%s", numbers[n - 1]);
}
else {
	printf("Greater than 9");
}
return 0;
}