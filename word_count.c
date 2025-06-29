#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct TreeMapEntry {
    char *key;  /* public */
    int value;  /* public */
    struct TreeMapEntry *__next;
    struct TreeMapEntry *__left;
    struct TreeMapEntry *__right;
};

struct TreeMapIter {
   struct TreeMapEntry *__current;

   struct TreeMapEntry* (*next)(struct TreeMapIter* self);
   void (*del)(struct TreeMapIter* self);
};

struct TreeMap {
   /* Attributes */
   struct TreeMapEntry *__head;
   struct TreeMapEntry *__root;
   int __count;
   int debug;

   /* Methods */
   void (*put)(struct TreeMap* self, char *key, int value);
   int (*get)(struct TreeMap* self, char *key, int def);
   int (*size)(struct TreeMap* self);
   void (*dump)(struct TreeMap* self);
   struct TreeMapIter* (*iter)(struct TreeMap* self);
   void (*del)(struct TreeMap* self);
};

void __TreeMap_del(struct TreeMap* self) {
    struct TreeMapEntry *cur, *next;
    cur = self->__head;
    while(cur) {
        free(cur->key);
        /* value is just part of the struct */
        next = cur->__next;
        free(cur);
        cur = next;
    }
    free((void *)self);
}

void __TreeMapIter_del(struct TreeMapIter* self) {
    free((void *)self);
}

void __TreeMap_dump_tree(struct TreeMapEntry *cur, int depth)
{
    int i;
    if ( cur == NULL ) return;
    for(i=0;i<depth;i++) printf("| ");
    printf("%s=%d\n", cur->key, cur->value);
    if ( cur->__left != NULL ) {
        __TreeMap_dump_tree(cur->__left, depth+1);
    }
    if ( cur->__right != NULL ) {
        __TreeMap_dump_tree(cur->__right, depth+1);
    }
}

void __TreeMap_dump(struct TreeMap* self)
{
    struct TreeMapEntry *cur;
    printf("Object TreeMap count=%d\n", self->__count);
    for(cur = self->__head; cur != NULL ; cur = cur->__next ) {
         printf("  %s=%d\n", cur->key, cur->value);
    }
    printf("\n");
    __TreeMap_dump_tree(self->__root, 0);
    printf("\n");
}

/* Run a check to see if left and right are broken */
void __Map_check(struct TreeMap* self, struct TreeMapEntry *left, char *key, struct TreeMapEntry *right)
{
    if ( self->debug ) 
        printf("Check position: %s < %s > %s\n", (left ? left->key : "0"),
            key, (right ? right->key : "0") );

    /* Check our location in the linked list */
    if ( left != NULL ) {
        if ( left->__next != right ) {
            printf("FAIL left->__next != right\n");
        }
    } else {
        if ( self->__head != right ) {
            printf("FAIL self->__head != right\n");
        }
    }

    /* Check our location in the tree */
    if ( right != NULL && right->__left == NULL ) {
        /* OK */
    } else if ( left != NULL && left->__right == NULL ) {
        /* OK */
    } else {
        printf("FAIL Neither right->__left nor left->__right are available\n");
    }
}

int __TreeMap_size(struct TreeMap* self)
{
    return self->__count;
}

struct TreeMapEntry* __TreeMapIter_next(struct TreeMapIter* self)
{
    /* Advance the iterator.  Recall that when we first 
     * create the iterator __current points to the first item
     * so we must return an item and then advance the iterator.
     */
    struct TreeMapEntry *retval = self->__current;
  	if (retval == NULL)
      return NULL;
  	self->__current = self->__current->__next;
  	return retval;
}

struct TreeMapIter* __TreeMap_iter(struct TreeMap* self)
{
    struct TreeMapIter *iter = malloc(sizeof(*iter));
    iter->__current = self->__head;
    iter->next = &__TreeMapIter_next;
    iter->del = &__TreeMapIter_del;
    return iter;
}

