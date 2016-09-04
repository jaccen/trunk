#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <Application.h>
#include "gl/Program.h"

class Sample final : public Application {
public:
	using Application::Application;
	Sample();
	~Sample();
public:
	void CreateVBO();

	void  SetVAO(bool usevao){ m_useVao = usevao; }
	bool  GetUseVAO(){ return m_useVao; }

	virtual bool initialize() override;
	virtual void finalize() override;
	virtual void update(float dt) override;
	virtual void render() override;

private:
	Program* _program{ nullptr };
	GLuint m_VBO = 0;
	GLuint m_IBO = 0;

	GLuint m_VAO = 0;
	bool   m_useVao = false;
};


#endif // SAMPLE_HPP