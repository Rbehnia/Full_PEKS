#ifndef params_peks_H
#define params_peks_H
#define MR_PAIRING_KSS    // AES-192 security
#define AES_SECURITY 192
typedef set<string> TYPE_KEYWORD_DICTIONARY;
typedef unsigned long int TYPE_COUNTER;
const int keywordLength= 45;
const int numOfKeywords = 20;
int numOfFiles = 1000;
#include <chrono>
#define time_now std::chrono::high_resolution_clock::now()

#endif