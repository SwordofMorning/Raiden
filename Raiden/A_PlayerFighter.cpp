#include "A_PlayerFighter.h"

extern const std::pair<int, int> PlayerFighterScale;
extern const std::vector<std::pair<int, int>> BulletScale;

/*=== ��Ա���� ===*/

//���캯��
A_PlayerFighter::A_PlayerFighter(std::string p_path, 
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit, 
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit) : 
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_BulletLevel = m_BulletLevelLowerLimit;
	m_Health = m_HealthAtBegin;

	//�ڵ�ͼƬ·��
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_0.png"));
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_1.png"));
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_2.png"));
	m_BulletImgPath.push_back(std::string(".\\Source\\Re_Bullets\\BulletLevel_3.png"));
}

//��������
A_PlayerFighter::~A_PlayerFighter()
{

}

//���ƹ��캯��
A_PlayerFighter::A_PlayerFighter(const A_PlayerFighter& Target) : A_Actor(Target)
{
	m_BulletLevel = m_BulletLevelLowerLimit;
	m_Health = m_HealthAtBegin;
}

//opera= ����
A_PlayerFighter A_PlayerFighter::operator=(const A_PlayerFighter& Target)
{
	A_PlayerFighter re(Target);
	return re;
}

//���������
void A_PlayerFighter::PlayerFighterFire_LeftClick()
{
	//��FIghterǰ�������ڵ�
	int BulletParaX = this->GetPos().second + PlayerFighterScale.second / 2;				//width����
	int BulletParaY = this->GetPos().first - BulletScale[m_BulletLevel].first;				//height - BulletScale.height(160)

	A_Bullet newBullet(m_BulletImgPath[m_BulletLevel], BulletParaY, BulletParaX);

	if (!(newBullet.GetPos().first < newBullet.GetHeightLowerLimit()))
	{
		//��С���Ͻ���Ϸ�
		m_BulletObjList.push_back(newBullet);
	}

	PlaySound(".\\Source\\Re_Sound\\PlayerFire.wav", NULL, SND_ASYNC);
}

//����ǰ���� �� �ӵ�������segBackGround
bool A_PlayerFighter::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b White{ 255, 255, 255 };
	cv::Vec3b Black{ 0, 0, 0 };

	//���Ʒɻ�
	for (int i(0); i < this->GetImg().size().height; ++i)
	{
		for (int j(0); j < this->GetImg().size().width; ++j)
		{
			//��(first, second)Ϊԭ�㽫this������seg
			if (White != this->GetImg().at<cv::Vec3b>(i, j) && Black != this->GetImg().at<cv::Vec3b>(i, j))
			{
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) = this->GetImg().at<cv::Vec3b>(i, j);
			}
		}
	}

	if (!this->m_BulletObjList.empty())
	{
		for (auto i : m_BulletObjList)
		{
			i.Segmentation(segBackGround);
		}
	}
	re = true;

	return re;
}

//�ɻ������ӵ��ƶ�
bool A_PlayerFighter::BulletMove()
{
	if (!this->m_BulletObjList.empty())
	{
		//�ӵ��ƶ�
		for (auto it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
		{
			it->MovePos(-(it->GetBulletMoveSpeed()), 0);
		}
	}

	//����׼��
	BulletOrderOP op;
	std::sort(this->m_BulletObjList.begin(), this->m_BulletObjList.end(), op);

	//�ӵ�ɾ��
	for (std::vector<A_Bullet>::iterator it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
	{
		if (it->DestoryObj())
		{
			m_BulletObjList.erase(std::remove(m_BulletObjList.begin(), m_BulletObjList.end(), *it), m_BulletObjList.end());
		}	
		break;
		/*--- ����break����Ϊһ��ֻɾһ�� ---*/
	}
	/*--- ��֪bug:�����ͷ��βɾ�� ---*/
	return true;
}

//�ж����Ѫ���Ƿ������Ϸ
bool A_PlayerFighter::IsAlive()
{
	bool re(true);
	m_Health > 0 ? re = true : re = false;
	return re;
}

//�ӵ��ȼ�
void A_PlayerFighter::SetBulletLevel(int p_level)
{
	m_BulletLevel = p_level;
}

//��⣺��� �� ����
bool A_PlayerFighter::CollionFighterWithEnemy(A_Enemy Target)
{
	bool re(false);
	re = this->RectangleCollision(Target);
	return re;
}

//��⣺���� �� ����ӵ�
bool A_PlayerFighter::CollionEnemyWithBullet(A_Enemy Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}

//��⣺Boss �� ����ӵ�
bool A_PlayerFighter::CollionBossWithBullet(A_Boss Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}
