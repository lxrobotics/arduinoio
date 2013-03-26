/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /**
 * @author Alexander Entinger, BSc
 * @file parser.h
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdint.h>

/**
 * @brief parses the incoming uart data according to the agreed protocol
 * @param data uart data to be parsed
 */
void parse(uint8_t const data);

#endif
