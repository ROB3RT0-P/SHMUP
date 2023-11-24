#pragma once

#include "../entity.h"

#include <iostream>

struct SDL_Texture;

class Player : public IEntity
{
public:
	static void registerWithEntityManager();
	
	Player(float x, float y);

	void init();
	void render();
	void update(float deltaTime);
	void move(float newX, float newY, float deltaTime);
	float lerp(float start, float end, float t);
	void checkBounds();

	void setPlayerX(float newPosX) { fPlayerX_ = newPosX; }
	void setPlayerY(float newPosY) { fPlayerY_ = newPosY; }

	float getPlayerX() { return fPlayerX_; }
	float getPlayerY() { return fPlayerY_; }

	Player() = default;
	~Player() {};

	int getPlayerHealth() { return iPlayerHealth_; }
	void damagePlayerHealth(int damage) { iPlayerHealth_ -= damage; }
	void setPlayerHealth(int healthAmount)
	{
		iPlayerHealth_ += healthAmount;
		if (iPlayerHealth_ > 100) { iPlayerHealth_ = 100; }
	}

	SDL_Texture& getTexture() { return *tTexture; }

	float getPlayerVelocityX(){ return fPlayerVelocityX_; }
	float getPlayerVelocityY() { return fPlayerVelocityY_; }
	float getPlayerAcceleration() { return fPlayerAcceleration_; }

	void setPlayerVelocityX( float fNewVelocityX ) { }
	void setPlayerVelocityY( float fNewVelocityY ) { }
	void setPlayerAcceleration( float fNewAcceleration) { }

private:
	float fPlayerY_;
	float fPlayerX_;
	float fPlayerAcceleration_;
	float fPlayerVelocityX_;
	float fPlayerVelocityY_;
	float fPlayerSpeed_;
	int iPlayerHealth_;
	float fBoundOffset_;

	friend IEntity* playerEntityCreateFunc(void* user);
	friend IEntity* playerEntityDestroyFunc(IEntity* entity, void* user);

	virtual void save() const;
	virtual void load();

	bool saveHighScore(int highScore) const;
	int loadHighScore();

	SDL_Texture* tTexture = NULL;
};