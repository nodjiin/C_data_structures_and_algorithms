
/**
 * \file			hashtable_prime.h
 * \brief           header file containing the prime lookup table used on hash table resizing.
 */

#ifndef HASHTABLE_PRIMES
#define HASHTABLE_PRIMES

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>

#define PRIME_NUMBERS_64BIT 62

/**
 * \brief           list of primes to use as possible sizes of an hash table. I'm borrowing this from gcc.
 */
static const size_t hashtable_primes[PRIME_NUMBERS_64BIT] = {
    /* 0     */ 5ul,
    /* 1     */ 11ul,
    /* 2     */ 23ul,
    /* 3     */ 47ul,
    /* 4     */ 97ul,
    /* 5     */ 199ul,
    /* 6     */ 409ul,
    /* 7     */ 823ul,
    /* 8     */ 1741ul,
    /* 9     */ 3469ul,
    /* 10    */ 6949ul,
    /* 11    */ 14033ul,
    /* 12    */ 28411ul,
    /* 13    */ 57557ul,
    /* 14    */ 116731ul,
    /* 15    */ 236897ul,
    /* 16    */ 480881ul,
    /* 17    */ 976369ul,
    /* 18    */ 1982627ul,
    /* 19    */ 4026031ul,
    /* 20    */ 8175383ul,
    /* 21    */ 16601593ul,
    /* 22    */ 33712729ul,
    /* 23    */ 68460391ul,
    /* 24    */ 139022417ul,
    /* 25    */ 282312799ul,
    /* 26    */ 573292817ul,
    /* 27    */ 1164186217ul,
    /* 28    */ 2364114217ul,
    /* 29    */ 4294967291ul,
    /* 30    */ 8589934583ull,
    /* 31    */ 17179869143ull,
    /* 32    */ 34359738337ull,
    /* 33    */ 68719476731ull,
    /* 34    */ 137438953447ull,
    /* 35    */ 274877906899ull,
    /* 36    */ 549755813881ull,
    /* 37    */ 1099511627689ull,
    /* 38    */ 2199023255531ull,
    /* 39    */ 4398046511093ull,
    /* 40    */ 8796093022151ull,
    /* 41    */ 17592186044399ull,
    /* 42    */ 35184372088777ull,
    /* 43    */ 70368744177643ull,
    /* 44    */ 140737488355213ull,
    /* 45    */ 281474976710597ull,
    /* 46    */ 562949953421231ull,
    /* 47    */ 1125899906842597ull,
    /* 48    */ 2251799813685119ull,
    /* 49    */ 4503599627370449ull,
    /* 50    */ 9007199254740881ull,
    /* 51    */ 18014398509481951ull,
    /* 52    */ 36028797018963913ull,
    /* 53    */ 72057594037927931ull,
    /* 54    */ 144115188075855859ull,
    /* 55    */ 288230376151711717ull,
    /* 56    */ 576460752303423433ull,
    /* 57    */ 1152921504606846883ull,
    /* 58    */ 2305843009213693951ull,
    /* 59    */ 4611686018427387847ull,
    /* 60    */ 9223372036854775783ull,
    /* 61    */ 18446744073709551557ull,
};

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // !HASHTABLE_PRIMES