class Block {
public:
	void InitialBlock();	//初始化方块
	void DrawBlock();		//打印方块
	void DrewNext();		//在游戏区域旁打印下一个方块

	bool JudgeLeft();		//分别判断是否可以左移，右移，下落
	bool JudgeRight();
	bool JudgeDown();

	bool JudgeTransform();	//判断是否可以变形

	void Move();		//执行移动，变形，消行
	void Transform();

	void Down();		//自动下落
	void accelerate();	//手动加速

	friend void fuse(Block now, Map A);

private:
	int shape[4][4];	//形状
	int x, y;	//位置
};
