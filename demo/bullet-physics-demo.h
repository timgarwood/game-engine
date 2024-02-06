#ifndef _BULLET_PHYSICS_DEMO_H
#define _BULLET_PHYSICS_DEMO_H

class BulletPhysicsDemo
{
public:
    static BulletPhysicsDemo *Instance();
    void Init();

private:
    BulletPhysicsDemo();
    static BulletPhysicsDemo *s_instance;
};

#endif