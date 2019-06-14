import sys, collections, heapq

# globals
initialStateFile  = None
goalStateFile     = None
mode              = None  #either bfs, dfs, iddfs, astar
outputFile        = None
#5 actions: 1 chicken, 2 chickens, 1 wolf, 1 wolf and 1 chicken, 2 wolves
possibleActions   = [[1,0],[2,0],[0,1],[1,1],[0,2]]
goalState         = None
numCreatedNodes = 0
nodeCount         = 0
lastExpansion     = 0
depthLimit        = 0

# priority queue class for astar
class PriorityQueue:
    def __init__(self):
        self._queue = []
        self._index = 0

    def push(self, item, priority):
        heapq.heappush(self._queue, (priority, self._index, item))
        self._index += 1

    def pop(self):
        return heapq.heappop(self._queue)[-1]

    def __len__(self):
        return len(self._queue)

# state of the game is represented by nodes
class Node():
  def __init__(self, leftSide, rightSide, parent, action, depth, pathcost):
    global numCreatedNodes
    self.leftSide = leftSide
    self.rightSide = rightSide
    self.parent = parent
    self.action = action
    self.depth = depth
    self.pathcost = pathcost
    self.key = tuple(self.leftSide + self.rightSide)
    numCreatedNodes = numCreatedNodes + 1

# puts the result of an action in a node
class actionResult():
    def __init__(self, startSide, endSide, action, endBoatSide):
        startSide[0] = startSide[0] - action[0]
        startSide[1] = startSide[1] - action[1]
        endSide[0] = endSide[0] + action[0]
        endSide[1] = endSide[1] + action[1]
        if endBoatSide == "right":
            self.rightSide = endSide
            self.leftSide = startSide
            self.rightSide[2] = 1
            self.leftSide[2] = 0
        else:
            self.rightSide = startSide
            self.leftSide = endSide
            self.rightSide[2] = 0
            self.leftSide[2] = 1
        self.action = action

# applies an action to a node
def applyAction(action, node):
  if node.rightSide[2] == 1:
    updatedNode = actionResult(list(node.rightSide), list(node.leftSide), action, "left")
  else:
    updatedNode = actionResult(list(node.leftSide), list(node.rightSide), action, "right")
  return updatedNode

# this checks if an action is allowed
def testAction(action, node):
  # find boat
  if node.rightSide[2] == 1:
    startSide = list(node.rightSide)
    endSide = list(node.leftSide)
  else:
    startSide = list(node.leftSide)
    endSide = list(node.rightSide)

  # perform action
  startSide[0] = startSide[0] - action[0]
  startSide[1] = startSide[1] - action[1]
  endSide[0] = endSide[0] + action[0]
  endSide[1] = endSide[1] + action[1]

  # test result of the action
  #if we try to move more chickens and wolves than we have, return false
  if (startSide[0] < 0) or (startSide[1] < 0) or (endSide[0] < 0) or (endSide[1] < 0):
    return False
  # if there are no chickens or number of chickens is greater or equal than
  # number of wolves on both sides, return true
  elif ((startSide[0] == 0) or (startSide[0] >= startSide[1])) and (endSide[0] == 0 or (endSide[0] >= endSide[1])):
    return True
  else:
    return False

# expand successors
def expand(node):
  successors = []
  for successor in filterAndApplyActions(node):
    newNode = Node(successor.leftSide, successor.rightSide, node, successor.action, node.depth + 1, node.depth + 1)
    successors.append(newNode)
  return successors

# applies only allowed actions to all successors
def filterAndApplyActions(node):
  global possibleActions
  if mode == "iddfs":
    if node.depth == depthLimit:
      return []
  allowedActions = filter(lambda x: testAction(x, node), possibleActions)
  successors = map(lambda y: applyAction(y, node), allowedActions)
  return successors


# checks if a node is in closed
def inClosed(node, closed):
  if node.key in closed:
    if node.depth >= closed[node.key]:
      return True
    else:
      return False

# tests if a node matches the goal state
def goalTest(node, goalNode):
    if (node.leftSide == goalNode.leftSide) and (node.rightSide == goalNode.rightSide):
        return True
    else:
        return False

# hueristic to determine pathcost
def hueristic(currentNode, goalNode):
    # find boat
    if goalNode.rightSide[2] == 1:
        cost = (currentNode.leftSide[0] + currentNode.leftSide[1]) - 1
    else:
        cost = (currentNode.rightSide[0] + currentNode.rightSide[1]) - 1
    return cost

