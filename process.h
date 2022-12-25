#ifndef BS_MOORE_PROZESS_H
#define BS_MOORE_PROZESS_H
#include <iostream>
#include <vector>
#include <iomanip>
#include "page.h"

using namespace std;

enum State {
	running,
	ready,
	blocked,
};

class Process {
public:
	Process(const string &fileName, vector<string> commandMemory);
	void setPid(int pid);
	int getPid() const;
	void setFileName(const string &fileName);
	string getFileName() const;
	void setData(int data);
	int getData() const;
	void setIndex(int index);
	int getIndex() const;
	void setWait(int wait);
	int getWait() const;
	void setState(State state);
	State getState() const;
	void createAllPagesToSingleProcess();
	vector<string> getCommandMemory();
	vector<Page*> getPageTable();
	~Process() = default;
private:
	int pid;
	string fileName;
	State state;
	vector<string> commandMemory;
	int data;					// for acc
	int index;					// for pc
	int wait;					// when in blocked
	vector<Page*> pageTable;	// virtual memory = page table
};


#endif //BS_MOORE_PROZESS_H
