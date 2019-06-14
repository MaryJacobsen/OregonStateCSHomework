import sys

class Vertex:
    def __init__(self, n):
        self.name = n
        self.neighbors = list()

        self.distance = 9999
        self.color = 'white'
        self.team = 'none'

    def add_neighbor(self, v):
        if v not in self.neighbors:
            self.neighbors.append(v)
            self.neighbors.sort()


class Graph:
    vertices = {}
    possible = True
    babyfaces = 'Babyfaces: '
    heels = 'Heels: '
    startVertex = None
    counter = 0

    def add_vertex(self, vertex):
        if isinstance(vertex, Vertex) and vertex.name not in self.vertices:
            self.vertices[vertex.name] = vertex
            if self.counter == 0:
                self.startVertex = vertex
                self.counter = self.counter + 1
            return True
        else:
            return False

    def add_edge(self, u, v):
        if u in self.vertices and v in self.vertices:
            for key, value in self.vertices.items():
                if key == u:
                    value.add_neighbor(v)
                if key == v:
                    value.add_neighbor(u)
            return True
        else:
            return False

    def print_graph(self):
        for key in sorted(list(self.vertices.keys())):
            print(key + str(self.vertices[key].neighbors) + "  " + str(self.vertices[key].distance))

    def print_Babyfaces(self):
        for vert in self.vertices:
            if self.vertices[vert].team == 'babyface':
                self.babyfaces = self.babyfaces + self.vertices[vert].name + ' '
        print(self.babyfaces)

    def print_Heels(self):
        for vert in self.vertices:
            if self.vertices[vert].team == 'heel':
                self.heels = self.heels + self.vertices[vert].name + ' '
        print(self.heels)

    def bfs(self, vert):
        q = list()
        vert.distance = 0
        vert.color = 'grey'
        vert.team = 'babyface'
        for v in vert.neighbors:
            self.vertices[v].distance = vert.distance + 1
            self.vertices[v].team = 'heel'
            q.append(v)

        while len(q) > 0:
            u = q.pop(0)
            node_u = self.vertices[u]
            node_u.color = 'grey'

            for v in node_u.neighbors:
                node_v = self.vertices[v]
                if node_v.color == 'white':
                    q.append(v)
                    if node_v.distance > node_u.distance + 1:
                        node_v.distance = node_u.distance + 1
                    if node_v.distance % 2 == 0:
                        node_v.team = 'babyface'
                    elif node_v.distance % 2 != 0:
                        node_v.team = 'heel'
                    if node_v.team == node_u.team:
                        self.possible = False

g = Graph()
rivalries = []

f = open(sys.argv[1], 'r')
lines = f.read().splitlines()

numWrestlers = map(int, lines[0])
numberWrestlers = ''.join(map(str, numWrestlers))
numberWrestlers = int(numberWrestlers)

for i in range(1, numberWrestlers + 1):
    g.add_vertex(Vertex(lines[i]))

numRivalries = map(int, lines[numberWrestlers + 1])
numberRivalries = ''.join(map(str, numRivalries))
numberRivalries = int(numberRivalries)

for x in range(numberWrestlers + 2, numberWrestlers + 1 + numberRivalries + 1):
     rivalries.append(lines[x])

for rival in rivalries:
    rivalOneTwo = rival.split()
    g.add_edge(rivalOneTwo[0], rivalOneTwo[1])

g.bfs(g.startVertex)

for m in g.vertices:
   if g.vertices[m].color == 'white':
      g.bfs(g.vertices[m])

#g.print_graph()
if g.possible:
    print("Yes")
    g.print_Babyfaces()
    g.print_Heels()
else:
    print("No")

f.close()
