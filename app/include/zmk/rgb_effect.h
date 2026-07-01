/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <zephyr/drivers/led_strip.h>
#include <zmk/rgb_underglow.h>

struct zmk_rgb_effect_ctx {
    struct led_rgb *pixels;
    uint16_t num_pixels;
    struct zmk_led_hsb base_color;
    uint16_t *animation_step;
    uint8_t animation_speed;
};

typedef void (*zmk_rgb_effect_render_fn)(struct zmk_rgb_effect_ctx *ctx);
typedef void (*zmk_rgb_effect_event_fn)(void);

#define ZMK_RGB_EFFECT_STATIC BIT(0)

struct zmk_rgb_effect {
    const char *name;
    zmk_rgb_effect_render_fn render;
    zmk_rgb_effect_event_fn on_select;
    zmk_rgb_effect_event_fn on_deselect;
    uint8_t flags;
};

#define ZMK_RGB_EFFECT_DEFINE(_sym, _name_str, _render, _flags, _on_select, _on_deselect)          \
    STRUCT_SECTION_ITERABLE(zmk_rgb_effect, _sym) = {                                              \
        .name = _name_str,                                                                         \
        .render = _render,                                                                         \
        .flags = _flags,                                                                           \
        .on_select = _on_select,                                                                   \
        .on_deselect = _on_deselect,                                                               \
    }

void zmk_rgb_request_refresh(void);
int zmk_rgb_effect_get_count(void);

struct led_rgb zmk_rgb_hsb_to_rgb(struct zmk_led_hsb hsb);
struct zmk_led_hsb zmk_rgb_hsb_scale_min_max(struct zmk_led_hsb hsb);
struct zmk_led_hsb zmk_rgb_hsb_scale_zero_max(struct zmk_led_hsb hsb);
