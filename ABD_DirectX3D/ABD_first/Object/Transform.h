#pragma once
class Transform
{
public:

	Transform();
	virtual ~Transform();

	void Update();
	void UpdateWorld();

	Matrix& GetWorld() {return  world; }

	void SetParent(Transform* parent) { this->parent = parent; }

	Vector3 Forward()	{ return forward; }
	Vector3 Backward()	{ return forward * -1; }

	Vector3 Right()		{ return right; }
	Vector3 Left()		{ return right * -1; }

	Vector3 Up()		{ return up; }
	Vector3 Down()		{ return up * -1; }

	void AddScale(Vector3 value) { scale += value; }
	void AddRotation(Vector3 value) { rotation += value; }
	void AddTranslation(Vector3 value) { translation += value; }

	void SetPosition(Vector3 value) { translation = value; }
	void SetAngle(Vector3 value) { rotation = value; }
	void SetScale(Vector3 value) { scale = value; }

	void Debug();

	void SetLabel(string label) { this->label = label; }

public:
	Vector3 scale          = {1.0f, 1.0f, 1.0f};
    Vector3 rotation       = {0.0f, 0.0f, 0.0f};
    Vector3 translation    = {0.0f, 0.0f, 0.0f};

protected:

    Matrix world;

	Vector3 pivot = {};

	Transform* parent = nullptr;

	Vector3 globalScale			;
	Vector3 globalRotation		;
	Vector3 globalPosition		;

	Vector3 right, up, forward	;
	string label = "";
};

