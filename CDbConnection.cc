/*
 * CDbConnection.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: lyd
 */
#include "IDatabase.h"
#include "CDbConnection.h"

namespace sqr
{

	CDbConnection::CDbConnection(CDatabase* pDatabase,const char* szHost,uint16 uPort
		,const char* szUser,const char* szPassword,const char* szDatabase)
		:m_pDatabase(pDatabase),m_pTag(NULL)
	{
		m_pMySql = mysql_init(NULL);
		/*
		if (!m_pMySql)
		{
	//		ostringstream strm;
	//		strm<<"mysql_init failed with error:"<<mysql_error(m_pMySql)<<ends;

		}
		*/

		MYSQL* pResult=mysql_real_connect(m_pMySql, szHost, szUser,szPassword,szDatabase, uPort, NULL, 0);
     /*
		if(m_pMySql != pResult)
		{
	//		ostringstream strm;
	//		strm<<"mysql_real_connect failed with error:"<<mysql_error(m_pMySql)<<ends;

		}
		*/

	}

	CDbConnection::CDbConnection(CDatabase* pDatabase,const char* szPipe
		,const char* szUser,const char* szPassword,const char* szDatabase)
		:m_pDatabase(pDatabase)
	{
		m_pMySql = mysql_init(NULL);
		/*
		if (!m_pMySql)
		{
	//		ostringstream strm;
//			strm<<"mysql_init failed with error:"<<mysql_error(m_pMySql)<<ends;

		}
       */
		MYSQL* pResult=mysql_real_connect(m_pMySql, NULL, szUser,szPassword,szDatabase, 0, szPipe, 0);
/*
		if(m_pMySql != pResult)
		{
	//		ostringstream strm;
	//		strm<<"mysql_real_connect failed with error:"<<mysql_error(m_pMySql)<<ends;

		}
		*/

	}

	CDbConnection:: ~CDbConnection()
	{

		mysql_close(m_pMySql);
	}




	bool CDbConnection::Ping()
	{
		return 0==mysql_ping(m_pMySql);
	}


	CDbResult* CDbConnection::GetResult(int nQueryReturnCode)
	{

		return NULL;
	}

	void CDbConnection::Execute(const char* szSqlBuffer)
	{
		int res;
		res = mysql_query(m_pMySql,szSqlBuffer);

	}

	void CDbConnection::Execute(const char* szSqlBuffer,uint32 uSize)
	{
		int res;
		res = mysql_real_query(m_pMySql,szSqlBuffer,uSize);

	}



	void CDbConnection::Release()
	{
		delete this;
	};

	void CDbConnection::SetTag(void* pTag)
	{
		m_pTag=pTag;
	}

	void* CDbConnection::GetTag()const
	{
		return m_pTag;
	}

}
