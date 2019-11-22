#ifndef UDPTYPES_H_
#define UDPTYPES_H_
typedef unsigned char UInt8;

typedef unsigned short UInt16;

typedef unsigned int UInt32;

typedef unsigned long ULong32;

typedef unsigned long long UInt64;

struct HeatPdu
{
	UInt16 header;
	UInt8 Mac[6];
	UInt16 RequestId;
	UInt8 Code;
	UInt8 SubCode;
	UInt16 DataLength;
	UInt8 data[0];
}__attribute__((packed));
struct SendHeartPacket1
{
    UInt16 header;
    UInt8 Mac[6];
    UInt16 RequestId;
    UInt8 Code;
 	UInt8 SubCode;
 	UInt16 DataLength;

 	UInt8 VendorId1;
 	UInt8 VendorId2;
 	UInt8 VendorId3;
 	UInt8 VendorId4;
  	UInt32 VendorId;
	UInt32 Reserved;

}__attribute__((packed));


struct SendHeartAckPacket
{
    UInt16 header;
    UInt8 Mac[6];
    UInt16 RequestId;
    UInt8 Code;
 	UInt8 SubCode;
 	UInt16 DataLength;

 	UInt32 Reserved;



}__attribute__((packed));

struct SendNakPacket
{
  UInt16 p1;
  UInt16 p2;
  UInt16 req;
  UInt32 p3;



}__attribute__((packed));

struct RecvD5Packet
{

	UInt8 T;
	UInt8 Mac[6];
	UInt16 SeqControl;
	UInt16 FrameControl;
	UInt8 RSSIType;
	UInt16 RSSI;
	UInt8 NoiseType;
	UInt16 Noise;
	UInt8 TxChannel;
	UInt8 RxChannel;
	UInt32 DataRate;
	UInt32 Time;
	UInt8 CurAssocFlag;
	UInt8 RadioMac[6];
	UInt8 RadiType;
	UInt8 AssocFlag;
	UInt8 AssocBSSID[6];
	UInt8 AssocSSID[32];
	UInt8 AssocSecurity;

}__attribute__((packed));
#endif /* UDPTYPES_H_ */
