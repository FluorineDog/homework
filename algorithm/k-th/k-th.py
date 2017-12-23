#!/usr/bin/python3
import random
SEG_LENGTH = 5
def get_mid_small(group):
	# group size is no more than 5
	# O(1)
	group.sort()
	return group[len(group) // 2]

def findK(raw_data, k):
	length = len(raw_data)
	if length <= SEG_LENGTH:
		raw_data.sort()
		return raw_data[k]
	# segment raw_data to equalsized groups
	groups = [raw_data[i:i+SEG_LENGTH] for i in range(0, length, SEG_LENGTH)]
	# sort each small group, cost O(n)
	mids = [get_mid_small(group) for group in groups]	
	# recursive work, T(n/5)
	mid = findK(mids, len(mids)//2)	
	# O(n) segmentation
	less_data = [x for x in raw_data if x < mid]
	greater_data = [x for x in raw_data if x > mid]
	# if Kth in left range, T(n/2 + n/5)

	if k < len(less_data):
		return findK(less_data, k)
	length_less_equal = len(raw_data) - len(greater_data)
	# if Kth in right range
	if k >= length_less_equal:
		return findK(greater_data, k - length_less_equal)
	return mid

def main():
	# print(input())
	count, root_k = input().split(' ')
	count = int(count)
	root_k = int(root_k) - 1
	raw_data = [int(string) for string in input().split(' ')]
	print(raw_data)

if __name__ == "__main__":
	# main()
	random.seed(3)
	raw_data = [x for x in range(0, 10000000)]
	random.shuffle(raw_data)
	data = findK(raw_data, 1984)
	print(data)
