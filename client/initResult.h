#pragma once
#include <Arduino.h>

enum class InitStatus{
    OK,
    Warning,
    Critical
};

struct InitResult{
    InitStatus status;
    String component;
    String message = "";

    const String statusAsString() const {
        switch (status) {
            case (InitStatus::OK): return "OK";
            case (InitStatus::Warning): return "WARNING";
            case (InitStatus::Critical): return "CRITICAL";
        }

        return "UNKNOWN";
    }
};