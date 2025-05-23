#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dnode {
    char *key;
    char *value;
    struct dnode *next;
};

struct pydict {
  struct dnode *head;
  struct dnode *tail;
  int count;
};

/* Constructor - dct = dict() */
struct pydict * pydict_new() {
    struct pydict *p = malloc(sizeof(*p));
    p->head = NULL;
    p->tail = NULL;
    p->count = 0;
    return p;
}

/* Destructor - del(dct) */
void pydict_del(struct pydict* self) {
    struct dnode *cur, *next;
    cur = self->head;
    while(cur) {
        free(cur->key);
        free(cur->value);
        next = cur->next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

int main(void)
{
    struct dnode * cur;
    struct pydict * dct = pydict_new();

    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    pydict_put(dct, "z", "Catch phrase");
    pydict_print(dct);
    pydict_put(dct, "z", "W");
    pydict_print(dct);
    pydict_put(dct, "y", "B");
    pydict_put(dct, "c", "C");
    pydict_put(dct, "a", "D");
    pydict_print(dct);
    printf("Length =%d\n",pydict_len(dct));

    printf("z=%s\n", pydict_get(dct, "z"));
    printf("x=%s\n", pydict_get(dct, "x"));

    printf("\nDump\n");
    for(cur = dct->head; cur != NULL ; cur = cur->next ) {
        printf("%s=%s\n", cur->key, cur->value);
    }

    pydict_del(dct);
}

void pydict_print(struct pydict* self)
{
  /* printf("HERE: %s\n", self->head->value); */
  	struct dnode *cur;
  	int i = 0;
    printf("{");
  	for(cur=self->head; cur != NULL; cur=cur->next) {
      if (i < (self->count - 1))
        printf("'%s': '%s', ", cur->key, cur->value);
      else
        printf("'%s': '%s'", cur->key, cur->value);
      i++;
    }
  	printf("}\n");
}

int pydict_len(const struct pydict* self)
{
    return self->count;
}

/* find a node - used in get and put */
struct dnode* pydict_find(struct pydict* self, char *key)
{
    struct dnode *cur;
  	for(cur=self->head; cur != NULL; cur=cur->next) {
      if(cur->key == key)
        return cur;
    }
  	return NULL;
}

/* x.get(key) - Returns NULL if not found */
char* pydict_get(struct pydict* self, char *key)
{
    struct dnode *cur = pydict_find(self, key);
  	return (cur == NULL) ? NULL : cur->value;
}

/* x[key] = value; Insert or replace the value associated with a key */
void pydict_put(struct pydict* self, char *key, char *value)
{
  	struct dnode *cur = pydict_find(self, key);
  	if (cur == NULL) {
		struct dnode *new = (struct dnode *) malloc(sizeof(struct dnode));
      	new->key = key;
      	new->value = value;
      	new->next = NULL;
      	if(self->head == NULL)
      		self->head = new;
 		else
      		self->tail->next = new;
    	self->tail = new;
  		self->count = self->count + 1;
    }
  	else
      	cur->value = value;
}