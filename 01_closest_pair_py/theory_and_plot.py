def paint(filename, title):
	import csv
	import matplotlib.pyplot as plt

	# storage of dataname: generate and process the arrary dynamically
	data_names = []

	# storage of color: unite the plot and scatter: Maybe I need more 
	color = ['#009999', '#FFAA00', '#1240AB', '#FF7400']
	color_flag = 0;	

	with open(filename, 'r') as f:
		reader = csv.reader(f)

		# get the header_row: use for legend, xlabel and ylabel
		header_row = next(reader)

		# get the data rows
		for index, values in enumerate(reader):
			# if there is no this group of datas before, make one
			if values[0] not in data_names:
				data_names.append(values[0])
				exec('{}_x_values = [0,]'.format(values[0]))
				exec('{}_y_values = [0,]'.format(values[0]))
				exec('{}_x_values.append({})'.format(values[0], values[1]))
				exec('{}_y_values.append({})'.format(values[0], values[2]))
			# else put the data in the existing one
			else:
				exec('{}_x_values.append({})'.format(values[0], values[1]))
				exec('{}_y_values.append({})'.format(values[0], values[2]))	

	# generate the plot and scatter dynamically
	for data_name in data_names:
		if data_name.find('THE_') == -1:
			# generate the expriment data
			exec('plt.plot({}_x_values, {}_y_values, label = "{}", \
				linewidth = 1, color = "{}", alpha = 0.9, \
				marker = "o", markeredgecolor = "{}", markersize = 8, linestyle = "-")'. \
				format(data_name, data_name, data_name, color[color_flag], color[color_flag])) 

			# generate the theory data
			if data_name == 'VIO':
				exec('plt.plot(THE_{}_x_values, THE_{}_y_values, label = "THE_{}", \
					linewidth = 1, color = "{}", alpha = 0.9, \
					marker = "s", markeredgecolor = "{}", markersize = 8, linestyle = "--")'. \
					format(data_name, data_name, data_name, color[color_flag], color[color_flag])) 	

				exec('plt.fill_between({}_x_values, {}_y_values, THE_{}_y_values, facecolor = "{}", alpha = 0.1)'.\
					format(data_name, data_name, data_name, color[color_flag]))
			elif data_name == 'DIV':
				exec('plt.plot(THE_BES_{}_x_values, THE_BES_{}_y_values, label = "THE_BES_{}", \
					linewidth = 1, color = "{}", alpha = 0.9, \
					marker = "s", markeredgecolor = "{}", markersize = 8, linestyle = "--")'. \
					format(data_name, data_name, data_name, color[color_flag], color[color_flag])) 	
				exec('plt.plot(THE_WOR_{}_x_values, THE_WOR_{}_y_values, label = "THE_WOR_{}", \
					linewidth = 1, color = "{}", alpha = 0.9, \
					marker = "^", markeredgecolor = "{}", markersize = 8, linestyle = "--")'. \
					format(data_name, data_name, data_name, color[color_flag], color[color_flag])) 

				exec('plt.fill_between({}_x_values, THE_BES_{}_y_values, THE_WOR_{}_y_values, facecolor = "{}", alpha = 0.1)'.\
					format(data_name, data_name, data_name, color[color_flag]))

			# mark which color we are using for this group of datas
			color_flag += 1
			# when the color is run out of, go back to the first one
			if color_flag > len(color) - 1:
				color_flag = 0

	# get the legend, xlabel, ylabel from head_row: But it is not elegant 
	for index, value in enumerate(header_row):
		if index == 0:
			p_legend = value.upper();
		if index == 1:
			p_xlabel = value.upper();
		if index == 2:
			p_ylabel = value.upper();

	# draw the title etc.
	plt.title(title.title(), fontsize = 24, fontweight = 'bold',)
	plt.xlabel(p_xlabel, fontsize = 12, style = 'normal')
	plt.ylabel(p_ylabel, fontsize = 12, style = 'normal')
	plt.legend(loc = 'upper left', fontsize = 10, title = p_legend, ncol = 1)
	plt.xlim(0)
	plt.ylim(0)
	plt.xlim(0)
	plt.ylim(0)

	# make a grid and show the data more clearly
	plt.grid(axis="x")
	plt.grid(axis="y")

	# things done
	exec("plt.savefig('{}.png')".format(filename))
	plt.show()

def getTheory(filename):
	import csv

	sort_name_01 = ['DIV']
	sort_name_02 = ['VIO']

	the_data = []
	base_time = 0

	base_N = 1000

	with open(filename, 'r') as f:
		reader = csv.reader(f)
		for index, values in enumerate(reader):
			the_data.append([values[0], values[1], values[2],])
			if values[0] in sort_name_01:
				if values[1] == str(base_N):
					base_time = float(values[2])
					the_data.append(['THE_WOR_'+values[0], values[1], values[2],])
					the_data.append(['THE_BES_'+values[0], values[1], values[2],])
				else:
					the_data.append(['THE_WOR_'+values[0], values[1], genTime(base_time, int(values[1]), base_N, 1),])
					the_data.append(['THE_BES_'+values[0], values[1], genTime(base_time, int(values[1]), base_N, 1) / 2,])
			if values[0] in sort_name_02:
				if values[1] == str(base_N):
					base_time = float(values[2])
					the_data.append(['THE_'+values[0], values[1], values[2],])
				else:
					the_data.append(['THE_'+values[0], values[1], genTime(base_time, int(values[1]),base_N, 2),])
		
	# print(the_data) 

	writer_f = open(filename,'w')
	writer = csv.writer(writer_f)

	for rows in the_data:
		writer.writerow(rows)

	writer_f.close();

# base_N need to be initiate
def genTime(base_time, N, base_N, gen_type):
	import math
	import numpy as np

	if gen_type == 1:
		per_time = base_time / (base_N * np.log2(base_N))
		out_time = per_time * N * np.log2(N)
		return round(out_time, 4)
	elif gen_type == 2:		
		per_time = base_time / pow(base_N, 2)
		out_time = per_time * pow(N, 2)
		return round(out_time,4)
		
# getTheory('expri_data.csv')

# paint('expri_data.csv', 'The Closest Pair Problem')