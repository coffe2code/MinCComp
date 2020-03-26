#include "defs.h"
#define extern_
#include "data.h"
#undef extern_
#include "decl.h"
#include <errno.h>
#include <stdlib.h>

static void init() {
	Line = 1;
	Putback = '\n';
}

static void usage(char *prog) {
  fprintf(stderr, "Usage: %s infile\n", prog);
  exit(1);
}


char *tokstr[] = {"+", "-", "*", "/", "intlit"};

static void scanfile() {

	struct token T;

	while(scan(&T)) {
		printf("Token %s", tokstr[T.token]);
		if (T.token == T_INTLIT)
			printf(", value %d", T.intvalue);
		printf("\n");
	}
}

void main(int argc, char *argv[]) {
	struct ASTnode *tree;

	if (argc != 2)
		usage(argv[0]);

	init();

	Infile = fopen(argv[1], "r");

	if (Infile == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  	}

  	if ((Outfile = fopen("out.s", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
    exit(1);
  	}

  	scan(&Token);
  	genpreamble();
  	tree = compound_statement();
  	genAST(tree, NOREG, 0);
  	genpostamble();
  	fclose(Outfile);
  	exit(0);
}