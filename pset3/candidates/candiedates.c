#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate get_candidate(string prompt);

int main(void)
{
    candidate president = get_candidate("Enter Candidate: ");
    printf("%d\n", president.votes);
    printf("%s\n", president.name);
}

candidate get_candidate(string prompt)
{
    printf("%s\n", prompt);
    candidate c;
    c.name = get_string("Name: ");
    c.votes = get_int("Number: ");
    return c;
}