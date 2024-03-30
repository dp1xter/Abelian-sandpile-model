#pragma once
#include "parser.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <filesystem>

static const size_t kSandCollapseNum = 4;
static const size_t kBufferSize = 64;
static const size_t kMaxLengthFileName = 40;

struct Point {
    int64_t x;
    int64_t y;
    uint64_t count_of_sand;
};

struct Points {
    Point* points_array;
    size_t points_array_length;
};

struct Field {
    size_t rows = 0;
    size_t columns = 0;
    uint64_t** array_cells;
    bool** status_cells;

    explicit Field(Points& info_array_points);

    ~Field();
};

enum class FieldBorder {
    kLeftBorder,
    kRightBorder,
    kTopBorder,
    kBottomBorder
};

std::filesystem::path MergeFilePath(const std::filesystem::path& file_path, size_t current_iteration);

bool CheckFieldStatus(Field& field);

Points GetArrayOfPoints(const Config& options);

void FieldExtension(Field& field, const FieldBorder& direction_expansion);

void CollapseAndCallExtension(Field& field, size_t& current_row, size_t& current_column);

void UpdateIterationAndCallBmp(const Config& options, Field& field, size_t& current_row,
                               size_t& current_iteration, bool& continue_flag);

void ProcessIterations(const Config& options, Field& field);
