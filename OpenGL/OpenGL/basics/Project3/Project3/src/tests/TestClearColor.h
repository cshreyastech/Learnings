#pragma once
#include "Test.h"
#include "include/Renderer.h"
#include "imgui/imgui.h"

namespace test {
	class TestClearColor : public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnIMGuiRender() override;

	private:
		float m_clearColor[4];
	};

}