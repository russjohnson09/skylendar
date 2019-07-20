/***************************************************************************
                          astroconstellations.cpp  -  description
                             -------------------
    begin                : sat april 18 2015
    copyright            : (C) 2015 by Christophe Gros
    email                : skylendar@yahoo.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "astroconstellations.h"
#include "astrosql.h"
#include "astroobjs.h"

AstroConstellations::AstroConstellations(AstroObjs* ao)
{
	AstroRequest arq;
	int i = 0;
	Ao = ao;
#ifdef IFEXCEPT
	arq.SetException(true);
 try
 {
#endif

	if(arq.Exec("SELECT * FROM ConsNames") && arq.Valid())
		do
		{
			int count = 0, idx = arq.GetInt("Idx", 0);
			AstroRequest arq1;
			if(arq1.Exec("SELECT COUNT(*) FROM Boundaries WHERE Idx = %d", idx) && arq1.Valid())
				count = arq1.GetInt("count", 0);
			Src[i] = new ConstData[count + 1];
			Des[i] = new ConstData[count + 1];
			ConstData* cd = Src[i];
			if(arq1.Exec("SELECT Ra, Dec FROM Boundaries WHERE Idx = %d", idx) && arq1.Valid())
			do
			{
				cd->x = arq1.GetDouble("Ra") * 360.0 / 24.0;
				cd->y = arq1.GetDouble("Dec");
				cd++;
			} while(arq1.Next());
			Names[i++] = arq < "Name";
			cd->x = 1000.0;
		} while(arq.Next() && i <= NBC -1);
#ifdef IFEXCEPT
	}
 catch (AstroException& ae)
 {
	 arq.Rollback();
	 Exception(ae);
 }
#endif
    arq.SetException(false);
		 
}

void AstroConstellations::Compute()
{
	AstroInterface* aif = Ao->GetInterface();
	Double3 d;
	d.ds.d1 = Ao->Longitude.Get();
	d.ds.d2 = Ao->Latitude.Get();
	d.ds.d3 = Ao->Altitude;
	for(int i = 0; i < NBC; i++)
	{
		aif->Azalt(Ao->GetJd(), d, Src[i], Des[i]); 
	}
}
