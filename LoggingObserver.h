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
    virtual ~Observer();
    virtual void Update(ILoggable* iloggable);

};

//this is a singleton class
class Subject{
private:


    static std::list<Observer*> observers;

public:


    Subject();

    ~Subject();

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void Notify(ILoggable* iloggable);

};


class LogObserver: public Observer{
private:
    std::ofstream logFile;


public:
    LogObserver();
    ~LogObserver();
    virtual void Update(ILoggable* iLoggable);
};


void testLoggingObserver();
#endif
