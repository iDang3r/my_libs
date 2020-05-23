//
// Created by Александр on 20.10.2019.
//

#ifndef ASM_INSTRUCTIONS_INIZ_H
#define ASM_INSTRUCTIONS_INIZ_H

#define DEF_CMD(name, num, next, cpu_code, disasm_code) \
    instructs[#name] = num;
//
#include "commands.h"
//
#undef DEF_CMD

#define DEF_REG(name, num) \
    find_registers[#name] = num; strcpy(find_registers[num], #name);

#include "registers.h"

#undef DEF_REG

#endif //ASM_INSTRUCTIONS_INIZ_H
