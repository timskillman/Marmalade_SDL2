Marmalade to SDL2.0 code  
========================

This repo holds SDL2 code that is equivalent to some Marmalade classes.


Classes
=======

- s3e (limited)
  - s3eSurfaceGetInt
  - s3eKeyboardUpdate
  - s3ePointerUpdate
  - s3eDeviceYield
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

- CIwFVec2
- CIwFVec3
- CIwTexture
- CIwMaterial
- CIwFMat
- CIwFMat2D

Objectives
==========
The objective of this development is to provide equivalent Marmalade classes to help developers use SDL2 as an alternative.

Sample Marmalade-SDL2 examples will be made available for you to try out very soon - so watch this space :)

Extensions
==========
This development makes it possible to add other non-Marmalade extensions such as file loaders (e.g. OBJ/STL) and other useful features! 
