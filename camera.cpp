#include "camera.h"
#include "window.h"
#include <cmath>

void Camera::update()
{
	Window& window = Window::getInstance();

	if (window.isKeyPressed(KEY_C))
		perspective = !perspective;

	window.clearKeyStatus(KEY_C);


	D3DXVECTOR3 objectAngle = target->getAngle();
	cameraDirection = (cameraDirection + objectAngle) / 2;
	cameraPosition = target->getPosition();

	

	D3DXMATRIX rotateX, rotateY, rotateZ, rotate;
	D3DXMatrixRotationX(&rotateX, cameraDirection.x);
	D3DXMatrixRotationY(&rotateY, cameraDirection.y);
	D3DXMatrixRotationZ(&rotateZ, cameraDirection.z);
	rotate = rotateZ * rotateY * rotateX;

	D3DXVECTOR4 cameraTargetDir;
	D3DXVec3Transform(&cameraTargetDir, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &rotate);
	D3DXVECTOR3 cameraTargetPosition = cameraPosition + D3DXVECTOR3(cameraTargetDir);

	D3DXVECTOR4 cameraUp;
	D3DXVec3Transform(&cameraUp, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &rotate);

	if (false == perspective)
	{
		cameraPosition.x -= distance * std::cosf(cameraDirection.y);
		cameraPosition.y += distance / 2;
		cameraPosition.z += distance * std::sinf(cameraDirection.y);
	}
		


	D3DXMatrixLookAtLH(&viewMatrix, &cameraPosition, &cameraTargetPosition, &D3DXVECTOR3(0, 1, 0));
	device->SetTransform(D3DTS_VIEW, &viewMatrix);
}

