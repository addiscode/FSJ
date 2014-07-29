/*
 * fsj.c
 *
 *  Created on: Jul 29, 2014
 *      Author: hafiz
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include "dbg.h"

#define BUFFER_SIZE 8096


int fsj_split(char *file_path, int peices) {
	printf("Split file to : %d peices\n", peices);
	FILE *fh = fopen(file_path, "rb");

	void *buffer = malloc(BUFFER_SIZE);

	struct stat stbuf;

	int stat_rs = stat(file_path, &stbuf);

	check(stat_rs != -1, "Failed to get stat");

	const double p_size = ceil(stbuf.st_size / peices);

	int i = 0;
	char *p_name = malloc(60);

	long cur_pos = 0;
	long bf_size;
	long max_ftell;
	for (; i < peices; i++) {
		sprintf(p_name, "%s.%d", file_path, i);
		bf_size = BUFFER_SIZE;
		if (i == peices - 1)
			max_ftell = stbuf.st_size;
		else
			max_ftell = p_size * (i + 1);

		cur_pos = ftell(fh);

		FILE *fp = fopen(p_name, "wb");

		while (ftell(fh) <= max_ftell && fread(buffer, bf_size, 1, fh)) {
			fwrite(buffer, bf_size, 1, fp);
			if ((max_ftell - ftell(fh)) < BUFFER_SIZE)
				bf_size = max_ftell - ftell(fh);

			if (bf_size != BUFFER_SIZE)
				printf("BUFFER SIZE: %d\n", bf_size);

		}

		fclose(fp);
		printf("peice_name: %s\n", p_name);
	}

	printf("File size: %d\n", stbuf.st_size);

	free(buffer);
	fclose(fh);
	return 0;

	error: return 0;
}

int fsj_join(char *file_path) {
	int peices = 3, i = 0;
	long buf_size;
	char *p_name = malloc(60);
	char *mf_name = malloc(60);

	sprintf(mf_name, "%s-hfj", file_path);

	log_info("Joining files to: %s", mf_name);
	FILE *fh = fopen(mf_name, "wb");

	void *buffer = malloc(BUFFER_SIZE);
	struct stat stbuf;
	for (; i < peices; i++) {
		buf_size = BUFFER_SIZE;
		sprintf(p_name, "%s.%d", file_path, i);
		log_info("Peice: %s", p_name);

		int stat_rs = stat(p_name, &stbuf);
		check(stat_rs != -1, "Failed to get stat");

		FILE *fp = fopen(p_name, "rb");

		while (fread(buffer, buf_size, 1, fp)) {
			fwrite(buffer, buf_size, 1, fh);

			if ((stbuf.st_size - ftell(fp)) < BUFFER_SIZE) {
				buf_size = stbuf.st_size - ftell(fp);
				printf("BUFFER SIZE: %d\n", buf_size);
			}

//			log_info("file_size: %d cur_pos: %d", stbuf.st_size, ftell(fp));
		}

		fclose(fp);

	}

	free(p_name);
	free(mf_name);
	free(buffer);
	fclose(fh);
	return 0;

	error: return 0;
	return 0;
}
