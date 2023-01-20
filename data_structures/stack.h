/**
 * \file            stack.h
 * \brief           header file containing the declaration of stack data structure, and connected functions.
 */

#ifndef STACK
#define STACK

#include <stdbool.h>
#include "dynamicarray.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * \brief           stack data structure.
 * \note            this implementation uses a dynamic array to store the stack content.
 */
typedef struct stack_t {
    dynamic_array_t* array; /*!< internal data storage */
} stack_t;

__declspec(dllexport) stack_t* stack_construct(size_t initial_size);
__declspec(dllexport) void stack_push(stack_t* stack, data_type value);
__declspec(dllexport) data_type stack_pop(stack_t* stack);
__declspec(dllexport) size_t stack_count(stack_t* stack);
__declspec(dllexport) bool stack_is_empty(stack_t* stack);
__declspec(dllexport) void stack_clear(stack_t** stack);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !STACK