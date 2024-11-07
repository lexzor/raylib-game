#pragma once
#include "raylib.h"

#define CAMERA_MOVE_SPEED                               0.4f       // Units per second
#define CAMERA_ROTATION_SPEED                           0.03f
#define CAMERA_PAN_SPEED                                0.2f

// Camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY                   0.003f

// Camera orbital speed in CAMERA_ORBITAL mode
#define CAMERA_ORBITAL_SPEED                            0.5f 

class CameraController
{
public:
	CameraController();
	~CameraController();

	void BeginCameraDraw() const;
	void EndCameraDraw();
	void OnFrame();

private:
	Camera3D m_Camera;
	Vector2 m_PreviousMousePosition = { 0.0f };
};