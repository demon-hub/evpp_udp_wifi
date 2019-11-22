
#ifndef CIDATABSE_H_
#define CIDATABSE_H_
#include "Database.h"
#include "CObject.h"

namespace sqr
{
class IDbTextResult
          :public sqr::CObject
           {
           public:
	       virtual void Release() = 0;

           };

class IDbConnection
      :public sqr::CObject{
public:
    virtual void Execute(const char* szSqlBuffer,uint32 uSize) = 0;
    virtual void Execute(const char* szSqlBuffer) = 0;
    virtual void Release()= 0;
    virtual void SetTag(void* pTag) = 0;
    virtual void* GetTag()const = 0;
    virtual bool Ping() = 0;

 };
class IDatabase:public sqr::CObject
     {
	public:
		virtual IDbConnection* CreateConnection(const char* szHost,uint16 uPort,
			const char* szUser,const char* szPassword,
			const char* szDatabase)=0;

		virtual IDbConnection* CreateConnection(const char* szPipe,//under unix is this unixsocket
			const char* szUser,const char* szPassword,
			const char* szDatabase)=0;

		virtual void Release()=0;
	};
	
	
	 IDatabase* GetDatabase();
}

#endif
