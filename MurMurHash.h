//
// Created by Александр on 15.10.2019.
//

#ifndef STACK_MURMURHASH_H
#define STACK_MURMURHASH_H

size_t MurMurHash2(char* key, size_t len)
{
    size_t m = 0x5bd1e995;
    size_t seed = 0;
    int r = 24;

    unsigned int h = seed ^ len;

    unsigned char* data = (unsigned char*)key;
    unsigned int k;

    while (len >= 4) {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

#endif //STACK_MURMURHASH_H
