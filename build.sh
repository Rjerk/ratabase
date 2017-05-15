#!/bin/bash

g++ -std=c++11 value.cpp hash.cpp list.cpp parser.cpp ratabaseManager.cpp ratabase.cpp server.cpp -o server

g++ client.cpp -o client
