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

Function dacMin (PX, PY)
BEGIN
	

END