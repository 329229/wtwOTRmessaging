/*
** Copyright (C) 2007-2015, K2T.eu
*/

#pragma once

#include "wtwPlugin.h"
#include "wtwProtocol.h"
#include "wtwProcAddr.h"

#define  HOTKEY_MOD_CONTROL (FCONTROL << 16)
#define  HOTKEY_MOD_ALT		(FALT << 16)
#define  HOTKEY_MOD_SHIFT	(FSHIFT << 16)

struct wtwMenuItemDef 
{
	__wtwStdStructDefs(wtwMenuItemDef);

	int				structSize;

	const wchar_t * itemId;
	const wchar_t * menuID;

	const wchar_t * menuCaption;
	const wchar_t * menuInsert;


	int				flags;
	int				position;

	const wchar_t *	iconId;
	
	WTWFUNCTION		callback;		// funkcja wywolywana po kliknieciu
									// WPARAM: wtwMenuItemDef *
									// LPARAM: wtwMenuPopupInfo *
	void		*	cbData;

	DWORD			hotKey;
  	             
	HINSTANCE		hModule;

	void		*	ownerData;

};

struct wtwMenuPopupInfo 
{
	__wtwStdStructDefs(wtwMenuPopupInfo);

	int				structSize;

	POINT			point;

	const wchar_t * menuID;
	const wchar_t * locationID;

	int				iContacts;
	wtwContactDef	*pContacts;
	void			*pNodes;		// array of ptr's actually, don't use, internal

	DWORD			hotKey;

};

#define WTW_EVENT_MENU_REBUILD		L"WTW/OnMenuRebuild"
#define WTW_EVENT_MENU_COMPLETED	L"WTW/OnMenuCompleted"

struct wtwMenuCallbackEvent 
{
	__wtwStdStructDefs(wtwMenuCallbackEvent);

	int					structSize;
	wtwMenuPopupInfo	*pInfo;

	void *				itemsToShow;

	stringListInterface slInt;		// domanipulacji na its;
};

#define	WTW_MENU_ITEM_ADD			L"WTW/Menu/Add"			//WPARAM: wtwMenuItemDef *
#define	WTW_MENU_ITEM_DELETE		L"WTW/Menu/Remove"		//WPARAM: wtwMenuItemDef *
#define	WTW_MENU_ITEM_MODIFY		L"WTW/Menu/Modify"		//WPARAM: wtwMenuItemDef *
#define	WTW_MENU_ITEM_GET			L"WTW/Menu/Get"			//WPARAM: wtwMenuItemDef *
#define	WTW_MENU_ITEM_GET_F			L"WTW/Menu/GetF"		//internal
#define	WTW_MENU_ITEM_CLEAR			L"WTW/Menu/Clear"		//WPARAM: hModule

#define	WTW_MENU_JUNCTION_ADD	L"WTW/Menu/AddJunction"	//WPARAM: wtwMenuJuctionDef *, LPARAM: lparam z EVENT_COMPLETED
#define	WTW_MENU_DYNAMIC_ADD	L"WTW/Menu/AddDynamic"	//WPARAM: wtwMenuItemDef *, LPARAM: lparam z EVENT_COMPLETED

struct wtwMenuJunctionDef 
{
	__wtwStdStructDefs(wtwMenuJunctionDef);

	int				structSize;

	const wchar_t * menuCaption;
	const wchar_t * menuLocation;
	const wchar_t * menuID;			// co pod��czyc
	
	int				iContacts;
	void			*pNodes;		// dla ktorych kontaktow

	int				position;

};

/*******************************************************************************
**
** Function: 
**		WTW_MENU_CREATE
**
** Return value: 
**		S_OK, E_*
**
** Parameters:
**		wP - wtwMenuDef*
**		lP - NULL
**
*/

#define	WTW_MENU_CREATE	L"WTW/Menu/Create"

struct wtwMenuDef
{
	__wtwStdStructDefs(wtwMenuDef);

	int				structSize;

	const wchar_t * menuId;

	DWORD			flags;
	HINSTANCE		hInst;

};

#define WTW_MENU_FLAG_STATIC	0x000001

/*******************************************************************************
**
** Function: 
**		WTW_MENU_DESTROY_ALL - not implemented
**
** Return value: 
**		S_OK, E_*
**
** Parameters:
**		wP - hInstance
**		lP - NULL
**
*/

