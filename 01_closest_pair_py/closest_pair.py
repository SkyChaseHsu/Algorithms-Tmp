import random
import math
import time
import csv

class Point(object):
	"""docstring for ClassName"""
	def __init__(self, x, y):
		self.x = x
		self.y = y

class Points(object):
	def __init__(self, N):
		self.N = N
		self.pts = []
		self.__gen()

	def __gen(self):
		for i in range(self.N):
			self.pts.append(Point(random.randrange(0, 10000), random.randrange(0, 10000)))
	
	def display(self):
		for i in range(self.N):
			print (self.pts[i].x, self.pts[i].y),

	def get_dis(self, a, b):
		return math.sqrt(math.pow(self.pts[a].x - self.pts[b].x, 2) + \
						 math.pow(self.pts[a].y - self.pts[b].y, 2))

	def append(self, x_value, y_value):
		self.pts.append(Point(x_value, y_value))
		self.N += 1

	def sort(self, variable):
		if variable == 'x':
			sorted(self.pts, key = lambda point: point.x)
		elif variable == 'y':
			sorted(self.pts, key = lambda point: point.y)

	def vio_min_dis(self):
		if self.N < 2:
			return float('inf')
		elif self.N == 2:
			return self.get_dis(0, 1)
		
		min_dis = float('inf')
		for i in range(0, self.N, 1):
			for j in range(i+1, self.N, 1):
				cur_dis = self.get_dis(i, j)
				if cur_dis < min_dis:
					min_dis = cur_dis
		return min_dis
		
	def dac_min_dis(self):
		if 	self.N < 2:
			return float('inf')
		elif self.N == 2:
			return self.get_dis(0, 1)

		self.sort('x');

		mid = self.pts[self.N / 2].x

		left_points = Points(0)
		right_points = Points(0)

		for i in range(0, self.N / 2, 1):
			left_points.append(self.pts[i].x, self.pts[i].y)
		for i in range(self.N / 2, self.N, 1):
			right_points.append(self.pts[i].x, self.pts[i].y)

		left_dis  = left_points.dac_min_dis()
		right_dis = right_points.dac_min_dis()

		min_dis = min(left_dis, right_dis)

		mid_points = Points(0)
		for i in range(0, self.N, 1):
			if(abs(self.pts[i].x - mid) <= min_dis):
				mid_points.append(self.pts[i].x, self.pts[i].y)

		mid_points.sort('y')

		for i in range(0, mid_points.N, 1):
			if mid_points.pts[i].x - mid >= 0:
				continue;
			# mark 6 points on the right of the midline
			cnt_right = 0 
			for j in range(i + 1, i + 6 + cnt_right + 1, 1):
				if j < mid_points.N:
					if mid_points.pts[j].x - mid < 0:
						cnt_right += 1
						continue
					if mid_points.get_dis(i, j) < min_dis:
						min_dis = mid_points.get_dis(i, j)

		return min_dis


csv_file = open('expri_data.csv','w')
writer = csv.writer(csv_file)
writer.writerow(['Type', 'N', 'Time'])

N_value = 100

for N in range(N_value, N_value * 11, N_value):
	time_cost = 0
	for i in range(20):
		points = Points(N)
		time_begin = time.time()
		points.dac_min_dis()
		time_end = time.time()
		time_cost += time_end - time_begin
	ave_time = time_cost * 1000 / 20
	print ('[DIV] N = '+ str(N) +\
			' Time = ' + str(ave_time) + ' \tms')
	writer.writerow(["DIV", str(N), str(ave_time)])

for N in range(N_value, N_value * 11, N_value):
	time_cost = 0
	for i in range(20):
		points = Points(N)
		time_begin = time.time()
		points.vio_min_dis()
		time_end = time.time()
		time_cost += time_end - time_begin
	ave_time = time_cost * 1000 / 20
	print ('[VIO] N = '+ str(N) +\
			' Time = ' + str(ave_time) + ' \tms')
	writer.writerow(["VIO", str(N), str(ave_time)])

csv_file.close()
