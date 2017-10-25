
#include "StdAfx.h"
#include "Animation.h"
#include "AnimationEntity.h"
#include "Scene.h"
#include "SceneFrame.h"
#include "Tween.h"
#include <ResBuf.h>
#include <SdsUtilFuncs.h>
#include "AnmHelper.h"


//#include <stdio.h>
//#include <errno.h>
//#include <io.h>

#include "../api/sds/sds.h"
#include "AnimEditInfo.h"

//#include "ResourceStrings.h"
//#include "..\adeko\icad\Configure_adeko.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



using namespace std;
using namespace Anim;


// Utility definition to get an array's element count (at compile time).
//   For  example:
//
//   int  arr[] = {1,2,3,4,5};
//
//   printf("%d", ARRAYELEMENTS(arr));
//
// would print a five.  ARRAYELEMENTS("abc") can also be used to tell how
// many bytes are in a string constant INCLUDING THE TRAILING NULL.
#define ARRAYELEMENTS(array) (sizeof(array)/sizeof((array)[0]))

// Define the structure of the table: a string giving the IntelliCAD name
// of the function, and a pointer to a function returning type int.
struct func_def { char *func_name; int (*func) (void); };

// Define the array of function names and handlers.
static struct func_def func_table[] = {
	{"anm_control"    , anm_control},
	{"anm_setCoor"	,anm_setCoordinate	},
	{"anm_addCoor"	,anm_addCoordinate	},
	{"anm_runScene" , anm_runScene},
	{"anm_cleanScene" , anm_cleanScene},
	{"anm_rewind" , anm_rewind},
	{"anm_reset" , anm_reset},
	{"anm_setRotateXYZ" , anm_setRotateXYZ	},
	{"anm_addRotateXYZ" , anm_addRotateXYZ	},
	{"anm_multipos" , anm_multiPos	},
	{"anm_setFPS", anm_setFPS},
	{"anm_getPosInfo" , anm_getPosInfo},
	{"anm_setPosInfo" , anm_setPosInfo},
	{"anm_addPosInfo" , anm_addPosInfo},
	//multiscene postponed // {"anm_createScene" , anm_createScene }


};
// To add more functions to this table, just put them in the list, after
// declaring the function names.

char      adsw_AppName[512];
char	 *ads_argVec = adsw_AppName;
char      ads_appname[512];
HWND      adsw_hwndAcad;
HINSTANCE adsw_hInstance;

HWND      adsw_hWnd;
int       adsw_wait;

sds_matrix ads_identmat;

// Protos
extern "C" int SDS_GetGlobals(char *appname,HWND *hwnd,HINSTANCE *hInstance);
void __declspec(dllexport) SDS_EntryPoint(HWND hWnd);


void __declspec(dllexport) SDS_EntryPoint(HWND hWnd) {

	int i,j;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	for(i=0; i<=3; i++) for(j=0; j<=3; j++)	ads_identmat[i][j]=0.0;
	for(i=0; i<=3; i++) ads_identmat[i][i]=1.0;

	SDS_GetGlobals(adsw_AppName,&adsw_hwndAcad,&adsw_hInstance);
	strncpy(ads_appname,adsw_AppName,sizeof(ads_appname)-1);
	SDS_main(1, &ads_argVec);
	return;
}

//CWnd * g_pcwndIcadMainWindow22;

// The code from here to the end of invokefun() is UNCHANGED when you add or delete
// functions.

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/* MAIN - the main routine */

Anim::Scene gLispAnimScene;
//multiscene postponed // std::string gSceneName = "gLispAnimScene";

typedef map<std::string,Anim::Scene *> SceneCollection;

SceneCollection gScenes;

int main(int argc, char** argv)
{
	short scode = RSRSLT;             // Normal result code (default)
	int stat;
	char errmsg[80];
	//multiscene postponed // gScenes[gSceneName] = &gLispAnimScene;

	sds_init(argc, argv);             // Open communication with lisp

	for ( ;; ) {                      // Request/Result loop
		if ((stat = sds_link(scode)) < 0) {
			sprintf(errmsg, "Templt: bad status from sds_link() = %d\n", stat);
			sds_printf(errmsg);
			sds_exit(-1);
		}
		scode = RSRSLT;               // Reset result code

		switch (stat) {
case RQXLOAD:                 // Load & define functions
	   //g_pcwndIcadMainWindow22 = CWnd::FromHandle ( sds_getmainhwnd () );
	   //AfxGetApp()->m_pActiveWnd = CWnd::FromHandle ( sds_getmainhwnd () );
	AfxGetApp()->m_pActiveWnd = CWnd::FromHandle ( sds_getmainhwnd () );
	scode = funcload() == RTNORM ? RSRSLT : RSERR;
	//sds_printf(animationLoaded);
	break;
case SDS_RQXUNLD:
	break;
case RQSUBR:                  // Handle external function requests
	scode = invokefun() == RTNORM ? RSRSLT : RSERR;
	break;
case SDS_RQSAVE:
	break;
case SDS_RQEND:
	break;
case SDS_RQQUIT:
	break;
case SDS_RQCFG:
	break;
case SDS_RQHUP:
	break;
case SDS_RQXHELP:
	break;
default:
	break;
		}
	}
	return(1);
}

