
#include "stack.h"
#include "stdio.h"
#include "assert.h"

#define STACK_CAPACITY 3
#define STACK_ITEM_SIZE sizeof(uint32_t)
#define TEST_VAL 0xdeadbeef

void stack_dump(const stack_t *const stack)
{
  printf("===== STACK DUMP =====\r\n"
         "Control Block\r\n"
         "\tDATA PTR: 0x%p\r\n"
         "\tCAPACITY: %lu\r\n"
         "\t ITEM SZ: %lu\r\n"
         "\t     TOP: %lu\r\n",
         stack->data,
         stack->capacity,
         stack->item_size,
         stack->top);
  printf("Data (raw)\r\n");
  for (size_t i = 0; i < stack->capacity * stack->item_size; ++i)
  {
    if (i)
    {
      if (i % 8 == 0)
      {
        printf("\r\n");
      }
      else
      {
        printf(" ");
      }
    }
    printf("%02x", *(uint8_t *)(stack->data + i));
  }
  printf("\r\n");
}

int main(int argc, char *argv[])
{
  (void)argc; // suppress compiler complaints
  (void)argv; // suppress compiler complaints

  uint8_t stack_mem[STACK_ITEM_SIZE * STACK_CAPACITY];
  stack_t stack;

  // NL_RESULT res;
  uint32_t junk = TEST_VAL;
  assert(stack_init(&stack, STACK_CAPACITY, STACK_ITEM_SIZE, stack_mem) == NL_OK);
  stack_dump(&stack);
  assert(stack_size(&stack) == 0);
  assert(stack_empty(&stack) == true);
  assert(stack_full(&stack) == false);
  assert(stack_pop(&stack, &junk) == NL_ERR_EMPTY);
  assert(stack_peek(&stack, &junk) == NL_ERR_EMPTY);
  assert(junk == TEST_VAL); // failed calls shoud not modify argument

  // add a single item to stack and recheck
  uint32_t junk_check = 0;
  assert(stack_push(&stack, &junk) == NL_OK);
  printf("Post push: %u\r\n", junk);
  stack_dump(&stack);
  assert(stack_size(&stack) == 1U);
  assert(stack_peek(&stack, &junk_check) == NL_OK);
  assert(stack_size(&stack) > 0);
  assert(stack_empty(&stack) == false);

  assert(junk_check == junk);
  junk_check = 0;
  assert(stack_pop(&stack, &junk_check) == NL_OK); // can peek if there's an item
  printf("Post pop\r\n");
  stack_dump(&stack);
  assert(junk_check == junk); // we got out what we put in
  assert(stack_empty(&stack) == true);
  assert(stack_size(&stack) == 0);
  assert(stack_full(&stack) == false);

  return 0;
}