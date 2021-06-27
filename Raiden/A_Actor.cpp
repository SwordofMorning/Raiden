#include "A_Actor.h"

extern const std::pair<int, int> BackGroundScale;
extern const std::pair<int, int> PlayerFighterScale;

//构造函数
A_Actor::A_Actor(std::string p_path, 
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit,
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit)
{
	/*--- 角色图像 ---*/
	m_Img = cv::imread(p_path, 1);											//角色图像
	m_ImgClone = m_Img.clone();												//角色图像的备份(const)

	/*--- 矩形边框 ---*/
	m_Pos.first = p_height;													//角色位置(左上)：first == height, second = Width
	m_Pos.second = p_width;
	m_PosLeftDown.first = m_Pos.first + m_Img.size().height;				//碰撞矩形左下角：height = 左上h + size.height
	m_PosLeftDown.second = m_Pos.second;									//                width = 左上w
	m_PosRightUp.first = m_Pos.first;										//碰撞矩形右上角：height = 左上h
	m_PosRightUp.second = m_Pos.second + m_Img.size().width;				//                width = 左上w + size.width

	/*--- 角色移动边界 ---*/
	m_HeightLowerLimit = p_HeightLowerLimit;
	m_HeightUpperLimit = p_HeightUpperLimit;
	m_WidthLowerLimit = p_WidthLowerLimit;
	m_WidthUpperLimit = p_WidthUpperLimit;

	/*--- 碰撞检测缓冲区 ---*/
	m_CollionBuffer = cv::Mat::zeros(cv::Size(BackGroundScale.second, BackGroundScale.first), CV_8UC3);
}

//析构函数
A_Actor::~A_Actor()
{
	m_Img.release();
	m_ImgClone.release();
	m_CollionBuffer.release();
	//释放
}

//自我销毁函数（对象碰撞游戏边界时发生）
bool A_Actor::DestoryObj()
{
	bool re(false);
	//左右判断
	if (this->m_Pos.second <= m_WidthLowerLimit)			//到达左界
	{
		this->~A_Actor();
		re = true;
	}
	else if (this->m_Pos.second >= m_WidthUpperLimit)		//到达右界
	{
		this->~A_Actor();
		re = true;
	}

	//上下判断
	if (this->m_Pos.first <= m_HeightLowerLimit)			//到达上界
	{
		this->~A_Actor();
		re = true;
	}
	else if (this->m_Pos.first >= m_HeightUpperLimit)		//到达下界
	{
		this->~A_Actor();
		re = true;
	}

	return re;
}

//将当前对象拷贝到segBackGround
bool A_Actor::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b White{ 255, 255, 255 };

	for (int i(0); i < this->m_Img.size().height; ++i)
	{
		for (int j(0); j < this->m_Img.size().width; ++j)
		{
			White == this->m_Img.at<cv::Vec3b>(i, j) ?
				segBackGround.at<cv::Vec3b>(i + this->m_Pos.first, j + this->m_Pos.second) :	//do nothing
				segBackGround.at<cv::Vec3b>(i + this->m_Pos.first, j + this->m_Pos.second) = this->m_Img.at<cv::Vec3b>(i, j);
			//以(first, second)为原点将this拷贝到seg
		}
	}
	re = true;

	return re;
}

//移动当前角色
bool A_Actor::MovePos(int p_height, int p_width)
{
	bool re(false);

	//左右判断
	if (this->m_Pos.second <= m_WidthLowerLimit)			//到达左界
	{
		//不能再向左：p_width >=0
		p_width < 0 ? p_width = 0 : p_width;
	}
	else if (this->m_Pos.second >= m_WidthUpperLimit)		//到达右界
	{
		//不能再向右：p_width <=0
		p_width > 0 ? p_width = 0 : p_width;
	}

	//上下判断
	if (this->m_Pos.first <= m_HeightLowerLimit)			//到达上界
	{
		//不能再向上：p_height >=0
		p_width < 0 ? p_width = 0 : p_width;
	}
	else if (this->m_Pos.first >= m_HeightUpperLimit)		//到达下界
	{
		//不能再向下：p_height <=0
		p_width > 0 ? p_width = 0 : p_width;
	}

	re = true;

	m_Pos.first += p_height;
	m_Pos.second += p_width;
	return re;
}

