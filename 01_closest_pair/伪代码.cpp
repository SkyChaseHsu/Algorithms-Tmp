def Closest_pair(points)
BEGIN
    length=points.length // 获取数组长度
    qsort(points,points+length,x) // 以x为标准对点集合points进行快速排序
    ClosestPair(Point points[], int length, Point &a, Point &b) // 求最近点对及最近点对距离
END

def ClosestPair(Point points[], int length, Point &a, Point &b)
BEGIN
    if length< 2
    then 
        return infinite // 如果数组长度小于2 返回无穷大
    
    else if length = 2
    then 
        return distance(points[0],points[1] // 如果数组长度等于2 返回该两点的距离
 
    else // 数组长度大于3
    then
        mid = points.mid // 获取中线
        pts1 = points(<=mid) // 存储两个集合点
        pts2 = points(>mid)
        d1 = ClosestPair(pts1, length / 2, a1, b1);             //分治求解左半部分子集的最近点  
        d2 = ClosestPair(pts2, length - length / 2, a2, b2);    //分治求解右半部分子集的最近点 
        d = min(d1,d2)
        
        // merge 合并子集解
        pts3 = points(abs(x-mid<d)  // 存储在2d之前的点
        for(each points : pits3)
            找到points在对侧相邻的6个点 依次计算距离
            判断是否更新距离distance 和 点a,b         

END

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