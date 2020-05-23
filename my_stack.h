//
// Created by Александр on 26/09/2019.
//

#ifndef DEDSKY32_MY_STACK_H
#define DEDSKY32_MY_STACK_H

#include "super_define.h"

#include "MurMurHash.h"

#define DUMP_INFO __FILE__, __PRETTY_FUNCTION__, __LINE__

#ifdef DEBUG
    #define ASSERT_OK {                  \
        int code_assert = is_ok();       \
        errno_ = code_assert;            \
        if (code_assert) {               \
            dump(DUMP_INFO);             \
            assert(!code_assert);        \
        }                                \
    }
#else
    #define ASSERT_OK ;
#endif


#define Stack(x) Stack_t x(#x);

typedef int Elem_t;

const size_t STACK_MAX_SIZE   = 256 * 1024 * 1024;
const size_t STACK_DELTA_SIZE = 8;

#ifdef DEBUG
const Elem_t Elem_poison      = -6e6;
const int    Kanareyka_const  = INT_MIN;
#endif

struct Stack_t {
#ifdef DEBUG
    int kanareyka1_;
#endif

    Elem_t* data_;
    size_t max_size_;
    size_t size_;

#ifdef DEBUG
    char* name_;
    int errno_;

    int kanareyka2_;

    size_t stack_hash{};
    size_t data_hash{};
#endif

    Stack_t(const char* name = "NO_NAME");

    ~Stack_t();

    size_t size();

    bool resize(int code = 1);

    size_t push(Elem_t Elem);

    Elem_t top();

    Elem_t pop();

#ifdef DEBUG
    int is_ok();

    void dump(const char *file, const char *func, int line, const char *flag = "ok");

    void rehash();
#endif
};

/*!
 * Constructor
 *
 * @param[in] name name if stack
 */

Stack_t::Stack_t(const char* name) {
#ifdef DEBUG
    kanareyka1_ = kanareyka2_ = Kanareyka_const;
    errno_ = 0;
#endif

    size_ = 0;
    max_size_ = STACK_DELTA_SIZE;

    data_ = (Elem_t*)calloc(max_size_ + 1, sizeof(Elem_t));
    if (data_ == nullptr) {
        assert(!"failed Constructor calloc");

#ifdef DEBUG
        errno_ = 7;
        dump(DUMP_INFO, "failed Constructor calloc");
#endif
    }

#ifdef DEBUG
    data_[0] = 0;
    for (size_t i = 1; i <= max_size_; ++i)
        data_[i] = Elem_poison;
    name_ = strdup(name);

    rehash();
#endif
}

/*!
 * Destructor
 */

Stack_t::~Stack_t() {
#ifdef DEBUG
    if (data_ == errptr <Elem_t> ())
        assert("DOUBLE DESTRUCTOR!!!" == ERROR);
    if (name_ == errptr <char> ())
        assert("DOUBLE DESTRUCTOR!!!" == ERROR);
#endif

    free(data_);

#ifdef DEBUG
    free(name_);
#endif

#ifdef DEBUG
    poison(&data_);
    poison(&name_);
#endif
}

/*!
 * gets size of stack
 *
 * @return size of stack
 */

size_t Stack_t::size() {
    ASSERT_OK
    return size_;
}

/*!
 * gets stack element
 *
 * @return stack element
 */

Elem_t Stack_t::top() {
    ASSERT_OK
    return data_[size_ - 1];
}

/*!
 * gets stack element and deletes it
 *
 * @return deleted stack element
 */

Elem_t Stack_t::pop() {
    ASSERT_OK

    if (size_ == 0) {
        assert("Stack: empty pop!" == ERROR);
    }
    
    Elem_t Elem_tmp = data_[size_ - 1];

#ifdef DEBUG
    data_[size_ - 1] = data_[size_] - Elem_tmp;
    data_[size_--] = Elem_poison;

    rehash();
#endif

    ASSERT_OK
    return Elem_tmp;
}

/*!
 * checks the stack correctly
 *
 * @return error value
 */

#ifdef DEBUG
int Stack_t::is_ok() {
    if (errno_)
        return errno_;

    if (size_ < 0 || size_ > max_size_
        || max_size_ > STACK_MAX_SIZE)
        return 2;

    int sum = 0;
    for (size_t i = 0; i < size_; ++i)
        sum += data_[i];
    if (sum != data_[size_])
        return 1;

    if (data_ == nullptr || name_ == nullptr)
        return 3;

    if (kanareyka1_ != Kanareyka_const || kanareyka2_ != Kanareyka_const)
        return 4;

    if (stack_hash != MurMurHash2((char*)this, sizeof(Stack_t) - 2 * sizeof(size_t)))
        return 5;

    if (data_hash != MurMurHash2((char*)data_, max_size_ * sizeof(Elem_t)))
        return 6;

    // 7 is reserved

    return 0;
}
#endif

