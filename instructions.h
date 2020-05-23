//
// Created by Александр on 02/10/2019.
//

#ifndef ASM_INSTRUCTIONS_H
#define ASM_INSTRUCTIONS_H

#include "my_map.h"

const int MAX_IMAGE_HEIGHT = 256;
const int MAX_IMAGE_WIDTH  = 256;
const int MAX_RAM_SIZE = 2048;

const int IMAGE_HEIGHT = 32;
const int IMAGE_WIDTH  = 64;
const int MAX_VRAM_SIZE = 640 * 480;

enum color {
    BLACK   = 40,
    RED     = 41,
    GREEN   = 42,
    YELLOW  = 43,
    BLUE    = 44,
    MAGENTA = 45,
    CYAN    = 46,
    WHITE   = 47
};

//std::map<std::string, char> instructs = {{"end",  0},
//                                         {"push", 1},
//                                         {"add",  2},
//                                         {"sub",  3},
//                                         {"mul",  4},
//                                         {"div",  5},
//                                        };

//#define DEF_CMD(name, num, next, cpu_code, disasm_code) \
//    {#name, num},
//
//std::map<std::string, char> instructs = {
//        #include "commands.h"
//};
//
//#undef DEF_CMD

my_map instructs;


//#define DEF_REG(name, num) \
//    {#name, num},
//
//std::map<std::string, char> find_registers = {
//    #include "registers.h"
//};
//
//#undef DEF_REG


my_map find_registers;


//#define DEF_REG(name, num) \
//    {num, #name},
//
//std::map<char, std::string> find_names_registers = {
//    #include "registers.h"
//};
//
//#undef DEF_REG

//std::map<std::string, char> labels;

my_map labels;

struct Signature {
    char main_sign_[3] = "AR";
    char version_[4] = "1.2";
    size_t source_size_ = 0;
    Signature(const char version[4], size_t source_size = 0) {
        strcpy(version_, version);
        source_size_ = source_size;
    }
    void dump() {
        printf("\n<<-----FILE_SIGNATURE----->>\n");
        printf("Main sgin: %s\n", main_sign_);
        printf("Version: %s\n", version_);
        printf("Source code size: %zu\n", source_size_);
        printf("Size of signature: %zu\n", sizeof(Signature));
        printf("<<----END_OF_SIGNATURE---->>\n\n");
    }
};



#endif //ASM_INSTRUCTIONS_H
