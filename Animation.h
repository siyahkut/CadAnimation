#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "KeyFrame.h"

using namespace Anim;

enum ANM_LISPFUNCTION {SETCOOR = 0, SETROTATEXYZ,SETALLPOSINFO};
enum ANM_SCENEFUNCTION {SCENERUN = 0, SCENECLEAN,VIEWREWIND,VIEWSCENERESET,SETSCENEFPS};

//  Declarations of other local support functions
int    main       (int, char **);
int    invokefun  (void);
int    funcload   (void);


int	  anm_control();
int	  anm_runScene();
int	  anm_cleanScene();
int	  anm_rewind();
int	  anm_reset();
int	  anm_setCoordinate();
int	  anm_getPosInfo();
int	  anm_setRotateXYZ();
int	  anm_multiPos();
int   anm_addCoordinate();
int   anm_addRotateXYZ();
//multiscene postponed //  int   anm_createScene();
int   anm_setSingleFunctions(ANM_LISPFUNCTION funInput,EditPositionInfo actInput);
int	  anm_SceneOperations (ANM_SCENEFUNCTION operation);
int	  anm_setFPS();
int   anm_actPosInfo(EditPositionInfo actInput);
int	  anm_setPosInfo();
int	  anm_addPosInfo();






/////////////////////////////////////////////////////////////////////////////
// CSceneApp
// See Scene.cpp for the implementation of this class
//

class CAnimationApp : public CWinApp
{
public:
	CAnimationApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSceneApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSceneApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.



