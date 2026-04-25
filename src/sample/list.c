#include "list.h"

// Send data via UART
void uart_send(const Data *data) {
	printf("%d\n", *data);
}

//Returnera en tom lista - funktionen är färdig
List create_empty_list(void)
{
    return NULL;
}

//Här skapas nya noder. Denna funktion är den enda som ska använda malloc.
//Denna funktion ska i sin tur bara kallas av add_first och add_last.
//Notera att den är static och inte finns med i interfacet
static Node * create_list_node(const Data data)
{
	//glöm inte att kolla så att malloc inte returnerade NULL
	Node *new_node = (Node *)malloc(sizeof(Node));
	if(new_node == NULL)
	{
		exit(1); // RAM full
	}
	new_node->data = data;
	return new_node;
}

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0
int is_empty(const List list)
{
	return list == NULL;
}

//Lägg till en nod först i listan
void add_first(List *list, const Data data)
{
	if(is_empty(*list))
	{
		*list = create_list_node(data);
		return;
	}
	if(is_empty((*list)->previous))
	{
		(*list)->previous = create_list_node(data);
		(*list)->previous->next = *list;
		return;
	}
	add_first(&(*list)->previous, data);
	return;
}

//lägg till nod sist i listan
void add_last(List *list, const Data data)
{
	if(is_empty(*list))
	{
		*list = create_list_node(data);
		return;
	}
	if(is_empty((*list)->next))
	{
		(*list)->next = create_list_node(data);
		(*list)->next->previous = *list;
		return;
	}
	add_last(&(*list)->next, data);
	return;
}

//Ta bort första noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_first(List *list)
{
	if(is_empty((*list)->next))
	{
		free(*list);
		*list = NULL;
		return;
	}
	remove_first(&(*list)->next);
	return;
}

//ta bort sista noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_last(List *list)
{
	if(is_empty((*list)->previous))
	{
		free(*list);
		*list = NULL;
		return;
	}
	remove_last(&(*list)->previous);
	return;
}

//töm listan (ta bort alla noder ur listan)
//postcondition: Listan är tom, *list är NULL
void clear_list(List *list)
{
	if(!is_empty(*list))
	{
		remove_last(list);
		clear_list(list);
	}
	return;
}

void print_list_worker(const List list)
{
	if(is_empty(list))
	{	
		return;
	}
	uart_send(&list->data);
	print_list_worker(list->next);
	return;
}

//Skriv ut listan genom UART
void print_list(const List list)
{
	if(!is_empty(list->previous))
	{
		print_list(list->previous);
		return;
	}
	print_list_worker(list);
	return;
}

//returnera första datat i listan
//precondition: listan är inte tom (testa med assert)
Data get_first_element(const List list)
{
	if(list->previous != NULL) {
		get_first_element(list->previous);
		return 0;
	}
	return list->data;
}

//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List list)
{
	if(list->next != NULL) {
		get_last_element(list->next);
		return 0;
	}
	return list->data;
}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list)
{
	if(is_empty(list))
		return 0;
	return 1 + number_of_nodes(list->next);
}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data)
{
	if(is_empty(list))
		return 0;
	if(list->data == data)
		return 1;
	return search(list->next, data);
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *list, const Data data)
{
	if(is_empty(*list))
		return 0;
	if((*list)->data == data)
	{
		remove_first(list);
		return 1;
	}
	return remove_element(&(*list)->next, data);
}
