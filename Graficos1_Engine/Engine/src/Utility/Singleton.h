#pragma once

#include <string>
#include <mutex>

template <class Type>
//https://refactoring.guru/design-patterns/singleton/cpp/example#example-1
/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Singleton
{
    /*
     * The Singleton's constructor/destructor should always be private to
     * prevent direct construction/desctruction calls with the `new`/`delete`
     * operator.
     */
public:
    //Singletons should not be cloneable.
    Singleton(Singleton& other) = delete;
    //Singletons should not be assignable.
    void operator=(const Singleton&) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static Singleton* GetInstance(const Type& value);
    /**
     * Finally, any singleton should define some business logic, which can be
     * executed on its instance.
     */
    void SomeBusinessLogic()
    {
        // ...
    }
    Type value() const { return value_; }
protected:
    Singleton(const Type value) : value_(value) { }
    ~Singleton() {}
    Type value_;
private:
    static Singleton* pinstance_;
    static std::mutex mutex_;
};