#define	WTW_MENU_DESTROY_ALL	L"WTW/Menu/DestrAll"

/*******************************************************************************
**
** Function: 
**		WTW_MENU_DESTROY
**
** Return value: 
**		S_OK, E_*
**
** Parameters:
**		wP - const wchar_t* menuId;
**		lP - NULL
**
*/

#define	WTW_MENU_DESTROY		L"WTW/Menu/Destr"

#define WTW_MENU_ITEM_FLAG_POPUP		0x00000001
#define WTW_MENU_ITEM_FLAG_CHECKED		0x00000002
#define WTW_MENU_ITEM_FLAG_DISABLED		0x00000004
#define WTW_MENU_ITEM_FLAG_AUTOCHK		0x00000008
#define WTW_MENU_ITEM_FLAG_SEPARATOR	0x00000010
#define WTW_MENU_ITEM_FLAG_DEFAULT		0x00000020
#define WTW_MENU_ITEM_FLAG_RADIOCHK		0x00000040
#define WTW_MENU_ITEM_FLAG_STATIC		0x00000080
#define WTW_MENU_ITEM_FLAG_INSERTP		0x00000100

#define	WTW_MENU_MASK_FLAGS			0x00000FFF
#define	WTW_MENU_MASK_MODIFY		0xFFF00000

#define WTW_MENU_MODIFY_CAPTION		0x10000000
#define WTW_MENU_MODIFY_POSITION	0x20000000
#define WTW_MENU_MODIFY_CALLBACK	0x40000000
#define WTW_MENU_MODIFY_FLAGS		0x80000000
#define WTW_MENU_MODIFY_ICON		0x01000000
#define WTW_MENU_MODIFY_HOTKEY		0x02000000
#define WTW_MENU_MODIFY_OWNERDATA	0x04000000
#define WTW_MENU_MODIFY_CBDATA		0x08000000

#define WTW_MENU_ID_MAIN		L"WTW/Menu/Main"		// glowne menu, nie uzywac
#define WTW_MENU_ID_MAIN_WTW	L"WTW/Menu/Main/WTW"	// popup glownego menu "WTW"
#define WTW_MENU_ID_MAIN_VIW	L"WTW/Menu/Main/View"	// popup glownego menu Widok
#define WTW_MENU_ID_MAIN_OPT	L"WTW/Menu/Main/Opt"	// popup "Narzedzia"
#define WTW_MENU_ID_MAIN_INF	L"WTW/Menu/Main/Inf"	// popup "Informacje"
#define WTW_MENU_ID_MAIN_STS	L"WTW/Menu/Main/States"	// "Stan"
#define WTW_MENU_ID_TRAY		L"WTW/Menu/TrayMenu"				// Tray
#define WTW_MENU_ID_MAIN_OPT_ARC		L"WTW/Menu/Main/Opt/Arc"	// Archiwum
#define WTW_MENU_ID_TAB					L"WTW/Menu/Tab"				// Zak�adki
#define WTW_MENU_ID_CHAT_EDIT_CONTEXT	L"WTW/Menu/ChatEditCtx"		// Menu kontekstowe okna edycji wiadomosci

#define WTW_MENU_ID_CONTACT			L"WTW/Menu/Contact"		// menu kontaktu
#define WTW_MENU_ID_CONTACT_SEND	L"WTW/Menu/Contact/Send"
#define WTW_MENU_ID_CONTACT_SHARE	L"WTW/Menu/Contact/Share"
#define WTW_MENU_ID_GROUP			L"WTW/Menu/Group"		// menu grupy
#define WTW_MENU_ID_MCONTACT		L"WTW/Menu/MContact"	// menu meta-kontaktu

#define WTW_MIID_TRAY_RESTART	L"WTW/Tray/Restart"
#define WTW_MIID_TRAY_EXIT		L"WTW/Exit"
#define WTW_MIID_TRAY_SEP1		L"WTW/Tray/Sep1"
#define WTW_MIID_TRAY_SEP2		L"WTW/Tray/Sep2"
#define WTW_MIID_TRAY_SEP3		L"WTW/Tray/Sep3"
#define WTW_MIID_TRAY_SEND_MSG	L"WTW/Tray/SendMessage"
#define WTW_MIID_TRAY_SEND_SMS	L"WTW/Tray/SendSMS"
#define WTW_MIID_TRAY_SHOW		L"WTW/Tray/Show"

