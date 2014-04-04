#!/bin/bash

for db in `ls db`; do
  echo "python getTriangels.py db/$db"
  python getTriangles.py db/$db
  echo "----------------------------------------------"
done;
