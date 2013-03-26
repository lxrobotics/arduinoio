/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file ioentity.cpp
 * @author Alexander Entinger, BSc
 * @brief this file implements the ioentity class
 * @license MPL2.0
 */

#include "ioentity.h"
#include <assert.h>
#include <algorithm>

namespace arduinoio {

/**
 * @brief Constructor
 * @param
 */
ioentity::ioentity(boost::shared_ptr<serial> const &serial) : m_serial(serial), m_isConfigured(false)  {

}

/**
 * @brief Destructor
 */
ioentity::~ioentity() {
  m_pinVect.clear();
}


} // end of namespace arduinoio
