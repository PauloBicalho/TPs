import networkx as nx
import matplotlib.pyplot as plt
import sys


def loadGraph(fileName):

  DG = nx.DiGraph()
  with open(fileName,'r') as fin:
    DG.add_edges_from([tuple(line.strip().split()) for line in fin.read().splitlines() 
      if not line.startswith("#") ])

  return DG

def calcPageRank(DG):
  return nx.pagerank(DG)

def calcHits(DG):
  return nx.hits(DG)

def getCdf(d):
  values = d.values()
  x_values = sorted(set(values))
  hist = [values.count(x) for x in x_values]

  cdf = []
  aux = 0
  for v in hist:
    aux += v
    cdf.append(aux)

  return x_values,cdf

def getDiff(d1,d2):
  diff = {}

  for n in d1:
    diff[n] = abs(d1[n] - d2[n])

  return diff

def main():
  DG = loadGraph(sys.argv[1])
  print "Loaded"

  pr = calcPageRank(DG)
  print "PageRank ... Done"
  ht = calcHits(DG)
  print "Hits ... Done"

  plt.figure()
  plt.title("CDF of PageRank and Hits values")
  plt.xlabel('Value')
  plt.ylabel('Y = P(X <= x)')
  x_values,cdf = getCdf(pr)
  plt.plot(x_values, cdf, marker='o', linestyle='--', label = 'PageRank')
  plt.legend(loc='best')
  
  x_values,cdf = getCdf(ht)
  plt.plot(x_values, cdf, marker='o', linestyle='--', label = 'Hits')

  plt.savefig("cdf.pdf")

  plt.figure()
  plt.title("CDF of the differences between Pagerank and Hits values")
  plt.xlabel('Value')
  plt.ylabel('Y = P(X <= x)')
  
  diff = getDiff(pr,ht)
  x_values,cdf = getCdf(diff)
  plt.plot(x_values, cdf, marker='o', linestyle='--')

  plt.savefig("cdf_diff.pdf")

main()
