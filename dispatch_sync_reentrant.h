/**
 * @file dispatch_sync_reentrant.h
 *
 * @brief Re-entrant (recursive) version of dispatch_sync for specific use cases
 *
 * @date 8/8/2016
 */

#import <dispatch/dispatch.h>

/**
 * A custom type for serial queues used with dispatch_sync_reentrant().  Ensures that
 * SDEs won't accidentally mix re-entrant and traditional queues.
 */
typedef dispatch_queue_t dispatch_reentrant_queue_t;

/**
 * Creates a re-entrant serial queue with the provided name.
 *
 * @param name name of the queue (for debugging)
 * @return A dispatch_reentrant_queue_t object
 */
dispatch_reentrant_queue_t dispatch_queue_create_reentrant_serial(const char *name);

/**
 * Executes a block on a queue synchronously.  If the current queue is equal to
 * queue and supports re-entrance, the block will be executed immediately.
 *
 * @param queue
 * The re-entrant target dispatch queue on which to execute the block.
 * The result of passing NULL in this parameter is undefined.
 *
 * @param block
 * The block to executed on the specified target queue.
 * The result of passing NULL in this parameter is undefined.
 */
void dispatch_sync_reentrant(dispatch_reentrant_queue_t queue, dispatch_block_t block);

/**
 * Returns a re-entrant version of the main queue.  Optimized for minimal overhead.
 *
 * @return A dispatch_reentrant_queue_t object for the main queue
 */
dispatch_reentrant_queue_t dispatch_get_reentrant_main_queue(void);

/**
 * Returns a BOOL indicating if the specified queue supports dispatch_sync_reentrant().
 * If YES, then the specified queue can safely be cast to the type dispatch_reentrant_queue_t.
 *
 * @param queue
 * The target queue to test.
 * The result of passing NULL in this parameter is NO.
 *
 * @return YES if the queue parameter supports dispatch_sync_reentrant().  NO otherwise.
 */
BOOL dispatch_queue_is_reentrant(dispatch_queue_t queue);
