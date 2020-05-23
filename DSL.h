#ifndef ASM_DSL_H
#define ASM_DSL_H

#define PUSH(value) St.push(value)

#define POP St.pop()

#define PRINT(value) printf("%g\n", value / 100.)

#define VAR(name) int name = 0

#define SCAN(name) scanf("%d", &name); name *= 100

#define NEXT_INT(cur) (*(int*)((cur) + 1))

#define NEXT_CHAR(cur) *(cur + 1)

#define GET_REG(num) registers[num]

#define PUT_REG(num) registers[num]

#define GET_REG_NAME(num) find_registers[num]

#define GET_REG_NUM(name) find_registers[name]

#define INT(cur) *(int*)(cur)

#define RETURN return 0

#define CONTINUE continue

#define PRINT_NAME(s) fprintf(out, "%s", s); fprintf(out, " ");

#define PRINT_STR(str) fprintf(out, #str); fprintf(out, " ");

#define PRINT_CS(str) fprintf(out, #str);

#define PRINT_VAR(x) fprintf(out, "%d", x);

#define PRINT_N fprintf(out, "\n")

#define GOTO(num) code = code_to_free + num

#define PUSH_FUNC_CALL Func_calls.push(int(code - code_to_free) + 5)

#define POP_FUNC_CALL Func_calls.pop()

#define RAM(x) RAM_[x]

#define VRAM(x) VRAM_[x]

#endif //ASM_DSL_H
