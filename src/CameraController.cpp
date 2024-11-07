#include "CameraController.h"
#include "raymath.h"

CameraController::CameraController()
{
	m_Camera = { 0 };
    m_Camera.position = { 0.0f, 10.0f, 10.0f };  // Camera position
    m_Camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
    m_Camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    m_Camera.fovy = 45.0f;                                // Camera field-of-view Y
    m_Camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

}

CameraController::~CameraController()
{
}

void CameraController::BeginCameraDraw() const
{
    BeginMode3D(m_Camera);
}

void CameraController::EndCameraDraw()
{
    EndMode3D();
}

void CameraController::OnFrame()
{
    static const float moveSpeed = 2.5f;
    static const float turnSpeed = 0.1f;

    static Vector2 currentMousePosition = { 0.0f };

    if (IsCursorHidden())
    {
        currentMousePosition = GetMousePosition();
    }

    float deltaX = (currentMousePosition.x - m_PreviousMousePosition.x) * turnSpeed;
    float deltaY = (currentMousePosition.y - m_PreviousMousePosition.y) * turnSpeed;

    Vector3 forward = Vector3Subtract(m_Camera.target, m_Camera.position);
    Vector3 right = Vector3CrossProduct(forward, m_Camera.up);

    Matrix rotationX = MatrixRotate(m_Camera.up, -deltaX * DEG2RAD);
    Matrix rotationY = MatrixRotate(right, -deltaY * DEG2RAD);

    forward = Vector3Transform(forward, rotationX);
    forward = Vector3Transform(forward, rotationY);
    m_Camera.target = Vector3Add(m_Camera.position, forward);

    if (IsCursorHidden())
    {
        m_PreviousMousePosition = currentMousePosition;
    }

    forward = Vector3Normalize(Vector3Subtract(m_Camera.target, m_Camera.position));
    right = Vector3CrossProduct(forward, m_Camera.up);

    if (IsKeyDown(KEY_W)) m_Camera.position = Vector3Add(m_Camera.position, Vector3Scale(forward, moveSpeed * GetFrameTime()));
    if (IsKeyDown(KEY_S)) m_Camera.position = Vector3Subtract(m_Camera.position, Vector3Scale(forward, moveSpeed * GetFrameTime()));
    if (IsKeyDown(KEY_A)) m_Camera.position = Vector3Subtract(m_Camera.position, Vector3Scale(right, moveSpeed * GetFrameTime()));
    if (IsKeyDown(KEY_D)) m_Camera.position = Vector3Add(m_Camera.position, Vector3Scale(right, moveSpeed * GetFrameTime()));

    m_Camera.target = Vector3Add(m_Camera.position, forward);

    //UpdateCamera(&m_Camera, CAMERA_FREE);
}
