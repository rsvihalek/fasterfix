/*
 *	Tag-value message buffer header file
 *
 *	(c) Copyright 2023, Roman Svihalek
 *		All Rights Reserved
 */

#pragma once

#include <array>
#include <memory>
#include <string_view>

namespace fasterfix {

    class tagvalue_buffer {

    public:
        using ptr = std::shared_ptr<tagvalue_buffer>;

        tagvalue_buffer()
            : _used_bytes{ 0 }
        {
        }

        ~tagvalue_buffer()
        {
        }

    // public member functions
    public:
        std::size_t used_bytes() const
        {
            return _used_bytes;
        }

        std::size_t free_bytes() const
        {
            return _buffer.size() - _used_bytes;
        }

        char* first_free()
        {
            return &_buffer[_used_bytes];
        }

        void append(const std::string_view& data)
        {
            // TODO: check the data size

            data.copy(first_free(), data.size());
            _used_bytes += data.size();
        }

    // private member variables
    private:
        std::array<char, 10 * 1024> _buffer;

        std::size_t _used_bytes;
    };

} // fasterfix
