#include "A_Enemy.h"

A_Enemy::A_Enemy(std::string p_path, 
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit,
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit) :
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_Alive = true;
}

//��������
A_Enemy::~A_Enemy()
{

}


bool A_Enemy::Segmentation(cv::Mat& segBackGround)
{
	bool re(false);

	cv::Vec3b Black{ 0, 0, 0 };

	//���Ƶ���
	for (int i(0); i < this->GetImg().size().height; ++i)
	{
		for (int j(0); j < this->GetImg().size().width; ++j)
		{
			Black == this->GetImg().at<cv::Vec3b>(i, j) ?
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) :	//do nothing
				segBackGround.at<cv::Vec3b>(i + this->GetPos().first, j + this->GetPos().second) = this->GetImg().at<cv::Vec3b>(i, j);
			//��(first, second)Ϊԭ�㽫this������seg
		}
	}

	//���Ƶ����ӵ�

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

//�����ƶ�
void A_Enemy::EnemyAutoMovie()
{
	int para_height = 10;
	int para_width = 0;
	//�����ƶ�

	/*--- �ƶ�ʱ���� ---*/
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10);
	int num = dis(gen);

	// 1/10�ļ��ʿ��� ��һ�����1��
	if (num == 1 && m_BulletObjList.size() < 2)
	{
		this->EnemyFire();
	}

	//�ƶ�
	this->MovePos(para_height, para_width);
}

//�������ٺ�����������ײ��Ϸ�߽�ʱ������
bool A_Enemy::DestoryObj()
{
	bool re(false);

	if (this->GetPos().first >= this->GetHeightUpperLimit())		//�����½�
	{
		this->~A_Enemy();
		re = true;
	}

	return re;
}

//���˿���
void A_Enemy::EnemyFire()
{
	//��FIghterǰ�������ڵ�	
	int BulletParaX = this->GetPos().second + this->GetImg().size().width / 2;				//width����
	int BulletParaY = this->GetPos().first + this->GetImg().size().height;					//height - BulletScale.height(160)

	A_EnemyBullets newBullet(".\\Source\\Re_EnemyBullets\\EnemyHit.png",
		BulletParaY, BulletParaX);

	if (!(newBullet.GetPos().first > newBullet.GetHeightUpperLimit()))
	{
		//�������Ͻ���Ϸ�
		m_BulletObjList.push_back(newBullet);
	}
}

//�����ӵ��ƶ�
bool A_Enemy::EnemyBulletMove()
{
	if (!this->m_BulletObjList.empty())
	{
		//�ӵ��ƶ�
		for (auto it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
		{
			it->MovePos((it->GetBulletMoveSpeed()), 0);
		}
	}

	//�ӵ�ɾ��
	for (std::vector<A_EnemyBullets>::iterator it = m_BulletObjList.begin(); it != m_BulletObjList.end(); ++it)
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

//��ȡ�ӵ���Ϣ
std::vector<A_EnemyBullets> A_Enemy::GetBulletObj()
{
	return m_BulletObjList;
}

//�����ӵ���Ϣ
void A_Enemy::SetBulletObj(std::vector<A_EnemyBullets> para)
{
	m_BulletObjList = para;
}



//��⣺��� �� �����ӵ�
bool A_Enemy::CollionEnemyBulletWithPlayer(A_PlayerFighter Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}
