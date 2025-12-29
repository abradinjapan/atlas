#pragma once

/* Include */
// atlas
#include "external_includes.hpp"

/* Defines */
namespace atlas {
    // type defines
    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
    typedef int8_t s8;
    typedef int16_t s16;
    typedef int32_t s32;
    typedef int64_t s64;
    typedef void* address;

    // character defines
    typedef atlas::u8 character;

    // error
    class error {
    public:
        bool occured;
        std::string json;

        // constructors
        error() {
            occured = false;
            json = "{\n\t\"reason\": \"No problem was detected.\"\n}";
        }
        error(bool _occured, std::string _json) {
            occured = _occured;
            json = _json;
        }
    };
}
