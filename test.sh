#!/bin/bash

make
sudo make install

cd configkit && make tester
cd ..
cd logkit && make tester
cd ..
cd processkit && make tester
cd ..

./logkit/test
if [ "$?" != "0" ]
  then
    exit 1
  fi

./configkit/test

if [ "$?" != "0" ]
  then
    exit 1
  fi

  ./processkit/test

  if [ "$?" != "0" ]
    then
      exit 1
    fi
