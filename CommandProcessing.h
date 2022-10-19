#pragma once 
#include <string>
#include <iostream>

using namespace std;

class Command{
private: 
string commands;
string effect;
public : 
Command();
void saveEffect();
string getCommands();
void setCommands();
string getEffect();
void setEffect();
};

class CommandProcessor {
 private :
 void readcommand();
 public : 
 string getCommand(); 
 void savecommand();
 
};


class FileCommandProcessorAdapter{

};

void testCommandProcessor();