#include "monty.h"
#include <stdio.h>

typedef struct {
    char *opcode;
    void (*f)(stack_t **stack, unsigned int counter);
} instruction_ops_t;

extern bus_t bus;

/**
* execute - executes the opcode
* @stack: head linked list - stack
* @counter: line_counter
* @file: pointer to monty file
* @content: line content
* Return: 0 on success, 1 on error
*/
int execute(char *content, stack_t **stack, unsigned int counter, FILE *file)
{
    /* Instruction operations */
    instruction_ops_t instruction_ops[] = {
                {"push", push}, {"pall", pall}, {"pint", pint},
                {"pop", pop},
                {"swap", swap},
                {"add", _add},
                {"nop", nop},
                {"sub", _sub},
                {"div", _div},
                {"mul", _mul},
                {"mod", mod},
                {"pchar", pchar},
                {"pstr", pstr},
                {"rotl", rotl},
                {"rotr", rotr},
                {"queue", addqueue},
                {"stack", stack},
                {NULL, NULL}
                };

    unsigned int i = 0;
    char *op;

    op = strtol(content, " \n\t");
    if (op && op[0] == '#') {
        /* Comment line */
        return (0);
    }
    bus.arg = strtok(NULL, " \n\t");

    /* Search for the matching opcode */
    while (instruction_ops[i].opcode && op) {
        if (strcmp(op, instruction_ops[i].opcode) == 0) {
            instruction_ops[i].f(stack, counter);
            return (0);
        }
        i++;
    }

    /* If the opcode is not found, print an error message and exit */
    if (op && instruction_ops[i].opcode == NULL) {
        fprintf(stderr, "L%d: unknown instruction %s\n", counter, op);
        fclose(file);
        free(content);
        free_stack(*stack);
        exit(EXIT_FAILURE);
    }

    return (1);
}
