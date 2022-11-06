#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H
#include <iostream>
#include <list>
#include <memory>
#include <fstream>


//this function will be used on
class ILoggable{
private:
    std::string log;
public:
    ILoggable();
    ~ILoggable();
    void Update(ILoggable* iLoggable);
    virtual std::string stringToLog() = 0;
};



class Observer{

public:
    Observer();
    ~Observer();
    virtual void Update(ILoggable* iloggable);

};




class Subject{
private:

public:

    std::list<std::shared_ptr<Observer>> observers;

    Subject();

    ~Subject();

    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);
    void Notify(ILoggable* iloggable);

};


class LogObserver: public Observer{
private:
    std::shared_ptr<std::fstream> logFile;

    void write_log();

public:
    LogObserver();
    ~LogObserver();
    void Update(ILoggable* iLoggable);
};


void testLoggingObserver();
#endif
