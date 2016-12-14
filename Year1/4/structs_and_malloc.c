
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 64
#define BUFSIZE 100

void print_play(struct play *p);
void print_plays(struct play *p);
struct play *create_play(int id, int artist_id, int playcount);
struct play *parse_play(char *line);
struct play *read_plays(char *file_name);
struct play *add_play(struct play *head, struct play *newp);
struct play *filter_user(int user_id, struct play *head);int count_plays(struct play *head);
void free_plays(struct play *p);
void free_play(struct play *p);

void print_play(struct play *p)
{
  if (p != NULL) printf("user: %d artist: %d count: %d\n", p->user_id, p->artist_id, p->playcount);
  else printf("NULL\n");
}

struct play *create_play(int id, int artist_id, int playcount)
{
  struct play *p = malloc(sizeof(struct play));
  p->artist_id = artist_id;
  p->user_id=id;
  p->playcount=playcount;
  p->next = NULL;
  return p;
}

struct play *parse_play(char *line)
{  
  printf("Function play *parse_play is not yet defined.\n");
  return NULL;
}

void free_play(struct play *p)
{
  free(p);
}

struct play *add_play(struct play *head, struct play *newp)
{  
  if(newp != NULL) {
    if(head == NULL) {
      head = newp;
      head->next = NULL;
    }else {
      newp->next = head;
      head = newp;
    }
  }
  return head;
}

void print_plays(struct play *p)
{
  while(p != NULL) {
      print_play(p);
      p = p->next;
  }
}

struct play *read_plays(char *file_name)
{
  FILE *fp;
  fp= fopen(file_name, "r");
  if (fp == NULL) return; // error handling
  char text[256];
  int id, artist_id, plays, i=0;
  struct play *new_play=NULL;
  struct play *head=NULL;
  while(fgets(text, 256, fp) != NULL){
    sscanf(text, "%d %d %d \n", &id, &artist_id, &plays);
    
    new_play = create_play(id, artist_id, plays);
    head = add_play(head, new_play);
  }
  return head;
}
int count_plays(struct play *head)
{
  int plays=0;
  while(head != NULL) {
      plays += head->playcount;
      head = head->next;
  }
  return plays;
}

struct play *filter_user(int user_id, struct play *head) {
    struct play *new_head, **tmp = &new_head;
    struct play *og_head = head;
   for ( ; head; head = head->next) {
      if (head->user_id == user_id) {       
         *tmp = malloc(sizeof(struct play));
         (*tmp)->artist_id = head->artist_id;
         (*tmp)->playcount = head->playcount;
         (*tmp)->user_id = head->user_id;
         tmp = &((*tmp)->next);
      }
   }
   *tmp = NULL;
   free_plays(og_head);
   return new_head;
}

void free_plays(struct play *p)
{
  while(p != NULL) {
    free_play(p);
    p = p->next;
  }
}


void exit_usage() {
  printf("USAGE: query_plays file command\n"
         "\n"
         "where command is one of\n"
         "\n"
         "   p <userid>  prints plays, optionally limited to user.\n"
         "   c <userid>  counts plays, optionally limited to user.\n");
   exit(1);
}

void test_task1() {
  struct play *test_play = NULL;
  print_play(test_play);
  test_play = create_play(1,2,3);
  print_play(test_play);
  free_play(test_play);
}

void test_task2() {
  struct play *a = create_play(1,2,3);
  struct play *b = create_play(4,5,6);
  a = add_play(a, b);
  a = add_play(a, NULL);
  print_plays(a);
  printf("There are %d plays in a.\n", count_plays(a));
}
