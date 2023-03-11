#ifndef QUEUE_TEST
#define QUEUE_TEST

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void queue_construct_test(void);
void queue_enqueue_test(void);
void queue_dequeue_test(void);
void queue_peek_test(void);
void queue_count_test(void);
void queue_is_empty_test(void);
void queue_clear_test(void);

void queue_testall(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !QUEUE_TEST
