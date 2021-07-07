#include "stdafx.h"
#include "GridClass.h"

CellData::CellData() {
	currentNum = 0;
	this->possibleNum.reset();
	this->pairFound.reset();
	this->tripletFound.reset();
}
void CellData::ClearFoundFlags() {
	this->pairFound.reset();
	this->tripletFound.reset();
}
void CellData::ClearPossibleNum() {
	bool definitionflag = this->possibleNum[0];
	this->possibleNum.reset();
	this->possibleNum[0] = definitionflag;
}
void CellData::SetDefinitionFlag(bool value) {
	this->possibleNum[0] = value;
}
bool CellData::GetDefinitionFlag() {
	return this->possibleNum[0];
}

CellData& GridData::at(int i) {
	return this->grid.at(i);
}
CellData& GridData::operator[](int xi) {
	return grid.at(xi);
}

void GridData::CopyFrom(GridData source) {
	for (int i = 0; i < gridSize; ++i) {
		this->grid[i] = source[i];
	}
}


GridData& GridData::operator=(const GridData& src) {
	//array < CellData, gridSize> * ans = new array < CellData, gridSize>();
	for (int i = 0; i < gridSize; ++i) {
		this->grid[i] = src.grid.at(i);
	}
	return *this;
}



CellData& GridData::atInterSect(int xi, int yi) {
	int index = xySize * yi + xi;
	return grid.at(index);
}

CellData& GridData::atInterSect(PointIndex pi) {
	int index = xySize * pi.yi + pi.xi;
	return grid.at(index);
}

CellData& GridData::atInterSect(int mode, int group, int index) {	
	int xi=0, yi=0;
	if (mode == 0) {
		yi = group;
		xi = index;
	}
	else if (mode == 1) {
		xi = group;
		yi = index;
	}
	else if (mode == 2) {
		yi = 3 * (group / 3) + (index / 3);
		xi = 3 * (group % 3) + (index % 3);
	}
	int ind = xySize * yi + xi;
	return grid.at(ind);
}

void GridData::RemovePossibility(PointIndex pi) {
	for (int mode = 0; mode < 3; ++mode) {
		PointIndex tgt;
		int group = pi.yi;
		if (mode == 0) {
			group = pi.yi;
		}
		else if (mode == 1) {
			group = pi.xi;
		}
		else if (mode == 2) {
			group = pi.xi / 3 + (pi.yi / 3) * 3;
		}
		int num = this->atInterSect(pi).currentNum;
		for (int index = 0; index < xySize; ++index) {
			tgt = Indexes(group, index, mode);
			if (!(tgt == pi)) {
				this->atInterSect(tgt).possibleNum[num] = false;
			}
		}
	}
}

bool PointIndex::operator==(PointIndex tgt) {
	return (tgt.xi == this->xi && tgt.yi == this->yi);
}

PointIndex Indexes(int group, int ind, int mode) {
	PointIndex ans = { 0,0 };
	// mode 0:row, 1: column, 2: area
	if (mode == 0) {
		ans.yi = group;
		ans.xi = ind;
	}
	else if (mode == 1) {
		ans.xi = group;
		ans.yi = ind;
	}
	else if (mode == 2) {
		ans.yi = 3 * (group / 3) + (ind / 3);
		ans.xi = 3 * (group % 3) + (ind % 3);
	}
	return ans;
}


bitset<10> Union(bitset<10> a, bitset<10> b) {
	return a | b;
}


int NPossibleNum(bitset<10> bits) {
	int n = 0;
	for (int i = minNum; i <= maxNum; ++i) {
		if (bits[i]) {
			++n;
		}
	}
	return n;
}