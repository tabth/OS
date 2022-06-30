#ifndef _FRAMEBUFFER_H
#define _FRAMEBUFFER_H 1

#include <kernel/bootloader.h>

#define POINT(x, y) (Point){.x = (_x), .y = (_y)}

typedef uint8_t byte;
typedef int8_t sbyte;

typedef struct Point {
    long x;
    long y;
} Point;


typedef struct Color {
    byte red, green, blue, alpha;
} Color;

typedef struct Rectangle {
    Point position;
    Point size;
} Rect;

typedef struct Framebuffer {
    Point size;
    uint16_t bits_per_pixel, pitch;
    byte memory_model, *pixels;

    struct {
        struct { byte size, shift; } red;
        struct { byte size, shift; } green;
        struct { byte size, shift; } blue;
    } masks;

    struct {
        struct stivale2_header_tag_framebuffer* header;
        struct stivale2_struct_tag_framebuffer* data;
    } bootloader;
} Framebuffer;

static inline struct Framebuffer Framebuffer_initialise(const BootloaderInfo_t *bl);
static inline uint32_t color_to_u32(Color col);
static void Framebuffer_draw_rect(const struct Framebuffer* fb, Rect rect, Color color);
static inline void Framebuffer_set_background(const struct Framebuffer* fb, Color color);

static inline void Framebuffer_draw_pixel(const struct Framebuffer* fb, Point pos, Color color);

void Framebuffer_draw_character(const struct Framebuffer *fb, char c);

#endif // !_FRAMEBUFFER_H