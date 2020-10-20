#ifndef DCOMMANDS_H
#define DCOMMANDS_H
#include <QString>
class Commands {
public:
    class Debug {
    public:
        static QString gyro;
        static QString accel;
        static QString stearing;
        static QString imu;
        static QString pid;
        static QString controller;
        static QString rx;
        static QString settings;
    };
    class Engines {
        public:
        static QString setSpeed(int speed);
        static QString stop;
    };
    class Settings {
        public:
        static QString restart;
        static QString show;
    };
};

QString Commands::Debug::gyro="/gyro";
QString Commands::Debug::accel="/accel";
QString Commands::Debug::stearing="/stear";
QString Commands::Debug::imu="/imu";
QString Commands::Debug::pid="/pid";
QString Commands::Debug::controller="/control";
QString Commands::Debug::rx="/rx";
QString Commands::Debug::settings="/settingsdo show";

QString Commands::Settings::restart = "/settingsdo restart";
QString Commands::Settings::show = "/settingsdo show";

QString Commands::Engines::stop = "/controldo stop";
QString Commands::Engines::setSpeed(int speed) {
    return "/controldo "+QString::number(speed);
}



#endif // COMMANDS_H
