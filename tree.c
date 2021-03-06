#include "defs.h"
#include "data.h"
#include "decl.h"

// Build and return an AST node

struct ASTnode *mkastnode(int op, struct ASTnode* left,
						  struct ASTnode *mid,
						  struct ASTnode* right, int intvalue) {
	struct ASTnode *n;

	n = (struct ASTnode *) malloc(sizeof(struct ASTnode));

	if (n==NULL) {
		fprintf(stderr, "Unable to malloc in mkastnode()\n" );
		exit(1);
	}

	n->op = op;
	n->left = left;
	n->mid = mid;
	n->right = right;
	n->v.intvalue = intvalue;

	return n;
}

struct ASTnode *mkastleaf(int op, int intvalue) {
	return (mkastnode(op, NULL, NULL, NULL, intvalue));
}

struct ASTnode *mkastunary(int op, struct ASTnode* left, int intvalue) {
	return (mkastnode(op, left, NULL, NULL, intvalue));
}