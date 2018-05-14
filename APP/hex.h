/* CC0 (Public domain) - see LICENSE file for details */
#ifndef CCAN_HEX_H
#define CCAN_HEX_H
#include <stdbool.h>
#include <stdlib.h>
#include "secp256k1.h"

/**
 * hex_decode - Unpack a hex string.
 * @str: the hexidecimal string
 * @slen: the length of @str
 * @buf: the buffer to write the data into
 * @bufsize: the length of @buf
 *
 * Returns false if there are any characters which aren't 0-9, a-f or A-F,
 * of the string wasn't the right length for @bufsize.
 *
 * Example:
 *	unsigned char data[20];
 *
 *	if (!hex_decode(argv[1], strlen(argv[1]), data, 20))
 *		printf("String is malformed!\n");
 */
bool hex_decode(const char *str, size_t slen, void *buf, size_t bufsize);

/**
 * hex_encode - Create a nul-terminated hex string
 * @buf: the buffer to read the data from
 * @bufsize: the length of @buf
 * @dest: the string to fill
 * @destsize: the max size of the string
 *
 * Returns true if the string, including terminator, fit in @destsize;
 *
 * Example:
 *	unsigned char buf[] = { 0x1F, 0x2F };
 *	char str[5];
 *
 *	if (!hex_encode(buf, sizeof(buf), str, sizeof(str)))
 *		abort();
 */
bool hex_encode(const void *buf, size_t bufsize, char *dest, size_t destsize);

/**
 * hex_str_size - Calculate how big a nul-terminated hex string is
 * @bytes: bytes of data to represent
 *
 * Example:
 *	unsigned char buf[] = { 0x1F, 0x2F };
 *	char str[hex_str_size(sizeof(buf))];
 *
 *	hex_encode(buf, sizeof(buf), str, sizeof(str));
 */
static SECP256K1_INLINE size_t hex_str_size(size_t bytes)
{
	return 2 * bytes + 1;
}

/**
 * hex_data_size - Calculate how many bytes of data in a hex string
 * @strlen: the length of the string (with or without NUL)
 *
 * Example:
 *	const char str[] = "1F2F";
 *	unsigned char buf[hex_data_size(sizeof(str))];
 *
 *	hex_decode(str, strlen(str), buf, sizeof(buf));
 */
static SECP256K1_INLINE size_t hex_data_size(size_t strlen)
{
	return strlen / 2;
}

bool char_to_hex(unsigned char *val, char c);
int wally_hex_from_bytes(const unsigned char *bytes, size_t bytes_len, char **output);
int wally_hex_to_bytes(const char *hex, unsigned char *bytes_out, size_t len, size_t *written);
void print_hexstr_key(char *tag, const unsigned char *in, uint16_t len);

#endif /* CCAN_HEX_H */
