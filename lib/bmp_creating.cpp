#include "bmp_creating.h"

BmpFileHeader::BmpFileHeader(size_t pixels_data_size) {
    bf_type = kAsciiBitmapFormat;
    bf_size = kFileHeaderSize + kFileInfoHeaderSize + kPaletteSize + pixels_data_size;
    bf_off_bits = kFileHeaderSize + kFileInfoHeaderSize + kPaletteSize;
}

BmpInfoHeader::BmpInfoHeader(const Field& field, size_t pixels_data_size) {
    bi_size = kFileInfoHeaderSize;
    bi_width = static_cast<int32_t> (field.columns);
    bi_height = static_cast<int32_t> (field.rows);
    bi_size_image = pixels_data_size;
}

char* BmpFileHeader::Serialize() const {
    static char header_byte_array[kFileHeaderSize];

    header_byte_array[0] = static_cast<char> (bf_type & 0xFF);
    header_byte_array[1] = static_cast<char> ((bf_type >> 8) & 0xFF);

    header_byte_array[2] = static_cast<char> (bf_size & 0xFF);
    header_byte_array[3] = static_cast<char> ((bf_size >> 8) & 0xFF);
    header_byte_array[4] = static_cast<char> ((bf_size >> 16) & 0xFF);
    header_byte_array[5] = static_cast<char> ((bf_size >> 24) & 0xFF);

    header_byte_array[6] = static_cast<char> (bf_reserved1 & 0xFF);
    header_byte_array[7] = static_cast<char> ((bf_reserved1 >> 8) & 0xFF);

    header_byte_array[8] = static_cast<char> (bf_reserved2 & 0xFF);
    header_byte_array[9] = static_cast<char> ((bf_reserved2 >> 8) & 0xFF);

    header_byte_array[10] = static_cast<char> (bf_off_bits & 0xFF);
    header_byte_array[11] = static_cast<char> ((bf_off_bits >> 8) & 0xFF);
    header_byte_array[12] = static_cast<char> ((bf_off_bits >> 16) & 0xFF);
    header_byte_array[13] = static_cast<char> ((bf_off_bits >> 24) & 0xFF);

    return header_byte_array;
}

