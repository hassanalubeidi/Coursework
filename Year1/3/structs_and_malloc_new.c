
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 64
#define BUFSIZE 100

struct play
{
  int user_id;
  int artist_id; 
  int playcount;
  struct play *next;
};

void print_play(struct play *p);
void print_plays(struct play *p);
struct play *create_play(int id, int artist_id, int playcount);
struct play *parse_play(char *line);
struct play *read_plays(char *file_name);
struct play *add_play(struct play *head, struct play *newp);
struct play *filter_user(int user_id, struct play *head);
int count_plays(struct play *head);
void free_plays(struct play *p);
void free_play(struct play *p);

void print_play(struct play *p)
{
  if(p != NULL) {
        printf("user: %d artist: %d count: %d\n", p->user_id, p->artist_id, p->playcount);
  } else { printf("NULL\n"); }
}

struct play *create_play(int id, int artist_id, int playcount)
{
  struct play *new_struct = malloc(sizeof(struct play));
    new_struct->user_id=id;new_struct->artist_id=artist_id;new_struct->playcount=playcount;

    return new_struct;
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
  if( head != NULL){
        struct play *tmp= head;
        while( tmp->next != NULL){
            tmp = tmp->next;
        }    
        tmp->next = newp;
        
  } else {
      
        head = newp;
  }
  
    return head;
}

void print_plays(struct play *p)
{
    int i = 0;
    
    while ( p->next !=  NULL ) { 
      printf("- %d - %d ", p, p->next);
        p = p->next; 
        i++;
    }  
    printf("%d PRINTED\n", i);
    print_play(p);
}

struct play *read_plays(char *file_name)
{
  FILE *fp;
  fp= fopen(file_name, "r");

  char text[256];
  int id, artist_id, plays, i=0;
  struct play *new_play=NULL;
  struct play *head=(struct play *)malloc(sizeof(struct play));
  while(fgets(text, 256, fp) != NULL && i < 2000){
    sscanf(text, "%d %d %d \n", &id, &artist_id, &plays);
    
    new_play = create_play(id, artist_id, plays);
    head = add_play(head, new_play);
  }

  // printf("FUCK\n\n");
  
   

  fclose(fp);
  return head;
}

int count_plays(struct play *head)
{
  struct play *tmp = head; 
    int count = 0;
    while ( tmp->next !=  NULL ) { 
        count+= tmp->playcount;
        tmp = tmp->next; 
    }  
    count+= tmp->playcount;
    return count;
}

struct play *filter_user(int user_id, struct play *p)
{
  struct play *filter_head=NULL;
  struct play *original_head = p;
  int i = 0;
  // for ( p = head; p !=  NULL ; p=p->next ) {
  //   if (p->user_id == user_id) {
  //     filter_head = add_play(filter_head, p);
  //     printf("%d|", ++i);
  //   }
    
  // }

  while ( p->next !=  NULL ) { 
      if (p->user_id == user_id) {
          filter_head = add_play(filter_head, p);
          printf("%d|", ++i);
      }
      p = p->next;
    }  
  free_plays(original_head);
  printf("FOUND");
  return filter_head;
}

void free_plays(struct play *head)
{
  struct play *p ;
  for ( p = head; p !=  NULL ; p=p->next ) {
    free(p);
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
  a = add_play(a, NULL);
  a = add_play(a, b);
  
  print_plays(a);
  printf("There are %d plays in a.\n", count_plays(a));
}

int main(int argc, char **argv) {

  test_task1();
  test_task2();
  // exit_usage();

  print_plays(read_plays("user_artist_data.txt"));
}