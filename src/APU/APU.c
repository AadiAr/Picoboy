//
// Created by aadia on 18/10/2026.
//

#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include <pico/audio_i2s.h>
#include <pico/audio.h>


void amp_init(audio_i2s_config_t *config, audio_format_t *format, audio_buffer_pool_t *buffer_pool) {
    audio_i2s_set_enabled(1);
    audio_i2s_setup(format,config);
    audio_i2s_connect(buffer_pool);
}

void Update_Buffer(audio_buffer_pool_t *buffer_pool) {
    audio_buffer_t* buffer = take_audio_buffer(buffer_pool,false);
    if (!buffer) return;
    int16_t *samples = (int16_t *)buffer->buffer->bytes;
    uint32_t max_samples = buffer->max_sample_count;


}