//设置当前角色位置
bool A_Actor::SetPos(const int& p_height, const int& p_width)
{
	m_Pos.first = p_height;
	m_Pos.second = p_width;
	return false;
}

//设置图片
void A_Actor::SetImg(cv::Mat Temp)
{
	Temp.copyTo(m_Img);
}

/*
	=== 碰撞检测算法 ===
（1）选择需要检测的两个精灵。
（2）先检测两个精灵是否发生包围盒碰撞，如果没有则退出，否则获取两个矩形的相交区域，并继续。
（3）把一个精灵绘制到和游戏屏幕等大的空白的后台缓冲区中，获取缓冲区中在相交区域的像素数据。
（4）清除后台缓冲区。
（5）对另一个精灵进行步骤3的操作。
（6）得到两个精灵在同一个相交矩形的像素数据后，循环比较每一个像素点，如果两个精灵在同一位置的透明度不都是0，则表示两个精灵有相交，退出循环，返回真。
*/

//矩形碰撞检测算法
bool A_Actor::RectangleCollision(A_Actor Target)
{
	bool re(false);

	m_CollionBuffer = cv::Mat::zeros(cv::Size(BackGroundScale.second, BackGroundScale.first), CV_8UC3);
	//刷新缓冲区

	//最大左下y和x
	int MaxLeftDownHeight = std::max(this->m_PosLeftDown.first, Target.m_PosLeftDown.first);
	int MaxLeftDownWidth = std::max(this->m_PosLeftDown.second, Target.m_PosLeftDown.second);
	//最小右上y和x
	int MinRightUpHeight = std::min(this->m_PosRightUp.first, Target.m_PosRightUp.first);
	int MinRightUpWidth = std::min(this->m_PosRightUp.second, Target.m_PosRightUp.second);

	//检测矩阵
	if (!((MaxLeftDownWidth > MinRightUpWidth) || (MaxLeftDownHeight < MinRightUpHeight)))
	{
		re = this->PixelCollision(Target);
	}

	return re;
}

//像素碰撞检测算法
bool A_Actor::PixelCollision(A_Actor Target)
{
	bool re(false);

	//把Target拷贝到缓冲区
	Target.Segmentation(this->m_CollionBuffer);

	//检查缓冲区
	for (int i(0); i < this->m_Img.size().height; ++i)
	{
		for (int j(0); j < this->m_Img.size().width; ++j)
		{
			if (m_CollionBuffer.at<cv::Vec3b>(m_Pos.first + i, m_Pos.second + j) != cv::Vec3b(0, 0, 0))
			{
				re = true;
			}
		}
	}

	return re;
}

//爆炸特效
void A_Actor::ActorBoom1()
{
	m_Img = cv::imread(".\\Source\\Re_Effects\\Boom1.png", 1);
}

//爆炸特效
void A_Actor::ActorBoom2()
{
	m_Img = cv::imread(".\\Source\\Re_Effects\\Boom2.png", 1);
}

//爆炸特效
void A_Actor::ActorBoom3()
{
	m_Img = cv::imread(".\\Source\\Re_Effects\\Boom3.png", 1);
}

//图像复原
void A_Actor::ImgRecover()
{
	m_ImgClone.copyTo(m_Img);
}

//获取图形m_Img
cv::Mat A_Actor::GetImg()
{
	return this->m_Img;
}

//获取角色位置m_Pos
std::pair<int, int> A_Actor::GetPos()
{
	return this->m_Pos;
}

//获取角色移动边界
int A_Actor::GetHeightLowerLimit()
{
	return m_HeightLowerLimit;
}

//获取角色移动边界
int A_Actor::GetHeightUpperLimit()
{
	return m_HeightUpperLimit;
}

//获取角色移动边界
int A_Actor::GetWidthLowerLimit()
{
	return m_WidthLowerLimit;
}

//获取角色移动边界
int A_Actor::GetWidthUpperLimit()
{
	return m_WidthUpperLimit;
}
