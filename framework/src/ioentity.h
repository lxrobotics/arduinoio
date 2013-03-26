/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file ioentity.h
 * @author Alexander Entinger, BSc
 * @brief this file implements the ioentity class
 * @license MPL2.0
 */

#ifndef IOENTITY_H_
#define IOENTITY_H_

#include "pin.h"
#include "serial.h"
#include <vector>
#include <boost/shared_ptr.hpp>

namespace arduinoio {

/**
 * @class ioentity
 * @brief implements an ioentity which is the generalised form of an conrete io object
 */
class ioentity {
public:
	/**
	 * @brief Constructor
	 * @param
	 */
	ioentity(boost::shared_ptr<serial> const &serial);

	/**
	 * @brief Destructor
	 */
	virtual ~ioentity();

	/**
	 * @brief performs the requested configuration for the ioentity in question
	 * @return true in case of success, false in case of failure
	 */
	virtual bool config() = 0;

	/**
	 * operator ==
	 */
	bool operator ==(ioentity &other) {
		std::vector<pin> *pOtherPinVect = other.getPinVect();
		if (pOtherPinVect == 0)
			return false;
		if (m_pinVect.size() != pOtherPinVect->size())
			return false;
		return (m_pinVect[0].getPin() == pOtherPinVect->at(0).getPin());
	}

	inline std::vector<pin> *getPinVect() {
		return &m_pinVect;
	}

	inline bool isConfigured() const {
		return m_isConfigured;
	}

protected:
	boost::shared_ptr<serial> m_serial;
	std::vector<pin> m_pinVect;

	inline void setIsConfiguredFlag() {
		m_isConfigured = true;
	}
private:
	bool m_isConfigured;
};

} // end of namespace arduinoio

#endif
