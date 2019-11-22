/*
 * CDbConnection.h
 *
 *  Created on: Dec 4, 2017
 *      Author: lyd
 */

#ifndef CDBCONNECTION_H_
#define CDBCONNECTION_H_
#include "IDatabase.h"

#include "mysql.h"
namespace sqr
{
	class CDatabase;
	class CDbResult;

	class CDbConnection
		:public IDbConnection
	{
	private:
		CDatabase*	m_pDatabase;
		void*		m_pTag;

		CDbResult* GetResult(int nQueryReturnCode);
	public:
		MYSQL* m_pMySql;

		CDbConnection(CDatabase* pDatabase,const char* szHost,uint16 uPort
			,const char* szUser,const char* szPassword,const char* szDatabase);
		CDbConnection(CDatabase* pDatabase,const char* szPipe
			,const char* szUser,const char* szPassword,const char* szDatabase);

		virtual ~CDbConnection();
        bool Ping();

		void Execute(const char* szSqlBuffer);
		void Execute(const char* szSqlBuffer,uint32 uSize);


		void SetTag(void* pTag);
		void* GetTag()const;

		void Release();
	};
}
#endif /* CDBCONNECTION_H_ */