//-----------------------------------------------------------------------------
// FUNCLOAD  --  Define this application's external functions.  Return
//               RTERROR on error, else RTNORM.

static int funcload()
{
	short i;

	for (i = 0; i < ARRAYELEMENTS(func_table); i++) {
		if (!sds_defun(func_table[i].func_name, i))
			return RTERROR;
	}
	return RTNORM;
}

//-----------------------------------------------------------------------------
// invokefun -- Execute external function (called upon an RQSUBR request).
//              Return value from the function executed, RTNORM or RTERROR.

static int invokefun()
{
	int val;

	// Get the function code and check that it's within range.
	// (It can't fail to be, but paranoia doesn't hurt.)
	if ((val = sds_getfuncode()) < 0 || val >= ARRAYELEMENTS(func_table)) {
		sds_fail("Received nonexistent function code.");
		return RTERROR;
	}

	// Call the handler and return its success-failure status.
	val = (*func_table[val].func)();
	return val;
}
//-----------------------------------------------------------------------------
// The code from the beginning of main() to here is UNCHANGED when you add or
// delete functions.
//-----------------------------------------------------------------------------

 int anm_control ()
{
	CResBuf crb;
	crb.GetArgs();
	char entHandleName[255];
	if (crb.GetString(entHandleName) != RTNORM) return RTERROR;
	sds_animPosInfo tempPos;
	sds_point jj = {0.0,0.0,0.0};
	sds_point_set(jj,tempPos._inputCoordinate);
	tempPos._scaleXYZ[0] = 1.0f;
	tempPos._scaleXYZ[1] = 1.0f;
	tempPos._scaleXYZ[2] = 1.0f;
	tempPos._rotateXYZ[0] = 0.0f;
	tempPos._rotateXYZ[1] = 0.0f;
	tempPos._rotateXYZ[2] =0.0f;
	int tt = 0;
	
	for (tt=0;tt<157;tt++)
	{
		tempPos._scaleXYZ[0] =  0.02f;
		sds_anim_setpos(entHandleName,tempPos);
	}


	return RTNORM;	
}

int anm_multiPos ()
{
	CResBuf crb;

	sds_point thatposition;
	sds_point thatrotation;
	sds_point thatscale;
	sds_animPosInfo mmm;
	char entHandleName[255];

	crb.GetArgs();

	if (crb.GetString(entHandleName) != RTNORM) return RTERROR;
	if (crb.GetPoint(thatposition) != RTNORM) return RTERROR;
	if (crb.GetPoint(thatrotation) != RTNORM) return RTERROR;
	if (crb.GetPoint(thatscale) != RTNORM) return RTERROR;

	sds_point_set(thatposition,mmm._inputCoordinate);
	mmm._rotateXYZ[0]=	thatrotation[0];
	mmm._rotateXYZ[1]=	thatrotation[1];
	mmm._rotateXYZ[2]=	thatrotation[2];
	mmm._scaleXYZ[0]=	thatscale[0];
	mmm._scaleXYZ[1]=	thatscale[1];
	mmm._scaleXYZ[2]=	thatscale[2];

	sds_anim_setpos(entHandleName,mmm);
	return RTNORM;

}

int anm_SceneOperations (ANM_SCENEFUNCTION operation)
{
	//multiscene postponed // std::string sceneName = gSceneName;
	/*char charSceneName[255];*/
	//CResBuf crb;
	//crb.GetArgs();

	//if (crb.GetString(charSceneName) == RTNORM) 
	//	sceneName = charSceneName;	
	//multiscene postponed // 

	switch (operation)
	{
		case SCENERUN:
			gLispAnimScene.run();
		break;
		case SCENECLEAN:			
			gLispAnimScene.clean();
			break;
		case VIEWREWIND:			
			sds_anim_refreshade();			
		break;
		case VIEWSCENERESET:		
			gLispAnimScene.clean();
			sds_anim_refreshade();			
			break;
		case SETSCENEFPS:
			CResBuf crb;
			int tempFrameRate;
			crb.GetArgs();
			if (crb.GetInt(tempFrameRate) != RTNORM) return RTERROR;
			gLispAnimScene._frameRate = tempFrameRate;
		break;
	}

	return RTNORM;
}

