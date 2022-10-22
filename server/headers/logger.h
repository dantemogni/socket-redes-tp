#pragma once

#include <iostream>
#include <fstream> 

#define LOG_FILE "./server/server.log"

using namespace std;

class Logger {
    public:
        static int Info(string message);
        static int Debug(string message);
        static int Error(string message);
    private:
        static string GetTimestamp();
        static int Write(string type, string message);
};
