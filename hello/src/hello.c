#include <stdio.h>
#include <unistd.h>

#define BUFFER 256

int main() {
	char hostname[BUFFER];
	gethostname(hostname, sizeof(hostname));

	printf("Hello from %s!\n", hostname);
}
