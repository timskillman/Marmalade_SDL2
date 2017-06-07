A Marmalade to SDL2.0 SDK alternative  
=====================================

For all those developers, left in the lurch by Marmalade, this Git repo provides a limited solution to help convert
Marmalade projects to SDL 2.0.

It aims to compile and run existing Marmalade SDK projects in SDL 2.0 and provide toolchains for cross platform deployment.

Development is underway to support the following;

Classes
=======

- s3e (limited)
  - s3eDeviceCheckQuitRequest
  - s3ePointerGetTouchX
  - s3ePointerGetTouchY
  - s3ePointerWheelChangedEvent
  - s3ePointerGetTouchState
  - s3eFileCheckExists
- IwGx
  - IwGxInit
  - IwGxTerminate
  - IwGxSetPerspMul
  - IwGxSetOrtho
  - IwGxSetFarZNearZ
  - IwGxSetViewMatrix
  - IwGxSetModelMatrix
  - IwGxGetModelViewClipMatrix
  - IwGxSetLightType
  - IwGxSetLightDirn
  - IwGxSetLightCol
  - IwGxFogOn
  - IwGxSetClearColour
  - IwGxClear
  - IwGxLightingOn
  - IwGxLightingOff
  - IwGxSetMaterial
  - IwGxFlush
  - IwGxSwapBuffers
  - IwGxClipVec
  - IwGxSetColStream
  - IwGxSetUVStream
  - IwGxSetNormStream
  - IwGxSetVertStream
  - IwGxSetVertStreamModelSpace
  - IwGxDrawPrims
  - _IwGxSetViewRect
  
- Iw2D
  - Iw2DDrawLine
  - Iw2DDrawPolygon
  - Iw2DDrawRect
  - Iw2DFillRect
  - Iw2DFillPolygon
  - Iw2DSetColour
  - Iw2DLineWidth
  - Iw2DDrawTexture
  

Types
=====

- CIwVector2D
- CIwVector3D
- CIwTexture
- CIwMaterial
- CIwFMat

Objectives
==========
The objective of this development is to simply replace Marmalade SDK with alternative classes of the same name and parameters
(but certainly not the same code!)

However, to replace the Marmalade SDK entriely is a massive undertaking and YOUR SUPPORT is essential to achieve this.

A sample Marmalade project and Marmalade wrapper WILL be made available for you to try out very soon - so watch this space :)

