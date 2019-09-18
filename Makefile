all: sthread nosync fib

sthread: thread.c
	cc -lpthread  thread.c -o sthread

nosync: thread_no_sync.c
	cc -lpthread  thread_no_sync.c -o nosync

fib: fibo.c
	cc -lpthread  fibo.c -o fib

clean:
	rm -f *.0 nosync sthread fib
