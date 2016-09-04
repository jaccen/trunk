#ifndef SAMPLE_HPP
#define SAMPLE_HPP

#include <Application.h>


class Sample final : public Application {
public:
	using Application::Application;
	Sample();
public:
	virtual bool initialize() override;
	virtual void finalize() override;
	virtual void update(float dt) override;
	virtual void render() override;
};


#endif // SAMPLE_HPP