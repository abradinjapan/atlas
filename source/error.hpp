#pragma once

/* Include */
#include "includes.hpp"

/* Error Class */
namespace atlas {
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
