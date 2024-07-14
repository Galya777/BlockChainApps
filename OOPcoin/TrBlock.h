#pragma once
#include "UserFuncs.h"

static int THIS_BL_ID = 0;
class TrBlock
{
unsigned computeHash(const unsigned char* memory, int length) {
	unsigned hash = 0xbeaf;

	for (int c = 0; c < length; c++) {
		hash += memory[c];
		hash += hash << 10;
		hash ^= hash >> 6;
	}

	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	return hash;
}
public:
	TrBlock();
	TrBlock(const TrBlock& other);
	TrBlock& operator=(const TrBlock& other);
	~TrBlock();

	//read from file
	void readFromFile(std::fstream& file);
	//write to file
	void writeToFile(std::fstream& file);

	BlockExtend* getBlocks() const;
	int getSize() const;
	int getTr() const;

	void quickSort(BlockExtend* arr, int length, bool reverse);
	void printBlocks(int num);

	void addTransaction(Transaction tr);
	bool verify_transactions();
private:
	void del();
	void copy(const TrBlock& other);

	void addToBlock(Transaction tr, BlockExtend bl);


	BlockExtend* blocks;
	size_t trSize;
	size_t blockSize;
};

