/**
 *    Copyright 2010 Daine Mamacos
 *
 *    This file is part of the nRF905 driver for AVR micro controllers.
 *
 *    The nRF905 driver is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License.
 *
 *    The nRF905 driver is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _NRF905_H
#define	_NRF905_H

#ifdef	__cplusplus
extern "C"
{
#endif

void SPI_MasterInit();
void SPI_MasterStart();
void SPI_MasterEnd();
unsigned char SPI_MasterTransmit(unsigned char cData);

/**
 * Sets the operating frequency of the nRF905
 *
 * This allows one to select the operating frequency
 * of the nRF905, along with the switch to the
 * Higher Frequency band. It also allows you to set
 * the output power.
 *
 * @param uint16_t freqKKhz
 *  Set's the frequncy in thousands of killoherts. For instance,
 *  433.1 Mhz becomes 4331 thousand Khz. If you wanted to set
 *  it to say, 450Mhz, you would set a value of 4500.
 * @param uint8_t HFREQ_PLL
 *  This sets the band you're working in.
 *  0 = 433Mhz band
 *  1 = 868 or 915 band
 * @param uint8_t power
 *  Sets the power output of the transmitter.
 *  0 = -10dBm
 *  1 = -2dBm
 *  2 = 6dBm
 *  3 = 10dBm
 */
void nRF905SetFreq(uint16_t freqKKhz, uint8_t HFREQ_PLL, uint8_t power);

/**
 * Set the width of the TX and RX address
 *
 * We can set the Tramission and Reception Addresses
 * with these values. Valid values are from 1 - 4.
 * This defined how many bytes wide the address will be.
 *
 * @param uint8_t txAddWidth
 *  Width of the TX address, 1 - 4
 * @param uint8_t rxAddWidth
 *  Width of the RX address, 1 - 4
 */
void nRF905SetTxRxAddWidth(uint8_t txAddWidth, uint8_t rxAddWidth);

/**
 * Set the Device Address
 *
 * This allows us to set the devices reception address.
 * Please note, if you set the address width narrow, the other
 * bytes are ignored by the nRF905.
 *
 * @param uint8_t address1
 *  First byte of address
 * @param uint8_t address2
 *  Second byte of address
 * @param uint8_t address3
 *  Third byte of address
 * @param uint8_t address4
 *  Fourth byte of address
 */
void nRF905SetRxAddress(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4);

/**
 * Set the RX payload width.
 *
 * We can specify how big the payload can be for each
 * packet here.
 *
 * @param uint8_t width
 *  Payload width, valid values are from 1 - 32. Any bigger
 *  values will be cut to 32 bytes.
 */
void nRF905SetRxPayloadWidth(uint8_t width);

/**
 * Set the TX payload width.
 *
 * We can specify how big the payload can be for each
 * packet here.
 *
 * @param uint8_t width
 *  Payload width, valid values are from 1 - 32. Any bigger
 *  values will be cut to 32 bytes.
 */
void nRF905SetTxPayloadWidth(uint8_t width);

/**
 * Set the address of any outgoing packets
 *
 * With this, we can change the address the chip uses to compose
 * packets to. This is likely to change very often, depending on what
 * other devices we are chatting to.
 * Please note, if you set the address width narrow, the other
 * bytes are ignored by the nRF905.
 *
 * @param uint8_t address1
 *  First byte of address
 * @param uint8_t address2
 *  Second byte of address
 * @param uint8_t address3
 *  Third byte of address
 * @param uint8_t address4
 *  Fourth byte of address
 */
void nRF905SetTxAddress(uint8_t address1, uint8_t address2, uint8_t address3, uint8_t address4);

/**
 * This fetches the TX address from the chip.
 *
 * This might come in handy, to check what TX address you have
 * currently storred in the chip. It's more of a conenience
 * method.
 *
 * @param uint8_t *buffer
 *  This is a pointer to a buffer passed in, into which each byte of
 *  the address will be copied. The buffer needs at least four bytes
 *  of space.
 */
void nRF905GetTxAddress(uint8_t *buffer);

