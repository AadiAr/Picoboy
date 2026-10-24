//
// Created by aadia on 18/10/2026.
//

#include <hardware/gpio.h>
#include <pico/stdlib.h>
#include <pico/audio_i2s.h>
#include <pico/audio.h>


void amp_init(audio_i2s_config_t *config, audio_format_t *format, audio_buffer_pool_t *buffer_pool) {
    audio_i2s_setup(format,config);
    audio_i2s_connect(buffer_pool);
    audio_i2s_set_enabled(1);
}

int16_t get_value(void) {
    return 0;
}

int16_t get_ch(uint index) {
    return 0;
}

void Update_Buffer(audio_buffer_pool_t *buffer_pool) {
    audio_buffer_t* buffer = take_audio_buffer(buffer_pool,false);
    if (!buffer) return;
    int16_t *samples = (int16_t *)buffer->buffer->bytes;
    uint32_t max_samples = buffer->max_sample_count;
    for (int i = 0; i < max_samples*2; i+=2) {
        int16_t ch1 = get_ch(1);
        int16_t ch2 = get_ch(2);
        int16_t ch3 = get_ch(3);
        int16_t ch4 = get_ch(4);
        int32_t mix = (ch1 + ch2 + ch3 + ch4)/4;
        samples[i] = (int16_t)mix;
        samples[i+1] = (int16_t)mix;
    }
    buffer->sample_count = buffer->max_sample_count;
    give_audio_buffer(buffer_pool,buffer);
}

