//
// Created by Hector Mejia on 3/15/24.
//

#pragma once

#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <string>

#define DEBUG 1

#define min(_a, _b) ({ __typeof__(_a) __a = (_a), __b = (_b); __a < __b ? __a : __b; })
#define max(_a, _b) ({ __typeof__(_a) __a = (_a), __b = (_b); __a > __b ? __a : __b; })

#define nil nullptr
typedef float f32;
typedef double f64;
typedef uint8_t byte;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef size_t usize;
typedef ssize_t isize;

#define Offset 50
#define ScreenWidth 750
#define ScreenHeight 700
#define FPS 120

void initLogger();

void panic(const char *message);
void panic(const std::string &message);
void panicIf(bool condition, const char *message);
