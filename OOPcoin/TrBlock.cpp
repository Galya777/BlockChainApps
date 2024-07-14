#include "TrBlock.h"
#include <iostream>
void TrBlock::del()
{
	delete[] blocks;
}

void TrBlock::copy(const TrBlock& other)
{
	this->blocks = other.blocks;
	this->blockSize = other.blockSize;
	this->trSize = other.trSize;
}

void TrBlock::addToBlock(Transaction tr, BlockExtend bl)
{
	 unsigned char* a= reinterpret_cast< unsigned char*>(trSize);
	if (blockSize > 0) {
		bl.block.prevBlockHash = computeHash(a, sizeof(blocks[blockSize - 2]));
		bl.block.prevBlockId = THIS_BL_ID - 1;
	}
	bl.block.prevBlockHash = 0;
	bl.block.prevBlockId = -1;
	bl.block.transactions[trSize].coins = tr.coins;
	bl.block.transactions[trSize].sender = tr.sender;
	bl.block.transactions[trSize].receiver = tr.receiver;
	bl.block.transactions[trSize].time = tr.time;
	bl.block.validTransactions++;
	bl.sum += bl.block.transactions[trSize].coins;
	trSize++;
}

TrBlock::TrBlock()
{
	blocks = new BlockExtend[1000];
	this->blockSize = 0;
	trSize = 0;
}

TrBlock::TrBlock(const TrBlock& other)
{
	copy(other);
}

TrBlock& TrBlock::operator=(const TrBlock& other)
{
	if (this != &other) {
		del();
		copy(other);
	}
	return *this;
	// TODO: insert return statement here
}

TrBlock::~TrBlock()
{
	del();
}

void TrBlock::readFromFile(std::fstream& file)
{
	for (size_t i = 0; i < blockSize; i++)
	{
		for (size_t j = 0; j < trSize; j++)
		{
			file.read((char*)blocks[i].block.transactions[j].time, sizeof(blocks[i].block.transactions[j].time));
			file.read((char*)blocks[i].block.transactions[j].receiver, sizeof(blocks[i].block.transactions[j].receiver));
			file.read((char*)blocks[i].block.transactions[j].sender, sizeof(blocks[i].block.transactions[j].sender));
			file >> blocks[i].block.transactions[j].coins;
			blocks[i].sum+=blocks[i].block.transactions[j].coins;
		}
		
	}
}

void TrBlock::writeToFile(std::fstream& file)
{
	for (size_t i = 0; i < blockSize; i++)
	{
		for (size_t j = 0; j < trSize; j++)
		{
			file<<blocks[i].block.transactions[j].time << " Sender: " << blocks[i].block.transactions[j].sender << " Receiver: " << blocks[i].block.transactions[j].receiver << " Balance: " << blocks[i].block.transactions[j].coins;
		}
		file << "\n";
	}
	file << "\n";
}

BlockExtend* TrBlock::getBlocks() const
{
	return blocks;
}

int TrBlock::getSize() const
{
	return blockSize;
}

int TrBlock::getTr() const
{
	return trSize;
}

void TrBlock::quickSort(BlockExtend* arr, int length, bool reverse)
{
	if (length <= 1) {
		return;
	}
	const int pivot_count = arr[length / 2].sum;
	int smaller_length = 0;
	int bigger_length = 0;
	int equal_length = 0;

	for (int i = 0; i < length; i++) {
		if (!reverse) {
			if (arr[i].sum < pivot_count) smaller_length++;
			if (arr[i].sum > pivot_count) bigger_length++;
		}
		else {
			if (arr[i].sum > pivot_count) smaller_length++;
			if (arr[i].sum < pivot_count) bigger_length++;
		}
		if (arr[i].sum == pivot_count) equal_length++;
	}

	BlockExtend* smaller = new BlockExtend[smaller_length];
	BlockExtend* bigger = new BlockExtend[bigger_length];
	BlockExtend* equal = new BlockExtend[equal_length];

	int smaller_i = 0;
	int bigger_i = 0;
	int equal_i = 0;

	// comparisons, this part should be pluggable to make this generic
	for (int i = 0; i < length; i++) {
		if (!reverse) {
			if (arr[i].sum < pivot_count) smaller[smaller_i++] = arr[i];
			if (arr[i].sum > pivot_count) bigger[bigger_i++] = arr[i];
		}
		else {
			if (arr[i].sum > pivot_count) smaller[smaller_i++] = arr[i];
			if (arr[i].sum < pivot_count) bigger[bigger_i++] = arr[i];
		}
		if (arr[i].sum == pivot_count) equal[equal_i++] = arr[i];
	}

	quickSort(smaller, smaller_length, reverse);
	quickSort(bigger, bigger_length, reverse);

	int j = 0;
	// now overwrite the original array with:
	// smaller + equal + bigger

	for (int i = 0; i < smaller_length; i++) arr[j++] = smaller[i];
	for (int i = 0; i < equal_length; i++) arr[j++] = equal[i];
	for (int i = 0; i < bigger_length; i++) arr[j++] = bigger[i];
}

void TrBlock::printBlocks(int num)
{
	if (num > blockSize) return;
	for (size_t i = 0; i < num; i++)
	{
		std::cout << blocks[i].block.id << " "<<blocks[i].sum;
	}
	std::cout << "\n";
}

void TrBlock::addTransaction(Transaction tr)
{	
	if (blockSize == 0&& trSize==0) {
		blockSize++;
		blocks[blockSize].block.id = THIS_BL_ID;
		addToBlock(tr, blocks[blockSize]);
	} else{
		if (trSize < 16) {
			addToBlock(tr, blocks[blockSize]);
		}
		else {
			trSize = 0;
			blockSize++;
			blocks[blockSize].block.id = THIS_BL_ID;
			THIS_BL_ID++;
			addToBlock(tr, blocks[blockSize]);
		}
	}
}

bool TrBlock::verify_transactions()
{
	for (size_t i = 0; i < blockSize; i++)
	{
		if (trSize<=0) return false;
	}
	return true;
}
