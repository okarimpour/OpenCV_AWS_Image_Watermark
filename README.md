![build](https://api.travis-ci.org/okarimpour/OpenCV_Project.svg?branch=master)
![version](https://img.shields.io/github/v/tag/okarimpour/OpenCV_Project.svg?sort=semver)
[![MIT license](https://img.shields.io/badge/license-MIT-brightgreen.svg)](http://opensource.org/licenses/MIT)

# OpenCV_Project

Overlay Images and Image Watermark on c++ and AWS Lambda function

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

You need to install an amazon linux 2 ([Running Amazon Linux 2 as a Virtual Machine On-Premises](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/amazon-linux-2-virtual-machine.html)) or use a amazon EC2, and evidently have access to amazon S3, AWS Lambda. You can find the link below to get started with these serveces and sign up for free trial by amazon at [Getting started with aws](https://aws.amazon.com/getting-started/).

### Installing

A step by step series of examples that tell you how to get a development env running:

A C++11 compiler, either GCC 5.x or later or Clang 3.3 or later

```
$ yum install gcc-c++ libcurl-devel
$ export CC=gcc
$ export CXX=g++
```

CMake v.3.5 or later

```
$ yum install cmake3
```

Download and compile the runtime

```
$ cd ~ 
$ git clone https://github.com/awslabs/aws-lambda-cpp.git
$ cd aws-lambda-cpp
$ mkdir build
$ cd build
$ cmake3 .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF \
-DCMAKE_INSTALL_PREFIX=~/out ..
$ make && make install
```

Install the following libraries:

* zlib-devel
* openssl-devel

```
$ yum install zlib-devel
$ yum install openssl-devel
```
Build aws sdk for c++

```
$ cd ~
$ git clone https://github.com/aws/aws-sdk-cpp.git
$ cd aws-sdk-cpp
$ mkdir build
$ cd build
$ cmake3 .. -DBUILD_ONLY=s3 \ -DBUILD_SHARED_LIBS=OFF \ -DENABLE_UNITY_BUILD=ON \ 
    -DCMAKE_BUILD_TYPE=Release \ -DCMAKE_INSTALL_PREFIX=~/out ..
$ make && make install
```

build the Lambda function

```
$ cd ../..
$ git clone https://github.com/okarimpour/OpenCV_Project.git
```

## Running the tests

How to run the automated tests for this system

## Deployment

Additional notes about how to deploy this on a live system

## Built With

## Authors

* **Omid Karimpour** - [okarimpour](https://github.com/okarimpour)

See also the list of [contributors](https://github.com/okarimpour/OpenCV_Project/graphs/contributors) who participated in this project.o

## License

This project is licensed under the MIT License - see the [LICENSE.md](https://github.com/okarimpour/OpenCV_Project/blob/master/LICENSE) file for details

## Acknowledgments

* Thanks to Sepeher hadizadeh to start this project and mentored me through this project.

## References

* https://aws.amazon.com/blogs/compute/introducing-the-c-lambda-runtime/



