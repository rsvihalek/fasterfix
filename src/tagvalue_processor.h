/*
 *	Tag-value messages processor header file
 *
 *	(c) Copyright 2023, Roman Svihalek
 *		All Rights Reserved
 */

#pragma once

#include "tagvalue_buffer.h"

namespace fasterfix {

	class tagvalue_parser {

	public:
        tagvalue_parser()
		{
		}

		~tagvalue_parser()
		{
		}

	// public member functions
	public:
		void parse_data(const std::string_view& data) throw(std::bad_alloc)
		{
            while (!data.empty())
            {
                // allocate buffer if none is available
                if (_buffer == nullptr)
                {
                    _buffer = std::make_shared<tagvalue_buffer>();
                }

                // TODO: check for the maximal message size

                _buffer->append(data);
            }
		}

	private:
		tagvalue_buffer::ptr _buffer;

	};

} // fasterfix
