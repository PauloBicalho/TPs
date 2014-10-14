import sys

mergedTopicsFile = sys.argv[1]
numInicialTopics = int(sys.argv[2])
wordsFile = sys.argv[3]


topicWords = {}

with open(wordsFile,'r') as fin:
  for topic in range(50):
    l = fin.readline()
  
    if not l.startswith("Topic"):
      print "ERROR"
      exit(1)

    topicWords[topic] = []

    words = []
    for i in range(10):
      line = fin.readline()
      word = line.strip().split()[0]
      words.append(word)

    topicWords[topic].append( ",".join(words) )

currentTopic = numInicialTopics
with open(mergedTopicsFile,'r') as fin:
  for line in fin:
    if not line.startswith('%%'):
      line = line.strip().split()
      t1 = int(line[0]) -1
      t2 = int(line[1]) -1

      topicWords[currentTopic] = topicWords[t1] + topicWords[t2]
      topicWords.pop(t1)
      topicWords.pop(t2)

      currentTopic += 1

for k in topicWords.keys():
  print "#############"
  for s in topicWords[k]:
    print s

