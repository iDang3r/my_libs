//
// Created by Александр on 20.10.2019.
//

#ifndef TEST_MY_MAP_H
#define TEST_MY_MAP_H

struct elem_map {
    char name_[128] = {};
    int num_ = 0;
    elem_map(){}
    elem_map(const char* name, int num) {
        strcpy(name_, name);
        num_ = num;
    }
};

struct my_map {
    static const int max_size_ = 1024;

    int size_ = 0;
    elem_map data_[max_size_];

    int find(const char* s) {
        for (int i = 0; i < size_; i++)
            if (strcmp(data_[i].name_, s) == 0)
                return i;
        return -1;
    }

    int find(int key) {
        for (int i = 0; i < size_; i++)
            if (data_[i].num_ == key)
                return i;
        return -1;
    }

    int add(elem_map El) {
        if (size_ == max_size_) {
            assert("My_map is full\n" == 0);
            return -1;
        }
        data_[size_] = El;
        return size_++;
    }

    int& operator[](const char* s) {
        int i = find(s);
        if (i == -1)
            i = add(elem_map(s, 0));
        return data_[i].num_;
    }

    char* operator[](int key) {
        int i = find(key);
        if (i == -1)
            i = add(elem_map("", key));
        return data_[i].name_;
    }
};

#endif //TEST_MY_MAP_H
