#pragma once
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include <BCommand.h>

class CTankTron;

//----------------------------------MOVERIGHT----------------------------------
class MoveHorizontal : public BCommand
{
public:
	MoveHorizontal(bool moveRight);
	~MoveHorizontal() override;

	void Execute(GameObject* pActor) override;

private:
	int m_DirectionValue;
	CTankTron* m_CTron = nullptr;
};
//----------------------------------MOVEUP----------------------------------
class MoveVertical : public BCommand
{
public:
	MoveVertical(bool moveUp);
	~MoveVertical() override;

	void Execute(GameObject* pActor) override;

private:
	int m_DirectionValue;
	CTankTron* m_CTron = nullptr;
};
//----------------------------------SHOOT----------------------------------
class Shoot : public BCommand
{
public:
	Shoot();
	~Shoot() override;

	void Execute(GameObject* pActor) override;

private:
	CTankTron* m_CTron = nullptr;
};
//----------------------------------MOVEBARREL----------------------------------
class MoveBarrel : public BCommand
{
public:
	MoveBarrel(bool shouldTrackMouse = true);
	~MoveBarrel() override;

	void Execute(GameObject* pActor) override;

private:
	bool m_TracksMouse;
	CTankTron* m_CTron = nullptr;
	glm::vec2 m_PrevMousePos{};

	void TrackMouse(GameObject* pActor);
	void TrackJoyStick(GameObject* pActor);
};
//----------------------------------NEXTSCENE----------------------------------
class OpenScene : public BCommand
{
public:
	OpenScene(int sceneIdx);
	~OpenScene() override;

	void Execute(GameObject* pActor) override;

private:
	int m_SceneIndex{};
};
//----------------------------------RESETSCENE----------------------------------
class ResetScene : public BCommand
{
public:
	ResetScene();
	~ResetScene() override;

	void Execute(GameObject* pActor) override;
};
//----------------------------------DISABLEWALLSCOLLISION----------------------------------
class DisableWall : public BCommand
{
public:
	DisableWall();
	~DisableWall() override;

	void Execute(GameObject* pActor) override;
};