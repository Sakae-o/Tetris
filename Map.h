class Map {
public:
	void InitialMap();	//初始化游戏地图
	void DrawMap();		//显示游戏区域

	bool JudgeClear();	//判断是否可消行
	void Clear_Line();	//执行消行
	void Add_line();	//同时对方加一行

	friend void fuse(Block now, Map A);

private:
	int map[MAXY][MAXX];	//地图数据
};
