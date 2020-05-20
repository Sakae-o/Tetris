const int MAXY = 24;
const int MAXX = 15;

class Map {
public:
	Map(int xx, int yy);

	void DrawMap();		//显示游戏区域

	bool JudgeClear();	//判断是否可消行
	void Clear_Line();	//执行消行
	void Add_line();	//同时对方加一行


private:
	int map[MAXY][MAXX];	//地图数据
	int x, y;		//左上角的坐标
};
