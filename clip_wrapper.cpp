#include "clip_wrapper.h"
#include "clip.h"
#include <cstring>
#include <vector>

extern "C" {

bool clip_set_text(const char* text) {
    return clip::set_text(std::string(text));
}

bool clip_get_text(char* buffer, size_t length) {
    std::string text;
    if (clip::get_text(text)) {
        strncpy(buffer, text.c_str(), length);
        buffer[length - 1] = '\0'; // Ensure null-termination
        return true;
    }
    return false;
}

bool clip_set_image_rgba(const void* data, int width, int height) {
    clip::image_spec spec;
    spec.width = width;
    spec.height = height;
    spec.bits_per_pixel = 32;
    spec.bytes_per_row = width * 4;
    spec.red_mask = 0x000000ff;
    spec.green_mask = 0x0000ff00;
    spec.blue_mask = 0x00ff0000;
    spec.alpha_mask = 0xff000000;
    spec.red_shift = 0;
    spec.green_shift = 8;
    spec.blue_shift = 16;
    spec.alpha_shift = 24;

    clip::image img(data, spec);
    return clip::set_image(img);
}

}