int anm_runScene ()
{
	return anm_SceneOperations(SCENERUN);
}

int anm_cleanScene ()
{
	return anm_SceneOperations(SCENECLEAN);
}

int anm_reset ()
{
	return anm_SceneOperations(VIEWSCENERESET);
}

int anm_rewind ()
{
	return anm_SceneOperations(VIEWREWIND);
}

int anm_setFPS ()
{
	return anm_SceneOperations(SETSCENEFPS);
}



//(functionname handlename startFrame positionReference insertPointOffset endFrame positionTarget insertPointOffset)
//for example:

//(anm_addRotateXYZ "1BD8F" 0 (list 0.0 0.0 0.0) 100 (list 0.0 1.57 0.0) (list 100.0 0.0 0.0))

int anm_setSingleFunctions(ANM_LISPFUNCTION funInput,EditPositionInfo actInput)
{

	CResBuf crb;
	crb.GetArgs();
	int startFrame;
	sds_point pos1;
	sds_point insertOffset = {0.0,0.0,0.0};
	int endFrame;
	sds_point pos2;
	char entHandleName[255];
	char charSceneName[255];
	std::string sceneName;
	sds_animPosInfo tempTransInfo;
	EditPositionInfo firstPos ;
	EditPositionInfo secondPos ;
	HelperConverter helpertemp;
	helpertemp.convertToNaNEditPosInfo(firstPos);
	helpertemp.convertToNaNEditPosInfo(secondPos);
	
	
	if (crb.GetString(entHandleName) != RTNORM) return RTERROR;
	if (crb.GetInt(startFrame) != RTNORM) 
	{
		if (crb.GetString(charSceneName) != RTNORM) return RTERROR;

		sceneName = charSceneName;
		if (crb.GetInt(startFrame) != RTNORM) return RTERROR;
	}
	if (crb.GetPoint(pos1) != RTNORM) return RTERROR;


	if (crb.GetInt(endFrame) != RTNORM) return RTERROR;
	
	if (crb.GetPoint(pos2) != RTNORM) return RTERROR;

	if (crb.GetPoint(insertOffset) == RTNORM)
	{
		firstPos._rotateOffset.translation = ADE::Vector3f(insertOffset[0], insertOffset[1], insertOffset[2]);
		secondPos._rotateOffset.translation = ADE::Vector3f(insertOffset[0], insertOffset[1], insertOffset[2]);
		
	}

	

	
	

	AnimationEntity animEnt(entHandleName);
	firstPos._actionType = actInput._actionType;
	secondPos._actionType = actInput._actionType;

	switch(funInput)
	{
		case SETCOOR:
			firstPos._inputPosition.translation = ADE::Vector3f(pos1[0], pos1[1], pos1[2]);
			secondPos._inputPosition.translation = ADE::Vector3f(pos2[0], pos2[1], pos2[2]);			
		break;

		case SETROTATEXYZ:						
			
			firstPos._inputPosition.rotation =   ADEX::createRotationX(pos1[0]) * ADEX::createRotationY(pos1[1]) * ADEX::createRotationZ(pos1[2]);
			secondPos._inputPosition.rotation =  ADEX::createRotationX(pos2[0]) * ADEX::createRotationY(pos2[1]) * ADEX::createRotationZ(pos2[2]);
			


		break;


		break;
	}

	Tween moveTween(startFrame,KeyFrame(animEnt,firstPos),endFrame,KeyFrame(animEnt,secondPos) );

	//multiscene postponed // 
	//if (gScenes[sceneName] != NULL)
	//{
	//	gScenes[sceneName] = &(*(gScenes[sceneName]) << moveTween.toScene());
	//}
	//multiscene postponed // 

	gLispAnimScene = gLispAnimScene << moveTween.toScene();

	return RTNORM;

}

//multiscene postponed // 
//int anm_createScene()
//{
//	Anim::Scene * tempScene = new Anim::Scene();
//	char charSceneName[255];
//	std::string sceneName;
//		
//	CResBuf crb;
//	crb.GetArgs();
//
//	if (crb.GetString(charSceneName) != RTNORM) return RTERROR;
//
//	sceneName = charSceneName;
//
//	gScenes[sceneName] = tempScene;
//
//	return RTNORM;
//}


