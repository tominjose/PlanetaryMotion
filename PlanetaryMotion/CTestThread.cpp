#include "pch.h"
#include "CTestThread.h"
#include "PlanetaryMotionView.h"


UINT CTestThread::RunThreadFunction(LPVOID param)
{
    CPlanetaryMotionView* pPlanetaryMotionView = (CPlanetaryMotionView*)param;
    while (1)
    {
        pPlanetaryMotionView->Invalidate();
        Sleep(100);
    }
}
