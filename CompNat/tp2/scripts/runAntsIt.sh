#!/bin/bash

exe=$1
db=$2
out=$3

stdAnts=100
stdIt=500
stdEvapRate=0.05
stdAlpha=1
stdBeta=2

mkdir -p $out/numAnts
mkdir -p $out/numIt
mkdir -p $out/evapRate
mkdir -p $out/alpha
mkdir -p $out/beta

for numAnts in 25 50 75 100; do
  for numIt in 50 150 300 500 1000; do
    for seed in {1..20..1}; do
      echo "$exe $db $numAnts $numIt 99999999 0 $stdEvapRate $stdAlpha $stdBeta $seed > $out/numAnts/${numAnts}_${numIt}_${seed}.log"
      $exe $db $numAnts $numIt 99999999 0 $stdEvapRate $stdAlpha $stdBeta $seed > $out/numAnts/${numAnts}_${numIt}_${seed}.log
    done
  
    echo "Agrupando resultados"
    echo "python calcMean.py $out/numAnts ${numAnts}_${numIt} $numIt > $out/numAnts/media${numAnts}_${numIt}.log"
    python calcMean.py $out/numAnts ${numAnts}_${numIt} $numIt > $out/numAnts/media${numAnts}_${numIt}.log
  done;
done


  echo ""

#  for numIt in 50 100 200 300 500 1000; do
#    echo "$exe $db $stdAnts $numIt 99999999 0 $stdEvapRate $stdAlpha $stdBeta $seed > $out/numIt/${numIt}_${seed}.log"
#    $exe $db $stdAnts $numIt 99999999 0 $stdEvapRate $stdAlpha $stdBeta $seed > $out/numIt/${numIt}_${seed}.log
#  done

#  echo ""

#  for evapRate in 0.001 0.01 0.05 0.10 0.25 0.5 0.75; do
#    echo "$exe $db $stdAnts $stdIt 99999999 0 $evapRate $stdAlpha $stdBeta $seed > $out/evapRate/${evapRate}_${seed}.log"
#    $exe $db $stdAnts $stdIt 99999999 0 $evapRate $stdAlpha $stdBeta $seed > $out/evapRate/${evapRate}_${seed}.log
#  done
  
#  echo ""

#  for alpha in {1..10..1}; do
#    echo "$exe $db $stdAnts $stdIt 99999999 0 $stdEvapRate $alpha $stdBeta $seed > $out/alpha/${alpha}_${seed}.log"
#    $exe $db $stdAnts $stdIt 99999999 0 $stdEvapRate $alpha $stdBeta $seed > $out/alpha/${alpha}_${seed}.log
#  done
  
#  echo ""

#  for beta in {1..10..1}; do
#    echo "$exe $db $stdAnts $stdIt 99999999 0 $stdEvapRate $stdAlpha $beta $seed > $out/beta/${beta}_${seed}.log"
#    $exe $db $stdAnts $stdIt 99999999 0 $stdEvapRate $stdAlpha $beta $seed > $out/beta/${beta}_${seed}.log

#  done; """