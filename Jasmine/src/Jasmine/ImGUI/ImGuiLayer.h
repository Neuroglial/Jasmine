#pragma once

#include "Jasmine/Core/Layer.h"

#include "Jasmine/Events/KeyEvent.h"
#include "Jasmine/Events/MouseEvent.h"
#include "Jasmine/Events/ApplicationEvent.h"

namespace Jasmine {

	class JASMINE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void BlockEvents(bool block) { m_BlockEvents = block; }
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};

}

