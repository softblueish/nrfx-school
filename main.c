#include <stdio.h>
#include "BSTree.h"
#include "uarte-commands.h"

int main(){
    BSTree tree = create_empty_tree();
    insert_sorted(&tree, 1);
    insert_sorted(&tree, 2);
    insert_sorted(&tree, 3);
    insert_sorted(&tree, 4);
    insert_sorted(&tree, 5);
    insert_sorted(&tree, 6);
    insert_sorted(&tree, 7);
    print_string("Preorder: ");
    print_preorder(tree);
    print_string("\nDepth: ");
    print_int(depth(tree));
    print_string("\nMin Depth: ");
    print_int(min_depth(tree));
    print_string("\n");
    balance_tree(&tree);
    print_string("\nPreorder: ");
    print_preorder(tree);
    print_string("\nDepth: ");
    print_int(depth(tree));
    print_string("\nMin Depth: ");
    print_int(min_depth(tree));
    print_string("\n");
    return 0;
}