#pragma once
#include <HTTPClient.h>

struct ApiResponse{
    bool success{false};
    int statusCode{-1};
    String statusMessage{""};
    String payload{""};
};

class APIClient{
    private:
        String IP;

    public:
        APIClient(const String& IP);
        ApiResponse get(const String& endpoint) const;
        ApiResponse del(const String& endpoint) const;
};