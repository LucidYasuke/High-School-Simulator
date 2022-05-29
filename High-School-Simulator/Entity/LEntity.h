#ifndef LENTITY_H
#define LENTITY_H


#include "../Physics.h"


namespace EntityComponent
{
	enum class Demographic { LOWER = 0, MIDDLE, UPPER };


	enum class MindState { HAPPY = 0, SAD, TIRED, DELERIOUS, BORED, INTOXICATED };


	struct Movement
	{
		bool isSprinting;
		sf::Vector2f velocity;
		sf::Vector2f direction;
	};


	struct Intoxication
	{
	private:
		double sobriety;
		double tolerance;

		sf::Time lastHigh;
		static const float lastHighMax;

		sf::Time cdHigh;
		static const float cdHighMax;
	public: 
		void getHigh();
		void update(const float& dt);

		const double& getSobriety() const;
		const double& getTolerance() const;

		template <typename T>
		std::string getSobrietyAsString();

		const float getLastHigh() const;
		const float& getLastHighMax() const;
	};


	class Psychology
	{
	private:
		double intelligence;
		double joy;
		double sadness;
		double fatigue;

		bool isSprinting;
		bool isAsleep;
		bool isStudying;

		std::vector<MindState> moods;

		sf::Time cdLastStudy;
		static const float cdLastStudyMax;

		static const float cdStatChangeMax;

		sf::Time cdIntelligenceDecrementStudy;
		sf::Time cdIntelligenceIncrementStudy;
		sf::Time cdIntelligenceDecrementSobriety;

		sf::Time cdJoyIncrementSobriety;
		sf::Time cdJoyDecrementSobriety;

		sf::Time cdSadnessIncrementSobriety;

		sf::Time cdFatigueDecrementSleep;
		sf::Time cdFatigueIncrementSobriety;
		sf::Time cdFatigueIncrementSprinting;
	public:
		Psychology();
		Psychology(Demographic demographic);
		virtual ~Psychology();

		void study();
		void sleep();

		void updateStudy(const float& dt, Intoxication& toxic);
		void updateIntelligence(const float& dt, Intoxication& toxic);
		void updateJoy(const float& dt, Intoxication& toxic);
		void updateSadness(const float& dt, Intoxication& toxic);
		void updateFatigue(const float& dt, Intoxication& toxic);


		void updateLimits();
		void update(const float& dt, Intoxication& toxic);

		const std::vector<MindState>& getMoods() const;

		const bool& getIsAsleep() const;
		const bool& getIsStudying() const;

		void setIsSprinting(bool condition);

		template <typename T>
		T getIntelligence();
		template <typename T>
		T getJoy();
		template <typename T>
		T getSadness();
		template <typename T>
		T getFatigue();

		template <typename T>
		std::string getIntelligenceAsString();
		template <typename T>
		std::string getJoyAsString();
		template <typename T>
		std::string getSadnessAsString();
		template <typename T>
		std::string getFatigueAsString();
	};


	class Wallet
	{
	private:
		double amount;
	public:
		Wallet();
		Wallet(Demographic demographic);
		virtual ~Wallet();

		void addMoney(double amount);
		void subMoney(double amount);

		template <typename T>
		T getMoney();

		template <typename T>
		std::string getMoneyAsString();
	};
}


class LEntity : sf::Sprite
{
protected:
	bool deleted;

	//===COMPONENTS===//
	EntityComponent::Movement* movementComponent;
	//---COMPONENTS---//
public:
	LEntity();
	LEntity(const sf::Texture& texture);
	LEntity(const sf::Texture& texture, const sf::IntRect& rectangle);
	virtual ~LEntity();

	void add(EntityComponent::Movement* movementComponent);

	EntityComponent::Movement*& getMovementComponent();

	const bool& getDeleted() const;
	void setDeleted(bool condition);

	//===Update===//
	void updateMovement(const float& dt);
	void update(const float& dt);
	//---Update---//
};


#endif
