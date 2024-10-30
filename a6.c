#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int x;
    int y;
} Dim_t;

typedef struct _Node_t
{
    struct _Node_t *left;
    struct _Node_t *right;
    int label;
    char cut;
    Dim_t dim;
} Node_t;

static Node_t *create_node() // pass uninitailzied note to it as checker
{
    Node_t *node = malloc(sizeof(*node));
    node->left = NULL;
    node->right = NULL;
    node->label = -1;
    node->cut = 0;
    node->dim.x = 0;
    node->dim.y = 0;
    return node;
}

static int linecount(FILE *fp)
{
    int ch;
    int line_count = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_count++;
        }
    }

    rewind(fp);
    return line_count;
}

static Node_t * buildtree_loop(FILE *fp)
{
    int node_count = linecount(fp);
    int stack_len = 0;

    Node_t **stack = malloc(node_count * sizeof(*stack));
    Node_t *head = NULL;

    for (int i = 0; i < node_count; i++)
    {
        char first = fgetc(fp);
        Node_t *node = create_node();

        if ((first == 'V') || (first == 'H'))
        {
            node->cut = first;
            fgetc(fp);

            node->right = stack[--stack_len];
            node->left = stack[--stack_len]; //poppping from stack and setting left and right
    
            stack[stack_len++] = node; //pushing node into stack
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
            fscanf(fp, "%d(%d,%d)\n", &node->label, &node->dim.x, &node->dim.y);

            stack[stack_len++] = node;
        }
    }
    head = stack[0];
    free(stack);
    return head;
}

static void free_t(Node_t* node)
{
    if(node==NULL)
    {
        return;
    }
    free_t(node->left);
    free_t(node->right);
    free(node);
}

int main(int argc, char **argv)
{
    FILE *fp = fopen(argv[1], "r");
    Node_t * head = buildtree_loop(fp);
    fclose(fp);
    free_t(head);
    return 0;
}

