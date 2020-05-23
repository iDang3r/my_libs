//
// Created by Александр on 02/10/2019.
//

#ifndef MY_DUMP_H
#define MY_DUMP_H

#define DUMP_INFO __FILE__, __PRETTY_FUNCTION__, __LINE__

/*!
 * Poor dump with message
 *
 * @param[in] "DUMP_INFO"
 * @param[in] flag message
 */

void dump(const char* file, const char* func, int line, const char* flag = "ok") {
    printf("\n\033[1;31mATTENTION\033[0m\n");
    printf("File: %s\n", file);
    printf("Function: %s\n", func);
    printf("Line: %d\n", line);
    printf("\033[1;31mFlag is:->\033[0m %s\n\n", flag);
};

#endif // MY_DUMP_H