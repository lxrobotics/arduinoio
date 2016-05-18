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

#include "serial.h"

namespace arduinoio {

/**
 * @brief Constructor
 */
serial::serial(std::string const &devNode, unsigned int const baudRate) :
		m_devNode(devNode), m_baudRate(baudRate), m_io_service(), m_serial_port(
				m_io_service, m_devNode) {

	m_serial_port.set_option(
			boost::asio::serial_port_base::baud_rate(m_baudRate));
	m_serial_port.set_option(boost::asio::serial_port_base::character_size(8));
	m_serial_port.set_option(
			boost::asio::serial_port_base::flow_control(
					boost::asio::serial_port_base::flow_control::none));
	m_serial_port.set_option(
			boost::asio::serial_port_base::parity(
					boost::asio::serial_port_base::parity::none));
	m_serial_port.set_option(
			boost::asio::serial_port_base::stop_bits(
					boost::asio::serial_port_base::stop_bits::one));
}

/**
 * @brief Destructor
 */
serial::~serial() {

}

/**
 * @brief write data to the serial port
 */
void serial::writeToSerial(unsigned char const *buf, unsigned int const size) {
	boost::asio::write(m_serial_port, boost::asio::buffer(buf, size));
}

/**
 * @brief read data from the serial port
 */
boost::shared_ptr<unsigned char> serial::readFromSerial(unsigned int const size) {
	boost::shared_ptr<unsigned char> buf(new unsigned char[size]);

	boost::asio::read(m_serial_port, boost::asio::buffer(buf.get(), size));

	return buf;
}

} // end of namespace arduinoio
