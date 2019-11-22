#ifndef _CMYSQLDBRESULT_H_
#define _CMYSQLDBRESULT_H_

#include "IDatabase.h"

namespace sqr
{

	class CDbResult
		:public IDbTextResult
	{

	public:
		CDbResult();

		virtual ~CDbResult();
        void Release();


	};

}

#endif
