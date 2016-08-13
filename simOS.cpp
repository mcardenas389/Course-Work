/************************************************
 * Michael Cardenas                             *
 * CSCI 340 01                                  *
 * 10/15/13                                     *
 *                                              *
 * simOs.cpp                                    *
 * A simple program meant to simulate an OS.    *
 * Handles the ready queue, queues for various  *
 * devices (i.e. printers, disks, and CD/RW),   *
 * and processes being worked on by the CPU.    *
 ************************************************/

#include <list>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::stack;
using std::string;
using std::vector;
using std::stringstream;

//process control block
struct PCB {
     int PID, memory, fileLength; //process ID, memory location
	 string filename;
	 char readWrite;//file is either read or written
	 
	 PCB (const int& thePID, const int& mem, const int& fl, const string& fn, const char& rw)
	     : PID(thePID), memory(mem), filename(fn), fileLength(fl), readWrite(rw) { }
};

//parses a string to int
int parseInt(const string& str)
{
     stringstream ss(str);
     int num;
     
	 //error
     if((ss >> num).fail())
         cout << "Failed to parse string to integer." << endl;
  
     return num;
}

//prints a queue
void printQueue(list<PCB>& q)
{
     if(!q.empty()) {
         int lineCounter = 0; //counts number of lines that have been printed
         list<PCB>::iterator it = q.begin();
	 
	     while(it != q.end()) {
	         cout << "PID: " << it -> PID << endl;
		     it++;
		     lineCounter++;
		 
		     if(lineCounter == 23) { //ensures that the information does that scroll off a 24 line screen
		         cout << "Press enter to continue . . .";
			     cin.get();
				 
				 lineCounter = 0;
		     }
	     }
	 }
	 else cout << "There is nothing to print from the queue." << endl;
}

//an overload of printQueue that prints a group of queues
void printQueue(const int& first, const int& last, const char& device, vector< list<PCB> >& sys)
{
     int lineCounter = 0, queueCounter = 1; //queueCounter counts the number of queues
	 string str1;//, str2, str3;
	 stringstream ss;
	 //unsigned pos; //stores position within a string
     list<PCB>::iterator it;
	 
	 if(device == 'c') str1 = "C1";
	 else if(device == 'd') str1 = "D1";
	 else if(device == 'p') str1 = "P1";
	 
	 for(int i = first; i <= last; i++) {
	     cout << str1 << endl;
		 lineCounter++;
		 
		 if(lineCounter == 23) { 
		     cout << "Press enter to continue . . .";
			 cin.get();
					 
		     lineCounter = 0;
		 }
		 
	     if(!sys[i].empty()) {
		     it = sys[i].begin();
			 
	         while(it != sys[i].end()) {
	             cout << "PID: " << it -> PID  << "\tMemory: " << it -> memory;
				 
				 if(it -> fileLength != -1)
				     cout << "\tLength: " << it -> fileLength;
				 
				 cout << "\tName: " << it -> filename 
				      << "\tR/W: " << it -> readWrite << endl;
				
				 /*str2 = ss.str();
				 
				 if(str2.size() > 80) {
				     pos = str2.find("Name:");
					 str3 = str2.substr(pos);
					 str2.erase(pos, pos - str2.size() - 1);
					 cout << str2 << endl
					      << str3;
					 
					 lineCounter += 2;
				 }
				 else {
				     cout << str2;
					 
		             lineCounter++;
				 }
				 
				 ss.str(std::string()); //clear the stringstream
				 */
				 
				 it++;
				 lineCounter++;
				 
				 //ensures that the information does not that scroll off a 24 line screen
		         if(lineCounter == 23) { 
		             cout << "Press enter to continue . . .";
			         cin.get();
					 
					 lineCounter = 0;
		         }
			 }
		 }
		 else {
		     cout << "Empty." << endl;
			 lineCounter++;
			 
			 if(lineCounter == 23) { 
		         cout << "Press enter to continue . . .";
			     cin.get();
				
			     lineCounter = 0;
		     }
		 }
		 
		 //raises the number of the device
		 ss << ++queueCounter;
		 str1.replace(str1.begin() + 1, str1.end(), ss.str());
		 ss.str(std::string()); //clears stringstream
	 }
}

