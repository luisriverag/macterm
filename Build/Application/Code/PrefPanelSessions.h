/*!	\file PrefPanelSessions.h
	\brief Implements the Sessions panel of Preferences.
*/
/*###############################################################

	MacTerm
		© 1998-2020 by Kevin Grant.
		© 2001-2003 by Ian Anderson.
		© 1986-1994 University of Illinois Board of Trustees
		(see About box for full list of U of I contributors).
	
	This program is free software; you can redistribute it or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version
	2 of the License, or (at your option) any later version.
	
	This program is distributed in the hope that it will be
	useful, but WITHOUT ANY WARRANTY; without even the implied
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
	PURPOSE.  See the GNU General Public License for more
	details.
	
	You should have received a copy of the GNU General Public
	License along with this program; if not, write to:
	
		Free Software Foundation, Inc.
		59 Temple Place, Suite 330
		Boston, MA  02111-1307
		USA

###############################################################*/

#include <UniversalDefines.h>

#pragma once

// application includes
#include "GenericPanelTabs.h"
#include "Keypads.h"
#include "Panel.h"
#include "Preferences.h"
#ifdef __OBJC__
#	include "PreferenceValue.objc++.h"
#	include "PrefsContextManager.objc++.h"
#endif
#include "ServerBrowser.h"



#pragma mark Types

#ifdef __OBJC__

/*!
Loads a NIB file that defines a panel view with tabs
and provides the sub-panels that the tabs contain.

Note that this is only in the header for the sake of
Interface Builder, which will not synchronize with
changes to an interface declared in a ".mm" file.
*/
@interface PrefPanelSessions_ViewManager : GenericPanelTabs_ViewManager @end


/*!
Loads a NIB file that defines the Resource pane.

Note that this is only in the header for the sake of
Interface Builder, which will not synchronize with
changes to an interface declared in a ".mm" file.
*/
@interface PrefPanelSessions_ResourceViewManager : Panel_ViewManager< Panel_Delegate,
																		PrefsWindow_PanelInterface,
																		ServerBrowser_DataChangeObserver > //{
{
	IBOutlet NSView*					commandLineTextField;
@private
	PrefsContextManager_Object*			prefsMgr;
	ListenerModel_StandardListener*		preferenceChangeListener;
	NSRect								idealFrame;
	NSMutableDictionary*				byKey;
	ServerBrowser_Ref					_serverBrowser;
	NSIndexSet*							_sessionFavoriteIndexes;
	NSArray*							_sessionFavorites;
	BOOL								isEditingRemoteShell;
}

// accessors: preferences
	- (PreferenceValue_StringByJoiningArray*)
	commandLine; // binding
	- (PreferenceValue_CollectionBinding*)
	formatFavoriteLightMode; // binding
	- (PreferenceValue_CollectionBinding*)
	formatFavoriteDarkMode; // binding
	- (PreferenceValue_CollectionBinding*)
	macroSetFavorite; // binding
	- (PreferenceValue_CollectionBinding*)
	terminalFavorite; // binding
	- (PreferenceValue_CollectionBinding*)
	translationFavorite; // binding

// accessors: low-level user interface state
	- (BOOL)
	isEditingRemoteShell; // binding
	@property (retain) NSIndexSet*
	sessionFavoriteIndexes; // binding
	@property (retain, readonly) NSArray*
	sessionFavorites; // binding

// accessors: internal bindings
	- (PreferenceValue_String*)
	serverHost;
	- (PreferenceValue_Number*)
	serverPort;
	- (PreferenceValue_Number*)
	serverProtocol;
	- (PreferenceValue_String*)
	serverUserID;

// actions
	- (IBAction)
	performSetCommandLineToDefaultShell:(id)_; // binding
	- (IBAction)
	performSetCommandLineToLogInShell:(id)_; // binding
	- (IBAction)
	performSetCommandLineToRemoteShell:(id)_; // binding

@end //}


/*!
Manages bindings for the capture-file preferences.
*/
@interface PrefPanelSessions_CaptureFileValue : PreferenceValue_Inherited //{
{
@private
	PreferenceValue_Flag*				enabledObject;
	PreferenceValue_Flag*				allowSubsObject;
	PreferenceValue_String*				fileNameObject;
	PreferenceValue_FileSystemObject*	directoryPathObject;
}

// initializers
	- (instancetype)
	initWithContextManager:(PrefsContextManager_Object*)_;

// accessors
	- (BOOL)
	isEnabled;
	- (void)
	setEnabled:(BOOL)_; // binding
	- (BOOL)
	allowSubstitutions;
	- (void)
	setAllowSubstitutions:(BOOL)_; // binding
	- (NSURL*)
	directoryPathURLValue;
	- (void)
	setDirectoryPathURLValue:(NSURL*)_; // binding
	- (NSString*)
	fileNameStringValue;
	- (void)
	setFileNameStringValue:(NSString*)_; // binding

@end //}


/*!
Loads a NIB file that defines the Data Flow pane.

Note that this is only in the header for the sake of
Interface Builder, which will not synchronize with
changes to an interface declared in a ".mm" file.
*/
@interface PrefPanelSessions_DataFlowViewManager : Panel_ViewManager< Panel_Delegate,
																		PrefsWindow_PanelInterface > //{
{
@private
	PrefsContextManager_Object*		prefsMgr;
	NSRect							idealFrame;
	NSMutableDictionary*			byKey;
}

// accessors
	- (PreferenceValue_Flag*)
	localEcho; // binding
	- (PreferenceValue_Number*)
	lineInsertionDelay; // binding
	- (PreferenceValue_Number*)
	scrollingDelay; // binding
	- (PrefPanelSessions_CaptureFileValue*)
	captureToFile; // binding

@end //}


@class PrefPanelSessions_KeyboardActionHandler; // implemented internally


/*!
Implements the “Keyboard” panel.
*/
@interface PrefPanelSessions_KeyboardVC : Panel_ViewManager< Panel_Delegate,
																PrefsWindow_PanelInterface > //{
{
@private
	NSRect										_idealFrame;
	PrefPanelSessions_KeyboardActionHandler*	_actionHandler;
}

// accessors
	@property (strong) PrefPanelSessions_KeyboardActionHandler*
	actionHandler;

@end //}


@class PrefPanelSessions_GraphicsActionHandler; // implemented internally


/*!
Implements the “vector graphics” panel.
*/
@interface PrefPanelSessions_GraphicsVC : Panel_ViewManager< Panel_Delegate,
																PrefsWindow_PanelInterface > //{
{
@private
	NSRect										_idealFrame;
	PrefPanelSessions_GraphicsActionHandler*	_actionHandler;
}

// accessors
	@property (strong) PrefPanelSessions_GraphicsActionHandler*
	actionHandler;

@end //}

#endif // __OBJC__



#pragma mark Public Methods

Preferences_TagSetRef
	PrefPanelSessions_NewDataFlowPaneTagSet		();

Preferences_TagSetRef
	PrefPanelSessions_NewGraphicsPaneTagSet		();

Preferences_TagSetRef
	PrefPanelSessions_NewKeyboardPaneTagSet		();

Preferences_TagSetRef
	PrefPanelSessions_NewResourcePaneTagSet		();

Preferences_TagSetRef
	PrefPanelSessions_NewTagSet					();

// BELOW IS REQUIRED NEWLINE TO END FILE
