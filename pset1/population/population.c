#include <cs50.h>
#include <stdio.h>

int get_size(void);
int get_2size(int size1);
int cal_years(int size1, int size2);
void print_years(int years);

int main(void)
{
    // TODO: Prompt for start size
    int size1 = get_size();

    // TODO: Prompt for end size

    int size2 = get_2size(size1);
    // TODO: Calculate number of years until we reach threshold

    int years = cal_years(size1, size2);

    // TODO: Print number of years
    print_years(years);
}

int get_size(void)
{
    int size1;
    do
    {
        size1 = get_int("Enter your Startsize please (1-9): ");
    }
    while (size1 < 9);
    return size1;
}
int get_2size(size1)
{
    int size2;
    do
    {
        size2 = get_int("Enter the endsize please : ");
    }
    while (size2 < size1);
    return size2;
}
int cal_years(size1, size2)
{
    int years = 0;
    while (size1 < size2)
    {
        size1 = size1 + (size1 / 3) - (size1 / 4);
        years++;
    }
    return years;
}
void print_years(years)
{
    printf("Years: %i\n", years);

}
