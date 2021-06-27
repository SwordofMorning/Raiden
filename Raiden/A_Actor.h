#pragma once

#include <opencv.hpp>

extern const std::pair<int, int> BackGroundScale;
extern const std::pair<int, int> PlayerFighterScale;

/*=== 角色基类 ===*/
class A_Actor
{
private:
	/*--- 角色图像 ---*/
	cv::Mat m_Img;							//角色图像
	cv::Mat m_ImgClone;						//角色图像的备份(const)

	/*--- 矩形边框 ---*/
	std::pair<int, int> m_Pos;				//角色位置(左上)：first == height, second = Width
	std::pair<int, int> m_PosLeftDown;		//碰撞矩形左下角
	std::pair<int, int> m_PosRightUp;		//碰撞矩形右上角

	/*--- 角色移动边界 ---*/
	int m_HeightLowerLimit;
	int m_HeightUpperLimit;
	int m_WidthLowerLimit;
	int m_WidthUpperLimit;

	/*--- 碰撞检测缓冲区 ---*/
	cv::Mat m_CollionBuffer;				//角色图像的缓冲区(用于碰撞检测)

public:
	/*--- 成员函数 ---*/
	A_Actor(std::string p_path = "\0", const int& p_height = 350, const int& p_width =350,
		const int& p_HeightLowerLimit = 0, 
		const int& p_HeightUpperLimit = BackGroundScale.first - 200,
		const int& p_WidthLowerLimit = 156, 
		const int& p_WidthUpperLimit = BackGroundScale.second - 156);								//构造函数

	~A_Actor();																						//析构函数

	virtual bool DestoryObj();																		//自我销毁函数（对象碰撞游戏边界时发生）

	virtual bool Segmentation(cv::Mat& segBackGround);												//将当前对象拷贝到segBackGround

	bool MovePos(int p_height, int p_width);														//移动当前角色

	virtual bool RectangleCollision(A_Actor Target);												//矩形碰撞检测算法

	virtual bool PixelCollision(A_Actor Target);												   	//像素碰撞检测算法

	virtual void ActorBoom1();																		//爆炸特效

	virtual void ActorBoom2();																		//爆炸特效

	virtual	void ActorBoom3();																		//爆炸特效

	void ImgRecover();																				//图像复原

	/*--- Get成员函数 ---*/
	cv::Mat GetImg();																				//获取图形m_Img

	std::pair<int, int> GetPos();																	//获取角色位置m_Pos

	int GetHeightLowerLimit();																		//获取角色移动边界

	int GetHeightUpperLimit();																		//获取角色移动边界

	int GetWidthLowerLimit();																		//获取角色移动边界

	int GetWidthUpperLimit();																		//获取角色移动边界

	/*--- Set成员函数 ---*/
	bool SetPos(const int& p_height, const int& p_width);											//设置当前角色位置

	void SetImg(cv::Mat Temp);																		//设置图片
};