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
FRAG_SESSION_SETUP_REQ example :
02 01 04 39 66 00 :  Frag index 0 MCGroupid 1, NbFrag = 50,fragsize 105,encoding  0,
02 01 00 32 64 00 :  Frag index 0 MCGroupid 1, NbFrag = 50,fragsize 105,encoding  0,
02 01 02 1E CC 00
*/

#include "mbed.h"
#include "Fragmentation.h"
#include "FragmentationDecode.h"
#include "Flash.h"
#include "ProtocolLayer.h"
#include "PackageFTM.h"
#include "FragmentationDecode.h"
#include "crc.h"

FTMPackageParams_t FTMPackageParams;
static uint8_t AppDataFTMPackage[LORAWAN_APP_FTM_PACKAGE_DATA_MAX_SIZE];
static int endOfTest	= FRAGMENTATION_NOT_STARTED;

/*!
 * \brief	Function to parse cmd during fragmented data block transport
 *
 * \param	[IN] McpsIndication_t
 * \param [IN]
 * \param	[OUT] void
 */
void FTMPackageCore(uint8_t* buffer, size_t buffer_size)
{
    // printf("FTMPackageCore message, length %d: [", buffer_size);
    // for (size_t ix = 0; ix < buffer_size; ix++) {
    //     printf("%02x ", buffer[ix]);
    // }
    // printf("]\n");

    static int firstFragment = 1;
    switch(buffer[0]) {

        case  FRAG_SESSION_SETUP_REQ : // TBD test all parameters
            printf("Receive FragSessionSetupReq\n");

            if( buffer_size == FRAG_SESSION_SETUP_REQ_LENGTH ) {
                FTMPackageParams.FragSession = buffer[1];
                FTMPackageParams.NbFrag = ( buffer[2] << 8 ) + buffer[3];
                FTMPackageParams.FragSize = buffer[4] ;
                FTMPackageParams.Encoding = buffer[5];
                FTMPackageParams.Redundancy = REDUNDANCYMAX-1;
                FotaParameterInit(FTMPackageParams.NbFrag , FTMPackageParams.Redundancy , FTMPackageParams.FragSize + 2);
                endOfTest = FRAGMENTATION_ON_GOING ;
                printf("Receive a Valid FRAG_SESSION_SETUP_REQ msg \n");
                SendFragSessionSetupAns( LORAWAN_FTMPACKAGE_PORT );
            } else {
                printf("Receive a FRAG_SESSION_SETUP_REQ msg with wrong length\n");
            }
            break;
        case  DATA_FRAGMENT : // TBD test all parameters
            if (firstFragment == 1)
            {
              firstFragment = 0;
            }
            if( buffer_size == FTMPackageParams.FragSize + 3 ) { // +3 because 2 for fcnt + 1 for cmd
                if (endOfTest == FRAGMENTATION_ON_GOING ) {
                    endOfTest= FragmentationDecodeCore(buffer+1,1);
                    printf("got some flashdata...\n");
                } else {
                    if (endOfTest >= 0) {
                        printf("FRAGMENT FULLY RECONSTRUCT WITH SUCCESS\n");
                        for (int q=0; q<150; q++) {
                            printf("\nFlashData[%d] = ",q);
                            for (int qq=0; qq<10; qq++) {
                                printf(" %d",FlashData[q][qq]);
                            }
                        }
                        SendDataBlockAuthReq( LORAWAN_FTMPACKAGE_PORT );
                        printf("Send a SendDataBlockAuthReq Msg\n");
                        endOfTest	= FRAGMENTATION_NOT_STARTED;
                        while(1){} // end of the demo
                    }
                }

            } else {
                printf("Receive a DATA_FRAGMENT with wrong length\n");
            }

    }

}

/*!
 * \brief	Function to send a ClassCSessionANS
 *
 * \param	[IN] port
 * \param [IN]
 * \param	[OUT] void
 */
bool SendFragSessionSetupAns( uint8_t port )
{
    printf("SendFragSessionSetupAns (port %d)\n", port);
}

/*!
 * \brief	Function to send a SendDataBlockAuthReq
 *
 * \param	[IN] port
 * \param [IN]
 * \param	[OUT] void
 */
bool SendDataBlockAuthReq( uint8_t port )
{
    printf("SendDataBlockAuthReq (port %d)\n", port);
}