//int anm_deleteScene()
//{
//	char charSceneName[255];
//	std::string sceneName;
//
//	CResBuf crb;
//	crb.GetArgs();
//
//	if (crb.GetString(charSceneName) != RTNORM) return RTERROR;
//
//	sceneName = charSceneName;
//	if (gScenes[sceneName] != NULL)
//	{
//		delete gScenes[sceneName];
//	}
//
//	return RTNORM;
//}

//multiscene postponed // 

int anm_setCoordinate ()
{
	return anm_setSingleFunctions(SETCOOR,EditPositionInfo(ABSOLUTE_ACT));	
}

int anm_setRotateXYZ ()
{
	return anm_setSingleFunctions(SETROTATEXYZ,EditPositionInfo(ABSOLUTE_ACT));	
}

int anm_addCoordinate()
{
	return anm_setSingleFunctions(SETCOOR,EditPositionInfo(RELATIVE_ACT));	
}

int anm_addRotateXYZ ()
{
	return anm_setSingleFunctions(SETROTATEXYZ,EditPositionInfo(RELATIVE_ACT));	
}

int anm_addPosInfo ()
{
	return anm_actPosInfo(EditPositionInfo(RELATIVE_ACT));	
}

int anm_setPosInfo ()
{
	return anm_actPosInfo(EditPositionInfo(ABSOLUTE_ACT));	
}

int anm_actPosInfo(EditPositionInfo actInput)
{
	//AnmHelper helperm;	
	HelperConverter helperm;

	sds_animPosInfo transInfo1, transInfo2;
	char entHandleName[255];
	CResBuf crb;
	int startFrame;		
	int endFrame;
	transInfo1._actType = static_cast<int>(actInput._actionType); //helperm.convertEditPosInfoToAnimPos(actInput);

	transInfo2._actType = static_cast<int>(actInput._actionType); //helperm.convertEditPosInfoToAnimPos(actInput);

	

	crb.GetArgs();

	if (crb.GetString(entHandleName) != RTNORM) return RTERROR;

	if (crb.GetInt(startFrame) != RTNORM) return RTERROR;

	if (crb.GetPoint(transInfo1._inputCoordinate) != RTNORM) return RTERROR;
	//sds_point_set(temp,transInfo1._inputCoordinate);
	if (crb.GetPoint(transInfo1._rotateXYZ) != RTNORM) return RTERROR;
	if (crb.GetPoint(transInfo1._rotateOffset) != RTNORM) return RTERROR;

	//sds_point_set(temp2,transInfo1._rotateXYZ);
	if (crb.GetPoint(transInfo1._scaleXYZ) != RTNORM)  return RTERROR;
	//sds_point_set(temp3,transInfo1._scaleXYZ);

	if (crb.GetInt(endFrame) != RTNORM) return RTERROR;

	if (crb.GetPoint(transInfo2._inputCoordinate) != RTNORM) return RTERROR;
	
	if (crb.GetPoint(transInfo2._rotateXYZ) != RTNORM) return RTERROR;

	if (crb.GetPoint(transInfo2._rotateOffset) != RTNORM) return RTERROR;
	
	if (crb.GetPoint(transInfo2._scaleXYZ) != RTNORM)  return RTERROR;
	

	AnimationEntity animEnt(entHandleName);

	Tween moveTween(startFrame,KeyFrame(animEnt,helperm.convertAnimPosToEditPosInfo(transInfo1)),endFrame,KeyFrame(animEnt,helperm.convertAnimPosToEditPosInfo(transInfo2)) );
	gLispAnimScene = gLispAnimScene << moveTween.toScene();

	return RTNORM;

}

int anm_getPosInfo ()
{	
	HelperConverter helperm;
	resbuf * prbList;
	sds_animPosInfo transInfo;
	char entHandleName[255];
	CResBuf crb;

	crb.GetArgs();

	if (crb.GetString(entHandleName) != RTNORM) return RTERROR;

	sds_anim_getpos(entHandleName,&transInfo);

	prbList = sds_buildlist(RT3DPOINT, transInfo._inputCoordinate, RT3DPOINT, transInfo._rotateXYZ, RT3DPOINT, transInfo._scaleXYZ,0);

	if (helperm.convertAnimPosToEditPosInfo(transInfo)._inputPosition.translation == helperm._nanEditPos._inputPosition.translation)
	{
		sds_retnil();
	}
	else
	{
		sds_retlist(prbList);
	}
	
	IC_RELRB(prbList);
	return RTNORM;
}


BEGIN_MESSAGE_MAP(CAnimationApp, CWinApp)
END_MESSAGE_MAP()


CAnimationApp::CAnimationApp()
{}

CAnimationApp theApp;

