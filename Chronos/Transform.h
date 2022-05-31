#pragma once

class Transform final
{
public:
	Transform(glm::vec3 pos) : m_Position{ pos } {}
	~Transform() = default;
	Transform(const Transform& other) = delete;
	Transform(Transform&& other) noexcept = delete;
	Transform& operator=(const Transform& other) = delete;
	Transform& operator=(Transform&& other) noexcept = delete;

	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(float x, float y, float z);
private:
	glm::vec3 m_Position;
};