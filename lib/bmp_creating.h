#pragma once
#include "process_iterations.h"
#include <iostream>

static const size_t kAsciiBitmapFormat = 0x4D42;
static const size_t kIndexOfBlackColor = 4;
static const size_t kFileHeaderSize = 14;
static const size_t kFileInfoHeaderSize = 40;
static const size_t kPaletteSize = 20;

#pragma pack(push, 1)
struct BmpFileHeader {
    uint16_t bf_type;
    uint32_t bf_size;
    uint16_t bf_reserved1 = 0;
    uint16_t bf_reserved2 = 0;
    uint32_t bf_off_bits;

    explicit BmpFileHeader(size_t pixels_data_size);

    char* Serialize() const;
};

struct BmpInfoHeader {
    uint32_t bi_size;
    int32_t bi_width;
    int32_t bi_height;
    uint16_t bi_planes = 1;
    uint16_t bi_bit_count = 4;
    uint32_t bi_compression = 0;
    uint32_t bi_size_image;
    int32_t bi_x_pels_per_meter = 0;
    int32_t bi_y_pels_per_meter = 0;
    uint32_t bi_color_used = 5;
    uint32_t bi_color_important = 5;

    BmpInfoHeader(const Field& field, size_t pixels_data_size);

    char* Serialize() const;
};
#pragma pack(pop)

static const unsigned char palette_array[kPaletteSize] = {
        255, 255, 255, 0,
        0, 255, 0, 0,
        0, 255, 255, 0,
        255, 0, 255, 0,
        0, 0, 0, 0
};

void CreateFileBMP(const Field& field, const std::filesystem::path& file_bmp_path);