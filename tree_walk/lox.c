#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BUFSIZE 1024

void
usage(const char *program_name) {
	fprintf(stderr, "Usage: %s [script]\n", program_name);
}

void
error(int line_number, const char *message) {
	fprintf(stderr, "%d: %s\n", line_number, message);
}

void
run(const char source[BUFSIZE]) {
	printf("got source: %s", source);
}

void
run_file(const char *file_name) {
	FILE *fp = fopen(file_name, "r");
	int file_len;
	if (fp == NULL) {
		fprintf(stderr, "Error opening %s file\n", file_name);
		exit(66);
	}
	fseek(fp, 0, SEEK_END); // move fp to the eof
	file_len = ftell(fp); // read fp pos
	fseek(fp, 0, SEEK_SET); // rewind to the beginning
	assert(BUFSIZE > file_len && "Error: buffer size too small");
	char buffer[BUFSIZE] = {0};
	int bytes_read = fread(buffer, 1, file_len, fp);
	assert(bytes_read == file_len && "Error: bytes read differ from file length");
	run(buffer);
}

void
run_prompt() {
	char input[BUFSIZE];
	for (;;) {
		printf("> ");
		fgets(input, BUFSIZE, stdin);
		run(input);
	}
}

int
main(int argc, char **argv) {
	if (argc > 2) {
		usage(argv[0]);
		exit(64);
	} else if (argc == 2) {
		run_file(argv[1]);
	} else {
		run_prompt();
	}
	return 0;
}
