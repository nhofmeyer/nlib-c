
#include "test.h"
#include "stack.h"

#define STACK_CAPACITY 2
#define STACK_ITEM_SIZE sizeof(uint32_t)
#define STACK_TEST_VAL 0xdeadbeef
#define STACK_TEST_VAL2 0xfeed5eed

void stack_dump(const stack_t *const stack)
{
    (void)stack;
#if STACK_DEBUG
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
#endif
}

void test_stack()
{
  uint8_t stack_mem[STACK_ITEM_SIZE * STACK_CAPACITY];
  stack_t stack;

  uint32_t junk = STACK_TEST_VAL;
  assert(stack_init(&stack, STACK_CAPACITY, STACK_ITEM_SIZE, stack_mem) == NL_OK);
  stack_dump(&stack);
  assert(stack_size(&stack) == 0);
  assert(stack_empty(&stack) == true);
  assert(stack_full(&stack) == false);
  assert(stack_pop(&stack, &junk) == NL_ERR_EMPTY);
  assert(stack_peek(&stack, &junk) == NL_ERR_EMPTY);
  assert(junk == STACK_TEST_VAL); // failed calls shoud not modify argument

  // add a single item to stack and recheck
  uint32_t junk_check = 0;
  assert(stack_push(&stack, &junk) == NL_OK);
  assert(stack_size(&stack) == 1U);
  assert(stack_peek(&stack, &junk_check) == NL_OK);
  assert(stack_empty(&stack) == false);
  assert(stack_full(&stack) == false); // has a single item
  assert(junk_check == junk);
  junk_check = 0;

  // add another element to fill the array
  junk = STACK_TEST_VAL2;
  assert(stack_push(&stack, &junk) == NL_OK);
  assert(stack_size(&stack) == 2U);
  assert(stack_peek(&stack, &junk_check) == NL_OK);
  assert(junk == junk_check);
  assert(stack_full(&stack) == true);
  assert(stack_empty(&stack) == false);

  // try to push on full array
  assert(stack_push(&stack, &junk) == NL_ERR_FULL);
  // make sure the push did not change the size of the stack or anything like that
  assert(stack_size(&stack) == 2U);
  assert(stack_full(&stack) == true);
  assert(stack_empty(&stack) == false);

  // peek value and check
  junk_check = 0;
  assert(stack_peek(&stack, &junk_check) == NL_OK);
  assert(junk == junk_check);
  assert(stack_size(&stack) == 2U);

  // pop value and check
  junk_check = 0x12345678;
  assert(stack_pop(&stack, &junk_check) == NL_OK);
  assert(junk == junk_check);
  assert(stack_size(&stack) == 1U);
  assert(stack_empty(&stack) == false);
  assert(stack_full(&stack) == false);

  // pop next value
  junk_check = 0x12345678;
  junk = STACK_TEST_VAL;
  assert(stack_pop(&stack, &junk_check) == NL_OK);
  assert(junk_check == junk);
  assert(stack_empty(&stack) == true);
  assert(stack_size(&stack) == 0U);
  assert(stack_full(&stack) == false);
  assert(stack_capacity(&stack) == 2U);
}