#define WTW_MIID_MAIN_WTW_OPEN_EXE_LOC	L"WTW/OpenExeLocation"
#define WTW_MIID_MAIN_WTW_OPEN_PROF_LOC	L"WTW/OpenProfileLoction"
#define WTW_MIID_MAIN_WTW_EXIT		L"WTW/Exit"
#define WTW_MIID_MAIN_WTW_RESTART	L"WTW/Restart"
#define WTW_MIID_MAIN_WTW_ENCRYPTION	L"WTW/Encryption"
#define WTW_MIID_MAIN_WTW_CLEANUP	L"WTW/Cleanup"
#define WTW_MIID_MAIN_WTW_SEP1		L"WTW/Separator1"
#define WTW_MIID_MAIN_WTW_SEP2		L"WTW/Separator2"
#define WTW_MIID_MAIN_WTW_SEP3		L"WTW/Separator3"
#define WTW_MIID_MAIN_WTW_SEP4		L"WTW/Separator4"
#define WTW_MIID_MAIN_WTW_ADD_CON		L"WTW/AddContact"
#define WTW_MIID_MAIN_WTW_SEND_MESSAGE	L"WTW/SendMessage"
#define WTW_MIID_MAIN_WTW_ADDONS	L"WTW/Addons"
#define WTW_MIID_MAIN_WTW_START_CHAT	L"WTW/StartChat"
#define WTW_MIID_MAIN_WTW_SEND_SMS	L"WTW/SendSMS"
#define WTW_MIID_MAIN_WTW_ACCOUNT	L"WTW/OptionsAccounts"
#define WTW_MIID_MAIN_OPT_OPT		L"WTW/Options"
#define WTW_MIID_MAIN_OPT_CON		L"WTW/Console"
#define WTW_MIID_MAIN_OPT_PCON		L"WTW/ProtoConsole"
#define WTW_MIID_MAIN_OPT_TRANS		L"WTW/TrasMan"

#define WTW_MIID_MAIN_OPT_ARC_ARC	L"WTW/Arch/Archive"
#define WTW_MIID_MAIN_OPT_COMPACT	L"WTW/Arch/Compact"
#define WTW_MIID_MAIN_OPT_IMP_ARC	L"WTW/Arch/Import"

#define WTW_MIID_MAIN_STS_ONLINE	L"WTW/Status/Available"
#define WTW_MIID_MAIN_STS_CHAT		L"WTW/Status/Chat"
#define WTW_MIID_MAIN_STS_DND		L"WTW/Status/DND"
#define WTW_MIID_MAIN_STS_AWAY		L"WTW/Status/Away"
#define WTW_MIID_MAIN_STS_XA		L"WTW/Status/XA"
#define WTW_MIID_MAIN_STS_INVISIBLE	L"WTW/Status/Invisible"
#define WTW_MIID_MAIN_STS_OFFLINE	L"WTW/Status/Unavailable"
#define WTW_MIID_MAIN_STS_DESC		L"WTW/Status/Desc"

#define WTW_MIID_MAIN_INF_ABOUT		L"WTW/Info/About"
#define WTW_MIID_MAIN_INF_BUGTRAQ	L"WTW/Info/Bugz"
#define WTW_MIID_MAIN_INF_DONATE	L"WTW/Info/Donate"
#define WTW_MIID_MAIN_INF_FB		L"WTW/Info/Facebook"
#define WTW_MIID_MAIN_INF_FORUM		L"WTW/Info/Forum"
#define WTW_MIID_MAIN_INF_HELP		L"WTW/Info/Help"
#define WTW_MIID_MAIN_INF_LICENSE	L"WTW/Info/License"
#define WTW_MIID_MAIN_INF_CHANGELOG	L"WTW/Info/Changelog"
#define WTW_MIID_MAIN_INF_UPDATE	L"WTW/Info/Update"

#define WTW_MIID_CHAT_CTX_PASTEANDSEND	L"WTW/ChatExt/PasteAndSend"

