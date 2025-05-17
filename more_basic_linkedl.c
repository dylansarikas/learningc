#include <stdio.h>
#include <stdlib.h>

struct lnode {
    int value;
    struct lnode *next;
};

struct list {
  struct lnode *head;
  struct lnode *tail;
};

int main()
{
    void list_add();
    void list_dump();
    struct lnode * list_find();

    struct list mylist;
    struct lnode * mynode;

    mylist.head = NULL;
    mylist.tail = NULL;

    list_add(&mylist, 10);
    list_add(&mylist, 20);
    list_add(&mylist, 30);
    list_dump(&mylist);

    list_remove(&mylist, 42);

    list_remove(&mylist, 10);
    list_dump(&mylist);

    list_remove(&mylist, 30);
    list_dump(&mylist);

    list_add(&mylist, 40);
    list_dump(&mylist);

}

void list_dump(lst)
    struct list *lst;
{
    struct lnode *cur;
    printf("\nDump:\n");
    for(cur=lst->head; cur != NULL; cur=cur->next) {
        printf("  %d\n", cur->value);
    }
}

struct lnode * list_find(lst, value)
    struct list *lst;
    int value;
{
    struct lnode *cur;
  	for(cur=lst->head; cur != NULL; cur=cur->next) {
      if(cur->value == value)
        return cur;
    }
  	return NULL;
}

void list_remove(lst, value)
    struct list *lst;
    int value;
{
  	struct lnode * rnode;
  	struct lnode *cur;

  	rnode = list_find(lst, value);
    if (rnode == NULL)
      return NULL;
  
  	if(lst->head == rnode) {
      lst->head = lst->head->next;
    }
  	else if(lst->tail == rnode) {
      for(cur=lst->head; cur != NULL; cur=cur->next) {
      	if(cur->next->value == value) {
          cur->next = NULL;
          lst->tail = cur;
        }
      }
    }
  	else
      printf("Middle\n");
}

void list_add(lst, value)
    struct list *lst;
    int value;
{
  	struct lnode *new = (struct lnode *) malloc(sizeof(struct lnode));
  	new->value = value;
  	new->next = NULL;
    if(lst->head == NULL)
      lst->head = new;
 	else
      lst->tail->next = new;
      lst->tail = new;
}