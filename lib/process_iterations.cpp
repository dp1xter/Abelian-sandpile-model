#include "process_iterations.h"
#include "bmp_creating.h"

Field::Field(Points& info_array_points) {
    int64_t right_point = info_array_points.points_array[0].x;
    int64_t top_point = info_array_points.points_array[0].y;
    int64_t left_point_x = info_array_points.points_array[0].x;
    int64_t bottom_point_y = info_array_points.points_array[0].y;

    for (int i = 0; i < info_array_points.points_array_length; ++i) {
        if (info_array_points.points_array[i].x < left_point_x) {
            left_point_x = info_array_points.points_array[i].x;
        }
        if (info_array_points.points_array[i].y < bottom_point_y) {
            bottom_point_y = info_array_points.points_array[i].y;
        }
    }

    for (int i = 0; i < info_array_points.points_array_length; ++i) {
        info_array_points.points_array[i].x -= left_point_x;
        info_array_points.points_array[i].y -= bottom_point_y;
        right_point = std::max(static_cast<int64_t> (info_array_points.points_array[i].x),
                               static_cast<int64_t> (right_point));
        top_point = std::max(static_cast<int64_t> (info_array_points.points_array[i].y),
                             static_cast<int64_t> (top_point));
    }

    rows = top_point + 1;
    columns = right_point + 1;

    array_cells = new uint64_t*[rows];
    status_cells = new bool*[rows];

    for (int i = 0; i < rows; ++i) {
        array_cells[i] = new uint64_t[columns]{};
        status_cells[i] = new bool[columns]{};
    }

    for (int i = 0; i < info_array_points.points_array_length; ++i) {
        array_cells[info_array_points.points_array[i].y][info_array_points.points_array[i].x] = info_array_points.points_array[i].count_of_sand;
    }
}

Field::~Field() {
    for (int i = 0; i < rows; ++i) {
        delete[] array_cells[i];
        delete[] status_cells[i];
    }

    delete[] array_cells;
    delete[] status_cells;
}

std::filesystem::path MergeFilePath(const std::filesystem::path& file_path, size_t current_iteration) {
    std::filesystem::path merged_path = file_path;
    char file_name[kMaxLengthFileName];
    sprintf(file_name, "\\sandpile_%d.bmp", static_cast<int32_t> (current_iteration));
    merged_path.concat(file_name);

    return merged_path;
}

Points GetArrayOfPoints(const Config& options) {
    std::ifstream file_tsv(options.input_file);
    char buffer[kBufferSize];
    size_t count_of_points = 0;

    while(!file_tsv.eof()) {
        file_tsv.getline(buffer, kBufferSize, '\n');
        ++count_of_points;
    }
    file_tsv.seekg(std::ios::beg);

    Points info_array_points = {new Point[count_of_points], count_of_points};
    size_t current_point_index = 0;
    int16_t x;
    int16_t y;
    uint64_t count_of_sand;

    while (file_tsv >> x >> y >> count_of_sand) {
        info_array_points.points_array[current_point_index++] = {x, y, count_of_sand};
    }

    file_tsv.close();

    return info_array_points;
}

bool CheckFieldStatus(Field& field) {
    bool status = false;

    for (int i = 0; i < field.rows; ++i) {
        for (int j = 0; j < field.columns; ++j) {
            field.status_cells[i][j] = (field.array_cells[i][j] >= kSandCollapseNum);
            if (field.status_cells[i][j]) {
                status = true;
            }
        }
    }

    return status;
}

