#!/usr/bin/python3

def find(forest, a):
	parent = forest[a]
	if(a != parent):
		forest[a] = find(forest, parent)
	return forest[a]

def union(forest, a, b):
	ra = find(forest, a)
	rb = find(forest, b)
	forest[rb] = ra
	return ra != rb

def kruskal(raw_data, N):
	raw_data.sort(key = lambda t:t[2], reverse=False)
	forest = [x for x in range(0, N)]
	count = 0
	sum_weight = 0
	for u, v, w in raw_data:
		if union(forest, u, v):
			sum_weight += w
			count += 1
			if count == N - 1:
				break
	return sum_weight

def main():
	while True:	
		dddd = None
		while not dddd:
			dddd = input()
		vertex_count, edge_count = dddd.split(" ")
		vertex_count = int(vertex_count)
		edge_count = int(edge_count)
		#print(vertex_count, "&", edge_count, "***")
		raw_data = []
		for i in range(0, edge_count):
			u, v, w = input().split(" ")
			raw_data.append((int(u) -1 , int(v) -1, int(w)))
		print(kruskal(raw_data, vertex_count))
try:
	main()
except EOFError:
	print("done")
	pass
