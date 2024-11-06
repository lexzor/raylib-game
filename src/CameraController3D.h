#include "raylib.h"
#include "raymath.h"

class CameraController3D {
public:
    Camera3D camera; 

    float moveSpeed = 5.0f;
    float turnSpeed = 0.1f;

    Vector2 previousMousePosition;
    
    CameraController3D(Vector3 position = { 0.0f, 1.0f, 5.0f }, Vector3 target = { 0.0f, 1.0f, 0.0f }) 
    {
        camera.position = position;
        camera.target = target;
        camera.up = { 0.0f, 1.0f, 0.0f };
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;

        previousMousePosition = GetMousePosition();
    }

    void OnUpdate()
    {
        Vector2 currentMousePosition = GetMousePosition();

        float deltaX = (currentMousePosition.x - previousMousePosition.x) * turnSpeed;
        float deltaY = (currentMousePosition.y - previousMousePosition.y) * turnSpeed;

        Vector3 forward = Vector3Subtract(camera.target, camera.position);
        Vector3 right = Vector3CrossProduct(forward, camera.up);

        Matrix rotationX = MatrixRotate(camera.up, -deltaX * DEG2RAD);
        Matrix rotationY = MatrixRotate(right, -deltaY * DEG2RAD);

        forward = Vector3Transform(forward, rotationX);
        forward = Vector3Transform(forward, rotationY);
        camera.target = Vector3Add(camera.position, forward);

        previousMousePosition = currentMousePosition;
        
        forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
        right = Vector3CrossProduct(forward, camera.up);

        if (IsKeyDown(KEY_W)) camera.position = Vector3Add(camera.position, Vector3Scale(forward, moveSpeed * GetFrameTime()));
        if (IsKeyDown(KEY_S)) camera.position = Vector3Subtract(camera.position, Vector3Scale(forward, moveSpeed * GetFrameTime()));
        if (IsKeyDown(KEY_A)) camera.position = Vector3Subtract(camera.position, Vector3Scale(right, moveSpeed * GetFrameTime()));
        if (IsKeyDown(KEY_D)) camera.position = Vector3Add(camera.position, Vector3Scale(right, moveSpeed * GetFrameTime()));

        camera.target = Vector3Add(camera.position, forward);
    }

    void BeginCamera() const
    {
        ::BeginMode3D(camera);
    }

    void EndCamera()
    {
        ::EndMode3D();
    }
};