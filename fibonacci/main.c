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
    printf("n=");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        printf("%d ", recursion(i));

    printf("\n");

    for (int i = 0; i < n; i++)
        printf("%d ", iteration(i));

    return 0;
}
