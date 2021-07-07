#pragma once

#include "stdafx.h"
#include "GridClass.h""
#include <list>

using namespace std;

struct answer {
	PointIndex point;
	int  num;
};

class CNumPlaceEngine
{
private:
	//void InitEngine();
public:
	CNumPlaceEngine();
	~CNumPlaceEngine();
	GridData grid;

	bool		defineMode = true;
	bool		protectDoubleEntry = true;
	bool		protectFalseEntry = false;
	bool		showRemainder = false;
	bool		searchDone = false;
	bool		advancedSearch = false;
	bool	    searchOp1p = true;
	bool		searchOp1n = false;
	bool		searchOpR13 = false;
	bool        searchOp2p = false;
	bool        searchOp2n = false;
	bool        searchOp3p = false;
	bool		searchOp3n = false;
	bool		searchOp4p = false;
	bool		searchOp4n = false;
	bool		searchOp5p = false;
	bool		searchOp5n = false;
	bool		editRemainder = false;

	std::list<answer> foundRule1;
	std::list<answer> foundRule2;
	std::list<GridData> trialStack;
	short		nCellsLeft;

	void InitEngine(bool CellDataOnly);
	void PlaceNum(int num, PointIndex pi);
	void SearchInitial();
	void ClearAnswer();
	void ExecuteSearch();
	void CheckRule(char kind, int level);
	void PushToTrialStack();
	void PopFromTrialStack();
	void NumSelected(PointIndex pi,int num);

private:	
	void CheckRule3();
	void CheckRuleNum(int Level);
	bool FindNum(int level, int currLevel, int group, int mode, int start, bitset<10> parentNums, int cellIndexes[] );
	void CheckRulePosition(int Level);
	bool FindPosition(int level, int currLevel, int group, int mode, int start, bitset<10> parentIndexes, int nums[] );	
	void ShowHints();
	// functions for triplet search
		
	bitset<10> NumToIndex(int num, int group, int mode);
	//
};

