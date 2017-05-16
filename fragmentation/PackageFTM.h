/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2017 Semtech

Description: 	Firmware update over the air with LoRa proof of concept
				Functions for the decoding

Readme :

*/
#ifndef __PACKAGEFTM_H
#define __PACKAGEFTM_H

#include "mbed.h"
#include "McpsTypes.h"

#define LORAWAN_FTMPACKAGE_PORT 201

#define FRAG_STATUS_REQ 0x01
#define FRAG_STATUS_ANS 0x01
#define FRAG_SESSION_SETUP_REQ  0x02
#define FRAG_SESSION_SETUP_ANS  0x02
#define FRAG_SESSION_DELETE_REQ 0x03
#define FRAG_SESSION_DELETE_ANS 0x03
#define DATA_BLOCK_AUTH_REQ  0x05
#define DATA_BLOCK_AUTH_ANS  0x05
#define DATA_FRAGMENT  0x08
#define FRAG_SESSION_SETUP_REQ_LENGTH 0x6

#define  FRAG_SESSION_SETUP_ANS_LENGTH 0x2
#define  DATA_BLOCK_AUTH_REQ_LENGTH 0xa
#define  LORAWAN_APP_FTM_PACKAGE_DATA_MAX_SIZE 20
/*!
 * Global  FTMPackage parameters
 */
typedef struct sFTMPackageParams
{
  	/*!
     * identifies the fragmentation session and contains the following fields
     */
    uint8_t FragSession ;
    /*!
     * specifies the total number of fragments of the data block to be transported
	   * during the coming multicast fragmentation session
     */
    uint16_t NbFrag;

    /*!
     * is the size in byte of each fragment.
     */
    uint8_t FragSize;

  	/*!
     * FragmentationMatrix   encodes the type of fragmentation algorithm used
	   * Block_ack_delay encodes the amplitude of the random delay that devices have
     * to wait between the moment they have reconstructed the full data block and the moment
	   * they transmit the DataBlockAuthReq message
     */
    uint8_t Encoding;
		/*!
     * specifies the total number of Redundancy fragments of the data block to be transported
	   * during the coming multicast fragmentation session
     */
    uint16_t Redundancy;

}FTMPackageParams_t;

void FTMPackageCore(uint8_t *buffer, size_t buffer_size);
bool SendFragSessionSetupAns( uint8_t port );
bool SendDataBlockAuthReq( uint8_t port );
#endif


