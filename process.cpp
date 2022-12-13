#include "process.h"

static int tmpPid = 0;

Process::Process(const string &fileName, vector<string> commandMemory){
	this->pid = tmpPid++;
	this->fileName = fileName;
	this->commandMemory = commandMemory;
	this->data = 0;
	this->state = State::running;
	this->index = 0;
	this->wait = 0;
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

void Process::setCommandMemory(vector<string> commandMemory) {
	this->commandMemory = commandMemory;
}

vector<string> Process::getCommandMemory() {
	return this->commandMemory;
}

void Process::printAllCommands() const{
	for (auto pr : commandMemory) {
		cout << pr << endl;
	}
}

Process::~Process() {

}