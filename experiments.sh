#!/bin/bash
make -s clean
make -s sol

./1_philosophes/tests.sh
./2_producteurs_consommateurs/tests.sh
./3_lecteurs_ecrivains/tests.sh

cat ./1_philosophes/compiled/results.csv
cat ./2_producteurs_consommateurs/compiled/results.csv
cat ./3_lecteurs_ecrivains/compiled/results.csv