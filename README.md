# Re-Entrant Safe dispatch_sync()

The dispatch_sync() method of GCD suffers from one major issue when using shared queues, such as the main queue: calling dispatch_sync(mainQueue, ^{}) when already on the main queue results in deadlock.

This code implements a re-entrant safe version of dispatch_sync() that you can safely call to your heart's content.

# Be cautious of hiding bugs

In general, blindly calling dispatch_sync() without knowing what queue you are already on is an anti-pattern that can conceal bugs, so use this utility with judgement and care.  Wherever possible, use design-by-contract to resolve thread safety problems before resorting to more blunt tools like this.