# This is based off the pseudo code for graph search
# on slide 67 of the uninformed search lecture.
# it executes astar, bfs, dfs, and iddfs
def graphSearch(initialNode, goalNode, fringe):
  global nodeCount, lastExpansion, depthLimit, numCreatedNodes
  closed = {}
  if mode == "astar":
    fringe.push(initialNode, initialNode.pathcost)
  else:
    fringe.append(initialNode)
  while True:
    # if fringe is empty, return failure unless in iddfs mode
    if len(fringe) == 0:
      # if iddfs mode, increment depthLimit and restart search
      if mode == "iddfs":
        if depthLimit > 500:
          exit(1)
        lastExpansion = 0
        fringe.append(initialNode)
        depthLimit = depthLimit + 1
        numCreatedNodes = 0
        closed = {}
        continue
      else:
        sys.exit("Failure: No solution found")

    if mode == "bfs":
      currentNode = fringe.popleft() # FIFO for bfs
    else:
      currentNode = fringe.pop() # LIFO for dfs and iddfs

    #test if we found goal state
    if goalTest(currentNode, goalNode):
      return currentNode

    # check if node is in closed
    if not inClosed(currentNode, closed):
      if mode == "dfs" and currentNode.depth >= 500:
        continue
      nodeCount = nodeCount + 1
      # add node to closed
      closed[currentNode.key] = currentNode.depth
      # insert node to fringe
      if mode == "astar":
        map(lambda x: fringe.push(x, x.pathcost + hueristic(x, goalState)), expand(currentNode))
      else:
        map(fringe.append, expand(currentNode))

# find the path that leads to the end node by using the parent pointers
def findNodePath(node):
    pathToNode = []
    currentNode = node
    while True:
        try:
            if currentNode.parent == None:
                break
            pathToNode.append(currentNode.action)
        except:
            break
        currentNode = currentNode.parent
    return pathToNode[::-1]

# prints the state path
def printStatePath(node):
    pathToNode = []
    currentNode = node
    while True:
        try:
            if currentNode.parent == None:
                break
            pathToNode.append(currentNode.action)
	    printState(currentNode)
	    print '\n'
        except:
            break
        currentNode = currentNode.parent
    return pathToNode[::-1]

# get the state from a file and put it in a node
# self, leftSide, rightSide, parent, action, depth, pathcost
def readStateFromFileToNode(file):
    with open(file) as f:
        fileContents = f.readlines()
    return Node(map(int, fileContents[0].strip('\n').split(',')), map(int, fileContents[1].strip('\n').split(',')), None, None, 0, 0)

# print a path of nodes to a file
def outputToFile(file, path, nodeCount, node):
    f = open(file, 'w')
    f.write('State Solution Path:\n')
    # need to do this with the file open
    # not ideal but oh well
    pathToNode = []
    currentNode = node
    while True:
        try:
            if currentNode.parent == None:
                break
            pathToNode.append(currentNode.action)
	    f.write(str(node.leftSide)[1:-1].replace(" ", ""))
	    f.write('\n')
    	    f.write(str(node.rightSide)[1:-1].replace(" ", ""))
	    f.write('\n\n')
        except:
            break
        currentNode = currentNode.parent

    f.write('Action Solution Path: ')
    f.write(str(path))
    f.write('\n')
    f.write('\n')
    f.write('Number of expanded nodes: %d\n' % nodeCount)
    f.write('Number of nodes in the solution path: %d\n' % len(path))

    f.close()

# print state from a node
def printState(node):
    print str(node.leftSide)[1:-1].replace(" ", "")
    print str(node.rightSide)[1:-1].replace(" ", "")

# main function
def main():
    global goalState

    # get the initial and goal states
    initialState = readStateFromFileToNode(initialStateFile)
    goalState    = readStateFromFileToNode(goalStateFile)
    #printState(initialState)
    #printState(goalState)

    # use a priority queue for astar
    # and a deque for dfs, iddfs, and bfs
    # for the deque, bfs is FIFO, dfs and iddfs is LIFO
    if (mode == "bfs") or (mode == "dfs") or (mode == "iddfs"):
        fringe = collections.deque()
    elif (mode == "astar"):
        fringe = PriorityQueue()
    else:
        sys.exit('Not a valid mode')

    endNode = graphSearch(initialState, goalState, fringe)

    outputToFile(outputFile, findNodePath(endNode), nodeCount, endNode)
    print'\n'
    print'State Solution Path: '
    printStatePath(endNode)
    print'Action Solution Path: '
    print findNodePath(endNode)
    print '\n'
    print 'Number of expanded nodes: %d\n' % nodeCount
    print 'Number of nodes in the solution path: %d\n' % len(findNodePath(endNode))

# set command line args to initialStateFile, goalStateFile, mode, and outputFile
if __name__ == "__main__":
    if len(sys.argv) < 5:
        sys.exit('Please provide: < initial state file > < goal state file > < mode > < output file >')
    initialStateFile = sys.argv[1]
    goalStateFile    = sys.argv[2]
    mode             = sys.argv[3]
    outputFile       = sys.argv[4]
    main()
