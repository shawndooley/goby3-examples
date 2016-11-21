#include "goby/middleware/single-thread-application.h"

#include "messages/nav.pb.h"
#include "config.pb.h"

// optional "using" declaration (reduces verbiage)
using Base = goby::SingleThreadApplication<BasicSubscriberConfig>;

class BasicSubscriber : public Base
{
public:
    // event driven subscriber doesn't need any loop() method (default constructor for Base)
    BasicSubscriber() 
        {
            // C++11 lambda that turns this->incoming_nav into a basic function that will be called when we get subscribed mail
            auto nav_callback = [this] (const NavigationReport& nav)
                { this->incoming_nav(nav); };
            // subscribe to a group for a given variable type and when we receive messages, call the nav_callback function
            portal().subscribe<nav_group, NavigationReport>(nav_callback);
        }

    // called each time a NavigationReport on the Group "navigation" is received
    void incoming_nav(const NavigationReport& nav)
        {
            std::cout << "Rx: " << nav.DebugString() << std::flush;
        }    
    
private:
    // "navigation" must match the group name used by the publisher(s)
    static constexpr goby::Group nav_group{"navigation"};
    
};

constexpr goby::Group BasicSubscriber::nav_group;


int main(int argc, char* argv[])
{ return goby::run<BasicSubscriber>(argc, argv); }