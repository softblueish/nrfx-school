#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"
#include "uarte-commands.h"

/*Det är helt tillåtet att lägga till egna hjälpfunktioner men de befintliga funktionerna ska implementeras enligt instruktionerna*/

/* Statiska hjälpfunktioner används av andra funktioner i trädet och ska inte ligga i interfacet (användaren behöver inte känna till dessa) */

/* Skapar en trädnod med det givna datat. Denna funktion bör vara den enda som använder malloc för att skapa en ny treeNode*/
static struct treeNode* create_tree_node(int data)
{
    struct treeNode* new_node = (struct treeNode*)malloc(sizeof(struct treeNode));
    assert(new_node != NULL); // Ran out of memory (lol)
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

static int* write_sorted_to_array_helper(const BSTree tree, int arr[], int* size)
{
    if(tree == NULL)
    {
        return arr;
    }
    arr = write_sorted_to_array_helper(tree->left, arr, size);
    if(arr == NULL) // If the array is not yet created, create it with the first element
    {
        arr = (int*)malloc(sizeof(int));
        assert(arr != NULL); // Ran out of memory (lol)
    } else {
        arr = realloc(arr, ((*size) + 1) * sizeof(int)); // Resize the array to fit the new element
        assert(arr != NULL); // Ran out of memory (lol)
    }
    arr[(*size)] = tree->data;
    (*size)++;
    arr = write_sorted_to_array_helper(tree->right, arr, size);
    return arr;
}

/* Returnerar en dynamiskt allokerad array som innehåller trädets data sorterat */
static int* write_sorted_to_array(const BSTree tree)
{
    /* Skapa en dynamisk array med rätt storlek
    
    Skriv datat från trädet sorterat till arrayen (minsta till största)
       - till detta kanske du behöver en hjälpfunktion */
    int* size = (int*)malloc(sizeof(int));
    assert(size != NULL); // Ran out of memory (lol)
    *size = 0;
    return write_sorted_to_array_helper(tree, NULL, size);

}

/* Bygger upp ett sorterat, balanserat träd från en sorterad array */
static void build_tree_sorted_from_array(BSTree* tree, const int arr[], int size)
{
    /* Bygg rekursivt från mitten.
    Mittenelementet i en delarray skapar rot i delträdet
    Vänster delarray bygger vänster delträd
    Höger delarray bygger höger delträd*/
    int selected_index = size / 2;
    int data = arr[selected_index];
    if((*tree) == NULL)
    {
        (*tree) = create_tree_node(data);
    }
    printf("Selected index: %d, data: %d\n", selected_index, data);
    (*tree)->data = data;
    if(size == 1)
    {
        return;
    }
    if(selected_index > 0) // Run again but with the left node becomes a new root
    {
        build_tree_sorted_from_array(&((*tree)->left), arr, size / 2);
    }
    if(selected_index < size - 1) // Run again but the right node becomes new root, I love trickery
    {
        build_tree_sorted_from_array(&((*tree)->right), arr + size / 2 + 1, size - size / 2 - 1);
    }
}

/* Implementation av trädet, funktionerna i interfacet */

/* Skapar ett tomt träd - denna funktion ar färdig */
BSTree create_empty_tree(void)
{
	return NULL;
}

/* Returnerar 1 ifall trädet är tomt, 0 annars */
int is_empty(const BSTree tree)
{
    return tree == NULL;
}

/* Sätter in 'data' sorterat i *tree */
void insert_sorted(BSTree* tree, int data)
{
	/*Tänk på att trädet kan vara tomt vid insättning
    I vanliga fall kan man lösa dubletter på olika sätt. Eftersom vi vill att era lösningar
    fungerar likadant inför examinationen så bestämmer jag att dubletter ej ska tillåtas i trädet.
    Post-condition kan verifieras med hjälp av find(...)*/
    if((*tree) == NULL)
    {
        (*tree) = create_tree_node(data);
        return;
    }
    if((*tree)->data == data)
    {
        return;
    }
    if(data < (*tree)->data)
    {
        insert_sorted(&((*tree)->left), data);
    }
    else if(data > (*tree)->data)
    {
        insert_sorted(&((*tree)->right), data);
    }
}

/* Utskriftsfunktioner
Det räcker att ni implementerar LR-ordningarna*/
void print_preorder(const BSTree tree)
{
    if(tree == NULL)
    {
        return;
    }
    print_int(tree->data);
    print_string(" ");
    print_preorder(tree->left);
    print_preorder(tree->right);
    return;
}

void print_inorder(const BSTree tree)
{
    if(tree == NULL)
    {
        return;
    }
    print_inorder(tree->left);
    print_int(tree->data);
    print_string(" ");
    print_inorder(tree->right);
    return;
}

void print_postorder(const BSTree tree)
{
    if(tree == NULL)
    {
        return;
    }
    print_postorder(tree->left);
    print_postorder(tree->right);
    print_int(tree->data);
    print_string(" ");
    return;
}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{
    // Tänk pa att trädet kan vara tomt
    if(tree == NULL)
    {
        return 0;
    }
    if(tree->data == data)
    {
        return 1;
    }
    if(data < tree->data)
    {
        return find(tree->left, data);
    }
    else
    {
        return find(tree->right, data);
    }
}

/* Tar bort 'data' från trädet om det finns */
void remove_element(BSTree* tree, int data)
{
	/* Inget data ska/kan tas bort från ett tomt träd
    Tre fall: Ett löv (inga barn), ett barn (vänster eller höger), två barn
    
    Glöm inte att frigöra noden när den länkats ur trädet'*/
    BSTree current_node = (*tree);
    BSTree parent_node = NULL;
    while(true) {
        if(current_node == NULL)
        {
            return;
        }
        if(current_node->data == data)
        {
            if(current_node->left == NULL && current_node->right == NULL)
            {
                if(parent_node == NULL)
                {
                    (*tree) = NULL;
                }
                if(parent_node->left == current_node)
                {
                    parent_node->left = NULL;
                }
                else if(parent_node->right == current_node)
                {
                    parent_node->right = NULL;
                }
                free(current_node);
                return;
            }
            if(current_node->left == NULL && current_node->right != NULL) {
                if(parent_node == NULL)
                {
                    (*tree) = current_node->right;
                }
                else if(parent_node->left == current_node)
                {
                    parent_node->left = current_node->right;
                }
                else
                {
                    parent_node->right = current_node->right;
                }
                free(current_node);
                return;
            }
            if(current_node->left != NULL && current_node->right == NULL) {
                if(parent_node == NULL)
                {
                    (*tree) = current_node->left;
                }
                else if(parent_node->left == current_node)
                {
                    parent_node->left = current_node->left;
                }
                else
                {
                    parent_node->right = current_node->left;
                }
                free(current_node);
                return;
            }
            if(current_node->left != NULL && current_node->right != NULL) {
                BSTree smallest_parent = current_node;
                BSTree smallest = current_node->right;
                while(smallest->left != NULL)
                {
                    smallest_parent = smallest;
                    smallest = smallest->left;
                }
                current_node->data = smallest->data;
                if(smallest_parent->left == smallest)
                {
                    smallest_parent->left = smallest->right;
                }
                else
                {
                    smallest_parent->right = smallest->right;
                }
                free(smallest);
                return;
            }
        }
        parent_node = current_node;
        if(data < current_node->data)
        {
            current_node = current_node->left;
        } else
        {
            current_node = current_node->right;
        }
    }
}

/* Returnerar hur många noder som totalt finns i trädet */
int number_of_nodes(const BSTree tree)
{
    if(tree == NULL)
    {
        return 0;
    }
    return 1 + number_of_nodes(tree->left) + number_of_nodes(tree->right);
}

/* Returnerar hur djupt trädet är */
int depth(const BSTree tree)
{
    
}

/* Returnerar minimidjupet för trädet
Se math.h för användbara funktioner*/
int min_depth(const BSTree tree)
{

}

/* Balansera trädet så att depth(tree) == minDepth(tree) */
void balance_tree(BSTree* tree)
{
/* Förslag på algoritm:
- överfor trädet till en dynamiskt allokerad array med writeSortedToArray()
- töm trädet med freeTree()
- bygg upp trädet rekursivt från arrayen med buildTreeSortedFromArray()
- frigör minne för den dynamiskt allokerade arrayen


Post-conditions:
- tree har lika många noder som tidigare
  - djupet för trädet är samma som minimumdjupet för trädet */
}


/* Töm trädet och frigör minnet för de olika noderna */
void free_tree(BSTree* tree)
{

}