/*!
 * puts Element in stack
 *
 * @param[in] Elem pushing element
 * @return size of stack
 */

size_t Stack_t::push(Elem_t Elem) {
    ASSERT_OK
    if (size_ == max_size_) {
        if (!resize()) {
#ifdef DEBUG
            errno_ = 7;
#endif
            assert("failed up resize");
            ASSERT_OK
            return size_;
        }
    }

#ifdef DEBUG
    data_[size_ + 1] = data_[size_] + Elem;
#endif

    data_[size_++] = Elem;

#ifdef DEBUG
    rehash();
#endif

    ASSERT_OK
    return size_;
}

/*!
 * resizing of stack
 *
 * @param[in] code (1) if resize up, (-1) if resize down
 * @return (true) if resizing was successful (false) else
 */

bool Stack_t::resize(int code) {
    ASSERT_OK
    if (code == 1) {
        if (size_ < max_size_)
            return true;
        if (max_size_ == STACK_MAX_SIZE)
            return false;

        size_t i = max_size_ + 1;
        max_size_ = MIN(max_size_ * 2, STACK_MAX_SIZE);

        Elem_t* data_copy = REALLOC(data_, max_size_ + 1);
        if (data_copy) {
            data_ = data_copy;
        } else {
            free(data_);
#ifdef DEBUG
            dump(DUMP_INFO, "failed resize realloc");
#endif
            assert("failed realloc" == ERROR);
        }
#ifdef DEBUG
        for (; i <= max_size_; ++i)
            data_[i] = Elem_poison;
#endif

//        cout << "UPPED!\n";
    } else if (code == -1) {
        if (size_ * 4 >= max_size_)
            return true;
        if (max_size_ <= STACK_DELTA_SIZE)
            return true;

        max_size_ /= 2;
        max_size_ = MAX(max_size_, STACK_DELTA_SIZE);

        Elem_t* data_copy = REALLOC(data_, max_size_ + 1);

        if (data_copy) {
            data_ = data_copy;
        } else {
            free(data_);
#ifdef DEBUG
            dump(DUMP_INFO, "failed resize realloc");
#endif
            assert("failed realloc" == ERROR);
        }

//        cout << "DOWNED\n";
    } else {
        assert(!"Unknown code");
        return false;
    }

#ifdef DEBUG
    rehash();
#endif

    ASSERT_OK
    return true;
}

/*!
 * Dump of stack
 *
 * @param[in] file from DUMO_INFO
 * @param[in] func from DUMO_INFO
 * @param[in] line from DUMO_INFO
 * @param[in] flag message of dump
 */

#ifdef DEBUG
void Stack_t::dump(const char* file, const char* func, int line, const char* flag) {
    printf("<<<-------- DUMP -------->>>\n");
    printf("File: %s\n", file);
    printf("Function: %s\n", func);
    printf("Line: %d\n", line);
    printf("Stack_t \"%s\"[%p] (%s)\n", name_, this, flag);
    printf("{\n");
    printf("  size = %zu\n", size_);
    printf("  data[%zu + (hash)] = [%p]\n", max_size_, data_);
    printf("    {\n");
    for (size_t i = 0; i <= max_size_; ++i) {
        printf("   ");
        printf((i < size_) ? "*" : " ");
        printf("[%zu] = %d", i, data_[i]);
        if (data_[i] == Elem_poison)
            printf(" [Poison]");
        if (size_ == i)
            printf(" [Hash summ]");
        printf("\n");
    }
    printf("    }\n");
    printf("  errno = %d ", errno_);
    switch (errno_) {
        case 0:
            printf("(ok)");
            break;
        case 1:
            printf("(failed hash)");
            break;
        case 2:
            printf("(failed size)");
            break;
        case 3:
            printf("(failed pointers)");
            break;
        case 4:
            printf("(failed kanareikis hehehe ;-) )");
            break;
        case 5:
            printf("(failed stack hash)");
            break;
        case 6:
            printf("(failed data hash)");
            break;
        case 7:
            printf("(failed resizing)");
            break;
        default:
            printf("(unknown error!)");
    }
    printf("\n");
    printf("}\n");
    printf("<<<-----END OF DUMP ----->>>\n");
}
#endif

#ifdef DEBUG
void Stack_t::rehash() {
    stack_hash = MurMurHash2((char*)this, sizeof(Stack_t) - 2*sizeof(size_t));
    data_hash = MurMurHash2((char*)data_, max_size_ * sizeof(Elem_t));
}
#endif

#endif //DEDSKY32_MY_STACK_H
