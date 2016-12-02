
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct artist {
    int artist_id;
    char artist_name[100];
    int playcount;
    int alternative_artist_id;
    struct artist *next;
};

struct artist *read_artists(char *fname);
struct artist *add_artist(struct artist *head, struct artist *newp);
struct artist *create_artist(int artist_id, char artist_name[100]);
void print_artists(struct artist *p);
void print_artist(struct artist *p);
void free_artists(struct artist *head);
void free_artist(struct artist *p);
struct artist *merge(struct artist *head_one, struct artist *head_two);
struct artist *mergesort(struct artist *head);

int main(int argc, char **argv) {
    struct artist *x = read_artists("artist_data.txt");
    printf(".");
    mergesort(x);
    print_artists(x);

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
        // sscanf(text, "%d\t%65[^\t\n]\n", &artist_id, &artist_name);
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
  // printf("%s == %s", *(p->artist_name), artist_name);
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
      print_artist(p);
      p = p->next;
  }
}

void print_artist(struct artist *p) {
  if (p != NULL) printf("%s (%d) [%d]\n",p->artist_name, p->artist_id, 0);
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


struct artist *mergesort(struct artist *head) {
 struct artist *head_one;
 struct artist *head_two;

 if((head == NULL) || (head->next == NULL)) 
  return head;

 head_one = head;
 head_two = head->next;
 while((head_two != NULL) && (head_two->next != NULL)) {
  head = head->next;
  head_two = head->next->next;
 }
 head_two = head->next;
 head->next = NULL;

 return merge(mergesort(head_one), mergesort(head_two));
}

/* merge the lists.. */
struct artist *merge(struct artist *head_one, struct artist *head_two) {
 struct artist *head_three;

 if(head_one == NULL) 
  return head_two;

 if(head_two == NULL) 
  return head_one;

 if(head_one->artist_id < head_two->artist_id) {
  head_three = head_one;
  head_three->next = merge(head_one->next, head_two);
 } else {
  head_three = head_two;
  head_three->next = merge(head_one, head_two->next);
 }

 return head_three;
}