/**
 * Set the TX payload.
 *
 * Here we can clock in all the data we want to send
 * from the device. It can be from 1 - 32 bytes in length.
 *
 * Please note, the payload width should match the payload width you have
 * configured with nRF905SetTxPayloadWidth, because only that ammount of
 * data will be sent from the unit, and you'll be sending unessesary
 * data over the SPI Bus.
 *
 * @param char *payload
 *  A pointer to the payload we want to send
 * @param uint8_t payloadWidth
 *  The length of payload. Valid values 1 - 32.
 */
void nRF905SetTxPayload(char *payload, uint8_t payloadWidth);

/**
 * Get the TX payload
 *
 * Again, this is a convenience function. It fetches the transmission
 * payload from the device.
 *
 * @param char *payload
 *  A pointer to a buffer we want the payload copied into
 *  It needs to be at least payloadWidth in size.
 * @param uint8_t payloadWidth
 *  The length of the payload. Valid values 1 - 32.
 */
void nRF905GetTxPayload(char *payload, uint8_t payloadWidth);

/**
 * Transmit the packet
 *
 * This function instructs the unit to send the packet.
 * The packet will be formulated with the payload and address
 * you have specified.
 */
void nRF905SendPacket();

/**
 * Put the device into sleep mode
 *
 * This puts the device into a deep sleep that consumes very little power,
 * the configuration is maintained in this mode.
 */
void nRF905DeviceSleep();

/**
 * Get values from the configuration register
 *
 * This method allows you to pick specificy bytes ouf of the
 * configuration. You can start at any arbitrary point on the
 * config.
 *
 * @param uint8_t from
 *  Where you would like to start reading from in the configuration.
 *  Valid values 0 - 9
 * @param uint8_t count
 *  How many bytes you would like to read from the configuration.
 * @param char *buffer
 *  A pointer to a buffer where you would like the config values to be
 *  copied into.
 */
void nRF905GetConfig(uint8_t from, uint8_t count, char *buffer);

/**
 * Set config options
 *
 * With this method we can set arbiraty config options. It works
 * in roughly the same manner as nRF905GetConfig.
 *
 * @param uint8_t from
 *  Where you would like to start writing to the configuration.
 *  Valid values 0 - 9
 * @param uint8_t count
 *  How many bytes you would like to write to he configuration.
 * @param char *buffer
 *  A pointer to a buffer that contains the configuration values
 *  you wish to set.
 */
void nRF905SetConfig(uint8_t from, uint8_t count, char *buffer);

/**
 * Initialise the device with a default set of values.
 *
 * This method uses a preset set of values, to dump into the
 * nRF905's configuration registers. The values are defined in the array
 * initData in the nRF905_conf.h
 * I suggest that you set up this array with the default values you
 * are likely to use. All the configuration can be manipulated from
 * this API, however for the sake of a lot of the values, it's probably
 * best if you pre-populate this array with the values you are most
 * likely to use.
 */
void nRF905Init();

/**
 * Put the device into receive mode
 */
void nRF905EnableRecv();

/**
 * Disable receive mode on the device
 */
void nRF905DisableRecv();

/**
 * Get the RX payload
 *
 * Again, this is a convenience function. It fetches the transmission
 * payload from the device.
 *
 * @param char *payload
 *  A pointer to a buffer we want the payload copied into
 *  It needs to be at least payloadWidth in size.
 * @param uint8_t payloadWidth
 *  The length of the payload. Valid values 1 - 32.
 */
void nRF905GetRxPayload(char *payload, uint8_t payloadWidth);

/**
 * Pull a packet off the device if the circumstances are correct.
 *
 * This is a convenience method to help you pull a packet off the
 * device. It only works if the address match line is high. This means
 * this function needs to be invoked either in an interrupt routine
 * where it's interrupted by the Address Match line, or in an endless while
 * loop waiting for an address match.
 *
 * If you have not wires up the AM or DR lines, there is another function
 * which can pull these values from a register for you to check if there
 * is basically a packet waiting on the line for you: nRF905RevcPacketWODL
 * I will provide examples of all this.
 *
 * @param char *buffer
 *  A pointer to a buffer that the payload will be copied into.
 *  It must be at least payloadWidth in size.
 * @param uint8_t payloadWidth
 *  The length of the payload to pull form the drvice.
 *  Valid values 1 - 32.
 * @param uint8_t stayInRecvMode
 *  If set to 1, this ensures the device stays in receive mode after
 *  it clocks the payload off the device. Otherwise it goes into
 *  a neutral mode.
 */
