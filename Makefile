parser: expr.c interp.c main.c scan.c tree.c
	cc -o PrecedenceClimbingparser -g expr2.c interp.c main.c scan.c tree.c

clean:
	rm -f parser *.o
