#ifndef TESTVALUES
#define TESTVALUES

#include <string.h>
#include "data_structures/datatype.h"
#include "algorithms/hashing.h"

#define TESTVAL1 1
#define TESTVAL2 2
#define TESTVAL3 3
#define TESTVAL4 4
#define TESTVAL5 5
#define TESTVAL6 6
#define TESTVAL7 7
#define TESTVAL8 8
#define TESTVAL9 9

#define TESTKEY1 "key1"
#define TESTKEY2 "ky1"
#define TESTKEY3 "key3"
#define TESTKEY4 "key4"
#define TESTKEY5 "key5"
#define TESTKEY6 "key6"
#define TESTKEY7 "key7"
#define TESTKEY8 "key8"
#define TESTKEY9 "key9"

inline int
compare(const data_type a, const data_type b) {
    return a - b;
}

inline uint64_t
hash(key_type value) {
    return hash_djb2(value);
}

inline int
key_compare(const key_type a, const key_type b) {
    return strcmp(a, b);
}

#endif // !TESTVALUES
