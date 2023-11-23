#include <stdio.h>
#include <cs50.h>
int get_height(void);
void print_brick(int n);

int main(void)
{
    int n = get_height(); // prompt for number
    print_brick(n); // printing the bricks "#"
}

int get_height(void) // prompt user for number
{
    int n;
    do
    {
        n = get_int("Enter height(1-8): ");
    }
    while (n < 1 || n > 8); // if a number is not between 1 - 8 prompt again
    return n;
}
void print_brick(int n) //printing the bricks
{
    for (int b = 0; b < n; b++) // This is the row horizontal
    {
        for (int c = 0; c < n; c++) // This is the row vertical
        {
            if (b + c < n - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}