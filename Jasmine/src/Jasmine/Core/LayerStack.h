#pragma once

#include "JM_PCH.h"

#include "Jasmine/Core/Core.h"
#include "Layer.h"

namespace Jasmine {

	class JASMINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		void ClearLayer();

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*> m_Layers;
	private:
		unsigned int m_LayerInsertIndex = 0;
	};

}
