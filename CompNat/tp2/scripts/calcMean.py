import sys
import commands as cmd
import numpy as np

path = sys.argv[1]
v = sys.argv[2]

it = int(sys.argv[3])

files = cmd.getoutput( "ls %s_*" % (path + "/" + v)  ).splitlines()

#vals = np.array([  [0.0]*4 ]*it )
vals = np.array([ [ [0.0]*len(files)]*4 ]*it )

k = 0
for f in files:
  fin = open(f, 'r')

  print >> sys.stderr, "Open %s" % f
  i = 0
  for line in fin:
    line = line.strip().split("\t")
    vals[i][0][k] = float(line[1])
    vals[i][1][k] = float(line[2])
    vals[i][2][k] = float(line[3])
    vals[i][3][k] = float(line[4])

    i += 1

  k+=1

for i in range(it):
  print "%.3f ( %.3f )" % (vals[i][0].mean(), vals[i][0].std()),
  print "%.3f ( %.3f )" % (vals[i][1].mean(), vals[i][1].std()),
  print "%.3f ( %.3f )" % (vals[i][2].mean(), vals[i][2].std()),
  print "%.3f ( %.3f )" % (vals[i][3].mean(), vals[i][3].std())

