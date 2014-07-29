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

	if (strcmp(argv[1], "-s") == 0) {
		check(argc >= 4, "Invalid command");

		fsj_split(argv[2], 3);
	} else if (strcmp(argv[1], "-j") == 0) {
		fsj_join(argv[2]);
	}

	return 0;



	error: print_usage();
	return 0;
}
