#pragma once

class CCamera;

class CRenderMgr :
    public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);
private:
    vector<CCamera*>    m_vecCam;

public:
    void RegisterCamera(CCamera* _Cam, int _Priority);

public:
    void init();
    void tick();
    void render();
};

