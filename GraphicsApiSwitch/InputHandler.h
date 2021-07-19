#pragma once

#include "CommonUtils.h"

enum eCommand
{
	ec_NextRenderApi = 0,
	ec_PrevRenderApi,
	ec_AddBox,
	ec_RemoveBox,
	
	ec_CommandNumber,
};

class InputHandler
{
public:
	static InputHandler* GetInstance();

	void ProcessInput();

	bool GetInputCommand(
		eCommand& command
	);

private:
	InputHandler();

	InputHandler(
		const InputHandler& rhs
	) = delete;

	InputHandler& operator=(
		const InputHandler& rhs
		) = delete;

	~InputHandler();

	void OnKeyboardInput();

	bool IsKeyDown(
		int vkeyCode
	);

	static InputHandler* m_pInstance;
	std::queue<eCommand>* m_pCommandQueue;
};