void FieldExtension(Field& field, const FieldBorder& direction_expansion) {
    size_t old_rows = field.rows;
    uint64_t** new_array_cells;
    bool** new_status_cells;

    if (direction_expansion == FieldBorder::kLeftBorder) {
        ++field.columns;
        new_array_cells = new uint64_t*[field.rows];
        new_status_cells = new bool*[field.rows];

        for (int i = 0; i < field.rows; ++i) {
            new_array_cells[i] = new uint64_t[field.columns]{};
            new_status_cells[i] = new bool[field.columns]{};

            for (int j = 1; j < field.columns; ++j) {
                new_array_cells[i][j] = field.array_cells[i][j-1];
                new_status_cells[i][j] = field.status_cells[i][j-1];
            }
        }
    } else if (direction_expansion == FieldBorder::kRightBorder) {
        ++field.columns;
        new_array_cells = new uint64_t*[field.rows];
        new_status_cells = new bool*[field.rows];

        for (int i = 0; i < field.rows; ++i) {
            new_array_cells[i] = new uint64_t[field.columns]{};
            new_status_cells[i] = new bool[field.columns]{};

            for (int j = 0; j < field.columns - 1; ++j) {
                new_array_cells[i][j] = field.array_cells[i][j];
                new_status_cells[i][j] = field.status_cells[i][j];
            }
        }
    } else if (direction_expansion == FieldBorder::kTopBorder) {
        ++field.rows;
        new_array_cells = new uint64_t*[field.rows];
        new_status_cells = new bool*[field.rows];

        for (int i = 0; i < field.rows; ++i) {
            new_array_cells[i] = new uint64_t[field.columns]{};
            new_status_cells[i] = new bool[field.columns]{};

            for (int j = 0; j < field.columns && i < field.rows - 1; ++j) {
                new_array_cells[i][j] = field.array_cells[i][j];
                new_status_cells[i][j] = field.status_cells[i][j];
            }
        }
    } else {
        ++field.rows;
        new_array_cells = new uint64_t*[field.rows];
        new_status_cells = new bool*[field.rows];

        for (int i = 0; i < field.rows; ++i) {
            new_array_cells[i] = new uint64_t[field.columns]{};
            new_status_cells[i] = new bool[field.columns]{};

            for (int j = 0; j < field.columns && i; ++j) {
                new_array_cells[i][j] = field.array_cells[i-1][j];
                new_status_cells[i][j] = field.status_cells[i-1][j];
            }
        }
    }

    for (int i = 0; i < old_rows; ++i) {
        delete[] field.array_cells[i];
        delete[] field.status_cells[i];
    }

    delete[] field.array_cells;
    delete[] field.status_cells;

    field.status_cells = new_status_cells;
    field.array_cells = new_array_cells;
}

void CollapseAndCallExtension(Field& field, size_t& current_row, size_t& current_column) {
    if (!current_column) {
        FieldExtension(field, FieldBorder::kLeftBorder);
        ++current_column;
    }
    if (!current_row) {
        FieldExtension(field, FieldBorder::kBottomBorder);
        ++current_row;
    }
    if (current_column == field.columns - 1) {
        FieldExtension(field, FieldBorder::kRightBorder);
    }
    if(current_row == field.rows - 1) {
        FieldExtension(field, FieldBorder::kTopBorder);
    }

    ++field.array_cells[current_row - 1][current_column];
    ++field.array_cells[current_row + 1][current_column];
    ++field.array_cells[current_row][current_column - 1];
    ++field.array_cells[current_row][current_column + 1];
    field.array_cells[current_row][current_column] -= kSandCollapseNum;
}

void UpdateIterationAndCallBmp(const Config& options, Field& field, size_t& current_row,
                               size_t& current_iteration, bool& continue_flag) {
    if (current_row != field.rows) {
        return;
    }

    continue_flag = CheckFieldStatus(field);
    ++current_iteration;

    if (current_iteration < options.maximum_iterations && continue_flag) {
        current_row = 0;
    }

    if (current_iteration == options.maximum_iterations || !continue_flag) {
        std::filesystem::path file_bmp_path = MergeFilePath(options.output_dir, current_iteration);
        CreateFileBMP(field, file_bmp_path);
    } else if (options.freq) {
        if (current_iteration % options.freq == 0) {
            std::filesystem::path file_bmp_path = MergeFilePath(options.output_dir, current_iteration);
            CreateFileBMP(field, file_bmp_path);
        }
    }
}

void ProcessIterations(const Config& options, Field& field) {
    size_t current_iteration = 0;

    bool continue_flag = CheckFieldStatus(field);
    size_t i = 0;

    while (i < field.rows && current_iteration < options.maximum_iterations && continue_flag) {
        size_t j = 0;

        while (j < field.columns) {
            if (field.status_cells[i][j]) {
                CollapseAndCallExtension(field, i, j);
            }
            ++j;
        }
        ++i;

        UpdateIterationAndCallBmp(options, field, i, current_iteration, continue_flag);
    }
}
