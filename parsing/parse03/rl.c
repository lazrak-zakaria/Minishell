
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "vector.h"
#include <string.h>

int main() {
    char* input;

    // Read input from the user using Readline
    input = readline("Enter a line of text: ");

    // Modify the input and replace the input line
    int input_len = strlen(input);
    char* modified_input = (char*) malloc(input_len + 7);
    strcpy(modified_input, "Hello ");
    strcat(modified_input, input);
    strcat(modified_input, "!");
    rl_replace_line(modified_input, 1);

    // Move the cursor to the end of the line and redisplay
    rl_point = rl_end;
    rl_redisplay();
    
    // Free the input buffers
    free(input);
    free(modified_input);

    return 0;
}
