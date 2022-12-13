#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "cpu.h"


int main() {
	Cpu* cpu = new Cpu();
	Scheduler* scheduler = new Scheduler();
	string fileName = "/test-programs/init";
	cpu->init(scheduler, fileName);
	std::cout << std::setw(10) << "Takt " << std::setw(10) << "PID " << std::setw(10) << "Process " << std::setw(10) << "PC " << std::setw(10) << "Acc " << std::setw(13) << "Befehl" << std::endl;
	std::cout << "No ready or blocked processes left. Simulation end" << std::endl;
	return 0;
}