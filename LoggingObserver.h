#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H
#include <iostream>
#include <list>
#include <memory>
#include <fstream>

//this is for getting different logs from different classes
class ILoggable{
public:
    ILoggable();
    ~ILoggable();
    virtual std::string stringToLog() = 0;
};


//observer base class
class Observer{
public:
    Observer();
    ~Observer();

    //notifications triggers this function
    virtual void Update(ILoggable* iloggable);
};


class Subject{
private:
    //static observer list
    static std::list<Observer*> observers;

public:
    Subject();

    ~Subject();

    //add and remove observers from list
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);

    //notifies all observers with log
    void Notify(ILoggable* iloggable);

};


class LogObserver: public Observer{
private:
    //the logs will be written on that file pointer
    std::ofstream logFile;

public:
    LogObserver();
    ~LogObserver();
    //the log observer will write the log on file after the subject's notification
    virtual void Update(ILoggable* iLoggable);
};

//this is for testing subject, observer, iloggable and logobserver classes
void testLoggingObserver();
#endif
