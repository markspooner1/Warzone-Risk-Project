#include "LoggingObserver.h"

LogObserver::LogObserver() {
    std::ofstream, logFile;
    logFile.open("gamelog.txt");

}

LogObserver::~LogObserver() {
    logFile->close();
}

void LogObserver::Update(ILoggable* iloggable) {
    *logFile << iloggable->stringToLog() << std::endl;
}

ILoggable::ILoggable() {
}

ILoggable::~ILoggable() {

}


Subject::Subject(){
}

Subject::~Subject(){
}


void Subject::addObserver(std::shared_ptr<Observer> observer){
    observers.push_back(observer);
}
void Subject::removeObserver(std::shared_ptr<Observer> observer){
    observers.remove(observer);
}
void Subject::Notify(ILoggable* iloggable){

    for(auto iter = observers.begin();iter!= observers.end();iter++) {
        (*iter)->Update(iloggable);
    }
}

Observer::Observer(){
}

Observer::~Observer(){
}

