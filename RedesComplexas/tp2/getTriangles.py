import networkx as nx
import sys

def getG(f):
  G = nx.Graph()

  fin = open(sys.argv[1],'r')
  for line in fin:
    if line.startswith('#'):
      continue

    i,j,v = map(int,line.strip().split())

    if i == j:
      continue

    G.add_edge(i,j)
    if 'weight' in G[i][j]:
      if( G[i][j]['weight'] != v ):
        G[i][j]['weight'] = -1
    else:
      G[i][j]['weight'] = v

  fin.close()
  return G

def getNeighbors(G,node):
  return (G.neighbors(node))

def isBalanced(G,a,b,c):
  positives = 0
  negatives = 0

  if G[a][b]['weight'] > 0:
    positives+=1
  else:
    negatives+=1

  if G[a][c]['weight'] > 0:
    positives+=1
  else:
    negatives+=1
  
  if G[b][c]['weight'] > 0:
    positives+=1
  else:
    negatives+=1


  return ((positives == 3 or positives == 1),positives)
    

def main():
  G = getG(sys.argv[1])

  total = 0
  balanced = 0
  types = {0: 0, 1: 0, 2: 0, 3: 0}
  for a in G.nodes():
    nA = getNeighbors(G,a)

    size = len(nA)
    for i in range(size-1):
      b = nA[i]
      for j in range(i+1,size):
        c = nA[j]

        if( G.has_edge(b,c) ):
          total += 1
          
          isB,t = isBalanced(G,a,b,c)
          types[t] += 1
          if( isB ):
            balanced += 1


    G.remove_node(a)


  print "Number of Triangles:", total
  print "Number of balanced triangles", balanced,"(%s)" % (balanced/float(total))
  print "\nTypes:"
  print "[+ + +] :", types[3], "(%s)" % (types[3]/float(total))
  print "[+ + -] :", types[2], "(%s)" % (types[2]/float(total))
  print "[+ - -] :", types[1], "(%s)" % (types[1]/float(total))
  print "[- - -] :", types[0], "(%s)" % (types[0]/float(total))
  print ""



  





main()
