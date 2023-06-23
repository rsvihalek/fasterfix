/*
 *	Tag-value messages parser header file
 *
 *	(c) Copyright 2023, Roman Svihalek
 *		All Rights Reserved
 */

#pragma once

#include <cstdint>

#include "parser_uint.h"
#include "fix.h"

namespace fasterfix {

    template<class handler>
    class tagvalue_parser
    {
        enum class state
        {
            message,
            tag_start,
            tag,
            equal,
            value,
            soh,
        };

    public:
        tagvalue_parser()
            : _state{ message }
        {
        }

        ~tagvalue_parser()
        {
        }

    // public member functions
    public:
        void parse(const std::string_view& data)
        {
            for (auto it = data.cbegin(); it != data.cend(); ++it)
            {
                switch (_state) {

                case state::message:
                    _handler.on_message();
                    // continue

                case state::tag_start:
                    _tag_parser.reset();
                    _state = state::tag;
                    // continue

                case state::tag:
                    do {
                        if (it == data.cend())
                        {
                            return;
                        }

                        if (!_tag_parser.add(*it))
                        {
                            break;
                        }
                    } while (++it);
                    _state = state::equal;
                    // continue

                case state::equal:
                    for(;;)
                    {
                        if (it == data.cend())
                        {
                            return;
                        }

                        char c = *it++;
                        if (c == '=')
                        {
                            _handler.on_tag(_tag_parser.value());
                            break;
                        }

                        _handler.on_taginvalidcharacter(c);
                    }
                    _state = state::value;
                    // continue

                case state::value:
                    for (;;)
                    {
                        if (it == data.cend())
                        {
                            _handler.on_value(c, false);
                            return;
                        }

                        if (*it++ == soh)
                        {
                            _handler.on_value(c, true);
                            break;
                        }
                    }
                    _state = state::soh;
                    // continue

                case state::soh:
                    break;

                }
            }
        }

    // private member variables
    private:
        handler _handler;

        state _state;

        parser_uint<tag::base_t, 5> _tag_parser;
    };

} // fasterfix
