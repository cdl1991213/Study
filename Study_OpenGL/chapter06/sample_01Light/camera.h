#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <vector>
#include <complex>
// 移动方向枚举量，是一种抽象，以避免特定于窗口系统的输入方式
// 这里是 WASDQE
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// 默认值
const float YAW         = -90.0f;   //绕y轴旋转
const float PITCH       = 0.0f;     //不抬头，平视
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM        = 45.0f;    //prospective投影角度

class Camera
{
public:
    // camera attributes
    QVector3D Position;/*照相机位置*/
    QVector3D Front;/*照相机目标方向*/
    QVector3D Up;/*Up axis*/
    QVector3D Right;/*Right axis*/
    QVector3D WorldUp;
    // euler angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed = SPEED;
    float MouseSensitivity = SENSITIVITY;
    float Zoom = ZOOM;

    // constructor with vectors
    Camera(QVector3D position = QVector3D(0.0f, 0.0f, 0.0f), QVector3D up = QVector3D(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    {
        Position = QVector3D(posX, posY, posZ);
        WorldUp = QVector3D(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    //3d矩阵中的view观察矩阵
    QMatrix4x4 GetViewMatrix()
    {
        QMatrix4x4 theMatrix;
        theMatrix.lookAt(Position, Position + Front, Up);
        return theMatrix;
    }

    // 处理键盘输入
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if(direction == FORWARD) {
            Position += Front * velocity;
        }
        if(direction == BACKWARD) {
            Position -= Front * velocity;
        }
        if(direction == LEFT) {
            Position -= Right * velocity;
        }
        if(direction == RIGHT) {
            Position += Right * velocity;
        }
        if(direction == UP) {
            Position += Up * velocity;
        }
        if(direction == DOWN) {
            Position -= Up * velocity;
        }
//        Position.setY(1.0f);
//        updateCameraVectors();
    }

    // 处理鼠标移动输入
    void ProcessMouseMovement(float xoffset, float yoffset)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        Yaw += xoffset;
        Pitch += yoffset;
        // 确保超出边界时屏幕不会翻转
        if (true) {
            if (Pitch > 89.0f) {
                Pitch = 89.0f;
            }
            if (Pitch < -89.0f) {
                Pitch = -89.0f;
            }
        }
        // 使用更新的Euler角度更新前、右和上矢量
        updateCameraVectors();
    }

    // 处理鼠标滚轮输入
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f) {
            Zoom = 1.0f;
        }
        if (Zoom > 75.0f) {
            Zoom = 75.0f;
        }
    }


private:
    // 根据相机的Euler角度计算前矢量
    void updateCameraVectors()
    {
        // calculate the Front vector
        float PI = 3.14159265f;
        QVector3D front;
        front.setX(cos(Yaw * PI / 180.0) * cos(Pitch * PI / 180.0));
        front.setY(sin(Pitch * PI / 180.0));
        front.setZ(sin(Yaw * PI / 180.0) * cos(Pitch * PI / 180.0));
        front.normalize();
        Front = front;
        // 重计算右向量和上向量
        Right = QVector3D::crossProduct(Front, WorldUp);
        Right.normalize();
        Up = QVector3D::crossProduct(Right, Front);
        Up.normalize();
    }
};


#endif // CAMERA_H
