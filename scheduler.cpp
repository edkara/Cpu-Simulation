#include <fstream>
#include "scheduler.h"

const int waitTime = 4;

Scheduler::Scheduler() {

}

vector<Process*> Scheduler::getReadyProcesses() const{
	return this->readyProcesses;
}

vector<Process*> Scheduler::getBlockedProcesses() const{
	return this->blockedProcesses;
}

void Scheduler::blockRunningProcess() {
	vector<Process*>::iterator it;
	for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
		if((*it)->getState() == State::running) {
			(*it)->setState(State::blocked);
			(*it)->setWait(waitTime);
			blockedProcesses.push_back((*it));
			delete *it;
			it = readyProcesses.erase(it);
		}
		else {
			++it;
		}
	}
}

void Scheduler::deleteRunningProcess() {
	vector<Process*>::iterator it;
	for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
		if((*it)->getState() == State::running) {
			delete *it;
			it = readyProcesses.erase(it);
		}
		else {
			++it;
		}
	}
}

void Scheduler::startRunningProcess() {
	if(getReadyProcesses().size() > 0) {
		vector<Process*>::iterator it;
		for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
			if((*it)->getState() != State::running) {
				(*it)->setState(State::running);
				break;
			} else {
				++it;
			}
		}
	} else {
		cout << "There are no existing ready processes!" << endl;
	}
}

Process* Scheduler::getRunningProcess(){
	Process *process = nullptr;
	vector<Process*>::iterator it;
	for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
		if((*it)->getState() == State::running) {
			return (*it);
		} else {
			++it;
		}
	}
	return process;
}

Process* Scheduler::loadNewProcess(string &fileName) {
	ifstream program(fileName);
	string line;
	vector<string> commandMemory;
	if(program.is_open())
	{
		while(getline(program,line))
		{
			commandMemory.push_back(line);
		}
		program.close();
	} else cout << "\n ERROR! Program not found." << endl;

	Process* process = new Process(fileName, commandMemory);
	this->readyProcesses.push_back(process);
	return process;
}

void Scheduler::deleteBlockedProcess(Process *process) {
	vector<Process*>::iterator it;
	for (it = blockedProcesses.begin(); it != blockedProcesses.end(); ) {
		if((*it)->getPid() == process->getPid()) {
			delete *it;
			it = readyProcesses.erase(it);
		}
		else {
			++it;
		}
	}
}

void Scheduler::updateWait() {
	if (this->blockedProcesses.size() > 0) {
		vector<Process *>::iterator it;
		for (it = blockedProcesses.begin(); it != blockedProcesses.end();) {
			int wait = (*it)->getWait();
			(*it)->setWait(wait--);
			if ((*it)->getWait() == 0) {
				(*it)->setState(State::ready);
				if (this->readyProcesses.size() < 0) {
					(*it)->setState(State::running);
				}
				this->readyProcesses.push_back((*it));
				deleteBlockedProcess((*it));
			}
		}
	}
}

Scheduler::~Scheduler() {

}



