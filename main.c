/*
 * main.c
 *
 *  Created on: Jul 29, 2014
 *      Author: hafiz
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "fsj.h"
#include "dbg.h"

void print_usage() {
	char *usage =
			"USAGE: hfsj [split|join] [file_name/0index_file] [number of peices]\n";
	printf(usage);
}

int main(int argc, char **argv) {
	check(argc >= 3, "Invalid command %d arguments supplied", argc);

	int peices;
	if (strcmp(argv[1], "-s") == 0) {
		check(argc >= 4, "Invalid command");

		peices = atoi(argv[3]);
		check(peices>1, "peices must be greater than one");

		fsj_split(argv[2], peices);
	} else if (strcmp(argv[1], "-j") == 0) {

		char *out_filename = "";
		if(argc>4 && strcmp(argv[3], "-o") == 0)
			out_filename = argv[4];

		fsj_join(argv[2], out_filename);
	}

	return 0;



	error: print_usage();
	return 0;
}