char* BmpInfoHeader::Serialize() const {
    static char header_info_byte_array[kFileInfoHeaderSize];

    header_info_byte_array[0] = static_cast<char> (bi_size & 0xFF);
    header_info_byte_array[1] = static_cast<char> ((bi_size >> 8) & 0xFF);
    header_info_byte_array[2] = static_cast<char> ((bi_size >> 16) & 0xFF);
    header_info_byte_array[3] = static_cast<char> ((bi_size >> 24) & 0xFF);

    header_info_byte_array[4] = static_cast<char> (bi_width & 0xFF);
    header_info_byte_array[5] = static_cast<char> ((bi_width >> 8) & 0xFF);
    header_info_byte_array[6] = static_cast<char> ((bi_width >> 16) & 0xFF);
    header_info_byte_array[7] = static_cast<char> ((bi_width >> 24) & 0xFF);

    header_info_byte_array[8] = static_cast<char> (bi_height & 0xFF);
    header_info_byte_array[9] = static_cast<char> ((bi_height >> 8) & 0xFF);
    header_info_byte_array[10] = static_cast<char> ((bi_height >> 16) & 0xFF);
    header_info_byte_array[11] = static_cast<char> ((bi_height >> 24) & 0xFF);

    header_info_byte_array[12] = static_cast<char> (bi_planes & 0xFF);
    header_info_byte_array[13] = static_cast<char> ((bi_planes >> 8) & 0xFF);

    header_info_byte_array[14] = static_cast<char> (bi_bit_count & 0xFF);
    header_info_byte_array[15] = static_cast<char> ((bi_bit_count >> 8) & 0xFF);

    header_info_byte_array[16] = static_cast<char> (bi_compression & 0xFF);
    header_info_byte_array[17] = static_cast<char> ((bi_compression >> 8) & 0xFF);
    header_info_byte_array[18] = static_cast<char> ((bi_compression >> 16) & 0xFF);
    header_info_byte_array[19] = static_cast<char> ((bi_compression >> 24) & 0xFF);

    header_info_byte_array[20] = static_cast<char> (bi_size_image & 0xFF);
    header_info_byte_array[21] = static_cast<char> ((bi_size_image >> 8) & 0xFF);
    header_info_byte_array[22] = static_cast<char> ((bi_size_image >> 16) & 0xFF);
    header_info_byte_array[23] = static_cast<char> ((bi_size_image >> 24) & 0xFF);

    header_info_byte_array[24] = static_cast<char> (bi_x_pels_per_meter & 0xFF);
    header_info_byte_array[25] = static_cast<char> ((bi_x_pels_per_meter >> 8) & 0xFF);
    header_info_byte_array[26] = static_cast<char> ((bi_x_pels_per_meter >> 16) & 0xFF);
    header_info_byte_array[27] = static_cast<char> ((bi_x_pels_per_meter >> 24) & 0xFF);

    header_info_byte_array[28] = static_cast<char> (bi_y_pels_per_meter & 0xFF);
    header_info_byte_array[29] = static_cast<char> ((bi_y_pels_per_meter >> 8) & 0xFF);
    header_info_byte_array[30] = static_cast<char> ((bi_y_pels_per_meter >> 16) & 0xFF);
    header_info_byte_array[31] = static_cast<char> ((bi_y_pels_per_meter >> 24) & 0xFF);

    header_info_byte_array[32] = static_cast<char> (bi_color_used & 0xFF);
    header_info_byte_array[33] = static_cast<char> ((bi_color_used >> 8) & 0xFF);
    header_info_byte_array[34] = static_cast<char> ((bi_color_used >> 16) & 0xFF);
    header_info_byte_array[35] = static_cast<char> ((bi_color_used >> 24) & 0xFF);

    header_info_byte_array[36] = static_cast<char> (bi_color_important & 0xFF);
    header_info_byte_array[37] = static_cast<char> ((bi_color_important >> 8) & 0xFF);
    header_info_byte_array[38] = static_cast<char> ((bi_color_important >> 16) & 0xFF);
    header_info_byte_array[39] = static_cast<char> ((bi_color_important >> 24) & 0xFF);

    return header_info_byte_array;
}

void CreateFileBMP(const Field& field, const std::filesystem::path& file_bmp_path) {
    std::ofstream file_bmp(file_bmp_path, std::ios::binary);

    const size_t row_length = field.columns / 2 + field.columns % 2;
    const size_t padding_row = (4 - (row_length % 4)) % 4;
    const size_t pixels_data_size = (row_length + padding_row) * field.rows;

    const BmpFileHeader file_header = BmpFileHeader(pixels_data_size);
    const BmpInfoHeader file_info_header = BmpInfoHeader(field, pixels_data_size);

    file_bmp.write(file_header.Serialize(), kFileHeaderSize);
    file_bmp.write(file_info_header.Serialize(), kFileInfoHeaderSize);
    file_bmp.write(reinterpret_cast<const char*> (palette_array), kPaletteSize);

    char* pixels_data = new char[pixels_data_size];
    char* current_two_pixels = pixels_data;

    for (int i = 0; i < field.rows; ++i) {
        for (int j = 0; j < field.columns; j += 2) {
            uint64_t first_pixel = std::min(static_cast<int64_t> (field.array_cells[i][j]),
                                            static_cast<int64_t> (kIndexOfBlackColor));
            uint64_t second_pixel = 0;
            if (j + 1 < field.columns) {
                second_pixel = std::min(static_cast<int64_t> (field.array_cells[i][j+1]),
                                        static_cast<int64_t> (kIndexOfBlackColor));
            }
            *current_two_pixels = static_cast<char> (first_pixel << 4 | second_pixel);
            ++current_two_pixels;
        }
        current_two_pixels += padding_row;
    }

    file_bmp.write(pixels_data, static_cast<int64_t> (pixels_data_size));

    delete[] pixels_data;

    file_bmp.close();
}