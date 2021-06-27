#include "A_Boss.h"

//���캯��
A_Boss::A_Boss(std::string p_path,
	int p_health, int p_MoveSpeed,
	const int& p_height, const int& p_width, 
	const int& p_HeightLowerLimit, const int& p_HeightUpperLimit,
	const int& p_WidthLowerLimit, const int& p_WidthUpperLimit) :
	A_Actor(p_path, p_height, p_width, p_HeightLowerLimit, p_HeightUpperLimit, p_WidthLowerLimit, p_WidthUpperLimit)
{
	m_health = p_health;
	m_MoveSpeed = p_MoveSpeed;

	cv::Mat TempImg = this->GetImg().clone();

	for (cv::MatIterator_<cv::Vec3b> it = TempImg.begin<cv::Vec3b>(); it != TempImg.end<cv::Vec3b>(); ++it)
	{
		(*it)[0] = (*it)[0] * 0;
		(*it)[1] = (*it)[1] * 0;
		(*it)[2] = (*it)[2] * 0.8;
	}

	TempImg.copyTo(m_HitImg);

	m_MoveDir = true;
}

//��������
A_Boss::~A_Boss()
{

}

//Boss�ƶ�
void A_Boss::AutoMove()
{
	int BossPosX = this->GetPos().second;
	int BossPosY = this->GetPos().first;

	//�������������
	if (BossPosX <= this->GetWidthLowerLimit())
	{
		m_MoveDir = false;
	}
	//�����ҽ�������
	else if (BossPosX >= this->GetWidthUpperLimit())
	{
		m_MoveDir = true;
	}

	//Boss����
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 8);
	int num = dis(gen);

	if (num == 1 && this->m_BulletObjList.size() < 5)
	{
		this->BossAutoFire();
	}

	//Boss�ƶ�
	if (m_MoveDir)
	{
		//this->MovePos(0, 0 - m_MoveSpeed);
		this->SetPos(this->GetPos().first, this->GetPos().second - 10);
	}
	else if (!m_MoveDir)
	{
		this->MovePos(0, m_MoveSpeed);
	}
}

//Boss����
void A_Boss::BossAutoFire()
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

//����ǰ���󿽱���segBackGround
bool A_Boss::Segmentation(cv::Mat& segBackGround)
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

//Boss�ӵ��ƶ�
bool A_Boss::BossBulletMove()
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

//BossѪ������
void A_Boss::BossHealthReduce()
{
	m_health--;
}

//Boss����ж�
bool A_Boss::IsBossAlive()
{
	bool re(true);
	this->m_health >= 0 ? 
		re = true : 
		re = false;
	return re;
}

//��������Ч
void A_Boss::Hitted()
{
	this->SetImg(m_HitImg);
}

//��ը��Ч
void A_Boss::ActorBoom1()
{
	this->SetImg(cv::imread(".\\Source\\Re_Effects\\BossBoom1.png", 1));
}

//��ը��Ч
void A_Boss::ActorBoom2()
{
	this->SetImg(cv::imread(".\\Source\\Re_Effects\\BossBoom2.png", 1));
}

//����Ѫ��
int A_Boss::GetHealth()
{
	return m_health;
}

//��⣺��� �� Boss�ӵ�
bool A_Boss::CollionPlayerWithBossBullet(A_PlayerFighter Target)
{
	bool re(false);
	for (auto i : this->m_BulletObjList)
	{
		re = i.RectangleCollision(Target);
	}
	return re;
}
