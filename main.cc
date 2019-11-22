#include <evpp/udp/udp_server.h>
#include <evpp/udp/udp_message.h>
#include <evpp/event_loop.h>
#include <evpp/event_loop_thread_pool.h>
#include <glog/logging.h>
#ifdef _WIN32
#include "../../winmain-inl.h"
#endif
#include "UdpTypes.h"
#include "UdpDecoder.h"

#include "IDatabase.h"
#include <time.h>
#include <iostream>
using namespace std;
using namespace sqr;

sqr::IDatabase *db=NULL;
IDbConnection *conn = NULL;
int main(int argc, char* argv[]) {
    std::vector<int> ports = { 1053, 5353 };
    int port = 9091;
    int thread_num = 2;
//    google::InitGoogleLogging(argv[0]);


    if (argc > 1) {
        if (std::string("-h") == argv[1] ||
            std::string("--h") == argv[1] ||
            std::string("-help") == argv[1] ||
            std::string("--help") == argv[1]) {
            std::cout << "usage : " << argv[0] << " <listen_port> <thread_num>\n";
            std::cout << " e.g. : " << argv[0] << " 8080 24\n";
            return 0;
        }
    }

    if (argc == 2) {
        port = atoi(argv[1]);
    }
    ports.push_back(port);

    if (argc == 3) {
        port = atoi(argv[1]);
        thread_num = atoi(argv[2]);
    }
 //   static int ireq = 1;
    db = GetDatabase();
    conn =db->CreateConnection("localhost",3306,"root","hradmin12341234","beewifi");
    evpp::udp::Server server;
    server.SetThreadDispatchPolicy(evpp::ThreadDispatchPolicy::kIPAddressHashing);
    server.SetMessageHandler([](evpp::EventLoop* loop, evpp::udp::MessagePtr& msg) {
        std::stringstream oss;
        oss << "func=" << __FUNCTION__ << " OK"
            << " body=" << std::string(msg->data(), msg->size()) << "\n";
    //   LOG(INFO)<<"hello,glog";
 //database zhushi

        std::cout<<"msg data:";
        std::cout<<msg->data()<<std::endl;
        std::cout<<"msg size:";
        std::cout<<msg->size()<<std::endl;

        struct HeatPdu* pp;
        pp =  (struct HeatPdu*)(msg->data());

        std::string ipaddr = "";
        ipaddr = msg->remote_ip();
        std::cout<<ipaddr<<std::endl;
        evpp_socket_t fd;
        fd = msg->sockfd();
        const struct sockaddr* sockaddr;
        sockaddr = msg->remote_addr();

        if(pp->Code)
        {
        UInt8 Code =  pp->Code;


        std::cout<<"Code is:"<<std::hex<<(int)Code<<std::endl;
        if(Code == 0xD1)
        {
              SendHeartAckPacket sendAckPacket;
                sendAckPacket.header = htons(25986);
                sendAckPacket.Mac[0] = 0x70;
                sendAckPacket.Mac[1] = 0x65;
                sendAckPacket.Mac[2] = 0x82;
                sendAckPacket.Mac[3] = 0xd8;
                sendAckPacket.Mac[4] = 0x9d;
                sendAckPacket.Mac[5] = 0xa0;
                sendAckPacket.RequestId = htons(1);
                sendAckPacket.Code = 0xB1;
                sendAckPacket.SubCode = 0x00;
                sendAckPacket.DataLength = htons(4);
                sendAckPacket.Reserved = htonl(0);
                struct SendHeartAckPacket *send2 = &sendAckPacket;

                evpp::udp::Message sendmsg1(fd,18);

                    sendmsg1.set_remote_addr(*sockaddr);
                   sendmsg1.Write(send2,18);


               evpp::udp::SendMessage(fd,sockaddr,sendmsg1.data(),sendmsg1.size());

        }
        }
        if(pp->SubCode)
        {

        UInt8 SubCode = pp->SubCode;

        std::cout<<"SubCode is:"<<std::hex<<(int)SubCode<<std::endl;
        }


        if(pp->Code && pp->SubCode)
        {
        UInt8 Code =  pp->Code;
        UInt8 SubCode = pp->SubCode;

      //  std::cout<<"Code is:"<<std::hex<<(int)Code<<std::endl;
        if((Code == 0xD5) && (SubCode == 0x04))
        {
        //if d5

            std::cout<<"d5 is right"<<std::endl;
            struct RecvD5Packet* ppd5;
            ppd5 =  (struct RecvD5Packet*)(pp->data);
            UInt8 T = ppd5->T;
            UInt8 Mac[6];
            Mac[0] = ppd5->Mac[0];
            Mac[1] = ppd5->Mac[1];
            Mac[2] = ppd5->Mac[2];
            Mac[3] = ppd5->Mac[3];
            Mac[4] = ppd5->Mac[4];
            Mac[5] = ppd5->Mac[5];
            UInt16 SeqControl = (UInt16)ntohs(ppd5->SeqControl);
            UInt16 FrameControl =(UInt16)ntohs(ppd5->FrameControl);
            UInt8 RSSIType =ppd5->RSSIType;
            UInt16 RSSI =(UInt16)ntohs(ppd5->RSSI);
            short pRSSI = RSSI;
            UInt8 NoiseType=ppd5->NoiseType;
            UInt16 Noise=(UInt16)ntohs(ppd5->Noise);
             short pNoise=Noise;
            UInt8 TxChannel =ppd5->TxChannel;
            UInt8 RxChannel=ppd5->RxChannel;
            UInt32 DataRate=(UInt32)ntohl(ppd5->DataRate);
            UInt32 Time=(UInt32)ntohl(ppd5->Time);
            long pTime = Time;
            UInt8 CurAssocFlag=ppd5->CurAssocFlag;
            UInt8 RadioMac[6];

            UInt8 RadiType=ppd5->RadiType;
            UInt8 AssocFlag=ppd5->AssocFlag;
            UInt8 AssocBSSID[6];

            UInt8 AssocSSID[32];

            UInt8 AssocSecurity=ppd5->AssocSecurity;

            std::cout<<"d5 is start"<<std::endl;
            std::cout<<"T is:"<<std::hex<<(int)T<<";"<<"MAc is:"<<std::hex<<(int)(Mac[0])<<";"<<std::hex<<(int)(Mac[1])<<";"<<std::hex<<(int)(Mac[2])<<";"<<std::hex<<(int)(Mac[3])<<";"<<std::hex<<(int)(Mac[4])<<";"<<std::hex<<(int)(Mac[5])<<";" <<std::endl;
            std::cout<<"SeqControl is:"<< (int)SeqControl<<";"<<"FrameControl is:"<<(int)FrameControl<<";"<<"RSSIType is:"<<std::hex<<(int)RSSIType<<";"<<std::endl;
            std::cout<<"RSSI is:"<< (int)(RSSI) <<";"<<"NoiseType is:"<<(int)NoiseType<<";"<<"Noise is:"<<(int)Noise<<";"<<std::endl;
            std::cout<<"TxChannel is:"<<std::hex<<(int)TxChannel<<";"<<"RxChannel is:"<<std::hex<<(int)RxChannel<<";"<<"DataRate is:"<<std::hex<<(int)DataRate<<";"<<std::endl;
            std::cout<<"Time is:"<<std::hex<<(int)Time<<";"<<"CurAssocFlag is:"<<std::hex<<(int)CurAssocFlag<<";"<<"RadioMac is:"<<std::hex<<(int)(RadioMac[0])<<";";
            std::cout<<std::hex<<(int)(RadioMac[1])<<";"<<std::endl;

            UInt8 OMac[6];
            OMac[0] = pp->Mac[0];
            OMac[1] = pp->Mac[1];
            OMac[2] = pp->Mac[2];
            OMac[3] = pp->Mac[3];
            OMac[4] = pp->Mac[4];
            OMac[5] = pp->Mac[5];
            char ppmac[30];
            sprintf(ppmac,"%02x:%02x:%02x:%02x:%02x:%02x",int(OMac[0]),int(OMac[1]),int(OMac[2]),int(OMac[3]),int(OMac[4]),int(OMac[5]));
            char Apmac[30];
            sprintf(Apmac,"%02x:%02x:%02x:%02x:%02x:%02x",int(Mac[0]),int(Mac[1]),int(Mac[2]),int(Mac[3]),int(Mac[4]),int(Mac[5]));
          //  time_t tick = (long int)Time;
          // time_t tick =(time_t)Time;
             //struct tm tm;
           //  tm = *localtime(&tick);
            /*
             long int second =(long int)Time;
               int year = 1970, month = 1, day = 1;
               int hour = 0, minute = 0;

               long int minuteSecond = 60;
               long int hourSecond = 60*minuteSecond;
               long int daySecond = 24*hourSecond;
               long int monthSecond = 30*daySecond;
               long int yearSecond = 12*monthSecond;
               if (second > yearSecond)
               {
                   int x = second/yearSecond;
                   year += x;
                   second -= x*yearSecond;

               }
               if (second > monthSecond)
               {
                   int x = second/monthSecond;
                   month += x;
                   second -= x*monthSecond;
               }
               if (second > daySecond)
               {
                   int x = second/daySecond;
                   day += x;
                   second -= x*daySecond;
               }
               if (second > hourSecond)
               {
                   int x = second/hourSecond;
                   hour += x;
                   second -= x*hourSecond;
                }
               if (second > minuteSecond)
               {
                   int x = second/minuteSecond;
                   minute += x;
                   second -= x*minuteSecond;
               }
               char buff[] = "1970/01/01 00:00:10";
               sprintf(buff,"%d-%02d-%02d %02d:%02d:%02d", year, month, day, hour, minute, second);
        */




            RadioMac[0] = ppd5->RadioMac[0];
            RadioMac[1] = ppd5->RadioMac[1];
            RadioMac[2] = ppd5->RadioMac[2];
            RadioMac[3] = ppd5->RadioMac[3];
            RadioMac[4] = ppd5->RadioMac[4];
            RadioMac[5] = ppd5->RadioMac[5];
            char radiomac[30];
            sprintf(radiomac,"%02x:%02x:%02x:%02x:%02x:%02x",int(RadioMac[0]),int(RadioMac[1]),int(RadioMac[2]),int(RadioMac[3]),int(RadioMac[4]),int(RadioMac[5]));
        //     char s[100];
          //  strftime(s,sizeof(s),"%Y-%m-%d %H:%M:%S",&tm);

            AssocBSSID[0] = ppd5->AssocBSSID[0];
            AssocBSSID[1] = ppd5->AssocBSSID[1];
            AssocBSSID[2] = ppd5->AssocBSSID[2];
            AssocBSSID[3] = ppd5->AssocBSSID[3];
            AssocBSSID[4] = ppd5->AssocBSSID[4];
            AssocBSSID[5] = ppd5->AssocBSSID[5];
            char Assocmac[30];
            sprintf(Assocmac,"%02x:%02x:%02x:%02x:%02x:%02x",int(AssocBSSID[0]),int(AssocBSSID[1]),int(AssocBSSID[2]),int(AssocBSSID[3]),int(AssocBSSID[4]),int(AssocBSSID[5]));

          try
          {
            char sqlquery[800];
            sprintf(sqlquery,"insert into originalsignalrecord values(0,'%s','%s',FROM_UNIXTIME(%ld),'%d','%d','%d','%d',b'%d','%d','%d','%d','%d','%s','%d','%s',b'%d')",ppmac,Apmac,pTime,pRSSI ,int(RSSIType),int(NoiseType),pNoise,int(AssocFlag),int(RxChannel),int(TxChannel),int(Code),int(DataRate),radiomac,(int)RadiType,Assocmac,int(CurAssocFlag));
            std::cout<<sqlquery<<std::endl;
            conn->Execute(sqlquery);
          }
          catch(std::exception e)
          {
        	  char clearquery[200] = " truncate table originalsignalrecord";

        	  conn->Execute(clearquery);

          }
               //conn->Execute("drop table heltest");
               //TextResult->Release();


        }
        }


        UInt16 datalength = (UInt16) ntohs(pp->DataLength);
        std::cout<<"Data length is :"<<datalength<<std::endl;
        if(pp->DataLength == 0x0004)
        	std::cout<<" Data length is right"<<std::endl;
        UInt8 *phe =(UInt8 *)msg->data();
        UInt32 psize = msg->size();
        evpp::udp::UdpDecoder UdpDe(phe,psize);
       UInt16 aas = UdpDe.GetHeader();
       std::cout<<"2 head_0:";
       std::cout<<std::hex<<aas<<std::endl;

        std::cout<<"getword32_2:";
        std::cout<<UdpDe.GetWord32(2)<<std::endl;

        std::cout<<"getword32_code_10:";
        std::cout<<UdpDe.GetWord32(10)<<std::endl;



        std::cout<<"getword32_datalength_12:";
        std::cout<<std::hex<<UdpDe.GetWord32(12)<<std::endl;
        std::cout<<"GetHeadMac64_0:";
        std::cout<<std::hex<<UdpDe.GetHeadMac(0)<<std::endl;
        std::cout<<"getHeadMac64_8:";
        std::cout<<std::hex<<UdpDe.GetHeadMac(8)<<std::endl;
        std::cout<<"getHeadMac64_16:";
        std::cout<<std::hex<<UdpDe.GetHeadMac(16)<<std::endl;
        std::cout<<"getHeadMac64_24:";
        std::cout<<std::hex<<UdpDe.GetHeadMac(24)<<std::endl;
        std::cout<<"getHeadMac64_32:";
          std::cout<<std::hex<<UdpDe.GetHeadMac(32)<<std::endl;

          std::cout<<"getHeadMac64_40:";
                std::cout<<std::hex<<UdpDe.GetHeadMac(40)<<std::endl;
                std::cout<<"getHeadMac64_48:";
                         std::cout<<std::hex<<UdpDe.GetHeadMac(48)<<std::endl;
        SendHeartPacket1 sendPacket1;
        sendPacket1.header = htons(25986);
        sendPacket1.Mac[0] = 0x70;
        sendPacket1.Mac[1] = 0x65;
        sendPacket1.Mac[2] = 0x82;
        sendPacket1.Mac[3] = 0xd8;
        sendPacket1.Mac[4] = 0x9d;
        sendPacket1.Mac[5] = 0xa0;
        sendPacket1.RequestId = htons(1);
        sendPacket1.Code = 209;
        sendPacket1.SubCode = 0;
        sendPacket1.DataLength = htons(8);

        sendPacket1.VendorId1 = 0x00;
         sendPacket1.VendorId2 = 0x70;
        sendPacket1.VendorId3 = 0x65;
         sendPacket1.VendorId4 = 0x82;
       //  UInt32 ht = 0x00706582;
    //     sendPacket1.VendorId = htonl(ht);
        sendPacket1.Reserved = htonl(0);


   //     struct SendHeartPacket1 *send1 = &sendPacket1;




    //Nak
        SendNakPacket sendNak;
/*
        sendNak.p1 = htons(3);
        sendNak.p2= htons(6);
        sendNak.req = htons(ireq++);
        sendNak.p3 = htonl(1);
        struct SendNakPacket *send3 = &sendNak;
*/


     /*
         evpp::udp::Message sendmsg1(fd,18);

         sendmsg1.set_remote_addr(*sockaddr);
        sendmsg1.Write(send2,18);
*/

     //   evpp::udp::Message sendmsg1(fd,10);

       //     sendmsg1.set_remote_addr(*sockaddr);
    //       sendmsg1.Write(send3,10);
      //  const char* a2 = "sfdfsd";;
     //   evpp::udp::SendMessage(fd,sockaddr,(const char*)send1,22);


      //  evpp::udp::SendMessage(fd,sockaddr,a3);


     //    evpp::udp::SendMessage(fd,sockaddr,a2,10);

    ///   evpp::udp::SendMessage(fd,sockaddr,sendmsg1.data(),sendmsg1.size());
      //  evpp::udp::MessagePtr sendmsg(new evpp::udp::Message(fd,10));

       //   evpp::udp::MessagePtr sendmsg1(fd,10);
    //    sendmsg1->set_remote_addr(*sockaddr);


      //   evpp::udp::SendMessage(sendmsg);

//write database
        /*
        sqr::IDatabase *db = GetDatabase();
        IDbConnection *conn =db->CreateConnection("192.168.1.101",3306,"zhen","123","hmpe");
        conn->Execute("insert into heltest values('1001','lyd')");
        //conn->Execute("drop table heltest");
        //TextResult->Release();
        conn->Release();
        db->Release();

 */

//jiexin d5
        /*
               std::cout<<"msg data:";
               std::cout<<msg->data()<<std::endl;
               std::cout<<"msg size:";
               std::cout<<msg->size()<<std::endl;
               struct RecvD5Packet* pprecvd5;
               pprecvd5 =  (struct RecvD5Packet*)(msg->data());
               if(pprecvd5->Code)
               {
               UInt8 Code =  pprecvd5->Code;


               std::cout<<"Code is:"<<std::hex<<(int)Code<<std::endl;

               UInt8 Code1 = 0xB1;


               std::cout<<"Code1 is:"<<std::hex<<(int)Code1<<std::endl;

               if(Code == Code1)
               	std::cout<<"Code is equal Code1"<<std::endl;
               }
               if(pprecvd5->SubCode)
               {

               UInt8 SubCode = pprecvd5->SubCode;

               std::cout<<"SubCode is:"<<std::hex<<(int)SubCode<<std::endl;
               }
               */

    });
    server.Init(ports);
   // server.Init(port);
    server.Start();

    evpp::EventLoop loop;
    std::shared_ptr<evpp::EventLoopThreadPool> tpool(new evpp::EventLoopThreadPool(&loop, thread_num));
    tpool->Start(true);
    server.SetEventLoopThreadPool(tpool);
    loop.Run();
    server.Stop(true);
    tpool->Stop(true);
    conn->Release();
    db->Release();
  //  google::ShutdownGoogleLogging();
    return 0;
}
