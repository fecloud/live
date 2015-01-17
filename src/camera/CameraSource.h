#ifndef CAMERASOURCE_H
#define CAMERASOURCE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "camera.h"

typedef int (*CameraDataCallback)(void *cookie,  void *data);

typedef struct CameraDataCallbackType{
	void *cookie;   //SimpleRecorder
	CameraDataCallback callback;
}CameraDataCallbackType;


typedef struct AWCameraDevice
{
	void *context;
	int  (*startCamera)(struct AWCameraDevice *p);
	int  (*stopCamera)(struct AWCameraDevice *p);
	int  (*returnFrame)(struct AWCameraDevice *p, int id);
	int  (*setCameraDatacallback)(struct AWCameraDevice *p, void *cookie, void *callback);
}AWCameraDevice;

AWCameraDevice *CreateCamera(int width, int height);
void DestroyCamera(AWCameraDevice* camera);
void* getV4L2ctx(AWCameraDevice *p);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CAMERASOURCE_H */