#include "process.h"

static int tmpPid = 0;
const int PAGETABLE_SIZE = 16;				//we have 16 entries in page table

Process::Process(const string &fileName, vector<string> commandMemory)
	:pageTable(PAGETABLE_SIZE) {
	this->pid = tmpPid++;
	this->fileName = fileName;
	this->commandMemory = commandMemory;
	this->data = 0;
	this->state = State::running;
	this->index = 0;
	this->wait = 0;
	createAllPagesToSingleProcess();
}

void Process::setPid(int pid) {
	this->pid = pid;
}

int Process::getPid() const {
	return this->pid;
}

void Process::setFileName(const string &fileName) {
	this->fileName = fileName;
}

string Process::getFileName() const {
	return this->fileName;
}

void Process::setData(int data) {
	this->data = data;
}

int Process::getData() const {
	return this->data;
}

void Process::setIndex(int index) {
	this->index = index;
}

int Process::getIndex() const {
	return this->index;
}

void Process::setWait(int wait) {
	this->wait = wait;
}

int Process::getWait() const {
	return this->wait;
}

void Process::setState(State state) {
	this->state = state;
}

State Process::getState() const {
	return this->state;
}

vector<string> Process::getCommandMemory() {
	return this->commandMemory;
}

vector<Page*> Process::getPageTable() {
	return this->pageTable;
}

void Process::createAllPagesToSingleProcess() {
	for(int i = 0; i < this->pageTable.size(); i++) {
		this->pageTable.at(i) = new Page();
	}
}
