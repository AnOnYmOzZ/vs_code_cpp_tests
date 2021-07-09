/** 
 * @file 	sdp_efueling_c_lib_main.h
 * 
 * @brief 	A description of the above named module in "cpp-test-programs".
 *
 * @details
 * @date 	Jul 6, 2021
 * @author 	jcliff
 *
 * @par       
 *
 * 			COPYRIGHT NOTICE: (c) 2020 fuelmetrics.  All rights reserved.
 */ 

#ifndef SDP_EFUELING_C_LIB_H_
#define SDP_EFUELING_C_LIB_H_

#include "ep_main.h"


int 
hexToString(uint8_t* hex
		, uint16_t h_len
		, uint8_t * hxOut
		, uint16_t hxOutLen);

int
hexFromString(uint8_t* hex
		, uint16_t h_len
		, uint8_t * hxOut
		, uint16_t hxOutSize);


#endif /* SDP_EFUELING_C_LIB_H_ */
/***** END OF FILE ******/
