#include <framebuffer/framebuffer.h>


static inline struct Framebuffer Framebuffer_initialise(const BootloaderInfo_t *bl) {
    struct stivale2_struct_tag_framebuffer* data = stivale2_get_tag(bl, STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID);

    return (Framebuffer) {
        .size = {data->framebuffer_width, data->framebuffer_height},
        .bits_per_pixel = data->framebuffer_bpp,
        .memory_model = data->memory_model,
        .pitch = data->framebuffer_pitch,
        .pixels = (byte*)data->framebuffer_addr,

        .masks = {
            .red = {data->red_mask_shift, data->red_mask_size},
            .green = {data->green_mask_shift, data->green_mask_size},
            .blue = {data->blue_mask_shift, data->blue_mask_size},
        },

        .bootloader = {
            .header = stivale2_get_tag(bl, STIVALE2_HEADER_TAG_FRAMEBUFFER_ID),
            .data = data
        }
    };
}

static inline uint32_t color_to_u32(Color col) {
    return (col.blue << 24) | (col.green << 16) | (col.red << 8) | col.alpha;
}

static void Framebuffer_draw_rect(const struct Framebuffer* fb, Rect rect, Color color) {
    for (uint32_t x = rect.position.x; x < rect.position.x + rect.size.x; x++) {
        for (uint32_t y = rect.position.y; y < rect.position.y + rect.size.y; y++) {
            fb->pixels[x * 0x4 + y*fb->pitch] = color_to_u32(color);
        }
    }
}

static inline void Framebuffer_set_background(const struct Framebuffer* fb, Color color) {
    Framebuffer_draw_rect(fb, (Rect){{0, 0}, fb->size}, color);
}

static inline void Framebuffer_draw_pixel(const struct Framebuffer* fb, Point pos, Color color) {
    fb->pixels[pos.x * 0x4 + pos.y * fb->pitch] = color_to_u32(color);
}