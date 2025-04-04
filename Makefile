CC = gcc

CFLAGS = -L /usr/local/Cellar/ncurses/6.5/lib -lncurses

lesson_%: lesson_%.c
	$(CC) -o /dist/lesson_$* $< $(CFLAGS)
	./dist/lesson_$*

block_%: block_%.c
	$(CC) -o /dist/block_$* $< $(CFLAGS)
	./dist/block_$*

clean:
	rm -f lesson_* block_*