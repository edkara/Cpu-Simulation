#ifndef BS_MOORE_PROZESS_H
#define BS_MOORE_PROZESS_H
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

enum State {
	running,
	ready,
	blocked,
};
static const char *enum_string[] = { "running", "ready", "blocked" };

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
	void setCommandMemory(vector <string> commandMemory);
	vector<string> getCommandMemory();
	void printAllCommands() const;
	~Process();
private:
	int pid;
	string fileName;
	State state;
	vector<string> commandMemory;
	int data;		// for acc
	int index;		// for pc
	int wait;		// when in blocked

};

/*string convertToEnum(int value) {
	string MyString(enum_string[value]);
	return MyString;
}*/

inline ostream& operator <<(ostream& output, const Process& process) {
	output << process.getPid() << setw(5) << setfill(' ') << left << process.getFileName()
	<< setw(5)  << setfill(' ')<< left << setw(5)  << setfill(' ')<< left << setw(5) << setfill(' ') << left << '\n';
	return output;
}


#endif //BS_MOORE_PROZESS_H
