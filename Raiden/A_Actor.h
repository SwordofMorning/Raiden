#pragma once

#include <opencv.hpp>

extern const std::pair<int, int> BackGroundScale;
extern const std::pair<int, int> PlayerFighterScale;

/*=== ��ɫ���� ===*/
class A_Actor
{
private:
	/*--- ��ɫͼ�� ---*/
	cv::Mat m_Img;							//��ɫͼ��
	cv::Mat m_ImgClone;						//��ɫͼ��ı���(const)

	/*--- ���α߿� ---*/
	std::pair<int, int> m_Pos;				//��ɫλ��(����)��first == height, second = Width
	std::pair<int, int> m_PosLeftDown;		//��ײ�������½�
	std::pair<int, int> m_PosRightUp;		//��ײ�������Ͻ�

	/*--- ��ɫ�ƶ��߽� ---*/
	int m_HeightLowerLimit;
	int m_HeightUpperLimit;
	int m_WidthLowerLimit;
	int m_WidthUpperLimit;

	/*--- ��ײ��⻺���� ---*/
	cv::Mat m_CollionBuffer;				//��ɫͼ��Ļ�����(������ײ���)

public:
	/*--- ��Ա���� ---*/
	A_Actor(std::string p_path = "\0", const int& p_height = 350, const int& p_width =350,
		const int& p_HeightLowerLimit = 0, 
		const int& p_HeightUpperLimit = BackGroundScale.first - 200,
		const int& p_WidthLowerLimit = 156, 
		const int& p_WidthUpperLimit = BackGroundScale.second - 156);								//���캯��

	~A_Actor();																						//��������

	virtual bool DestoryObj();																		//�������ٺ�����������ײ��Ϸ�߽�ʱ������

	virtual bool Segmentation(cv::Mat& segBackGround);												//����ǰ���󿽱���segBackGround

	bool MovePos(int p_height, int p_width);														//�ƶ���ǰ��ɫ

	virtual bool RectangleCollision(A_Actor Target);												//������ײ����㷨

	virtual bool PixelCollision(A_Actor Target);												   	//������ײ����㷨

	virtual void ActorBoom1();																		//��ը��Ч

	virtual void ActorBoom2();																		//��ը��Ч

	virtual	void ActorBoom3();																		//��ը��Ч

	void ImgRecover();																				//ͼ��ԭ

	/*--- Get��Ա���� ---*/
	cv::Mat GetImg();																				//��ȡͼ��m_Img

	std::pair<int, int> GetPos();																	//��ȡ��ɫλ��m_Pos

	int GetHeightLowerLimit();																		//��ȡ��ɫ�ƶ��߽�

	int GetHeightUpperLimit();																		//��ȡ��ɫ�ƶ��߽�

	int GetWidthLowerLimit();																		//��ȡ��ɫ�ƶ��߽�

	int GetWidthUpperLimit();																		//��ȡ��ɫ�ƶ��߽�

	/*--- Set��Ա���� ---*/
	bool SetPos(const int& p_height, const int& p_width);											//���õ�ǰ��ɫλ��

	void SetImg(cv::Mat Temp);																		//����ͼƬ
};