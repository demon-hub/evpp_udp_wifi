/*
 * CDbResult.cpp
 *
 *  Created on: Dec 5, 2017
 *      Author: lyd
 */
#include "CDbResult.h"

namespace sqr
{

	CDbResult::CDbResult()

	{

	}


	CDbResult::~CDbResult()
	{

	}


   void CDbResult::Release()
   {
	   delete this;
   }


}
