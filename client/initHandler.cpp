#include "initHandler.h"
#include "screen.h"

InitHandler::InitHandler(Screen& screen)
    : screen(screen)
{}

bool InitHandler::handle(const InitResult& res)
{
    String message{"- " + res.component + ": " + res.statusAsString() + " - " + res.message};
    Serial.println(message);
    screen.println(message);

    return (res.status != InitStatus::Critical);
}