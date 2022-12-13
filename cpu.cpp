#include <fstream>
#include "cpu.h"

int simulation = 1;
int quantumCounter = 0;
int quantum = 1000;

Cpu::Cpu() {

}

Cpu::Cpu(int accumulator, int programCounter, int tact)
: accumulator(accumulator), programCounter(programCounter), tact(tact){
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

void Cpu::peripheral(Scheduler* scheduler, Process* process) {
	process->setIndex(getProgramCounter()+1);
	process->setData(getAccumulator());
	scheduler->blockRunningProcess();
	scheduler->startRunningProcess();
}

void Cpu::init(Scheduler* scheduler, string fileName) {
	Process* newProcess = scheduler->loadNewProcess(fileName);
	execute(scheduler, newProcess);
}

pair<string,string> Cpu::parseCommand(string command) {
	pair<string,string> parsedCommand;
	string delimiter = " ";
	size_t pos = command.find(delimiter);
	parsedCommand.first = command.substr(0, command.find(delimiter));
	parsedCommand.second = command.substr(pos + 1);
	return parsedCommand;
}

void Cpu::execute(Scheduler* scheduler, Process* process) {
	while (simulation == 1) {
		scheduler->updateWait();
		if (scheduler->getReadyProcesses().size() > 0) {
			quantumCounter = 0;
			process = scheduler->getRunningProcess();
			setProgramCounter(process->getIndex());
			setAccumulator(process->getData());
			setTact(tact++);
		}
		else {
			cout << setw(10) << getTact() << setw(10) << process->getPid() << setw(10) << process->getFileName() << setw(10) << getProgramCounter()
						<< "/" << process->getCommandMemory().size() - 1 << setw(10) << getAccumulator() << setw(13) << "--" << endl;
			setTact(tact++);
			continue;
		}

		while (getProgramCounter() < process->getCommandMemory().size()) {
			quantumCounter++;
			string command = process->getCommandMemory().at(getProgramCounter());
			cout << setw(10) << getTact() << setw(10) << process->getPid() << setw(10) << process->getFileName()
					<< std::setw(10) << getProgramCounter() << "/" << process->getCommandMemory().size()-1 << setw(10) << getAccumulator() << std::setw(13) << command << endl;
			pair<string, string> givenCommand = parseCommand(command);
			string function = givenCommand.first;
			string variable = givenCommand.second;

			if(quantumCounter%quantum == 0 ){

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
				peripheral(scheduler, process);
			}
			else if (function == "X") {
				scheduler->getRunningProcess()->setIndex(getProgramCounter()+1);
				scheduler->getRunningProcess()->setData(getAccumulator());
				scheduler->getRunningProcess()->setState(State::ready);
				scheduler->loadNewProcess(variable);
			}
			else if (function == "Z") {
				stop(scheduler);
			}
			setProgramCounter(this->programCounter++);
			setTact(this->tact++);
			scheduler->updateWait();
		}
	}
}

void Cpu::stop(Scheduler* scheduler) {
	scheduler->deleteRunningProcess();
	if(scheduler->getReadyProcesses().size() > 0) {
		scheduler->startRunningProcess();
	} else if(scheduler->getBlockedProcesses().size() == 0){
		simulation = 0;
	}
}

Cpu::~Cpu() {

}
