#include <stdio.h>
#include "BSTree.h"
#include "uarte-commands.h"

int main(){
    BSTree tree = create_empty_tree();
    insert_sorted(&tree, 5);
    insert_sorted(&tree, 3);
    insert_sorted(&tree, 7);
    insert_sorted(&tree, 2);
    insert_sorted(&tree, 4);
    insert_sorted(&tree, 6);
    insert_sorted(&tree, 8);
    print_preorder(tree);
    print_string("\n");
    remove_element(&tree, 8);
    print_preorder(tree);
    print_string("\n");
    return 0;
}