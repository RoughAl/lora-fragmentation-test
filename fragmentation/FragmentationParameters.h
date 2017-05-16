/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2016 Semtech

Description: 	Firmware update over the air with LoRa proof of concept
				Functions for the fragmentation parameters

By: Paul Marcelis
*/
#ifndef __FRAGMENTATION_PARAMETERS_H
#define __FRAGMENTATION_PARAMETERS_H

class FragmentationParameters
{
public:
    static int m2fragNb( int m )
    {
        static const int fragNbConversion[] = { 32, 40, 48, 56, 64 };
        for( int i = 0; i < sizeof( fragNbConversion ) / sizeof( fragNbConversion[0] ); i++ )
        {
            if ( fragNbConversion[i] == m )
            {
                return i;
            }
        }
        return -1;
    }
    static int fragNb2m( int fragNb )
    {
        static const int fragNbConversion[] = { 32, 40, 48, 56, 64 };
        if( fragNb > 0 || fragNb < sizeof( fragNbConversion ) / sizeof( fragNbConversion[0] ) )
        {
            return fragNbConversion[fragNb];
        }
        return -1;
    }
    static int fpf2fragPerFrame( int fpf )
    {
        static const int fragPerFrameConversion[] = { 1, 2, 4, 8, 16 };
        for( int i = 0; i < sizeof( fragPerFrameConversion ) / sizeof( fragPerFrameConversion[0] ); i++ )
        {
            if( fragPerFrameConversion[i] == fpf )
            {
                return i;
            }
        }
        return -1;
    }
    static int fragPerFrame2fpf( int fragPerFrame )
    {
        static const int fragPerFrameConversion[] = { 1, 2, 4, 8, 16 };
        if( fragPerFrame > 0 || fragPerFrame < sizeof( fragPerFrameConversion ) / sizeof( fragPerFrameConversion[0] ) )
        {
            return fragPerFrameConversion[fragPerFrame];
        }
        return -1;
    }
};

#endif


