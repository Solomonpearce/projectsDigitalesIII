/*
 * LabS.h
 *
 *  Created on: March 2024 
 *      Authors: HAGG - JCMM
 */



#ifndef LABS_H
#define LABS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define BITS_PER_BYTE 8
#define Longitud 256


uint8_t Bec[Longitud * 12]; // Array de bytes para encode
uint8_t *BitsToBytes(uint8_t *b, size_t length);
uint8_t *BytesToBits(uint8_t* B, int l);
uint8_t *ByteEncode(int F[Longitud]);
uint8_t *ByteDecode(uint8_t *B, int d);
uint8_t *SampleNTT(uint8_t *B);
uint8_t *SamplePolyCBD(uint8_t *B);


#endif // LABS_H