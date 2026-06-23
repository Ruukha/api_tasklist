#include "APIClient.h"

APIClient::APIClient(const String& IP)
    : IP(IP)
{}

ApiResponse APIClient::get(const String& endpoint) const
{
    ApiResponse response;
    HTTPClient http;

    http.begin(String(IP) + endpoint);
    response.statusCode = http.GET();
    Serial.printf("HTTP status code: %d\n", response.statusCode);

    if (response.statusCode == 200){
        response.payload = http.getString();
        response.success = true;
        response.statusMessage = "OK";
    }
    else if (response.statusCode <= 0){
        response.statusMessage = http.errorToString(response.statusCode);
    }
    else{
        response.statusMessage = "HTTP status code: " + String(response.statusCode);
    }
    
    http.end();
    return response;
}

ApiResponse APIClient::del(const String& endpoint) const 
{
    ApiResponse response;
    HTTPClient http;

    http.begin(String(IP) + endpoint);
    response.statusCode = http.sendRequest("DELETE");
    if (response.statusCode == 204){
        response.success = true;
        response.statusMessage = "OK";
    }
    else if (response.statusCode <= 0){
        response.statusMessage = http.errorToString(response.statusCode);
    }
    else {
        response.statusMessage = "HTTP status code: " + String(response.statusCode);
    }
    
    http.end();
    return response;
}
