/*
 * CDatabase.h
 *
 *  Created on: Dec 4, 2017
 *      Author: lyd
 */

#ifndef CDATABASE_H_
#define CDATABASE_H_


#include "IDatabase.h"


namespace sqr
{

	class CDatabase
		:public IDatabase
	{
	public:

		IDbConnection* CreateConnection(const char* szHost,uint16 uPort,
			const char* szUser,const char* szPassword,
			const char* szDatabase);

		IDbConnection* CreateConnection(const char* szPipe,
			const char* szUser,const char* szPassword,
			const char* szDatabase);

		void Release();
	};

}

#endif /* CDATABASE_H_ */