//runs the "OS"
void run(const int& pNum, const int& dNum, const int& cNum, vector< list<PCB> >& sys)
{
     int PID = 0, location;
	 string str;
	 PCB recProc(-1, -1, -1, "-1", 'w'), //recProc will be a recycled PCB
	     nextProc(-1, -1, -1, "-1", 'w'); //nextProc is a container for the next process
	 list<PCB> readyQueue;
	 stack<PCB> CPU;

	 cout << "\nTo call a device enter 'device letter' + 'device number'" << endl 
	      << "(e.g. for 'printer 1' enter 'p1')" << endl
	      << "\nEnter 'exit' to terminate SimOS." << endl;
	 
	 for(int i = 1; i > 0; i++) {
		 cout << "\nEnter command: ";
		 getline(cin, str);
		 
		 if(str[0] == 'A') { //creates a new PCB
		     if(readyQueue.size() < readyQueue.max_size()) {
		         if(recProc.PID == -1) { //checks if recProc is not empty
					 PCB newProc(PID++, -1, -1, "-1", 'w');
					 readyQueue.push_back(newProc);
				 }
				 else {
					 recProc.PID = PID++;
					 recProc.fileLength = -1;
					 readyQueue.push_back(recProc);
					 recProc.PID = -1;
				 }
			 
				 cout << "Process was successfully created." << endl;
			 }
			 else cout << "A new process failed to be created because the queue is full." << endl;
		 }
		 else if(str[0] == 'S') { //prints a requested queue
		     cout << "Enter which queues you want to print: ";
			 getline(cin, str);
			 
			 if(str[0] == 'c') //print CD/RW queues
			     if(cNum > 0)
			         printQueue((pNum + dNum), (pNum + dNum + cNum - 1), str[0], sys);
				 else cout << "There are no CD/RW devices connected to the system." << endl;
			 else if(str[0] == 'd') //print disk queues
			     if(dNum > 0)
			         printQueue(pNum, (pNum + dNum - 1), str[0], sys);
				 else cout << "There are no disks connected to the system." << endl;
			 else if(str[0] == 'p') //print printer queues
			     if(pNum > 0)
			         printQueue(0, (pNum - 1), str[0], sys);
				 else cout << "There are no printers connected to the system." << endl;
			 else if(str[0] == 'r') //print ready queue
				 printQueue(readyQueue);
			 else cout << "Command is not recognized." << endl;
		 }
		 else if(str[0] == 'C') { //pops process from CD/RW queue
		     if(cNum > 0) {
			     str.erase(0, 1);
				 
			     if(str[0] >= 49 && str[0] <= 57 && parseInt(str.c_str()) <= cNum) {
				     location = pNum + dNum + parseInt(str) - 1;
					 
					 if(!sys[location].empty()) {
					     nextProc = sys[location].front();
						 readyQueue.push_back(nextProc);
					     sys[location].pop_front();
					     cout << "Process was successfully dequeued." << endl;
					 }
					 else cout << "There is no process in requested queue." << endl;
				 }
				 else cout << "There is no such device number in the system currently." << endl;
			 }
			 else cout << "There are no connected CD/RW devices on this system." << endl;
		 }
		 else if(str[0] == 'D') { //pops process from disk queue
		     if(dNum > 0) {
			     str.erase(0, 1);
				 
			     if(str[0] >= 49 && str[0] <= 57 && parseInt(str.c_str()) <= dNum) {
				     location = pNum + parseInt(str) - 1;
					 
					 if(!sys[location].empty()) {
					     nextProc = sys[location].front();
						 readyQueue.push_back(nextProc);
					     sys[location].pop_front();
					     cout << "Process was successfully dequeued." << endl;
					 }
					 else cout << "There is no process in requested queue." << endl;
				 }
				 else cout << "There is no such device number in the system currently." << endl;
			 }
			 else cout << "There are no connected disks on this system." << endl;
		 }
		 else if(str[0] == 'P') { //pops process from printer queue
		     if(pNum > 0) {
			     str.erase(0, 1);
				 
			     if(str[0] >= 49 && str[0] <= 57 && parseInt(str.c_str()) <= pNum) {
				     location = parseInt(str) - 1;
					 
					 if(!sys[location].empty()) {
					     nextProc = sys[location].front();
						 readyQueue.push_back(nextProc);
					     sys[location].pop_front();
					     cout << "Process was successfully dequeued." << endl;
					 }
					 else cout << "There is no process in requested queue." << endl;
				 }
				 else cout << "There is no such device number in the system currently." << endl;
			 }
			 else cout << "There are no connected printers on this system." << endl;
		 }
		 else if(str[0] == 'c') { //send process to CD/RW
		     if(cNum > 0) {
			     str.erase(0, 1);
				 
			     if(str[0] >= 49 && str[0] <= 57 && parseInt(str.c_str()) <= cNum) {
					 if(!CPU.empty()) {
						 nextProc = CPU.top();
					     CPU.pop();
						 
						 location = pNum + dNum + parseInt(str) - 1;
						 
						 cout << "Please enter the following: " << endl
							  << "\nFile name: ";
						 getline(cin, str);
						 nextProc.filename = str;
						 
						 cout << "Location in memory: ";
						 getline(cin, str);
						 nextProc.memory = parseInt(str);
						 
						 cout << "Read or write (r/w): ";
						 getline(cin, str);
						 nextProc.readWrite = str[0];
						 
						 if(str[0] == 'w') {
						     cout << "File length: ";
							 getline(cin, str);
							 nextProc.fileLength = parseInt(str);
						 }
						 
						 sys[location].push_back(nextProc);
						 str.erase();
						
						 cout << "\nProcess was successfully moved to the requested device." << endl;
					 }
					 else cout << "There is currently no process in the CPU." << endl;
				 }
				 else cout << "There is no such device name in the system." << endl;
			 }
			 else cout << "There are no connected CD/RW devices on this system." << endl;
		 }
		 else if(str[0] == 'd') { //send process to disk
		     if(dNum > 0) {
			     str.erase(0, 1);
				 
			     if(str[0] >= 49 && str[0] <= 57 && parseInt(str.c_str()) <= dNum) {
				     if(!CPU.empty()) {
						 nextProc = CPU.top();
					     CPU.pop();
						
						 location = pNum + parseInt(str) - 1;
						 
						 cout << "Please enter the following: " << endl
							  << "\nFile name: ";
						 getline(cin, str);
						 nextProc.filename = str;
						 
						 cout << "Location in memory: ";
						 getline(cin, str);
						 nextProc.memory = parseInt(str);
						 
						 cout << "Read or write (r/w): ";
						 getline(cin, str);
						 nextProc.readWrite = str[0];
						 
						 if(str[0] == 'w') {
						     cout << "File length: ";
							 getline(cin, str);
							 nextProc.fileLength = parseInt(str);
						 }	 
						 
						 sys[location].push_back(nextProc);
						 str.erase();
						
						 cout << "\nProcess was successfully moved to the requested device." << endl;
					 }
					 else cout << "There is currently no process in the CPU." << endl;
				 }
				 else cout << "There is no such device name in the system." << endl;
			 }
			 else cout << "There are no connected disks on this system." << endl;
		 }
		 else if(str[0] == 'p') { //send process to printer
		     if(pNum > 0) {
			     str.erase(0, 1);
			 
			     if(str[0] >= 49 && str[0] <= 57 && parseInt(str.c_str()) <= pNum) {
				     if(!CPU.empty()) {
						 nextProc = CPU.top();
						 CPU.pop();
							 
						 location = parseInt(str) - 1;
						 
						 cout << "Please enter the following: " << endl
							  << "\nFile name: ";
						 getline(cin, str);
						 nextProc.filename = str;
						 
						 cout << "Location in memory: ";
						 getline(cin, str);
						 nextProc.memory = parseInt(str);
						 
						 cout << "File length: ";
						 getline(cin, str);
						 nextProc.fileLength = parseInt(str);
						 
						 sys[location].push_back(nextProc);
						 str.erase();
							 
						 cout << "\nProcess was successfully moved to the requested device." << endl;
					 }
					 else cout << "There is currently no process in the CPU." << endl;
				 }
				 else cout << "There is no such device name in the system." << endl;
			 }
			 else cout << "There are no connected printers on this system." << endl;
		 }
		 else if(str[0] == 't') { //terminate process currently in CPU
		     if(!CPU.empty()) {
			     recProc = CPU.top();
				 CPU.pop();
				 cout << "Process was successfully terminated." << endl;
			 }
			 else cout << "There is no process to terminate in the CPU." << endl;
		 }
		 else if(str == "exit") break; //exit loop
		 else cout << "Command is not recognized." << endl;
		 
         //if a process exists in the ready queue push it into the CPU
		 if(CPU.empty() && !readyQueue.empty()) {
		     nextProc = readyQueue.front();
			 CPU.push(nextProc);
			 readyQueue.pop_front();
		 }
	 }
}

//gathers information about system (i.e. how many of each device exists)
void sysgen()
{
     int pNum = 0, dNum = 0, cNum = 0; //printer number, disk number, and cd number
     string str;
	 
	 cout << "\t\tWelcome to SimOS!"  << endl
	      << "Please enter the number of the following devices:\n\nPrinter: ";
	 getline(cin, str);
	 pNum = parseInt(str);
	 
	 cout << "\nDisks: ";
	 getline(cin, str);
	 dNum = parseInt(str);
	 
	 cout << "\nCD/RW: ";
	 getline(cin, str);
	 cNum = parseInt(str);
	 
	 list<PCB> q;
	 vector< list<PCB> > sys(pNum + dNum + cNum, q);
	 
	 run(pNum, dNum, cNum, sys);
}

int main()
{
     sysgen();
	 
	 return 0;
}