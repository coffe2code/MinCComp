comp1: cg.c expr.c gen.c interp.c main.c scan.c tree.c
	cc -o comp1 -g cg.c expr.c gen.c interp.c main.c scan.c tree.c

clean:
	rm -f comp1 *.o *.s out

test: comp1
	./comp1 Tests/input1
	cc -o out out.s
	./out
	./comp1 Tests/input2
	cc -o out out.s
	./out
