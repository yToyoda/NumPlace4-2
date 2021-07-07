#pragma once
#include "stdafx.h"
#include <list>
#include <bitset>
#include <array>

using namespace std;

const int gridSize = 81;
const int xySize = 9;
const int minNum = 1;
const int maxNum = 9;

struct PointIndex {
	int xi;
	int yi;
	bool operator==(PointIndex tgt);
};
struct CellData {
	int  currentNum;
	bitset<10> possibleNum;
	bitset<3> pairFound;
	bitset<3> tripletFound;
	CellData();
	void ClearFoundFlags();
	void ClearPossibleNum();
	void SetDefinitionFlag(bool value);
	bool GetDefinitionFlag();
}; 
struct GridData {	
	array < CellData, gridSize> grid;	
	CellData& operator[](int xi);
	CellData& at(int i);
	CellData& atInterSect(int xi, int yi);
	CellData& atInterSect(PointIndex pi);
	CellData& atInterSect(int mode, int group, int index);
	void RemovePossibility(PointIndex pi);
	void CopyFrom(GridData source);
	GridData& operator=(const GridData& src);
	//GridData& operator=(const GridData& src) = default;
};
// independent functions
PointIndex Indexes(int group, int ind, int mode);
bitset<10> Union(bitset<10> a, bitset<10> b);
int NPossibleNum(bitset<10> bits);

