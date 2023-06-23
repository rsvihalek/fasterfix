/*
 *	Unsigned integer parser header file
 *
 *	(c) Copyright 2023, Roman Svihalek
 *		All Rights Reserved
 */

#pragma once

namespace fasterfix {

    template<typename base_t, size_t maxdecimals>
    class parser_uint
    {
    public:
        parser_uint()
            : _decimals{ 0 },
            , _value{ 0 }
        {
        }

    // public member functions
    public:
        void reset()
        {
            _decimals = 0;
            _value = 0;
        }

        bool add(char decimal)
        {
            if (!isalpha(decimal))
            {
                return false;
            }

            // TODO: check for number of decimals

            // TODO: detect overflow
            decimal -= '0';
            _value *= 10;
            _value += decimal;
            ++_decimals;
            return true;
        }

        base_t value() const
        {
            return _value;
        }

    // private member variables
    private:
        size_t _decimals;

        base_t _value;
    };

} // fasterfix
