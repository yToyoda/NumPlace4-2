#include "stdafx.h"
#include "NumPlaceEngine.h"
#include "NumPlace2.h"


CNumPlaceEngine::CNumPlaceEngine()
{
	InitEngine(false);
}


CNumPlaceEngine::~CNumPlaceEngine()
{

}

void CNumPlaceEngine::InitEngine(bool possibleNumOnly = false) {
	for (int i = 0; i < gridSize; i++) {
		if (!possibleNumOnly) {
			grid[i].currentNum = 0;   // init by 0 = blank
			grid[i].possibleNum.set();
			grid[i].SetDefinitionFlag(false);   // Question Definition / Answer flag   true = Question Definition
			grid[i].ClearFoundFlags();       // clear pairFound flag
		}
	}
	nCellsLeft = gridSize;
	searchDone = false;
	trialStack.clear();
}

void CNumPlaceEngine::ClearAnswer(){
	bool cmode = defineMode;
	for (int i = 0; i < gridSize; i++) {
			for (int j = 1; j <= maxNum; j++) {
				grid[i].possibleNum[j] = true;   // set all possibility
			}
			if (! grid[i].GetDefinitionFlag()) {
				// answer
				grid[i].currentNum = 0;   // init by 0 = blank
				grid[i].ClearFoundFlags();        // clear pairFound flag
			}			

	}
	nCellsLeft = gridSize;
	defineMode = true;
	for (int xi = 0; xi < xySize; xi++) {
		for (int yi = 0; yi < xySize; yi++) {
			if (grid.atInterSect(xi,yi).GetDefinitionFlag()) {
				// question
				PlaceNum(grid.atInterSect(xi, yi).currentNum, { xi, yi });
			}
		}
	}
	defineMode = cmode;
	searchDone = false;
}



void CNumPlaceEngine::PlaceNum(int num, PointIndex pi) {
	bool placeable = true;
	if (num >= 1 && num <= maxNum) {
		if (!defineMode && protectFalseEntry) {
			placeable = false;
			for (auto ans : foundRule1) {
				if (ans.point.xi == pi.xi && ans.point.yi == pi.yi && ans.num == num) placeable = true;
			}
			for (auto ans : foundRule2){
				if (ans.point.xi == pi.xi && ans.point.yi == pi.yi && ans.num == num) placeable = true;
			}
		}
		else if (defineMode || (!defineMode && protectDoubleEntry)){
			placeable = grid.atInterSect(pi).possibleNum[num];
		}
		if (placeable) {
			grid.atInterSect(pi).currentNum = num;
			grid.atInterSect(pi).possibleNum.reset();               // no possibility to place other number
			grid.atInterSect(pi).SetDefinitionFlag(defineMode);       // shows part of definition
			grid.RemovePossibility(pi);									// remove possibility of column, rows, and 3x3 section
			if (!defineMode) {
				ExecuteSearch();
			}
			--nCellsLeft;
		}
		else {
			Beep(880, 0.5);
		}
	}
	else if (num == -1) { // delete current num
		if (defineMode || !defineMode && !grid.atInterSect(pi).GetDefinitionFlag()) {
			grid.atInterSect(pi).currentNum = 0;   // remove num at current position
			grid.atInterSect(pi).SetDefinitionFlag(false);
			InitEngine(true); // clear possible num only
			nCellsLeft = gridSize;
			// for reset of Cells in Grid
			for (int xi = 0; xi < xySize; xi++) {
				for (int yi = 0; yi < xySize; yi++) {
					if (grid.atInterSect(xi,yi).currentNum > 0) {
						grid.atInterSect(xi, yi).ClearPossibleNum();
						grid.RemovePossibility({ xi, yi });
						if (advancedSearch) CheckRule3();
						--nCellsLeft;
					}
				}
			}
		}
		if (!defineMode) {
			ExecuteSearch();
		}
	}

}
void CNumPlaceEngine::SearchInitial() {
	foundRule1.clear();
	foundRule2.clear();
	CheckRulePosition(1);

	if (searchOp2n) {
		//CheckRule2();
		CheckRuleNum(1);
	}
	searchDone = true;
}

void CNumPlaceEngine::ExecuteSearch() {
	if (searchOp2p) {
		//CheckRule6();
		CheckRulePosition(2);
	}
	if (searchOp3p) {
		//CheckRule7();
		CheckRulePosition(3);
	}
	if (searchOp4p) {
		CheckRulePosition(4);
	}
	if (searchOp5p) {
		CheckRulePosition(5);
	}

	if (searchOp2n) {
		//CheckRule4();
		CheckRuleNum(2);
	}
	if (searchOp3n) {
		//CheckRule5();
		CheckRuleNum(3);
	}
	if (searchOp4n) {
		CheckRuleNum(4);
	}
	if (searchOp5n) {
		CheckRuleNum(5);
	}

	if (searchOpR13) {
		CheckRule3();
	}

	foundRule1.clear();
	foundRule2.clear();
	//CheckRule1();
	CheckRulePosition(1);
	if (searchOp1n) {
		//CheckRule2();
		CheckRuleNum(1);
	}

}

