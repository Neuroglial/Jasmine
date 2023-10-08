#include <Jasmine.h>
#include <Jasmine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Jasmine {

	class JasmineEditor : public Application
	{
	public:
		JasmineEditor()
			: Application("Jasmine Editor")
		{
			PushLayer(new EditorLayer());
		}

		~JasmineEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new JasmineEditor();
	}

}