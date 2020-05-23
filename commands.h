#ifndef ASM_COMMANDS_H

#include "DSL.h"

/*
 * DEF_CMD(name_of_command, number_of_command, size_of_command + size_of_params, {
 *      CODE_FOR_CPU
 * }
 *
 */

DEF_CMD(end, 0, sizeof(char), {          // DO NOT USE!
    PRINT(POP);
    RETURN;
}, {})

DEF_CMD(push, 1, sizeof(char) + sizeof(int), {
    PUSH(NEXT_INT(code));
}, {
    PRINT_VAR(NEXT_INT(buff) / 100);
})

DEF_CMD(add, 2, sizeof(char), {
    PUSH(POP + POP);
}, {})

DEF_CMD(sub, 3, sizeof(char), {
    PUSH(-POP + POP);
}, {})

DEF_CMD(mul, 4, sizeof(char), {
    PUSH(POP * POP / 100);
}, {})

DEF_CMD(div, 5, sizeof(char), {
    VAR(x);
    x = POP;
    VAR(y);
    y = POP;
    PUSH(100 * y / x);
}, {})

DEF_CMD(in, 6, sizeof(char), {
    VAR(x);
    SCAN(x);
    PUSH(x);
}, {})

DEF_CMD(out, 7, sizeof(char), {
    PRINT(POP);
}, {})

DEF_CMD(sqr, 8, sizeof(char), {

}, {})

DEF_CMD(sqrt, 9, sizeof(char), {
    PUSH(sqrt(POP * 100));
}, {})

DEF_CMD(pushr, 10, 2 * sizeof(char), {
    PUSH(GET_REG(NEXT_CHAR(code)));
}, {
    PRINT_NAME(GET_REG_NAME(NEXT_CHAR(buff)));
})

DEF_CMD(popr, 11, 2 * sizeof(char), {
    PUT_REG(NEXT_CHAR(code)) = POP;
}, {
    PRINT_NAME(GET_REG_NAME(NEXT_CHAR(buff)));
})

DEF_CMD(pushm, 15, 2 * sizeof(char) + sizeof(int), {
    PUSH(RAM(GET_REG(NEXT_CHAR(code)) / 100 + NEXT_INT(code + sizeof(char))));
}, {
    PRINT_CS([);
    PRINT_VAR(NEXT_INT(buff));
    PRINT_CS(]);
})

DEF_CMD(popm, 16, 2 * sizeof(char) + sizeof(int), {
    RAM(GET_REG(NEXT_CHAR(code)) / 100 + NEXT_INT(code + sizeof(char))) = POP;
}, {
    PRINT_CS([);
    PRINT_VAR(NEXT_INT(buff));
    PRINT_CS(]);
})

DEF_CMD(pushv, 17, 2 * sizeof(char) + sizeof(int), {
    PUSH(VRAM(GET_REG(NEXT_CHAR(code)) / 100 + NEXT_INT(code + sizeof(char))) * 100);
//    PUSH(VRAM(NEXT_INT(code)) * 100);
}, {
    PRINT_CS([);
    PRINT_VAR(NEXT_INT(buff));
    PRINT_CS(]);
})

DEF_CMD(popv, 18, 2 * sizeof(char) + sizeof(int), {
    VRAM(GET_REG(NEXT_CHAR(code)) / 100 + NEXT_INT(code + sizeof(char))) = char(POP / 100);
//    VRAM(NEXT_INT(code)) = (char)(POP / 100);
}, {
    PRINT_CS([);
    PRINT_VAR(NEXT_INT(buff));
    PRINT_CS(]);
})

DEF_CMD(pic, 19, sizeof(char), {
    printf("\n");
    for (int i = 0; i < IMAGE_HEIGHT; i++) {
        for (int j = 0; j < IMAGE_WIDTH; j++) {
            printf("\033[%dm  \033[0m", VRAM(i * IMAGE_WIDTH + j) + BLACK);
        }
        printf("\n");
    }
    printf("\n");
}, {

})

DEF_CMD(circle, 20, sizeof(char) + sizeof(int), {
    VAR(radius);
    radius = NEXT_INT(code);
    make_circle(radius);
    print_image(2 * radius + 1, 2 * radius + 1);
}, {
    PRINT_VAR(NEXT_INT(buff))
})

DEF_CMD(inc, 21, 2 * sizeof(char), {
    GET_REG(NEXT_CHAR(code)) += 100;
}, {
    PRINT_NAME(GET_REG_NAME(NEXT_CHAR(buff)));
})

DEF_CMD(ret, 48, sizeof(char), {
    GOTO(POP_FUNC_CALL);
    CONTINUE;
}, {
    PRINT_N;
})

DEF_CMD(call, 49, sizeof(char) + sizeof(int), {
    PUSH_FUNC_CALL;
    GOTO(NEXT_INT(code));
    CONTINUE;
}, {
    PRINT_CS(label_);

    for (int i = 0; i < labels_size; i++) {
        if (NEXT_INT(buff) == labels_pointers[i]) {
            PRINT_VAR(i + 1);
            break;
        }
    }

    PRINT_CS(:\n);
})

DEF_CMD(jmp, 50, sizeof(char) + sizeof(int), {
    GOTO(NEXT_INT(code));
    CONTINUE;
}, {
    PRINT_CS(label_);

    for (int i = 0; i < labels_size; i++) {
        if (NEXT_INT(buff) == labels_pointers[i]) {
            PRINT_VAR(i + 1);
            break;
        }
    }

    PRINT_CS(:\n);
})

#define DEF_JMP(name, num, cmp)                         \
DEF_CMD(name, 50 + num, sizeof(char) + sizeof(int), {   \
    if (POP cmp POP) {                                  \
        GOTO(NEXT_INT(code));                           \
        CONTINUE;                                       \
    }                                                   \
}, {                                                    \
    PRINT_CS(label_);                                   \
    for (int i = 0; i < labels_size; i++) {             \
        if (NEXT_INT(buff) == labels_pointers[i]) {     \
            PRINT_VAR(i + 1);                           \
            break;                                      \
        }                                               \
    }                                                   \
    PRINT_CS(:\n);                                      \
})

#include "jumps.h"

#undef DEF_JMP


#endif //ASM_COMMANDS_H