void CNumPlaceEngine::CheckRule(char kind, int level) {
	if (kind == 'r') {
		CheckRule3();
	}
	else if (kind == 'p') {
		CheckRulePosition(level);
	}
	else if (kind == 'n') {
		CheckRuleNum(level);
	}
}

void CNumPlaceEngine::ShowHints() {

}

void CNumPlaceEngine::CheckRule3(){
	// bool result[3];
	int count , ifound;
	bool exist;
	// Mode 0  Search Row (3x1 block x3)
	for (int yi = 0; yi < xySize; ++yi) {
		int ySection = yi / 3;		
		for (int num = 1; num <= maxNum; ++num) {
			// serach a row yi
			count = 0; ifound = -1;
			for (int xSection = 0; xSection < 3; ++xSection) {
				exist = false;
				// search in 3x1 section
				for (int i = 0; i < 3; ++i) {
					if (grid.atInterSect(xSection * 3 + i,yi).possibleNum[num]) exist = true;
				}
				if (exist) {
					++count;
					ifound = xSection;
				}
			}
			if (count == 1) { // num is in only 3x1 xSection. Erase possibleNum in the includding block				
				for (int incY = 0; incY < 3; ++incY) {
					if (ySection * 3 + incY != yi) {
						for (int i = 0; i < 3; ++i) {
							grid.atInterSect(ifound * 3 + i,ySection * 3 + incY).possibleNum[num] = false;
						}
					}
				}
			}
		}
	}
	// Mode 1  Search along Column  (1x3 block x 3) 
	for (int xi = 0; xi < xySize; ++xi) {		
		int xSection = xi / 3;
		for (int num = 1; num <= maxNum; ++num) {
			// serach a row yi
			count = 0; ifound = -1;
			for (int ySection = 0; ySection < 3; ++ySection) {
				exist = false;
				// search in 3x1 section
				for (int i = 0; i < 3; ++i) {
					if (grid.atInterSect(xi,ySection * 3 + i).possibleNum[num]) exist = true;
				}
				if (exist) {
					++count;
					ifound = ySection;
				}
			}
			if (count == 1) { // num is in only 1x3 ySection  Erase possibleNum in the includding block				
				for (int incX = 0; incX < 3; ++incX) {
					if (xSection * 3 + incX != xi) {
						for (int i = 0; i < 3; ++i) {
							grid.atInterSect(xSection*3 + incX,ifound * 3 + i).possibleNum[num] = false;
						}
					}
				}
			}
		}
	}
	// Mode 2  Search 3x3 section
	for (int blockIndex = 0; blockIndex < xySize; ++blockIndex) {
		int xSection = blockIndex % 3;
		int ySection = blockIndex / 3;
		
		for (int num = 1; num <= maxNum; ++num) {
			// serach in row direction (3x1 bolck) 
			count = 0; ifound = -1;
			for (int incY = 0; incY < 3; ++incY) {
				exist = false;
				// search in 3x1 section
				for (int i = 0; i < 3; ++i) {
					if (grid.atInterSect(xSection * 3 + i,ySection * 3 + incY).possibleNum[num]) exist = true;
				}
				if (exist) {
					++count;
					ifound = incY;
				}
			}
			if (count == 1) { // num is in only 3x1 xSection
				int yi = ySection * 3 + ifound;
				for (int xs = 0; xs < 3; ++xs) {
					if (xs != xSection) {
						for (int i = 0; i < 3; ++i) {
							grid.atInterSect(xs * 3 + i,yi).possibleNum[num] = false;
						}
					}
				}
			}
			// serach in column direction (1x3 bolck) 
			count = 0; ifound = -1;
			for (int incX = 0; incX < 3; ++incX) {
				exist = false;
				// search in 3x1 section
				for (int i = 0; i < 3; ++i) {
					if (grid.atInterSect(xSection * 3 + incX,ySection * 3 + i).possibleNum[num]) exist = true;
				}
				if (exist) {
					++count;
					ifound = incX;
				}
			}
			if (count == 1) { // num is in only 1x3 ySection
				int xi = xSection * 3 + ifound;
				for (int ys = 0; ys < 3; ++ys) {
					if (ys != ySection) {
						for (int i = 0; i < 3; ++i) {
							grid.atInterSect(xi,ys * 3 + i).possibleNum[num] = false;
						}
					}
				}
			}
		}
	}

}




bitset<10> CNumPlaceEngine::NumToIndex(int num, int group, int mode) {
	bitset<10> ans;
	for (int ind = 0; ind < xySize; ++ind) {		
		if (grid.atInterSect(mode,group,ind).possibleNum[num]) {
			ans[ind + 1] = true;  // user index +1 location in array
		}
	}
	return ans;
}

void CNumPlaceEngine::CheckRuleNum(int level) {
	bitset<10> parent;
	
	bool pnumPairent[10] = { false };
	for (int mode = 0; mode < 3; ++mode) {
		for (int group = 0; group < xySize; ++group) {
			int cellIndexes[9];
			parent.reset();
			for (int i = 0; i < xySize; ++i) cellIndexes[i] = -1;
			FindNum(level, 1, group, mode, 0, parent, cellIndexes);
		}
	}
}

