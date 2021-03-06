/*
 * Copyright (c) 2014-2015 Pavel Kalvoda <me@pavelkalvoda.com>
 *
 * libcbor is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include "cbor.h"
#include <stdio.h>

void usage()
{
	printf("Usage: readfile [input file]\n");
	exit(1);
}

/*
 * Reads data from a file. Example usage:
 * $ ./examples/readfile examples/data/nested_array.cbor
 */

int main(int argc, char * argv[])
{
	if (argc != 2)
		usage();
	FILE * f = fopen(argv[1], "rb");
	if (f == NULL)
		usage();
	fseek(f, 0, SEEK_END);
	size_t length = (size_t)ftell(f);
	fseek(f, 0, SEEK_SET);
	unsigned char * buffer = malloc(length);
	fread(buffer, length, 1, f);

	/* Assuming `buffer` contains `length` bytes of input data */
	struct cbor_load_result result;
	cbor_item_t * item = cbor_load(buffer, length, &result);
	/* Pretty-print the result */
	cbor_describe(item, stdout);
	fflush(stdout);
	/* Deallocate the result */
	cbor_decref(&item);

	fclose(f);
}
