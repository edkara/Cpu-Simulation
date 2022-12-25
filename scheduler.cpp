#include <fstream>
#include "scheduler.h"

const int waitTime = 4;
const int PAGE_SIZE = 64;
const int FRAME_TABLE_SIZE = 4;
const int MAX_VIRTUAL_ADDRESS = 1023;

vector<char> RAM(PAGE_SIZE * FRAME_TABLE_SIZE);
vector<vector<char>> HDD;
vector<pair<Page*, Process*>> LOOK_UP_TABLE;

Scheduler::Scheduler() {

}

vector<Process*> Scheduler::getReadyProcesses() const{
	return this->readyProcesses;
}

vector<Process*> Scheduler::getBlockedProcesses() const{
	return this->blockedProcesses;
}


bool Scheduler::existsRunningProcess() {
	bool processExisting = false;
	vector<Process*>::iterator it;
	for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
		if((*it)->getState() == State::running ) {
			processExisting = true;
			break;
		}
		else {
			++it;
		}
	}
	return processExisting;
}

void Scheduler::blockRunningProcess(Process* process) {
	vector<Process*>::iterator it;
	for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
		if((*it)->getState() == State::running && (*it)->getPid() == process->getPid()) {
			(*it)->setState(State::blocked);
			(*it)->setWait(waitTime);
			blockedProcesses.push_back((*it));
			it = readyProcesses.erase(it);
			break;
		}
		else {
			++it;
		}
	}
}

void Scheduler::deleteRunningProcess(Process* process) {
	vector<Process*>::iterator it;
	for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
		if((*it)->getState() == State::running && (*it)->getPid() == process->getPid()) {
			delete (*it);
			it = readyProcesses.erase(it);
			break;
		}
		else {
			++it;
		}
	}
}

void Scheduler::startProcess() {
	if(getReadyProcesses().size() > 0) {
		if(!existsRunningProcess()) {
			vector<Process *>::reverse_iterator it;
			for (it = readyProcesses.rbegin(); it != readyProcesses.rend(); ) {
				if((*it)->getState() == State::ready) {
					(*it)->setState(State::running);
					break;
				} else {
					++it;
				}
			}
			cout << "The last ready Process was started!"<< endl;
		}
	} else {
		cout << "I wanted to start new process, but there was no existing ready/running processes at all!" << endl;
	}
}

Process* Scheduler::getRunningProcess(){
	Process* tmp = nullptr;
	vector<Process*>::iterator it;
	for (it = readyProcesses.begin(); it != readyProcesses.end(); ) {
		if((*it)->getState() == State::running) {
			tmp = (*it);
			break;
		} else {
			++it;
		}
	}
	return tmp;
}

void Scheduler::loadNewProcess(string fileName) {
	string fullPath = "/home/eddka/CLionProjects/BS_Moore/bs_03/" + fileName;
	ifstream program(fullPath);
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
	// add virtual address
	HDD.push_back(vector<char>(1024));
}

void Scheduler::deleteBlockedProcess(Process *process) {
	vector<Process*>::iterator it;
	for (it = blockedProcesses.begin(); it != blockedProcesses.end(); ) {
		if((*it)->getPid() == process->getPid() && (*it)->getPid() == process->getPid()) {
			it = blockedProcesses.erase(it);
			break;
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
			(*it)->setWait((*it)->getWait() - 1);
			if ((*it)->getWait() == 0) {
				(*it)->setState(State::ready);
				if (!existsRunningProcess()) {
					(*it)->setState(State::running);
				}
				this->readyProcesses.push_back((*it));
				deleteBlockedProcess((*it));
			} else {
				++it;
			}
		}
	}
}

int Scheduler::stopProcess(Process* process) {
	deleteRunningProcess(process);
	if(getReadyProcesses().size() > 0) {
		startProcess();
		return 0;
	}
	return 1;
}


Process* Scheduler::getLastBlockedProcess() {
	Process* tmp  = nullptr;
	vector<Process *>::reverse_iterator it;
	for ( it = blockedProcesses.rbegin(); it != blockedProcesses.rend(); ++it ) {
		if((*it)->getState() == State::blocked && (*it)->getWait() > 0) {
			tmp = (*it);
			break;
		}
	}
	return tmp;
}

Scheduler::~Scheduler() {

}



