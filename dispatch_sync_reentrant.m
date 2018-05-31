/**
 * @file dispatch_sync_reentrant.m
 *
 * @brief Re-entrant (recursive) version of dispatch_sync for specific use cases
 *
 * @date 8/8/2016
 */

#import "dispatch_sync_reentrant.h"


static const void *const ReentrantQueueKey = (const void *) &ReentrantQueueKey;

dispatch_reentrant_queue_t dispatch_queue_create_reentrant_serial(const char *name)
{
    dispatch_queue_t queue = dispatch_queue_create(name, DISPATCH_QUEUE_SERIAL);
    dispatch_queue_set_specific(queue, ReentrantQueueKey, (__bridge void *) (queue), NULL);

    return queue;
}

void dispatch_sync_reentrant(dispatch_reentrant_queue_t queue, dispatch_block_t block)
{
    if (queue == NULL || block == NULL)
    {
        return;
    }

    if (dispatch_get_specific(ReentrantQueueKey) == (__bridge void *) (queue))
    {
        block();
    }
    else
    {
        dispatch_sync(queue, block);
    }
}

dispatch_reentrant_queue_t dispatch_get_reentrant_main_queue(void)
{
    return (dispatch_reentrant_queue_t) dispatch_get_main_queue();
}

BOOL dispatch_queue_is_reentrant(dispatch_queue_t queue)
{
    return (queue != NULL) && (dispatch_queue_get_specific(queue, ReentrantQueueKey) == (__bridge void *)queue);
}

// Sets ReentrantQueueKey on the main queue to ensure it is setup for dispatch_sync_reentrant().
// The compiler attribute ensures this gets executed at load time.
__attribute__((constructor)) static void dispatch_sync_reentrant_setup_main_queue(void)
{
    dispatch_reentrant_queue_t mainQueue = dispatch_get_main_queue();
    dispatch_queue_set_specific(mainQueue, ReentrantQueueKey, (__bridge void *) (mainQueue), NULL);
}
