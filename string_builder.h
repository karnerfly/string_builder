#ifndef STRING_BUILDER_H_
#define STRING_BUILDER_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *items;
    size_t count;
    size_t capacity;
} String_Builder;

#define da_alloc(da, size)       \
do                               \
{                                \
(da)->items = malloc((size));    \
(da)->count = 0;                 \
(da)->capacity = (size);         \
} while(0)                       \

#define da_resize(da, cap)                    \
do                                            \
{                                             \
(da)->items = realloc((da)->items, (cap));    \
(da)->capacity = (cap);                       \
} while(0)                                    \

#define da_append(da, item, cap)                       \
do                                                     \
{                                                      \
if ((cap) >= (da)->capacity)                           \
{                                                      \
(da)->capacity *= 2;                                   \
(da)->items = realloc((da)->items, (da)->capacity);    \
}                                                      \
(da)->items[(da)->count++] = (item);                   \
} while(0)                                             \

#define da_uninitialized(da) (da)->items == NULL ? true : false

void sb_append(String_Builder *sb, const char *str);
void sb_append_field(String_Builder *sb, const char *str);
void sb_append_at(String_Builder *sb, const char ch, size_t at);


void sb_append(String_Builder *sb, const char *str)
{
    if (da_uninitialized(sb))
    	da_alloc(sb, strlen(str) + 1);

    for (size_t i = 0; str[i] != '\0'; ++i) {
        da_append(sb, str[i], sb->count + 1);
    }
}

void sb_append_field(String_Builder *sb, const char *str)
{
    if (da_uninitialized(sb))
    	da_alloc(sb, strlen(str) + 1);

    for (size_t i = 0; str[i] != '\0'; ++i) {
        da_append(sb, str[i], sb->count + 1);
    }

    da_append(sb, ' ', sb->count + 1);
}

void sb_append_at(String_Builder *sb, const char ch, size_t at)
{
    if (at <= sb->count) {
        if (sb->capacity - (sb->count + 1) == 0)
        	da_resize(sb, sb->capacity + 1);

        int i = (int)sb->count;
        for (; i >= (int)at; --i) {
            sb->items[i + 1] = sb->items[i];
        }

        sb->items[i + 1] = ch;
        sb->count++;
    }
}

#endif