#define WTW_MIID_CT_MESSAGE		L"WTW/Contact/Message"
#define WTW_MIID_CT_CHAT		L"WTW/Contact/Chat"
#define WTW_MIID_CT_CALL_VIDEO	L"WTW/Contact/CallVideo"
#define WTW_MIID_CT_CALL_AUDIO	L"WTW/Contact/CallAudio"
#define WTW_MIID_CT_CALL_END	L"WTW/Contact/CallEnd"
#define WTW_MIID_CT_SHOW_GEOLOC	L"WTW/Contact/ShowOnMap"
#define WTW_MIID_CT_MARKER		L"WTW/Contact/Marker"
#define WTW_MIID_CT_EDIT		L"WTW/Contact/Edit"
#define WTW_MIID_CT_PUBDIR		L"WTW/Contact/PubDir"
#define WTW_MIID_CT_ADD			L"WTW/Contact/Add"
#define WTW_MIID_CT_DELETE		L"WTW/Contact/Delete"
#define WTW_MIID_CT_ARCHIVE		L"WTW/Contact/Archive"
#define WTW_MIID_CT_SEND_FILE	L"WTW/Contact/SendFile"
#define WTW_MIID_CT_SEND_PICT	L"WTW/Contact/SendPicture"
#define WTW_MIID_CT_SEND_IMGH	L"WTW/Contact/SendPictureIH"
#define WTW_MIID_CT_COPY_DESC	L"WTW/Contact/CopyDesc"
#define WTW_MIID_CT_CREATE_META	L"WTW/Contact/CreateMeta"
#define WTW_MIID_CT_FOLLOW_LINK	L"WTW/Contact/FollowLink"
#define WTW_MIID_CT_HTML_EXPORT	L"WTW/Contact/ExportToHTML"
#define WTW_MIID_CT_FAV_ADD		L"WTW/Contact/FavAdd"
#define WTW_MIID_CT_FAV_REMOVE	L"WTW/Contact/FavRemove"

#define WTW_MIID_GP_OPTIONS			L"WTW/Group/Options"
#define WTW_MIID_GP_SEND_MESSAGE	L"WTW/Group/SendMessage"

#define WTW_MIID_VIEW_TREE		L"WTW/View/Tree"
#define WTW_MIID_VIEW_LIST		L"WTW/View/List"
#define WTW_MIID_VIEW_S1		L"WTW/View/Sep1"
#define WTW_MIID_VIEW_HIDE_OFF	L"WTW/View/HideOff"
#define WTW_MIID_VIEW_S2		L"WTW/View/Sep2"
#define WTW_MIID_VIEW_DESC_SHOW	L"WTW/View/DescShow"
#define WTW_MIID_VIEW_S3		L"WTW/View/Sep3"
#define WTW_MIID_VIEW_AVATAR_SHOW_ALWAYS	L"WTW/View/AvatarShowAlways"
#define WTW_MIID_VIEW_AVATAR_SHOW_ONLINE	L"WTW/View/AvatarShowOnline"

#define WTW_MIID_TAB_CLOSE			L"WTW/Menu/Tab/Close"
#define WTW_MIID_TAB_CLOSE_OTHER	L"WTW/Menu/Tab/CloseOther"
#define WTW_MIID_TAB_CLOSE_THIS		L"WTW/Menu/Tab/CloseThis"
#define WTW_MIID_TAB_CLOSE_ALL		L"WTW/Menu/Tab/CloseAll"
#define WTW_MIID_TAB_CLOSE_R		L"WTW/Menu/Tab/CloseR"
#define WTW_MIID_TAB_CLOSE_L		L"WTW/Menu/Tab/CloseL"
#define WTW_MIID_TAB_DETACH			L"WTW/Menu/Tab/Detach"
#define WTW_MIID_TAB_RESTORE		L"WTW/Menu/Tab/Restore"

#define WTW_MENU_LOCATION_MAINWND	L"WTW/Loc/MainWND"	// glowne okno
#define WTW_MENU_LOCATION_TRAY		L"WTW/Loc/Tray"		// systray
#define WTW_MENU_LOCATION_TAB		L"WTW/Loc/Tab"		// zakladka
#define WTW_MENU_LOCATION_CHATWND	L"WTW/Loc/ChatWND"	// okno chata
#define WTW_MENU_LOCATION_CONFWND	L"WTW/Loc/ConfWND"	// okno konferencji
#define WTW_MENU_LOCATION_MWCTRL	L"WTW/Loc/MWCTRL"	// lista kontaktow
