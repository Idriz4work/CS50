#include <stdio.h>
#include <cs50.h>

string get_username(void);
void print_hello(string username);

int main(void)
{
    // Prompting User for name
    string username = get_username();
    // printing "Hello + username"
    print_hello(username);
}

string get_username(void)
{
    string username = get_string("What is your name? \n");
    return username;
}
void print_hello(string username)
{
    printf("Hello, %s\n", username);
}