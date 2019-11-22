/*
 * UdpDecoder.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: lyd
 */
#include "udp/udp_server.h"
#include "udp/udp_message.h"
#include "UdpDecoder.h"
#include "UdpTypes.h"
namespace evpp {
namespace udp {
//network to host long 64
UInt64  ntohl64(UInt64 host)
{
	UInt64   ret = 0;
	UInt64   high,low;
	low   =   host & 0xFFFFFFFF;
	high   =  (host >> 32) & 0xFFFFFFFF;
	low   =   ntohl(low);
	high   =   ntohl(high);
	ret   =   low;
	ret   <<= 32;
	ret   |=   high;
	return   ret;
}
 UInt8* UdpDecoder::GetPacket(UInt32 byteOffset)
		{
		  return &mpPacket[byteOffset];
		}


UInt16 UdpDecoder::GetHeader()
{
	return (UInt16) ntohs(*(UInt16*)GetPacket());
}



UInt32 UdpDecoder::GetPacketSize()
		{
	    return (GetPacketLength() + 1) * sizeof(UInt32);
		}

UInt16 UdpDecoder::GetPacketLength()
		{
	   return (UInt16) GetWord32(day2::KPacketLengthOffset,day2::KPacketLengthMask);
		}

  UInt32 UdpDecoder::GetWord32(UInt32 byteOffset)
		{
	     return ntohl(*(UInt32*)GetPacket(byteOffset));
		}

  UInt32 UdpDecoder::GetWord32(UInt32 byteOffset, UInt32 mask)
		{
	     return GetWord32(byteOffset) & mask;
		}
 UInt32 UdpDecoder::GetWord32(UInt32 byteOffset , UInt32 mask ,UInt32 shift )
		{
	    return GetWord32(byteOffset,mask) >>shift;
		}
 UInt32 UdpDecoder::GetApMac()
 {

	 UInt32 macp4 = GetWord32(2);
	 mac[0] =  (macp4>>24);
	 mac[1] =  ((macp4>>16)&0x00ff);
	 mac[2] =  ((macp4>>8)&0x0000ff);
	 mac[3] = (macp4&0x000000ff);
	 UInt32 mach2 = GetWord32(6);
	 mac[4] =(mach2>>24);
	 mac[5] =  ((mach2>>16)&0x00ff);
 }
 UInt64 UdpDecoder::GetHeadMac(UInt32 byteOffset)
 {
	 return (UInt64) ntohl64(*(UInt64*)GetPacket(byteOffset));
 }
} /* namespace udp */
} /* namespace evpp */
