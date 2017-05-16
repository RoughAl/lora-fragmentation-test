/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2016 Semtech

Description: 	Firmware update over the air with LoRa proof of concept
				Functions for the decoding


*/
#ifndef __FRAGMENTATION_DECODE_H
#define __FRAGMENTATION_DECODE_H
#include "mbed.h"
#define NBOFUTILFRAMEMAX 200
#define SIZEOFFRAMETRANSMITMAX 204 //204

#define REDUNDANCYMAX 120
#define REDUNDANCYMAXB REDUNDANCYMAX/8

#define EXTRABYTELORAWAN 2 // fcnt

static enum eFragmentationDecodeStatus {
    DECODE_IDLE,
    DECODE_RECEIVING,
    DECODE_COMPLETE
} FragmentationDecodeStatus = DECODE_IDLE;

typedef enum {
    DECODE_NO_ERROR,
    DECODE_UNKNOWN_ERROR,
    DECODE_ERROR_FRAGMENTATION_DONE,
    DECODE_ERROR_ALL_FRAGMENTS_FOUND,
    DECODE_ERROR_M_VALUE_INCORRECT,
    DECODE_ERROR_FPF_VALUE_INCORRECT,
    DECODE_ERROR_ALL_FRAGMENTS_RECEIVED,
    DECODE_ERROR_NOT_IN_CORRECT_STATE,
    DECODE_ERROR_NO_FRAME_WITH_FRAGMENTS,
    DECODE_ERROR_FRAGMENTATION_PARAMS_INCONSISTENT
} eFragmentationDecodeError;

typedef enum {
    DECODE_RESULT_ERROR,
    DECODE_RESULT_RECEIVING,
    DECODE_RESULT_COMPLETE,
    DECODE_RESULT_DONE
} eFragmentationDecodeResultType;

struct sFragmentationDecodeResult {
    eFragmentationDecodeResultType type;

    // type DECODE_RESULT_ERROR
    eFragmentationDecodeError error;

    // type DECODE_RESULT_RECEIVING
    int fragID;
    int fragmentsFound;
    int M;

    // type DECODE_RESULT_DONE
    unsigned char *data;
    unsigned long dataCRC;
    int dataSize;
    int fragmentsNeeded;
    // also int fragID;
};

sFragmentationDecodeResult FragmentationDecodeReceiveFrame( unsigned char *, const int );
sFragmentationDecodeResult FragmentationDecode( void );
bool FragmentationDecodeReset( bool );

struct FotaParameter {
    int M; // NbOfUtilFrames=SIZEOFFRAMETRANSMIT;
    int Redundancy; // nbr of extra frame
	  int DataSize;   // included the lorawan specific data hdr,devadrr,...but without mic and payload decrypted
	  int LastReceiveFrameCnt;
    int NumberOfLoosingFrame;
    uint32_t MissingFrameIndex[NBOFUTILFRAMEMAX];
	  uint8_t MatrixM2B[REDUNDANCYMAXB*REDUNDANCYMAX];
};
extern FotaParameter sFotaParameter;
extern uint8_t FlashData[NBOFUTILFRAMEMAX][SIZEOFFRAMETRANSMITMAX];
extern uint8_t FlashDataa[1024 * 8];
void StoreRowInFlash( uint8_t* rowData, int index, int bank );
int CatchFrameCounter( uint8_t* rowData );
void FotaParameterInit( int M, int Redundancy, int DataSize );
void FindMissingReceiveFrame( int  frameCounter );
int FragmentationDecodeCore( uint8_t* rowData, int bank ) ;
void XorLineData( uint8_t* dataL1,uint8_t* dataL2, int size);
void XorLineBool( bool* dataL1,bool* dataL2, int size);
void GetRowInFlash(int l, uint8_t* rowData );
int  FindMissingFrameIndex ( int x );
int FindFirstOne( bool* boolData, int size);
bool VectorIsNull( bool* boolData, int size);
void RemoveLoraExtraByte ( uint8_t* rowData, int size);
void PushLineToBinaryMatrix( bool* boolVector, int rownumber, int numberOfBit);
void ExtractLineFromBinaryMatrix( bool* boolVector, int rownumber, int numberOfBit);
#endif

