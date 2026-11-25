/*
 *
 * MIT License
 *
 * Copyright (c) 2026 Mika Tuupola
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * -cut-
 *
 * This file is part of libdrip: https://github.com/tuupola/libdrip
 *
 * SPDX-License-Identifier: MIT
 *
 */

#ifndef DRIP_JSON_H
#define DRIP_JSON_H

#ifndef DRIP_DISABLE_JSON

#include <stddef.h>
#include <stdint.h>

typedef struct drip_json {
    char *buffer;
    size_t buffer_size;
    size_t position;
    uint8_t need_comma;
} drip_json_t;

void drip_json_start(drip_json_t *json, char *buffer, size_t buffer_size);
int drip_json_end(drip_json_t *json);
void drip_json_array_start(drip_json_t *json);
void drip_json_array_end(drip_json_t *json);
void drip_json_key(drip_json_t *json, const char *key);
void drip_json_uint(drip_json_t *json, unsigned value);
void drip_json_string(drip_json_t *json, const char *string);
void drip_json_hex(drip_json_t *json, const uint8_t *data, size_t data_size);
void drip_json_uuid(drip_json_t *json, const uint8_t *uuid);
void drip_json_null(drip_json_t *json);
void drip_json_raw(drip_json_t *json, const char *token, size_t token_length);

#endif /* DRIP_DISABLE_JSON */

#endif /* DRIP_JSON_H */
