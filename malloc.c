#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

struct block {
  size_t size;
  bool free;
  void *address;
  struct block *next;
} *head = NULL;

void print_blocks(int line)
{
  struct block *temp;

  temp = head;
  printf("line %d:\n", line);
  while (NULL != temp)
  {
    printf("address: %p, size: %ld, free: %d\n", temp, temp->size, temp->free);
    temp = temp->next;
  }
  printf("\n");
}

void update_head(struct block *block)
{
  if (NULL == head)
  {
    block->free = false;
    head = block;
    head->next = NULL;
  }
  else
  {
    block->next = head->next;
    head->next = block;
  }
}

void *check_head(size_t size)
{
  struct block *temp;
  
  temp = head;
  while (NULL != temp)
  {
    if (temp->free && size <= temp->size)
    {
      temp->free = false;
      return temp;
    }
    temp = temp->next;
  }
  return NULL;
}

void *my_malloc(size_t size) {
  struct block *new;
  size_t total_size, oct_size;
 
  new = check_head(size);
  if (NULL == new)
  {
    total_size = size + sizeof(*new);
    oct_size = (total_size / 8) * 8;
    total_size = oct_size + 8;
    new = sbrk(total_size);
    new->size = size;
    new->free = false;
    new->next = NULL;
    update_head(new);
  }
  else
  {
    printf("[inserted %ld bytes into freed memory]\n\n", size);
  } 
  new->address = new + sizeof(*new);
  return new->address;
}

void *my_free(void *p) {
  struct block *temp;
  
  if (NULL == p) {
    return NULL;
  }
  temp = head;
  while (NULL != temp)
  {
    if (temp->address == p)
    {
      temp->free = true;
    }
    temp = temp->next;
  }
  return NULL;
}

int main(){
    char *p, *q, *r, *s;
    
    p = my_malloc(4*sizeof(*p));
    print_blocks(__LINE__);
    if (NULL == p)
    {
        return 1;
    }
    p = my_free(p);

    q = my_malloc(3*sizeof(*q));
    print_blocks(__LINE__);
    if (NULL == q)
    {
      return 1;
    }
    q = my_free(q);

    r = my_malloc(5*sizeof(*r));
    print_blocks(__LINE__);
    if (NULL == r)
    {
      return 1;
    }
    r = my_free(r);

    s = my_malloc(5*sizeof(*s));
    print_blocks(__LINE__);
    if (NULL == s)
    {
      return 1;
    }
    print_blocks(__LINE__);
    s = my_free(s);
    
    print_blocks(__LINE__);
    return 0;
}