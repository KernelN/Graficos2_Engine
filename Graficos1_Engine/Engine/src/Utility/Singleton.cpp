//#include "Singleton.h"
//#include<iostream>
//
////https://refactoring.guru/design-patterns/singleton/cpp/example#example-1
//
//Singleton<Type>* Singleton::pinstance_{ nullptr };
//std::mutex Singleton::mutex_;
//
///**
// * The first time we call GetInstance we will lock the storage location
// *      and then we make sure again that the variable is null and then we
// *      set the value. RU:
// */
//Singleton* Singleton::GetInstance(const Type& value)
//{
//    std::lock_guard<std::mutex> lock(mutex_);
//    if (pinstance_ == nullptr)
//    {
//        pinstance_ = new Singleton(value);
//    }
//    return pinstance_;
//}
//
//
//#pragma region EXAMPLE
//void ThreadFoo() {
//    // Following code emulates slow initialization.
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    Singleton* singleton = Singleton::GetInstance("FOO");
//    std::cout << singleton->value() << "\n";
//}
//void ThreadBar() {
//    // Following code emulates slow initialization.
//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//    Singleton* singleton = Singleton::GetInstance("BAR");
//    std::cout << singleton->value() << "\n";
//}
//int main()
//{
//    std::cout << "If you see the same value, then singleton was reused (yay!\n" <<
//        "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
//        "RESULT:\n";
//    std::thread t1(ThreadFoo);
//    std::thread t2(ThreadBar);
//    t1.join();
//    t2.join();
//
//    return 0;
//}
//#pragma endregion