void __TreeMap_put(struct TreeMap* self, char *key, int value) {
    struct TreeMapEntry *cur, *left, *right;
    int cmp;
    struct TreeMapEntry *old, *new;
    char *new_key;

    cur = self->__root;
    left = NULL;
    right = NULL;
  
  	if (cur != NULL) {
  		printf("ROOOOOOOT: %s\n", cur->key);
  		self->dump(self);
    }

  	while (cur != NULL) {
    //   printf("%s : %s\n", key, cur->key);
      cmp = strcmp(key, cur->key);
      if (cmp == 0) {
        cur->value = value;
        self->dump(self);
        return;
      }
      if (cmp < 0) {
        right = cur;
        cur = cur->__left;
      }
      else {
        left = cur;
        cur = cur->__right;
      }
    }
  
    new = malloc(sizeof(*new));
  	new->key = key;
  	new->value = value;
  	new->__left = NULL;
  	new->__right = NULL;

    if ( self->__head == NULL ) {
    //   	printf("WHERE THE JOURNEY BEGINS:%s\n", key);
        self->__head = new;
        self->__root = new;
        self->__count++;
      	self->dump(self);
    //   	printf("WHERE THE JOURNEY ENDS: %s\n", self->__root->key);
    //   	self->dump(self);
        return;
    }

    __Map_check(self, left, key, right);

  	if (left != NULL) {
      new->__next = right;
      left->__next = new;
    }
  	else {
      new->__next = self->__head;
      self->__head = new;
    }

  	if (left != NULL && left->__right == NULL)
      left->__right = new;
  	else if (right != NULL && right->__left == NULL)
      right->__left = new;
  	else
      printf("FAIL\n");
  	
//   	self->dump(self);
  	self->__count++;
}

int __TreeMap_get(struct TreeMap* self, char *key, int def)
{
    int cmp;
    struct TreeMapEntry *cur;

    if ( self == NULL || key == NULL || self->__root == NULL ) return def;
  
  	if (self->__root != NULL) {
  		printf("HERE IN GET: %s\n", self->__root->key);
  		// self->dump(self);
    }

    cur = self->__root;

    /* TODO: scan down the tree and if the key is found, return the value.
     * If the key is not found, return the default value (def).
     */
  	while (cur != NULL) {
      cmp = strcmp(key, cur->key);
      if (cmp == 0)
        return cur->value;
      else if (cmp < 0)
        cur = cur->__left;
      else if (cmp > 0)
        cur = cur->__right;
    }

//   	printf("POST GET: %s\n", cur->key);
    return def;
}

struct TreeMap * TreeMap_new() {
    struct TreeMap *p = malloc(sizeof(*p));

    p->__head = NULL;
    p->__root = NULL;
    p->__count = 0;
    p->debug = 0;

    p->put = &__TreeMap_put;
    p->get = &__TreeMap_get;
    p->size = &__TreeMap_size;
    p->dump = &__TreeMap_dump;
    p->iter = &__TreeMap_iter;
    p->del = &__TreeMap_del;
    return p;
}

int main(void)
{
    struct TreeMap * map = TreeMap_new();
    struct TreeMapEntry *cur;
    struct TreeMapIter *iter;
    // char word[24][100] = ["the", "clown", "ran", "after", "the", "car", "and", "the", "car", "ran", "into", "the", "tent", "and", "the", "tent", "fell", "down", "on", "the", "clown", "and", "the", "car"];  /* Yes, this is dangerous */
    char * word[] = {
    "the",
 "clown",
 "ran",
 "after",
 "the",
 "car",
 "and",
 "the",
 "car",
 "ran",
 "into",
 "the",
 "tent",
 "and",
 "the",
 "tent",
 "fell",
 "down",
 "on",
 "the",
 "clown",
 "and",
 "the",
 "car"
    };
    int i;
    int count, maxvalue;
    char *maxkey;

    setvbuf(stdout, NULL, _IONBF, 0);  /* Internal */

    /* Turn off debug */
    map->debug = 0;

    /* Loop over each word in the file */
    for (i=0; i < 24; i++) {
        printf("Word: %s\n", word[i]);
        count = map->get(map, word[i], 0);
        map->put(map, word[i], count+1);
        printf("Done\n");
    }
    

    maxkey = NULL;
    maxvalue = -1;
    iter = map->iter(map);
    while(1) {
        cur = iter->next(iter);
        if ( cur == NULL ) break;
        if ( maxkey == NULL || cur->value > maxvalue ) {
            maxkey = cur->key;
            maxvalue = cur->value;
        }
    }
    iter->del(iter);
    printf("HERE AT THE END OF ALL THINGS \n%s %d\n", maxkey, maxvalue);

    map->del(map);
}