/*
 *	Tag header file
 *
 *	(c) Copyright 2023, Roman Svihalek
 *		All Rights Reserved
 */

#pragma once

#include <cstdint>

namespace fasterfix {

    const char soh = static_cast<char>(1);

    class tag
    {
    public:
        using base_t = std::uint16_t;

        static bool is_BeginString(base_t tagval)
        {
            return tagval == 8;
        }

        static bool is_BodyLength(base_t tagval)
        {
            return tagval == 9;
        }
    };

} // fasterfix
