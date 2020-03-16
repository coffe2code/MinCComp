#include "defs.h"
#include "data.h"
#include "decl.h"

static int Globs = 0;  // Position of next free global symbol list


// Determine if symbol s in in the global symbol table
// Return it's slot position or -1 if not found

int findglob(char *s) {
	int i;

	for(i = 0; i<Globs; i++) {
		if (*s == *Gsym[i].name && !strcmp(s, Gsym[i].name))
			return i;
	}

	return -1;		
}

// Get the position of a new global symbol slot

static int newglob(void) {
	int p;

	if((p = Globs++) >= NSYMBOLS)
		fatal("Too many global symbols");
	return p;
}

int addglob(char *name) {
	int y;

	if((y = findglob(name)) != -1)
		return y;

	y = newglob();
	Gsym[y].name = strdup(name);
	return y;
}