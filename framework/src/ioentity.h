/* Copyright (c) 2016, Alexander Entinger / LXRobotics
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of motor-controller-highpower-motorshield nor the names of its
 *  contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
