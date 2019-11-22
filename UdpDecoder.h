/*
 * UdpDecoder.h
 *
 *  Created on: Dec 6, 2017
 *      Author: lyd
 */

#ifndef UDPDECODER_H_
#define UDPDECODER_H_
#include "UdpTypes.h"
namespace evpp {
namespace udp {

class UdpDecoder  {
public:
	UdpDecoder(UInt8* inPacket,UInt32 inPacketLen):mpPacket(inPacket),mPacketlen(inPacketLen)
    {

    }
	virtual ~UdpDecoder()
	{

	}
public:
	enum day1 {
			KRTCPVersionSupported = 2,
			KRTCPHeaderSize = 8,
			KRTCPSrcIDSize =4
		};
	enum day2 {
			KVersionOffset = 0,
			KVersionMask = 0xC0000000UL,
			KVersionShift = 30,
			KPaddingOffset = 0,
			KPaddingMask = 0x20000000UL,
			kPaddingShift = 29,
			KReportCoutOffset = 0,
			kReportCoutMask = 0x1F000000UL,
			KReportCoutShift =24,
			KPacketTypeOffset = 0,
			KPacketTypeMask = 0x00ff0000UL,
			KPacketTypeShift = 16,
			KPacketLengthOffset = 0,
			KPacketLengthMask = 0x0000FFFFUL,
			kPacketLengthShift = 0,
			KPacketSSrcIDOffset = 4
		};
protected:
   UInt8* GetPacket(UInt32 byteOffset = 0) ;

public:
  //  UInt16 GetHeader();
    unsigned char mac[6];
    UInt16 GetHeader();
    UInt32 GetApMac();

    UInt64 GetHeadMac(UInt32 byteOffset);
    UInt32 GetPacketSize()  ;

    UInt16 GetPacketLength() ;


    UInt32 GetWord32(UInt32 byteOffset)  ;
    UInt32 GetWord32(UInt32 byteOffset, UInt32 mask) ;
    UInt32 GetWord32(UInt32 byteOffset,UInt32 mask, UInt32 shift) ;

private:
    UInt8* mpPacket;   //pointer to the incmming udp packet
    UInt32 mPacketlen; //length of te incoming udp packet
};

} /* namespace udp */
} /* namespace evpp */

#endif /* UDPDECODER_H_ */
