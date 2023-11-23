#include <stdio.h>
#include <cs50.h>
int get_height(void); // defining variables
void print_brick(int n);

int main(void)
{
    int n = get_height();
    print_brick(n);
}
// Asking the user for a number between 1 and 8
int get_height(void)
{
    int n;
    do
    {
        n = get_int("Enter height(1-8): ");
    }
    while (n < 1 || n > 8);
    return n;
}
// printing the pyramid
void print_brick(int n)
{
    for (int b = 0; b < n; b++)
    {
        for (int c = 0; c < n + b + 3; c++) // when n + b + 3 is bigger than c, c will increase by 1
        {
            if (c == n || c == n + 1 || b + c < n - 1) 
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