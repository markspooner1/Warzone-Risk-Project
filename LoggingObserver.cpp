#include "LoggingObserver.h"

LogObserver::LogObserver() {
    logFile.open("gamelog.txt");
}

LogObserver::~LogObserver() {
    logFile.close();
}

void LogObserver::Update(ILoggable* iloggable) {
    std::cout << "Updated" << std::endl;
    logFile << iloggable->stringToLog()  << std::endl;
}

ILoggable::ILoggable() {
}

ILoggable::~ILoggable() {

}


Subject::Subject(){
}

Subject::~Subject(){
}



void Subject::addObserver(Observer* observer){
    observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer){
    observers.remove(observer);
}
void Subject::Notify(ILoggable* iloggable){
    std::cout << "Notified : ";
    std::cout << observers.size() << std::endl;
    for(auto iter = observers.begin();iter!= observers.end();iter++) {

        (*iter)->Update(iloggable);
    }
}

std::list<Observer*> Subject::observers;


Observer::Observer(){
}

Observer::~Observer(){
}
void Observer::Update(ILoggable* iloggable){

}