bool CNumPlaceEngine::FindNum(int level, int currLevel, int group, int mode, int start, bitset<10> parentNums, int cellIndexes[]) {
	PointIndex pref;
	bitset<10> currNums, tempNums;
	bool found = false;
	int npll = 2;
	if (level == 1) {
		npll = 1;
	}
	for (int ind = start; ind < xySize - (level - currLevel); ++ind) {
		pref = Indexes(group, ind, mode);
		currNums = grid.atInterSect(pref).possibleNum;		
		//if (!currNums.pairFound[mode] && !currNums.tripletFound[mode]) {
			int np = NPossibleNum(currNums);
			if (np >= npll && np <= level) {
				tempNums = Union(parentNums, currNums);
				cellIndexes[currLevel - 1] = ind;
				if (currLevel < level) {
					found = FindNum(level, currLevel + 1, group, mode, ind + 1, tempNums, cellIndexes);
				}
				else {
					if (NPossibleNum(tempNums) == level) {						
						// target found;
						found = true;
						//GetCellPointer(pref)->tripletFound[mode] = true;
						//GetCellPointer(p2)->tripletFound[mode] = true;
						//GetCellPointer(p3)->tripletFound[mode] = true;

						for (int num = minNum; num <= maxNum; ++num) {
							if (tempNums[num]) {
								for (int i = 0; i < xySize; ++i) {
									bool target = true;
									for (int l = 0; l < level; ++l) {
										if (i == cellIndexes[l]) target = false;
									}
									if (target) {
										PointIndex px = Indexes(group, i, mode);
										grid.atInterSect(px).possibleNum[num] = false;
									}									
								}
								if (level == 1) {
									answer ans;
									ans.point = pref;
									ans.num = num;
									foundRule2.push_back(ans);
								}
							}
						}
					}
				} // else of if (currLevel < level) 
			}

		//} if (!currNums.pairFound[mode] && !currNums.tripletFound[mode]) 
	} // end of for ind1
	return found;
}
void CNumPlaceEngine::CheckRulePosition(int level) {	
	bitset<10> parentIndexes;	
	for (int mode = 0; mode < 3; ++mode) {
		for (int group = 0; group < xySize; ++group) {
			int nums[xySize];			
			parentIndexes.reset();
			FindPosition(level, 1, group, mode, 1, parentIndexes, nums);
		}
	}
}
bool CNumPlaceEngine::FindPosition(int level, int currLevel, int group, int mode, int start, bitset<10> parentIndexes,int nums[]) {
	bool found = false;
	bitset<10> pIndexes, tempIndexes ;
	for (int num = start ; num <= maxNum-(level-currLevel) ; ++num) {
		pIndexes = NumToIndex(num, group, mode);
		int npn = NPossibleNum(pIndexes);
		if (npn >= 1 && npn <= level) {
			nums[currLevel - 1] = num;
			tempIndexes = Union(parentIndexes, pIndexes);
			if (currLevel < level) { // final search stage								
				found = FindPosition(level, currLevel + 1, group, mode, num + 1, tempIndexes, nums);
			} else {
				if (NPossibleNum(tempIndexes) == level) {
					// found 
					found = true;					
					for (int ind = 0; ind < xySize; ++ind) {
						if (tempIndexes[ind + 1]) {
							for (int n = 1; n <= maxNum; ++n) {
								bool target = true;
								for (int l = 0; l < level; ++l) {
									if (n == nums[l]) target = false;
								}
								if (target) {
									grid.atInterSect(mode,group,ind).possibleNum[n] = false;
								}
							} // end n
							if (level == 1) {
								answer ans;
								ans.point = Indexes(group,ind,mode);
								ans.num = num ;
								foundRule1.push_back(ans);
							}

						}
					} // end ind
				}
			}
		}
	} // end num3
	return found;
}

void CNumPlaceEngine::NumSelected(PointIndex pi, int num) {	
	CellData& currCell = grid.atInterSect(pi);
	if (!defineMode && editRemainder && grid.atInterSect(pi).currentNum == 0) {
		// edit possiblity		
		currCell.possibleNum[num] = !currCell.possibleNum[num];
		if (NPossibleNum(currCell.possibleNum) == 1) {
			int n = 0;
			for (int ni = minNum; ni <= maxNum; ++ni) {
				if (currCell.possibleNum[ni]) n = ni;
			}
			PlaceNum(n, pi);
		}
	}
	else {
		if (!defineMode && currCell.possibleNum[num] && NPossibleNum(currCell.possibleNum) > 1 ) {
			theApp.pMainFrame->OnBnClickedButtonNewtrial();		
		}
		PlaceNum(num, pi);
	}
}

void CNumPlaceEngine::PushToTrialStack(){
	trialStack.push_back(grid);
}
void CNumPlaceEngine::PopFromTrialStack() {
	//grid.CopyFrom(trialStack.back());
	grid = trialStack.back();
	trialStack.pop_back();
}