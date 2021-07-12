/**
 * main-state-machine-cpp
 *
*  Created on: Nov 10, 2020
 *      Author: J.cliff
 *
 *      Desc: This was written in Cpp but used no std cpp lib
 *
 *      It is an adaption of the state_design_pattern code written for remis switch
 *      program now written to be more event driven
 *
 *
 */

/** C Standard library */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

/** user library */
#include "stringToHex.h"


/** String to hex and vice versa */
int
hexToString(const uint8_t* hx_in
		, uint16_t h_len
		, uint8_t * hxOut
		, uint16_t hxOutSize)
{
	int buff_size = ( hxOutSize/2 ) - 2;

	if (h_len > buff_size){
		ep_log("<%s> DATA TOO LARGE\n", __FUNCTION__);
		return -1;
	}

	memset(hxOut, 0, hxOutSize);
	for(int i=0; i<h_len; i++){
		sprintf( (char*)hxOut+(i*2), "%02x", hx_in[i]);
	}

	ep_log("[%s]<> %s\n", __FUNCTION__, hxOut);
    return h_len;
}

/** String to hex and vice versa */
const char nib[][16]= {{0,10,11,12,13,14,15},{0,1,2,3,4,5,6,7,8,9}};
const char f = ~(0x3f);
const char f2 = 0x0f;
//16 is the maximum value of this guy

int
hexFromString(const uint8_t* hex
		, uint16_t h_len
		, uint8_t * hxOut
		, uint16_t hxOutSize)
{

	if (h_len > ( hxOutSize*2 ) ){
		ep_log("<%s> DATA TOO LARGE\n", __FUNCTION__);
		return -1;
	}

	memset(hxOut, 0, hxOutSize);
    int i=0, ret=0, j=0;
	while(i<h_len){
		//TODO: test algorithm speed as compared to 
		hxOut[i/2] = (nib[ !(hex[i] & f) ][ hex[i] & f2 ] << 4) 
		|  (nib[ !( hex[i+1] & f) ][ hex[i+1] & f2 ] ) ;

		// ret = sscanf( (const char*)hex+(i), "%02x", hxOut+(i/2));
        // if (ret != 1) break;
        ep_log("[%s]scanned: %d, hexvalue: %x\n", __FUNCTION__, ret, hxOut[i/2]);
		i = i+2;
		j++;
	}
    return j;
}

