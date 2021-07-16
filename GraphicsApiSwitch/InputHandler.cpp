#include "InputHandler.h"

InputHandler* InputHandler::m_pInstance = nullptr;

InputHandler::InputHandler()
{
	m_pCommandQueue = new std::queue<eCommand>();
}

InputHandler::~InputHandler()
{
}

void InputHandler::ProcessInput()
{
	OnKeyboardInput();
}

void InputHandler::OnKeyboardInput()
{
	if (IsKeyDown(VK_LEFT))
		m_pCommandQueue->push(eCommand::ec_PrevRenderApi);

	if (IsKeyDown(VK_RIGHT))
		m_pCommandQueue->push(eCommand::ec_NextRenderApi);

	/*if (IsKeyDown(VK_UP))

	if (IsKeyDown(VK_DOWN))*/
}

bool InputHandler::IsKeyDown(
	int vkeyCode
)
{
	return (GetAsyncKeyState(vkeyCode) & 0x8000) != 0;
}

InputHandler* InputHandler::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new InputHandler();
	}

	return m_pInstance;
}

bool InputHandler::GetInputCommand(
	eCommand& command
)
{
	if (m_pCommandQueue->size())
	{
		command = m_pCommandQueue->front();
		m_pCommandQueue->pop();
		return true;
	}
	
	return false;
}