void nRF905RecvPacket(char *buffer, uint8_t payloadWidth, uint8_t stayInRecvMode);

/**
 * Pull a packet off the device if the circumstances are correct.
 *
 * This is a convenience method to help you pull a packet off the
 * device. It only works if the address match status register bit is set.
 *
 * This is an alternative to nRF905RecvPacket, in that it does not require that
 * the address match line, or the data ready line is hooked up. It polls
 * the status register of the nRF905 to see if there is an address match, or
 * the data is ready.
 *
 * @param char *buffer
 *  A pointer to a buffer that the payload will be copied into.
 *  It must be at least payloadWidth in size.
 * @param uint8_t payloadWidth
 *  The length of the payload to pull form the drvice.
 *  Valid values 1 - 32.
 * @param uint8_t stayInRecvMode
 *  If set to 1, this ensures the device stays in receive mode after
 *  it clocks the payload off the device. Otherwise it goes into
 *  a neutral mode.
 */
void nRF905RecvPacketWODL(char *buffer, uint8_t payloadWidth, uint8_t stayInRecvMode);

/**
 * Reduce the RX power of the device.
 *
 * This reduces the power consumption while in RX mode, however it also
 * reduces senitivity of the device
 *
 * @param uint8_t rxPwrRed
 *  turn reduced power on or off. Valid values 0 - 1
 */
void nRF905SetReduceRxPwr(uint8_t rxPwrRed);

/**
 * Turn on the Auto Retransmit feature
 *
 * When sending a packet, one can stipulate that it gets transmitted
 * forever untill the user tells it to stop.
 *
 * @param uint8_t autoRetransmit
 *  turn on or off this feature. Valid values 0 - 1
 */
void nRF905SetAutoRetransmit(uint8_t autoRetransmit);

/**
 * The nRF can supply an external clock line
 *
 * One of the handy features of the device, is it's ability
 * to drive an external clock line. This method allows you to
 * turn on or off that feature, and stipulate it's frequency.
 *
 * @param uint8_t outClockFreq
 *  The frequency of the clock signal. Valid values:
 *  0 = 4Mhz
 *  1 = 2Mhz
 *  2 = 1Mhz
 *  3 = 500Khz
 * @param uint8_t enable
 *  enable the external clock driving line. Valid values 0 - 1
 */
void nRF905SetOuputClock(uint8_t outClockFreq, uint8_t enable);

/**
 * Confgure the CRC checks
 *
 * We can stipulate if we want CRC checks, and what kind.
 *
 * @param uint8_t CRCMode
 *  Specify the CRC mode:
 *  0 = 8 CRC check bit
 *  1 = 16 CRC check bit
 * @paran uint8_t enable
 *  enable the CRC checks. Valid values 0 - 1
 */
void nRF905SetCRC(uint8_t CRCMode, uint8_t enable);

/**
 * Set the value of the external reference crystal.
 *
 * The nRF905 needs an external reference crystal. It can handle a wide
 * range of crystals.
 *
 * @param uint8_t freq
 *  Set the frequency of the external reference crystal:
 *  0 = 4Mhz
 *  1 = 8Mhz
 *  2 = 12Mhz
 *  3 = 16Mhz
 *  4 = 20Mhz
 */
void nRF905SetOscFreq(uint8_t freq);

/**
 * Retrieve the status register
 *
 * The status rgister contains the current values of AM (Address Match)
 * and DR (Data Ready). This is a useful function to have if you have
 * not wired up the physical AM or DR lines on the IC. While you
 * can't use it to trigger an interrupt, you can poll the device to see
 * when data might be ready to fetch
 */
uint8_t nRF905GetStatusReg();

/**
 * Use this to test values in the status register
 *
 * EG: if(AM_IN_STATUS_REG(reg)) { ... }
 */
#define AM_IN_STATUS_REG(x) (x & 0x80)

/**
 * Use this to test values in the status register
 *
 * EG: if(DR_IN_STATUS_REG(reg)) { ... }
 */
#define DR_IN_STATUS_REG(x) (x & 0x20)


#ifdef	__cplusplus
}
#endif

#endif	/* _NRF905_H */

