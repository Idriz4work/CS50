#include <cs50.h>
#include <stdio.h>
int get_size(void);
void print_grid(int n);

int main(void)
{
    int n = get_size();
    print_grid(n);
}

int get_size(void)
{
    // getting size of pyramide
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 5);
    return n;
}

void print_grid(int n)
{
    // printing bricks according to number
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}