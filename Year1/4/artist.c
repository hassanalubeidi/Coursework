
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PLAYCOUNT 0
#define ARTISTID  1

struct artist {
    int artist_id;
    char artist_name[100];
    int playcount;
    int alternative_artist_id;
    struct artist *next;
};

struct play
{
  int user_id;
  int artist_id; 
  int playcount;
  struct play *next;
};

#include "structs_and_malloc.c"

struct artist *read_artists(char *fname);
struct artist *add_artist(struct artist *head, struct artist *newp);
struct artist *create_artist(int artist_id, char artist_name[100]);
void print_artists(struct artist *p);
void print_artist(struct artist *p);
void free_artists(struct artist *head);
void free_artist(struct artist *p);
struct play *sort_plays(struct play *head);
struct play *play_merge(struct play *x, struct play *y);
struct play *play_find_middle(struct play *x);
struct artist *sort_artists(struct artist *head, int criterion);
struct artist *artist_merge(struct artist *x, struct artist *y, int criterion);
struct artist *artist_find_middle(struct artist *x);
struct artist *update_counts(struct artist *a, struct play *p);
void top_artists(struct artist *head, int k);


int main(int argc, char **argv) {
    int k;
    sscanf(argv[1], "%d", &k);
    
    struct artist *x = read_artists(argv[2]);
    struct play *y = read_plays(argv[3]);

    x = sort_artists(x, ARTISTID);
    y = sort_plays(y);
    x = update_counts(x, y);
    x = sort_artists(x, PLAYCOUNT);
    
    top_artists(x, k);

    return 0;
}

struct artist *read_artists(char *fname) {
    FILE *fp;
    fp= fopen(fname, "r");
    if (fp == NULL) return; // error handling
    char text[256];
    int artist_id;
    char artist_name[100];
    struct artist *new_artist=NULL;
    struct artist *head=NULL;
    while(fgets(text, 256, fp) != NULL) {
        sscanf(text, "%d\t%65[^\t\n]\n", &artist_id, artist_name);
        artist_name[100] = '\0';
        new_artist = create_artist(artist_id, artist_name);
        head = add_artist(head, new_artist);
    }
    return head;
}




struct artist *create_artist(int artist_id, char artist_name[100]) {
  struct artist *p = malloc(sizeof(struct artist));
  p->artist_id = artist_id;
  strcpy(p->artist_name, artist_name);
  p->next = NULL;
  return p;
}

struct artist *add_artist(struct artist *head, struct artist *newa) {  
  if(newa != NULL) {
    if(head == NULL) {
      head = newa;
      head->next = NULL;
    }else {
      newa->next = head;
      head = newa;
    }
  }
  return head;
}

void print_artists(struct artist *p) {
  while(p != NULL) {
      if (p->playcount > 0) {
        print_artist(p);
      }
      p = p->next;
  }
}

void print_artist(struct artist *p) {
  if (p != NULL) printf("%s (%d) [%d]\n",p->artist_name, p->artist_id, p->playcount);
  else printf("NULL\n");
}

void free_artists(struct artist *head)
{
  struct artist *p ;
  for ( p = head; p !=  NULL ; p=p->next ) {
    free(p);
  }
}

void free_artist(struct artist *p)
{
  free(p);
}


struct play *play_find_middle(struct play *x) {
 struct play *slow = x;
 struct play *fast = x;
 while( fast->next != NULL &&
 fast->next->next != NULL ) {
 slow = slow->next;
 fast = fast->next->next;
 }
 return slow;
}

struct play *play_merge(struct play *x, struct play *y)
{
 struct play *tmp = NULL;
 struct play *head = NULL;
 struct play *curr = NULL;

 if( x == NULL )
 return y;
 else if( y == NULL )
 return x;
 while( x != NULL && y != NULL ) {
 // Swap x and y if x is smaller than y.
 if( x->artist_id > y->artist_id ) {
 tmp = y;
 y = x;
 x = tmp;
 }

 if( head == NULL ) { // First element?
 head = x;
 curr = x;
 } else {
 curr->next = x;
 curr = curr->next;
 }
 x = x->next;
 }

 // Either x or y is empty.
 if( x == NULL )
 curr->next = y;
 else
 curr->next = x;

 return head;
}

struct play *sort_plays(struct play *head)
{
 struct play *m = NULL;
 struct play *x = NULL;
 struct play *y = NULL;
 if ( head == NULL || head->next == NULL )
 return head;
 x = head;
 m = play_find_middle(head);
 y = m->next;
 m->next = NULL;
 return play_merge( sort_plays(x),
 sort_plays(y) );
}

struct artist *artist_find_middle(struct artist *x) {
 struct artist *slow = x;
 struct artist *fast = x;
 while( fast->next != NULL &&
 fast->next->next != NULL ) {
 slow = slow->next;
 fast = fast->next->next;
 }
 return slow;
}

struct artist *artist_merge(struct artist *x, struct artist *y, int criterion)
{
 struct artist *tmp = NULL;
 struct artist *head = NULL;
 struct artist *curr = NULL;

 if( x == NULL )
 return y;
 else if( y == NULL )
 return x;
 while( x != NULL && y != NULL ) {
 // Swap x and y if x is smaller than y.
    if(criterion == ARTISTID) {
      if( x->artist_id > y->artist_id ) {
          tmp = y;
          y = x;
          x = tmp;
      }
    } else if(criterion == PLAYCOUNT) {
      if( x->playcount < y->playcount ) {
          tmp = y;
          y = x;
          x = tmp;
      }
    }
    

 if( head == NULL ) { // First element?
        head = x;
        curr = x;
 } else {
    curr->next = x;
    curr = curr->next;
  }
  x = x->next;
 }

 // Either x or y is empty.
 if( x == NULL ) curr->next = y;
 else curr->next = x;

 return head;
}

struct artist *sort_artists(struct artist *head, int criterion)
{
 struct artist *m = NULL;
 struct artist *x = NULL;
 struct artist *y = NULL;
 if ( head == NULL || head->next == NULL )
 return head;
 x = head;
 m = artist_find_middle(head);
 y = m->next;
 m->next = NULL;
 return artist_merge( sort_artists(x, criterion),
 sort_artists(y, criterion), criterion);
}

struct artist *update_counts(struct artist *a, struct play *p) {
  struct artist *og= a;
  struct play *curP = p;
  while(a->next != NULL) {
    int count = 0;
    while(a->artist_id >= curP->artist_id) {
      count = count + curP->playcount;
      curP = curP->next;
    }
    a->playcount = count;
    a = a->next;
  }
  return og;
}

void top_artists(struct artist *head, int k) {
  while(k > 0) {
    print_artist(head);
    head = head->next;
    k -= 1;
  }
} 