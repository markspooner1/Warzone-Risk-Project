#include "LoggingObserver.h"


//Constructor for logobserver
LogObserver::LogObserver() {
    //opens the log file
    logFile.open("gamelog.txt");
}

//deconstructor for logobserver
LogObserver::~LogObserver() {
    //closes the log file
    logFile.close();
}


//Writes logs into log file
void LogObserver::Update(ILoggable* iloggable) {
    std::cout << "Log Observer Updated" << std::endl;
    logFile << iloggable->stringToLog()  << std::endl;
}

//constructor for iloggable
ILoggable::ILoggable() {
}

//deconstructor for iloggable
ILoggable::~ILoggable() {

}

//constructor for subject
Subject::Subject(){
}

//deconstructor for subject
Subject::~Subject(){
}


//pushes observers into observer list
void Subject::addObserver(Observer* observer){
    observers.push_back(observer);
}

//removes observers into observer list
void Subject::removeObserver(Observer* observer){
    observers.remove(observer);
}

//notifies all observers with the event
void Subject::Notify(ILoggable* iloggable){
    for(auto iter = observers.begin();iter!= observers.end();iter++) {
        (*iter)->Update(iloggable);
    }
}

//outside definition for static observer-list
std::list<Observer*> Subject::observers;

//constructor for observer
Observer::Observer(){
}

//deconstructor for observer
Observer::~Observer(){
}

//observer update function
void Observer::Update(ILoggable* iloggable){

}

