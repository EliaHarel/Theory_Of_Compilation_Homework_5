#!/bin/bash

#	link to Makefile:
makefileurl="https://webcourse.cs.technion.ac.il/fc159753hw_236360_202001/hw/WCFiles/makefile"
#	link to tests:
testsurl="https://webcourse.cs.technion.ac.il/fc159753hw_236360_202001/hw/WCFiles/hw5-tests.zip"
#	number of tests:


hostname="cscomp"


rm -f lex.yy.c
rm -f parser.tab.*pp
rm -f hw5


if [ $( hostname ) != "$hostname" ]
then
  echo "This script is only intended to run on "$hostname"!"
  exit
fi


make &> /dev/null

cp hw5 "tests/"
cp hw5 "tests/____runner_tests"
cp hw5 "tests/hw5tests_zip"
cp hw5 "tests/kiv_tests"

echo "#################################### staff tests ####################################"
cd tests/
./selfcheck-hw5


echo "#################################### runner tests ####################################"
cd ____runner_tests/
./runner.sh
cd -


echo "#################################### zip tests tests ####################################"
cd hw5tests_zip/
./tests.sh
cd -


echo "#################################### need to add kiv tests ####################################"


exit
