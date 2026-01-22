#ifndef SAFE_STRING_H
#define SAFE_STRING_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Safe string copy with bounds checking
 * @param dest Destination buffer
 * @param src Source string
 * @param dest_size Size of destination buffer (including null terminator)
 * @return Number of characters copied
 */
static inline int safe_strcpy(char *dest, const char *src, size_t dest_size) {
    if (!dest || !src || dest_size == 0) return 0;
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
    return strlen(dest);
}

/**
 * Safe formatted string copy
 * @param dest Destination buffer
 * @param dest_size Size of destination buffer
 * @param format Format string
 * @return Number of characters written (excluding null terminator)
 */
#define safe_sprintf(dest, dest_size, format, ...) \
    snprintf(dest, dest_size, format, __VA_ARGS__)

/**
 * Allocate and copy string safely
 * @param src Source string to duplicate
 * @return Newly allocated string, caller must free()
 */
static inline char* safe_strdup(const char *src) {
    if (!src) return NULL;
    size_t len = strlen(src) + 1;
    char *dup = (char *)malloc(len);
    if (dup) {
        strncpy(dup, src, len - 1);
        dup[len - 1] = '\0';
    }
    return dup;
}

/**
 * Clear string by setting to null terminator
 * @param str String buffer to clear
 * @param size Size of buffer
 */
static inline void clear_string(char *str, size_t size) {
    if (str && size > 0) {
        str[0] = '\0';
    }
}

#endif
