FLAGS = -Wall -Wextra -std=c99

bstrees: bstrees.o bst.o vbst.o rbt.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o
	gcc $(FLAGS) bstrees.o bst.o vbst.o rbt.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o -o bstrees
bstrees.o: bstrees.c bst.h vbst.h comparator.h integer.h real.h string.h
	gcc $(FLAGS) -c bstrees.c
bst.o: bst.c bst.h
	gcc $(FLAGS) -c bst.c
vbst.o: vbst.c vbst.h bst.h
	gcc $(FLAGS) -c vbst.c
rbt.o: rbt.c rbt.h bst.h
	gcc $(FLAGS) -c rbt.c
scanner.o: scanner.c scanner.h
	gcc $(FLAGS) -c scanner.c
comparator.o: comparator.c comparator.h
	gcc $(FLAGS) -c comparator.c
integer.o: integer.c integer.h
	gcc $(FLAGS) -c integer.c
real.o: real.c real.h
	gcc $(FLAGS) -c real.c
string.o: string.c string.h
	gcc $(FLAGS) -c string.c
sll.o: sll.c sll.h
	gcc $(FLAGS) -c sll.c
queue.o: queue.c queue.h sll.h
	gcc $(FLAGS) -c queue.c
# cleaner.o: cleaner.c cleaner.h string.h scanner.h
# 	gcc $(FLAGS) -c cleaner.c
cleanbuild:
	clear
	make clean
	make
clean:
	rm -f bstrees.o bst.o vbst.o rbt.o scanner.o comparator.o integer.o real.o string.o sll.o queue.o bstrees

test : bstrees
	./bstrees -v clean.0 display btest3.txt
	./bstrees -r clean.0 display btest4.txt
	./bstrees -v spaces.0 display btest5.txt
	./bstrees -r spaces.0 display btest6.txt
	./bstrees -v empty commands.0 btest7.txt
	./bstrees -r empty commands.0 btest8.txt
	./bstrees -v s9.0 display btest9.txt
	./bstrees -r s10.0 display btest10.txt
	./bstrees -v s11.0 display btest11.txt
	./bstrees -r s12.0 display btest12.txt
	./bstrees -v s13.0 display btest13.txt
	./bstrees -r s14.0 display btest14.txt
	./bstrees -v s15.0 display btest15.txt
	./bstrees -r w16.0 display btest16.txt
	./bstrees -v w17.0 display btest17.txt
	./bstrees -r w18.0 display btest18.txt
	./bstrees -v w19.0 display btest19.txt
	./bstrees -r w20.0 display btest20.txt
	./bstrees -v w21.0 display btest21.txt
	./bstrees -r w22.0 display btest22.txt
	./bstrees -v w23.0 display btest23.txt
	./bstrees -r w24.0 display btest24.txt
	./bstrees -v clean.0 c25.0 btest25.txt
	./bstrees -r clean.0 c26.0 btest26.txt
	./bstrees -v clean.0 c27.0 btest27.txt
	./bstrees -r clean.0 c28.0 btest28.txt
	./bstrees -v clean.0 c29.0 btest29.txt
	./bstrees -r clean.0 c30.0 btest30.txt
	./bstrees -v clean.0 c31.0 btest31.txt
	./bstrees -r clean.0 c32.0 btest32.txt
	@echo dun dun dunnnnn
	./bstrees -r shakespeare.txt shakespeare.display btest33.txt
	@echo dun dun dunnnnn
	./bstrees -r beowulf.txt display btest34.txt
	./bstrees -r clean.0 c35.0 btest35.txt
	@echo Test 36 runs alternate code in graded version
	./bstrees -v clean.0 c36.0 btest36.txt
	./bstrees -v clean.0 c37.0 btest37.txt
	#Testing against existing files
	diff btest3.txt test3.txt
	diff btest4.txt test4.txt
	diff btest5.txt test5.txt
	diff btest6.txt test6.txt
	diff btest7.txt test7.txt
	diff btest8.txt test8.txt
	diff btest9.txt test9.txt
	diff btest10.txt test10.txt
	diff btest11.txt test11.txt
	diff btest12.txt test12.txt
	diff btest13.txt test13.txt
	diff btest14.txt test14.txt
	diff btest15.txt test15.txt
	diff btest16.txt test16.txt
	diff btest17.txt test17.txt
	diff btest18.txt test18.txt
	diff btest19.txt test19.txt
	diff btest20.txt test20.txt
	diff btest21.txt test21.txt
	diff btest22.txt test22.txt
	diff btest23.txt test23.txt
	diff btest24.txt test24.txt
	diff btest25.txt test25.txt
	diff btest26.txt test26.txt
	diff btest27.txt test27.txt
	diff btest28.txt test28.txt
	diff btest29.txt test29.txt
	diff btest30.txt test30.txt
	diff btest31.txt test31.txt
	diff btest32.txt test32.txt
	diff btest33.txt test33.txt
	diff btest34.txt test34.txt
	diff btest35.txt test35.txt
	diff btest36.txt test36.txt
	diff btest37.txt test37.txt
	@echo Testing Sequence complete.