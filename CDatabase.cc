/*
 * CDatabase.cpp
 *
 *  Created on: Dec 4, 2017
 *      Author: lyd
 */
#include "CDbConnection.h"
#include "CDatabase.h"

namespace sqr
{
	IDatabase* GetDatabase()
	{
		return new CDatabase;
	}

	IDbConnection* CDatabase::CreateConnection(const char* szHost,uint16 uPort,
		const char* szUser,const char* szPassword,
		const char* szDatabase)
	{
		return new CDbConnection(this,szHost,uPort,szUser,szPassword,szDatabase);
	}

	IDbConnection* CDatabase::CreateConnection(const char* szPipe,
		const char* szUser,const char* szPassword,
		const char* szDatabase)
	{
		return new CDbConnection(this,szPipe,szUser,szPassword,szDatabase);
	}

	void CDatabase::Release()
	{
		delete this;
	}
}
