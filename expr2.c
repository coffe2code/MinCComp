// This code imposes operator precedence by using
// recursive descent parsing.
#include "defs.h"
#include "data.h"
#include "decl.h"

static struct ASTnode *primary(void) {
  struct ASTnode *n;

  // For an INTLIT token, make a leaf AST node for it
  // and scan in the next token. Otherwise, a syntax error
  // for any other token type.
  switch (Token.token) {
  case T_INTLIT:
    n = mkastleaf(A_INTLIT, Token.intvalue);
    scan(&Token);
    return (n);
  default:
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, Token.token);
    exit(1);
  }
}


static int arithop(int tok) {
  switch (tok) {
  case T_PLUS:
    return (A_ADD);
  case T_MINUS:
    return (A_SUBTRACT);
  case T_STAR:
    return (A_MULTIPLY);
  case T_SLASH:
    return (A_DIVIDE);
  default:
    fprintf(stderr, "syntax error on line %d, token %d\n", Line, tok);
    exit(1);
  }
}

struct ASTnode *multiplicative_expr(void) {
	struct ASTnode *left, *right;
	int tokentype;

	left = primary();

	tokentype = Token.token;
	if(tokentype == T_EOF)
		return left;

	while ((tokentype == T_STAR) || (tokentype == T_SLASH)) {

		scan(&Token);
		right = primary();

		left = mkastnode(arithop(tokentype), left, right, 0);

		tokentype = Token.token;
		if (tokentype == T_EOF)
			break;
	}

	return left;
}


// Return an AST tree node whose root is a '+' or '-' binary operator

struct ASTnode *additive_expr(void) {
	struct ASTnode *left, *right;
	int tokentype;

	left = multiplicative_expr();

	tokentype = Token.token;
	if(tokentype == T_EOF)
		return left;

	while(1) {
		scan(&Token);

		right = multiplicative_expr();

		left = mkastnode(arithop(tokentype), left, right, 0);

		tokentype = Token.token;
		if(tokentype == T_EOF)
			break;
	}


	return left;
}



struct ASTnode *binexpr(int n) {
	return additive_expr();
}