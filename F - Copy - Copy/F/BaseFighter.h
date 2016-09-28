#ifndef __BASE_FIGHTER__
#define __BASE_FIGHTER__

#include <string>

class C_BaseFighter
{
public:

	C_BaseFighter();
	~C_BaseFighter();

	bool isKOd();
	void knockDown();
	void gainHp(int ammount);
	virtual void rest();
	int getHp();
	virtual void takeDamage(int ammount, bool gainMeter = true);
	std::string getName();
	virtual bool canUseHyperSkill();
	bool getKnockedDown();
	virtual void useHyper();
	void takeFocusDamage(int ammount);
	virtual void gainFocus(int ammount);
	virtual std::string status();
	void addToName(std::string add);

protected:

	int m_hp;
	int m_previousHP;
	int m_maxHp;
	std::string m_name;
	int m_focus;
	int m_maxFocus;
	int m_previousFocus;
	bool m_knockedDown;

};

#endif // !__BASE_FIGHTER__


