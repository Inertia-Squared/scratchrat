#ifndef CLIP_WRAPPER_H
#define CLIP_WRAPPER_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

bool clip_set_text(const char* text);
bool clip_get_text(char* buffer, size_t length);
bool clip_set_image_rgba(const void* data, int width, int height);

#ifdef __cplusplus
}
#endif

#endif // CLIP_WRAPPER_H
