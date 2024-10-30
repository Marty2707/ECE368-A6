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
struct _Node_t * left;
struct _Node_t * right;
int label;
char cut;
Dim_t dim;
} Node_t;

static void init_node(Node_t* node) //pass uninitailzied note to it as checker
{
    node-> left = NULL;
    node-> right = NULL;
    node-> label = -1;
    node-> cut = 0;
    node -> dim.x = 0;
    node -> dim.y = 0;
}

static int linecount(FILE * fp)
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

static void buildtree(FILE * fp)
{
    int node_count = linecount(fp);

    for (int i =0; i<node_count; i++)
    {
        char first = fgetc(fp);
        Node_t node;
        init_node(&node);
        if ((first == 'V') || (first == 'H'))
        {
            node.cut = first;
            fgetc(fp);
            printf("%c\n", first);
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
            fscanf(fp, "%d(%d,%d)\n", &node.label, &node.dim.x, &node.dim.y); 
            printf("%d(%d,%d)\n", node.label, node.dim.x, node.dim.y);
        }
    }

}

int main(int argc, char** argv) 
{
    FILE *fp = fopen(argv[1], "r"); 
    buildtree(fp);
    fclose(fp);
    return 0;
}