import networkx as nx
import matplotlib.pyplot as plt
import pickle
import sys
import operator
from scipy.stats import spearmanr
from scipy.stats import pearsonr


def loadGraph(fileName):

  DG = nx.DiGraph()
  with open(fileName,'r') as fin:
    DG.add_edges_from([tuple(map(int,line.strip().split())) for line in fin.read().splitlines() 
      if not line.startswith("#") ])

  return DG

def calcPageRank(DG):
  return nx.pagerank(DG)

def calcHits(DG):
  return nx.hits(DG)

def getCdf(d):
  size = float(len(d))
  histogram = {}

  for k in d:
    val = d[k]

    if val not in histogram:
      histogram[val] = 1
    else:
      histogram[val] += 1


  sorted_keys = sorted(histogram.keys())

  x_values = []
  cdf = []

  aux = 0
  for val in sorted_keys:
    hist = histogram[val]
    x_values.append(val)
    
    aux += hist
    cdf.append(aux/size)

  return x_values,cdf

def getCdf2(d):
  values = d.values()
  x_values = sorted(set(values))
  hist = [values.count(x)/len(values) for x in x_values]

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

def spearmanCorrelation(d1,d2):
  keys = set(d1.keys())

  v1 = [d1[x] for x in keys]
  v2 = [d2[x] for x in keys]
  return pearsonr(v1,v2)[0]

def getNodosRank(d):
  sorted_d = sorted(d.iteritems(),key=operator.itemgetter(1),reverse=True)
  rank = [key for key,value in sorted_d]
  return rank

def getIntersection(rank1,rank2,t):
  set1 = set(rank1[0:t])
  set2 = set(rank2[0:t])

  return set1.intersection(set2)

def main():
  #DG = loadGraph(sys.argv[1])
  print "Loaded"

  #pr = calcPageRank(DG)
  #pickle.dump(pr, open("pr.p",'wb'))
  pr = pickle.load(open("pr.p",'rb'))
  print "PageRank ... Done"
  #ht = calcHits(DG)
  #pickle.dump(ht, open("ht.p",'wb'))
  ht = pickle.load(open("ht.p",'rb'))
  print "Hits ... Done"

  sumDiff = 0
  
  keys1 = pr.keys()
  keys2 = ht[1].keys()
  for i in range(len(keys1)):
    sumDiff += keys1[i] - keys2[i]
  print sumDiff


  print "Spearman Correlation PageRank - Authorities: " ,spearmanCorrelation(pr,ht[1])
  print "Spearman Correlation PageRank - Authorities: " ,spearmanCorrelation(pr,pr)
  print "Spearman Correlation PageRank - Hubs: " ,spearmanCorrelation(pr,ht[0])

  rankPr = getNodosRank(pr)
  rankAu = getNodosRank(ht[1])
  rankHu = getNodosRank(ht[0])

  for t in [5,10,20,50,100,150,200]:
    print "[PageRank - Authorities] Intersection in top", t, ": ", len(getIntersection(rankPr,rankAu,t))
    print "[PageRank - Hubs] Intersection in top", t, ": ", len(getIntersection(rankPr,rankHu,t))
    print "[Authorities - Hubs] Intersection in top", t, ": ", len(getIntersection(rankAu,rankHu,t))





  plt.figure()
  plt.title("CDF of PageRank values")
  plt.xlabel('Value')
  plt.ylabel('Y = P(X <= x)')
  x_values,cdf = getCdf(pr)
  #plt.xscale('log')
  plt.xlim(xmin=-0.01,xmax=0.2)
  plt.ylim(ymax=1.1)
  plt.plot(x_values, cdf, label = 'PageRank')
  plt.savefig("cdf_pr.pdf")
  
  plt.figure()
  plt.title("CDF of Hubs values")
  plt.xlabel('Value')
  plt.ylabel('Y = P(X <= x)')
  #plt.xscale('log')
  plt.xlim(xmin=-0.01,xmax=0.2)
  plt.ylim(ymax=1.1)
  x_values,cdf = getCdf(ht[0])
  plt.plot(x_values, cdf, label = 'Hubs')
  plt.savefig("cdf_hub.pdf")
  
  plt.figure()
  plt.title("CDF of Authorities values")
  plt.xlabel('Value')
  plt.ylabel('Y = P(X <= x)')
  #plt.xscale('log')
  plt.xlim(xmin=-0.01,xmax=0.2)
  plt.ylim(ymax=1.1)
  x_values,cdf = getCdf(ht[1])
  plt.plot(x_values, cdf, label = 'Authorities')
  plt.savefig("cdf_auto.pdf")


  plt.figure()
  plt.title("CDF of PageRank and Hits values")
  plt.xlabel('Value')
  plt.ylabel('Y = P(X <= x)')
  plt.xscale('log')

  x_values,cdf = getCdf(pr)
  #plt.plot(x_values, cdf, marker='o', linestyle='--', label = 'PageRank')
  plt.plot(x_values, cdf, label = 'PageRank')
  x_values,cdf = getCdf(ht[0])
  plt.plot(x_values, cdf, label = 'Hits - Hubs')
  x_values,cdf = getCdf(ht[1])
  plt.plot(x_values, cdf, label = 'Hits - Authorities')
  
  plt.legend(loc='best')
  plt.savefig("cdf.pdf")



main()
