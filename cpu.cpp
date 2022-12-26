#include <fstream>
#include "cpu.h"

int simulation = 1;
int quantumCounter = 0;
int quantum = 5;

Cpu::Cpu() {

}

void Cpu::setAccumulator(int accumulator) {
	this->accumulator = accumulator;
}

int Cpu::getAccumulator() {
	return this->accumulator;
}

void Cpu::setProgramCounter(int programCounter) {
	this->programCounter = programCounter;
}

int Cpu::getProgramCounter() {
	return this->programCounter;
}

void Cpu::setTact(int tact) {
	this->tact = tact;
}

int Cpu::getTact() {
	return this->tact;
}

void Cpu::load(int n) {
	this->accumulator = n;
}

void Cpu::add(int n) {
	this->accumulator+=n;
}

void Cpu::subtract(int n) {
	this->accumulator-=n;
}

void Cpu::write(int n) {
	RAM.at(n) = static_cast<char>(this->accumulator);
}

void Cpu::read(int n) {
	this->accumulator = RAM.at(n);
}

void Cpu::peripheral(Scheduler* scheduler, Process* process) {
	process->setIndex(getProgramCounter()+1);			// zuerst wird der counter um 1 erhöht, damit ich später dort anfange, wo ich aufgehört habe
	process->setData(getAccumulator());
	scheduler->blockRunningProcess(process);			// blockiere der Process
	scheduler->startProcess();							// starte neuer ready Process, falls es in dem vector gibt
}

void Cpu::init(Scheduler* scheduler, string fileName) {
	scheduler->loadNewProcess(fileName);
	MMU* mmu = new MMU();
	execute(scheduler, mmu);
}

pair<string,string> Cpu::parseCommand(string command) {
	pair<string,string> parsedCommand;
	string delimiter = " ";
	size_t pos = command.find(delimiter);
	parsedCommand.first = command.substr(0, command.find(delimiter));
	parsedCommand.second = command.substr(pos + 1);
	return parsedCommand;
}

void Cpu::execute(Scheduler* scheduler, MMU* mmu) {
	while (simulation == 1) {
		scheduler->updateWait();
		//updateAccessTime();
		Process* runningProcess = nullptr;

		if (scheduler->existsRunningProcess()) {
			runningProcess = scheduler->getRunningProcess();
			quantumCounter = 0;
			setProgramCounter(runningProcess->getIndex());
			setAccumulator(runningProcess->getData());
		}
		else {
			Process* lastBlockedProcess = scheduler->getLastBlockedProcess();
			cout << setw(10) << getTact() << setw(10) << lastBlockedProcess->getPid() << setw(10) << lastBlockedProcess->getFileName()
				<< setw(10) << getProgramCounter() << "/" << lastBlockedProcess->getCommandMemory().size() - 1
				<< setw(10) << getAccumulator() << setw(13) << "--" << endl;
			setTact(getTact() + 1);
			continue;
		}

		while (getProgramCounter() < runningProcess->getCommandMemory().size()) {
			quantumCounter++;
			string command = runningProcess->getCommandMemory().at(getProgramCounter());
			cout << setw(10) << getTact() << setw(10) << runningProcess->getPid()
				<< setw(10) << runningProcess->getFileName() << std::setw(10) << getProgramCounter() << "/" << runningProcess->getCommandMemory().size()-1
				<< setw(10) << getAccumulator() << std::setw(13) << command << endl;
			pair<string, string> givenCommand = parseCommand(command);
			string function = givenCommand.first;
			string variable = givenCommand.second;

			if(quantumCounter%quantum == 0){
				function = "P";
				int newPc = getProgramCounter() - 1;
				setProgramCounter(newPc);
			}
			if (function == "L") {
				load(stoi(variable));
			}
			else if (function == "A") {
				add(stoi(variable));
			}
			else if (function == "S") {
				subtract(stoi(variable));
			}
			else if (function == "P") {
				peripheral(scheduler, runningProcess);
				break;
			}
			else if (function == "X") {
				runningProcess->setState(State::ready);
				runningProcess->setIndex(getProgramCounter()+1);
				runningProcess->setData(getAccumulator());
				scheduler->loadNewProcess(variable);
				break;
			}
			else if (function == "W") {
				int physicalAddress = mmu->convertToPhysicalAddress(variable, runningProcess, true);
				write(physicalAddress);
			}
			else if (function == "R") {
				int physicalAddress = mmu->convertToPhysicalAddress(variable, runningProcess);
				read(physicalAddress);
			}
			else if (function == "Z") {
                //int indexOfProcess = runningProcess->getPid();
				int terminate = scheduler->stopProcess(runningProcess);
				if(terminate) {
					cout << "The running process was deleted!" << endl;
                    //HDD.erase( next( begin( HDD ), indexOfProcess ) );
					if(scheduler->getBlockedProcesses().size() == 0) {
						cout << "There was no blocked or ready processes. So I have stopped the simulation! Bye." << endl;
						simulation = 0;
						break;
					}
				}
				cout << "The running process was deleted and new process was started!" << endl;
				break;
			}
			setProgramCounter(getProgramCounter()+1);
			setTact(getTact() + 1);
			scheduler->updateWait();
			updateDisk();
		}
	}
}

/*
void updateAccessTime() {
	if(LOOK_UP_TABLE.size() > 0) {
		vector<pair<Page*, Process*>>::iterator it;
		for (it = LOOK_UP_TABLE.begin(); it != LOOK_UP_TABLE.end(); ++it) {
			Page* page = (*it).first;
			if(page->isReferenced() ) {
				page->setAccessTime(page->getAccessTime() + 1);
				if(page->getAccessTime() == 5) {
					page->setReferencedBit(false);
					page->setAccessTime(0);
				}
			}
		}
	}
}
*/

void updateDisk() {
	if(LOOK_UP_TABLE.size() > 0) {
		vector<pair<Page*, Process*>>::iterator it;
		for (it = LOOK_UP_TABLE.begin(); it != LOOK_UP_TABLE.end(); ++it) {
			Page* page = (*it).first;
			Process* process = (*it).second;
			for(int j = 0; j < PAGE_SIZE; j++) {
				HDD.at(process->getPid()).at(page->getPageFrameId() * PAGE_SIZE + j) =
						RAM.at(page->getPageFrameId() * PAGE_SIZE + j );
			}
		}
	}
}

Cpu::~Cpu() {

}
