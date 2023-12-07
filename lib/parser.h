#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <filesystem>

static const size_t kFileExtensionTSV = 4;
static const size_t kMinimalLengthInputFile = 8;
static const size_t kMinimalLengthOutputDir = 9;
static const size_t kMinimalLengthIterations = 11;
static const size_t kMinimalLengthFreq = 7;

struct Config {
    std::filesystem::path input_file;
    std::filesystem::path output_dir;
    size_t maximum_iterations = 0;
    size_t freq = 0;
};

Config ParseCommands(int argc, char* argv[]);
