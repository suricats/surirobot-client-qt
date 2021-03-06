# Surirobot Client

The client of Surirobot made with [Qt 5.5.1](https://www1.qt.io/qt5-5/);

## Getting Started

Surirobot Client is available for Linux system.

## Prerequisites
`install build-essential gdb`
## Installing under Linux with Netbeans

The installation has been tested on Ubuntu 16.04 with Netbeans 8.2

1. Install [Netbeans C/C++](https://netbeans.org/downloads/index.html)
2. Install Qt5, Qt5Multimedia and QMake
```bash
sudo apt-get install qt5-default qtmultimedia5-dev qt5-doc
```
3. Install HiRedis
```bash
sudo apt-get install libhiredis-dev
```
4. Install UUID and OpenCV
```bash
sudo apt-get install libopencv-dev uuid-dev 
```
5. Install audio packages (OpenAL, SNDFile, AVDevice and SDL2)
```bash
sudo apt-get install libopenal-dev libalut-dev libsndfile1-dev libsdl2-dev libsdl2-mixer-dev libavdevice-dev
```
6. Optional packages
```bash
libmpg123-dev libao-dev
```
7. Clone and open project
8. Use **linux-debug** build configuration or
* Add a linker to HiRedis library: **Properties > Linker > Librairies > Add Library File > Find libhiredis.so**
* Add other linkers 
* Enable QtNetwork : **Properties > Qt > Check 'QtNetwork'**


## Installing under Linux with command lines
Look at Dockerfile


## Authors

* **Suricats Consulting** - [website](http://www.suricats-consulting.com/)
* **Switch Team** 

## License

This project is licensed under the MIT License

