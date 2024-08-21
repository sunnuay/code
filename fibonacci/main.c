#include <stdio.h>

int recursion(int n)
{
    if (n <= 1)
        return n;
    return recursion(n - 1) + recursion(n - 2);
}

int iteration(int n)
{
    if (n <= 1)
        return n;

    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main()
{
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    printf("Fibonacci sequence using recursion:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", recursion(i));
    }
    printf("\n");

    printf("Fibonacci sequence using iteration:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", iteration(i));
    }
    printf("\n");

    return 0;
}
