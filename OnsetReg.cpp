#include "stdafx.h"
#include "idb.h"
#include "db.h"
#include "relation.h"
#include "slist.h"
#include <fstream.h>
#include "IdbDoc.h"
#include "OwnListBox.h"
#include "IdbView.h"
#include "OnSetReg.h"

void OnSetReg::OnSetRegColor(int StartTime , int EndTime)
{

	fstream out;
	out.open("zghdj.txt",ios::out);

	CIdbDoc* pDoc;
	ASSERT(pDoc!= NULL);

	DB* dataBase = &(pDoc->m_dataBase);

	if (!(*dataBase).numRels) 
	{
		out <<"syed"<<endl;
		return; 
	}
	else
	{
//		m_listRecord.ResetContent();
		int nNum = 0;
		SlistIter<Relation> relationListIter(*(*dataBase).m_pRelationList);
		Relation* p_r; 
		while(p_r = (Relation*)relationListIter())
		{
			CString strOut("");
			String strName = p_r->Name();
			out << strName << endl;
		}
	}
}

