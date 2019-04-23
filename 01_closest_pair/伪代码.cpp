Function main (points)
BEGIN
	length <- points.length // 获取点集的规模
	points_y <- points      // 复制 points 

	sort(points, x)			// 以 x 值进行排序
	sort(pionts_y, y)		// 以 y 值进行排序
	dacDis(points, points_y, length)	// 分治法求最近点距
END

Function dacDis (poits, points_y, length)
BEGIN
	if length < 2 // 点数小于2，点距为无限
	then
		return infinite 
	else if length = 2 // 点数为2，返回它们的点距
	then
		return distance(points[0], points[1])
	else
	then 
		mid <- points.mid // 获取点集的中线

		// 按照中线对点集进行划分，划成左右两边
		points_left 	<- points(<=mid)
		points_right 	<- points(>mid)

		points_y_left 	<- points(<=mid)
		points_y_right 	<- points(>mid)

		// 分别求取左右点集的最小点距，两者中的较小值为整个点集的最小点距
		dis_left 	<- dacDis(points_left, points_y_left, n/2)
		dis_right 	<- dacDis(points_right, points_y_right, n - n/2)
		dis 		<- min(dis_left, dis_right)

		// 以y排序的点集，将mid - dis 到 mid + dis 中的点组成新的点集 points_mid
		// 计算左右点集之前的点距是否小于 dis，如果是，它就是 dis
		points_mid <- points_y(abs(x-mid<=d))
		for mid_left in points_mid(x<=mid)
			// 对于在mid线左边的每个点，计算在右边的上面3点和下面3点的点距，与 dis 进比较
			for mid_right <- mid_left-3 to mid_left +3
				cur_dis <- distangce(mid_left, mid_right)
				if cur_dis < dis
				then
					dis <- cur_dis

		// 返回最小点距
		return dis
END