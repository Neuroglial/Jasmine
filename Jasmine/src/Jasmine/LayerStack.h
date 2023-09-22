#pragma once

#include "Jasmine/Core.h"
#include "Layer.h"

#include <vector>

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

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*> m_Layers;
	private:
		std::vector<Layer*>::iterator m_LayerInsert;
	};

}
