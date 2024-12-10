#ifndef SERVICE_H
#define SERVICE_H

template <typename T>
class Service
{
public:
    Service(const Service &) = delete;
    Service &operator=(const Service &) = delete;

    static T& getInstance()
    {
        static T instance;
        return instance;
    }
    
protected:
    static T* instance;
    Service() {}

private:

};

#endif