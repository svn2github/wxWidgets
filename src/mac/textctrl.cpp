/////////////////////////////////////////////////////////////////////////////
// Name:        textctrl.cpp
// Purpose:     wxTextCtrl
// Author:      AUTHOR
// Modified by:
// Created:     ??/??/98
// RCS-ID:      $Id$
// Copyright:   (c) AUTHOR
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "textctrl.h"
#endif

#include "wx/defs.h"

#if wxUSE_TEXTCTRL

#ifdef __DARWIN__
  #include <sys/types.h>
  #include <sys/stat.h>
#else
  #include <stat.h>
#endif
#include <fstream.h>

#include "wx/app.h"
#include "wx/dc.h"
#include "wx/button.h"
#include "wx/toplevel.h"
#include "wx/textctrl.h"
#include "wx/notebook.h"
#include "wx/tabctrl.h"
#include "wx/settings.h"
#include "wx/filefn.h"
#include "wx/utils.h"

#if defined(__BORLANDC__) && !defined(__WIN32__)
  #include <alloc.h>
#elif !defined(__MWERKS__) && !defined(__GNUWIN32) && !defined(__DARWIN__)
  #include <malloc.h>
#endif

#ifndef __DARWIN__
#include <Scrap.h>
#endif
#include <MacTextEditor.h>
#include "ATSUnicode.h"
#include "TextCommon.h"
#include "TextEncodingConverter.h"
#include "wx/mac/uma.h"

extern wxApp *wxTheApp ;
// CS:We will replace the TextEdit by using the MultiLanguageTextEngine based on the following code written by apple

/*
    File: mUPControl.c
    
    Description:
        mUPControl implementation.

    Copyright:
        � Copyright 2000 Apple Computer, Inc. All rights reserved.
    
    Disclaimer:
        IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
        ("Apple") in consideration of your agreement to the following terms, and your
        use, installation, modification or redistribution of this Apple software
        constitutes acceptance of these terms.  If you do not agree with these terms,
        please do not use, install, modify or redistribute this Apple software.

        In consideration of your agreement to abide by the following terms, and subject
        to these terms, Apple grants you a personal, non-exclusive license, under Apple�s
        copyrights in this original Apple software (the "Apple Software"), to use,
        reproduce, modify and redistribute the Apple Software, with or without
        modifications, in source and/or binary forms; provided that if you redistribute
        the Apple Software in its entirety and without modifications, you must retain
        this notice and the following text and disclaimers in all such redistributions of
        the Apple Software.  Neither the name, trademarks, service marks or logos of
        Apple Computer, Inc. may be used to endorse or promote products derived from the
        Apple Software without specific prior written permission from Apple.  Except as
        expressly stated in this notice, no other rights or licenses, express or implied,
        are granted by Apple herein, including but not limited to any patent rights that
        may be infringed by your derivative works or by other works in which the Apple
        Software may be incorporated.

        The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
        WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
        WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
        PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
        COMBINATION WITH YOUR PRODUCTS.

        IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
        CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
        GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
        ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION AND/OR DISTRIBUTION
        OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER THEORY OF CONTRACT, TORT
        (INCLUDING NEGLIGENCE), STRICT LIABILITY OR OTHERWISE, EVEN IF APPLE HAS BEEN
        ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    Change History (most recent first):
        Fri, Jan 28, 2000 -- created
*/

#include "MacTextEditor.h"

/* part codes */

/* kmUPTextPart is the part code we return to indicate the user has clicked
    in the text area of our control */
#define kmUPTextPart 1

/* kmUPScrollPart is the part code we return to indicate the user has clicked
    in the scroll bar part of the control. */
#define kmUPScrollPart 2


/* routines for using existing user pane controls.
    These routines are useful for cases where you would like to use an
    existing user pane control in, say, a dialog window as a scrolling
    text edit field.*/
    
/* mUPOpenControl initializes a user pane control so it will be drawn
    and will behave as a scrolling text edit field inside of a window.
    This routine performs all of the initialization steps necessary,
    except it does not create the user pane control itself.  theControl
    should refer to a user pane control that you have either created
    yourself or extracted from a dialog's control heirarchy using
    the GetDialogItemAsControl routine.  */
OSStatus mUPOpenControl(ControlHandle theControl, bool multiline);

/* Utility Routines */

enum {
    kShiftKeyCode = 56
};

/* kUserClickedToFocusPart is a part code we pass to the SetKeyboardFocus
    routine.  In our focus switching routine this part code is understood
    as meaning 'the user has clicked in the control and we need to switch
    the current focus to ourselves before we can continue'. */
#define kUserClickedToFocusPart 100


/* kmUPClickScrollDelayTicks is a time measurement in ticks used to
    slow the speed of 'auto scrolling' inside of our clickloop routine.
    This value prevents the text from wizzzzzing by while the mouse
    is being held down inside of the text area. */
#define kmUPClickScrollDelayTicks 3


/* STPTextPaneVars is a structure used for storing the the mUP Control's
    internal variables and state information.  A handle to this record is
    stored in the pane control's reference value field using the
    SetControlReference routine. */

typedef struct {
        /* OS records referenced */
    TXNObject fTXNRec; /* the txn record */
    TXNFrameID fTXNFrame; /* the txn frame ID */
	bool fMultiline ;
    ControlHandle fUserPaneRec;  /* handle to the user pane control */
    WindowPtr fOwner; /* window containing control */
    GrafPtr fDrawingEnvironment; /* grafport where control is drawn */
        /* flags */
    Boolean fInFocus; /* true while the focus rect is drawn around the control */
    Boolean fIsActive; /* true while the control is drawn in the active state */
    Boolean fTEActive; /* reflects the activation state of the text edit record */ 
    Boolean fInDialogWindow; /* true if displayed in a dialog window */ 
        /* calculated locations */
    Rect fRTextArea; /* area where the text is drawn */
    Rect fRFocusOutline;  /* rectangle used to draw the focus box */
    Rect fRTextOutline; /* rectangle used to draw the border */
    RgnHandle fTextBackgroundRgn; /* background region for the text, erased before calling TEUpdate */
        /* our focus advance override routine */
    EventHandlerUPP handlerUPP;
    EventHandlerRef handlerRef;
} STPTextPaneVars;




/* Univerals Procedure Pointer variables used by the
    mUP Control.  These variables are set up
    the first time that mUPOpenControl is called. */
ControlUserPaneDrawUPP gTPDrawProc = NULL;
ControlUserPaneHitTestUPP gTPHitProc = NULL;
ControlUserPaneTrackingUPP gTPTrackProc = NULL;
ControlUserPaneIdleUPP gTPIdleProc = NULL;
ControlUserPaneKeyDownUPP gTPKeyProc = NULL;
ControlUserPaneActivateUPP gTPActivateProc = NULL;
ControlUserPaneFocusUPP gTPFocusProc = NULL;

    /* events handled by our focus advance override routine */
#if TARGET_CARBON
//static const EventTypeSpec gMLTEEvents[] = { { kEventClassTextInput, kEventUnicodeForKeyEvent } };
//#define kMLTEEventCount (sizeof( gMLTEEvents ) / sizeof( EventTypeSpec ))
#endif


/* TPActivatePaneText activates or deactivates the text edit record
    according to the value of setActive.  The primary purpose of this
    routine is to ensure each call is only made once. */
static void TPActivatePaneText(STPTextPaneVars **tpvars, Boolean setActive) {
    STPTextPaneVars *varsp;
    varsp = *tpvars;
    if (varsp->fTEActive != setActive) {
    
        varsp->fTEActive = setActive;
        
        TXNActivate(varsp->fTXNRec, varsp->fTXNFrame, varsp->fTEActive);
        
        if (varsp->fInFocus)
            TXNFocus( varsp->fTXNRec, varsp->fTEActive);
    }
}


/* TPFocusPaneText set the focus state for the text record. */
static void TPFocusPaneText(STPTextPaneVars **tpvars, Boolean setFocus) {
    STPTextPaneVars *varsp;
    varsp = *tpvars;
    if (varsp->fInFocus != setFocus) {
        varsp->fInFocus = setFocus;
        TXNFocus( varsp->fTXNRec, varsp->fInFocus);
    }
}


/* TPPaneDrawProc is called to redraw the control and for update events
    referring to the control.  This routine erases the text area's background,
    and redraws the text.  This routine assumes the scroll bar has been
    redrawn by a call to DrawControls. */
static pascal void TPPaneDrawProc(ControlRef theControl, ControlPartCode thePart) {
    STPTextPaneVars **tpvars, *varsp;
    char state;
    Rect bounds;
        /* set up our globals */
    tpvars = (STPTextPaneVars **) GetControlReference(theControl);
    if (tpvars != NULL) {
        state = HGetState((Handle) tpvars);
        HLock((Handle) tpvars);
        varsp = *tpvars;
            
            /* save the drawing state */
        SetPort((**tpvars).fDrawingEnvironment);
            /* verify our boundary */
        GetControlBounds(theControl, &bounds);
		if ( ! EqualRect(&bounds, &varsp->fRFocusOutline) ) {
		    // scrollbar is on the border, we add one
		    Rect oldbounds = varsp->fRFocusOutline ;
		    InsetRect( &oldbounds , -1 , -1 ) ;
		    
//		    InvalWindowRect( GetControlOwner( theControl ) , &oldbounds ) ;
			SetRect(&varsp->fRFocusOutline, bounds.left, bounds.top, bounds.right, bounds.bottom);
			SetRect(&varsp->fRTextOutline, bounds.left, bounds.top, bounds.right, bounds.bottom);
        	SetRect(&varsp->fRTextArea, bounds.left + 2 , bounds.top + (varsp->fMultiline ? 0 : 2) , 
        	    bounds.right - (varsp->fMultiline ? 0 : 2), bounds.bottom - (varsp->fMultiline ? 0 : 2));
            RectRgn(varsp->fTextBackgroundRgn, &varsp->fRTextOutline);
			TXNSetFrameBounds(  varsp->fTXNRec, varsp->fRTextArea.top, varsp->fRTextArea.left, 
			    varsp->fRTextArea.bottom, varsp->fRTextArea.right, varsp->fTXNFrame);
        }

            /* update the text region */
		RGBColor white = { 65535 , 65535 , 65535 } ;
		RGBBackColor( &white ) ;
        EraseRgn(varsp->fTextBackgroundRgn);
        TXNDraw(varsp->fTXNRec, NULL);
            /* restore the drawing environment */
            /* draw the text frame and focus frame (if necessary) */
        DrawThemeEditTextFrame(&varsp->fRTextOutline, varsp->fIsActive ? kThemeStateActive: kThemeStateInactive);
        if ((**tpvars).fIsActive && varsp->fInFocus) DrawThemeFocusRect(&varsp->fRFocusOutline, true);
            /* release our globals */
        HSetState((Handle) tpvars, state);
    }
}


/* TPPaneHitTestProc is called when the control manager would
    like to determine what part of the control the mouse resides over.
    We also call this routine from our tracking proc to determine how
    to handle mouse clicks. */
static pascal ControlPartCode TPPaneHitTestProc(ControlHandle theControl, Point where) {
    STPTextPaneVars **tpvars;
    ControlPartCode result;
    char state;
        /* set up our locals and lock down our globals*/
    result = 0;
    tpvars = (STPTextPaneVars **) GetControlReference(theControl);
    if (tpvars != NULL) {
        state = HGetState((Handle) tpvars);
        HLock((Handle) tpvars);
            /* find the region where we clicked */
        if (PtInRect(where, &(**tpvars).fRTextArea)) {
            result = kmUPTextPart;
        } else result = 0;
            /* release oure globals */
        HSetState((Handle) tpvars, state);
    }
    return result;
}





/* TPPaneTrackingProc is called when the mouse is being held down
    over our control.  This routine handles clicks in the text area
    and in the scroll bar. */
static pascal ControlPartCode TPPaneTrackingProc(ControlHandle theControl, Point startPt, ControlActionUPP actionProc) {
    STPTextPaneVars **tpvars, *varsp;
    char state;
    ControlPartCode partCodeResult;
        /* make sure we have some variables... */
    partCodeResult = 0;
    tpvars = (STPTextPaneVars **) GetControlReference(theControl);
    if (tpvars != NULL) {
            /* lock 'em down */
        state = HGetState((Handle) tpvars);
        HLock((Handle) tpvars);
        varsp = *tpvars;
            /* we don't do any of these functions unless we're in focus */
        if ( ! varsp->fInFocus) {
            WindowPtr owner;
            owner = GetControlOwner(theControl);
            ClearKeyboardFocus(owner);
            SetKeyboardFocus(owner, theControl, kUserClickedToFocusPart);
        }
            /* find the location for the click */
        switch (TPPaneHitTestProc(theControl, startPt)) {
                
                /* handle clicks in the text part */
            case kmUPTextPart:
                {   SetPort((**tpvars).fDrawingEnvironment);
                    TXNClick( varsp->fTXNRec, (const EventRecord*) wxTheApp->MacGetCurrentEvent());
                }
                break;
            
        }
        
        HSetState((Handle) tpvars, state);
    }
    return partCodeResult;
}


/* TPPaneIdleProc is our user pane idle routine.  When our text field
    is active and in focus, we use this routine to set the cursor. */
static pascal void TPPaneIdleProc(ControlHandle theControl) {
    STPTextPaneVars **tpvars, *varsp;
        /* set up locals */
    tpvars = (STPTextPaneVars **) GetControlReference(theControl);
    if (tpvars != NULL) {
            /* if we're not active, then we have nothing to say about the cursor */
        if ((**tpvars).fIsActive) {
            char state;
            Rect bounds;
            Point mousep;
                /* lock down the globals */
            state = HGetState((Handle) tpvars);
            HLock((Handle) tpvars);
            varsp = *tpvars;
                /* get the current mouse coordinates (in our window) */
            SetPortWindowPort(GetControlOwner(theControl));
            GetMouse(&mousep);
                /* there's a 'focus thing' and an 'unfocused thing' */
            if (varsp->fInFocus) {
                    /* flash the cursor */
                SetPort((**tpvars).fDrawingEnvironment);
                TXNIdle(varsp->fTXNRec);
                /* set the cursor */
                if (PtInRect(mousep, &varsp->fRTextArea)) {
                    RgnHandle theRgn;
                    RectRgn((theRgn = NewRgn()), &varsp->fRTextArea);
                    TXNAdjustCursor(varsp->fTXNRec, theRgn);
                    DisposeRgn(theRgn);
                 } else SetThemeCursor(kThemeArrowCursor);
            } else {
                /* if it's in our bounds, set the cursor */
                GetControlBounds(theControl, &bounds);
                if (PtInRect(mousep, &bounds))
                    SetThemeCursor(kThemeArrowCursor);
            }
            
            HSetState((Handle) tpvars, state);
        }
    }
}


/* TPPaneKeyDownProc is called whenever a keydown event is directed
    at our control.  Here, we direct the keydown event to the text
    edit record and redraw the scroll bar and text field as appropriate. */
static pascal ControlPartCode TPPaneKeyDownProc(ControlHandle theControl,
                            SInt16 keyCode, SInt16 charCode, SInt16 modifiers) {
    STPTextPaneVars **tpvars;
    tpvars = (STPTextPaneVars **) GetControlReference(theControl);
    if (tpvars != NULL) {
        if ((**tpvars).fInFocus) {
                /* turn autoscrolling on and send the key event to text edit */
            SetPort((**tpvars).fDrawingEnvironment);
            TXNKeyDown( (**tpvars).fTXNRec, (const EventRecord*) wxTheApp->MacGetCurrentEvent());
        }
    }
    return kControlEntireControl;
}


/* TPPaneActivateProc is called when the window containing
    the user pane control receives activate events. Here, we redraw
    the control and it's text as necessary for the activation state. */
static pascal void TPPaneActivateProc(ControlHandle theControl, Boolean activating) {
    Rect bounds;
    STPTextPaneVars **tpvars, *varsp;
    char state;
        /* set up locals */
    tpvars = (STPTextPaneVars **) GetControlReference(theControl);
    if (tpvars != NULL) {
        state = HGetState((Handle) tpvars);
        HLock((Handle) tpvars);
        varsp = *tpvars;
            /* de/activate the text edit record */
        SetPort((**tpvars).fDrawingEnvironment);
            GetControlBounds(theControl, &bounds);
            varsp->fIsActive = activating;
            TPActivatePaneText(tpvars, varsp->fIsActive && varsp->fInFocus);
            /* redraw the frame */
        DrawThemeEditTextFrame(&varsp->fRTextOutline, varsp->fIsActive ? kThemeStateActive: kThemeStateInactive);
        if (varsp->fInFocus) DrawThemeFocusRect(&varsp->fRFocusOutline, varsp->fIsActive);
        HSetState((Handle) tpvars, state);
    }
}


/* TPPaneFocusProc is called when every the focus changes to or
    from our control.  Herein, switch the focus appropriately
    according to the parameters and redraw the control as
    necessary.  */
static pascal ControlPartCode TPPaneFocusProc(ControlHandle theControl, ControlFocusPart action) {
    ControlPartCode focusResult;
    STPTextPaneVars **tpvars, *varsp;
    char state;
        /* set up locals */
    focusResult = kControlFocusNoPart;
    tpvars = (STPTextPaneVars **) GetControlReference(theControl);
    if (tpvars != NULL) {
        state = HGetState((Handle) tpvars);
        HLock((Handle) tpvars);
        varsp = *tpvars;
            /* if kControlFocusPrevPart and kControlFocusNextPart are received when the user is
            tabbing forwards (or shift tabbing backwards) through the items in the dialog,
            and kControlFocusNextPart will be received.  When the user clicks in our field
            and it is not the current focus, then the constant kUserClickedToFocusPart will
            be received.  The constant kControlFocusNoPart will be received when our control
            is the current focus and the user clicks in another control.  In your focus routine,
            you should respond to these codes as follows:

            kControlFocusNoPart - turn off focus and return kControlFocusNoPart.  redraw
                the control and the focus rectangle as necessary.

            kControlFocusPrevPart or kControlFocusNextPart - toggle focus on or off
                depending on its current state.  redraw the control and the focus rectangle
                as appropriate for the new focus state.  If the focus state is 'off', return the constant
                kControlFocusNoPart, otherwise return a non-zero part code.
            kUserClickedToFocusPart - is a constant defined for this example.  You should
                define your own value for handling click-to-focus type events. */
            /* save the drawing state */
        SetPort((**tpvars).fDrawingEnvironment);
            /* calculate the next highlight state */
        switch (action) {
            default:
            case kControlFocusNoPart:
                TPFocusPaneText(tpvars, false);
                focusResult = kControlFocusNoPart;
                break;
            case kUserClickedToFocusPart:
                TPFocusPaneText(tpvars, true);
                focusResult = 1;
                break;
            case kControlFocusPrevPart:
            case kControlFocusNextPart:
                TPFocusPaneText(tpvars, ( ! varsp->fInFocus));
                focusResult = varsp->fInFocus ? 1 : kControlFocusNoPart;
                break;
        }
            TPActivatePaneText(tpvars, varsp->fIsActive && varsp->fInFocus);
            /* redraw the text fram and focus rectangle to indicate the
            new focus state */
        DrawThemeEditTextFrame(&varsp->fRTextOutline, varsp->fIsActive ? kThemeStateActive: kThemeStateInactive);
        DrawThemeFocusRect(&varsp->fRFocusOutline, varsp->fIsActive && varsp->fInFocus);
            /* done */
        HSetState((Handle) tpvars, state);
    }
    return focusResult;
}

//This our carbon event handler for unicode key downs
#if TARGET_CARBON
static pascal OSStatus FocusAdvanceOverride(EventHandlerCallRef myHandler, EventRef event, void* userData) {
    WindowRef window;
    STPTextPaneVars **tpvars;
    OSStatus err;
    unsigned short mUnicodeText;
    ByteCount charCounts=0;
        /* get our window pointer */
    tpvars = (STPTextPaneVars **) userData;
    window = (**tpvars).fOwner;
        //find out how many bytes are needed
    err = GetEventParameter(event, kEventParamTextInputSendText,
                typeUnicodeText, NULL, 0, &charCounts, NULL);
    if (err != noErr) goto bail;
        /* we're only looking at single characters */
    if (charCounts != 2) { err = eventNotHandledErr; goto bail; }
        /* get the character */
    err = GetEventParameter(event, kEventParamTextInputSendText, 
                typeUnicodeText, NULL, sizeof(mUnicodeText),
                &charCounts, (char*) &mUnicodeText);
    if (err != noErr) goto bail;
        /* if it's not the tab key, forget it... */
    if ((mUnicodeText != '\t')) { err = eventNotHandledErr; goto bail; }
        /* advance the keyboard focus */
    AdvanceKeyboardFocus(window);
        /* noErr lets the CEM know we handled the event */
    return noErr;
bail:
    return eventNotHandledErr;
}
#endif


/* mUPOpenControl initializes a user pane control so it will be drawn
	and will behave as a scrolling text edit field inside of a window.
	This routine performs all of the initialization steps necessary,
	except it does not create the user pane control itself.  theControl
	should refer to a user pane control that you have either created
	yourself or extracted from a dialog's control heirarchy using
	the GetDialogItemAsControl routine.  */
OSStatus mUPOpenControl(ControlHandle theControl, bool multiline) 
{
	Rect bounds;
	WindowRef theWindow;
	STPTextPaneVars **tpvars, *varsp;
	OSStatus err;
	RGBColor rgbWhite = {0xFFFF, 0xFFFF, 0xFFFF};
	TXNBackground tback;
	
		/* set up our globals */
	if (gTPDrawProc == NULL) gTPDrawProc = NewControlUserPaneDrawUPP(TPPaneDrawProc);
	if (gTPHitProc == NULL) gTPHitProc = NewControlUserPaneHitTestUPP(TPPaneHitTestProc);
	if (gTPTrackProc == NULL) gTPTrackProc = NewControlUserPaneTrackingUPP(TPPaneTrackingProc);
	if (gTPIdleProc == NULL) gTPIdleProc = NewControlUserPaneIdleUPP(TPPaneIdleProc);
	if (gTPKeyProc == NULL) gTPKeyProc = NewControlUserPaneKeyDownUPP(TPPaneKeyDownProc);
	if (gTPActivateProc == NULL) gTPActivateProc = NewControlUserPaneActivateUPP(TPPaneActivateProc);
	if (gTPFocusProc == NULL) gTPFocusProc = NewControlUserPaneFocusUPP(TPPaneFocusProc);
		
		/* allocate our private storage */
	tpvars = (STPTextPaneVars **) NewHandleClear(sizeof(STPTextPaneVars));
	SetControlReference(theControl, (long) tpvars);
	HLock((Handle) tpvars);
	varsp = *tpvars;
		/* set the initial settings for our private data */
    varsp->fMultiline = multiline ;
	varsp->fInFocus = false;
	varsp->fIsActive = true;
	varsp->fTEActive = true; // in order to get a deactivate
	varsp->fUserPaneRec = theControl;
	theWindow = varsp->fOwner = GetControlOwner(theControl);

    varsp->fDrawingEnvironment = (GrafPtr)  GetWindowPort(theWindow);

    varsp->fInDialogWindow = ( GetWindowKind(varsp->fOwner) == kDialogWindowKind );
        /* set up the user pane procedures */
    SetControlData(theControl, kControlEntireControl, kControlUserPaneDrawProcTag, sizeof(gTPDrawProc), &gTPDrawProc);
    SetControlData(theControl, kControlEntireControl, kControlUserPaneHitTestProcTag, sizeof(gTPHitProc), &gTPHitProc);
    SetControlData(theControl, kControlEntireControl, kControlUserPaneTrackingProcTag, sizeof(gTPTrackProc), &gTPTrackProc);
    SetControlData(theControl, kControlEntireControl, kControlUserPaneIdleProcTag, sizeof(gTPIdleProc), &gTPIdleProc);
    SetControlData(theControl, kControlEntireControl, kControlUserPaneKeyDownProcTag, sizeof(gTPKeyProc), &gTPKeyProc);
    SetControlData(theControl, kControlEntireControl, kControlUserPaneActivateProcTag, sizeof(gTPActivateProc), &gTPActivateProc);
    SetControlData(theControl, kControlEntireControl, kControlUserPaneFocusProcTag, sizeof(gTPFocusProc), &gTPFocusProc);
        /* calculate the rectangles used by the control */
    GetControlBounds(theControl, &bounds);
    SetRect(&varsp->fRFocusOutline, bounds.left, bounds.top, bounds.right, bounds.bottom);
    SetRect(&varsp->fRTextOutline, bounds.left, bounds.top, bounds.right, bounds.bottom);
    SetRect(&varsp->fRTextArea, bounds.left + 2 , bounds.top + (varsp->fMultiline ? 0 : 2) , 
        bounds.right - (varsp->fMultiline ? 0 : 2), bounds.bottom - (varsp->fMultiline ? 0 : 2));
        /* calculate the background region for the text.  In this case, it's kindof
        and irregular region because we're setting the scroll bar a little ways inside
        of the text area. */
    RectRgn((varsp->fTextBackgroundRgn = NewRgn()), &varsp->fRTextOutline);

        /* set up the drawing environment */
    SetPort(varsp->fDrawingEnvironment);

        /* create the new edit field */
    TXNNewObject(NULL, varsp->fOwner, &varsp->fRTextArea,
	  ( multiline ? kTXNWantVScrollBarMask : 0 )
		 | kTXNAlwaysWrapAtViewEdgeMask,
        kTXNTextEditStyleFrameType,
        kTXNTextensionFile,
        kTXNSystemDefaultEncoding, 
        &varsp->fTXNRec, &varsp->fTXNFrame, (TXNObjectRefcon) tpvars);

		/* set the field's font and style */
		TXNTypeAttributes typeAttr[2];
    typeAttr[0].tag = kTXNQDFontSizeAttribute;
    typeAttr[0].size = kTXNFontSizeAttributeSize;
    typeAttr[0].data.dataValue = 10 << 16;		

    typeAttr[1].tag = kTXNQDFontStyleAttribute;
    typeAttr[1].size = kTXNQDFontStyleAttributeSize;
    typeAttr[1].data.dataValue = normal ;		

		/* this does not seem to get the font id through
    typeAttr[2].tag = kTXNQDFontFamilyIDAttribute ; // NameAttribute;
    typeAttr[2].size = kTXNQDFontFamilyIDAttributeSize ; // kTXNQDFontNameAttributeSize;
    typeAttr[2].data.dataValue = kFontIDTimes ; // (void*) "\pGeneva" ;		
     */

    OSStatus status = TXNSetTypeAttributes (varsp->fTXNRec, sizeof( typeAttr ) / sizeof(TXNTypeAttributes) , typeAttr,
      kTXNStartOffset,
      kTXNEndOffset);
        /* set the field's background */
    tback.bgType = kTXNBackgroundTypeRGB;
    tback.bg.color = rgbWhite;
    TXNSetBackground( varsp->fTXNRec, &tback);

        /* install our focus advance override routine */
#if TARGET_CARBON
//	varsp->handlerUPP = NewEventHandlerUPP(FocusAdvanceOverride);
//	err = InstallWindowEventHandler( varsp->fOwner, varsp->handlerUPP,
//		kMLTEEventCount, gMLTEEvents, tpvars, &varsp->handlerRef );
#endif
		
        /* unlock our storage */
    HUnlock((Handle) tpvars);
        /* perform final activations and setup for our text field.  Here,
        we assume that the window is going to be the 'active' window. */
    TPActivatePaneText(tpvars, varsp->fIsActive && varsp->fInFocus);
        /* all done */
    return noErr;
}




#if !USE_SHARED_LIBRARY
IMPLEMENT_DYNAMIC_CLASS(wxTextCtrl, wxControl)

BEGIN_EVENT_TABLE(wxTextCtrl, wxControl)
    EVT_DROP_FILES(wxTextCtrl::OnDropFiles)
    EVT_CHAR(wxTextCtrl::OnChar)
    EVT_MENU(wxID_CUT, wxTextCtrl::OnCut)
    EVT_MENU(wxID_COPY, wxTextCtrl::OnCopy)
    EVT_MENU(wxID_PASTE, wxTextCtrl::OnPaste)
    EVT_MENU(wxID_UNDO, wxTextCtrl::OnUndo)
    EVT_MENU(wxID_REDO, wxTextCtrl::OnRedo)

    EVT_UPDATE_UI(wxID_CUT, wxTextCtrl::OnUpdateCut)
    EVT_UPDATE_UI(wxID_COPY, wxTextCtrl::OnUpdateCopy)
    EVT_UPDATE_UI(wxID_PASTE, wxTextCtrl::OnUpdatePaste)
    EVT_UPDATE_UI(wxID_UNDO, wxTextCtrl::OnUpdateUndo)
    EVT_UPDATE_UI(wxID_REDO, wxTextCtrl::OnUpdateRedo)
END_EVENT_TABLE()
#endif

// Text item
wxTextCtrl::wxTextCtrl()
{
  ((TEHandle) m_macTE) = NULL ;
  ((TXNObject) m_macTXN) = NULL ;
  m_macUsesTXN = false ;
  m_editable = true ;
}

wxTextCtrl::~wxTextCtrl()
{
    if ( m_macUsesTXN )
    {
        TXNDeleteObject((TXNObject)m_macTXN);
    #if TARGET_CARBON
            /* remove our focus advance override */
    //    RemoveEventHandler((**tpvars).handlerRef);
    //    DisposeEventHandlerUPP((**tpvars).handlerUPP);
    #endif
        /* delete our private storage */
        DisposeHandle((Handle) m_macTXNvars);
        /* zero the control reference */
        SetControlReference((ControlHandle)m_macControl, 0) ;
    }
}

const short kVerticalMargin = 2 ;
const short kHorizontalMargin = 2 ;

bool wxTextCtrl::Create(wxWindow *parent, wxWindowID id,
           const wxString& st,
           const wxPoint& pos,
           const wxSize& size, long style,
           const wxValidator& validator,
           const wxString& name)
{
  ((TEHandle) m_macTE) = NULL ;
  ((TXNObject) m_macTXN) = NULL ;
  m_macUsesTXN = false ;
  m_editable = true ;

  m_macUsesTXN = ! (style & wxTE_PASSWORD ) ; 

  m_macUsesTXN &= (TXNInitTextension != (void*) kUnresolvedCFragSymbolAddress) ;
    
    // base initialization
    if ( !CreateBase(parent, id, pos, size, style, validator, name) )
        return FALSE;

    wxSize mySize = size ;
	if ( m_macUsesTXN )
	{
		m_macHorizontalBorder = 5 ; // additional pixels around the real control
		m_macVerticalBorder = 3 ;
	}
	else
    {
        m_macHorizontalBorder = 5 ; // additional pixels around the real control
        m_macVerticalBorder = 5 ;
    }


    Rect bounds ;
    Str255 title ;

    if ( mySize.y == -1 )
    {
		if ( !m_macUsesTXN )
            mySize.y = 13 ;
        else
			mySize.y = 16 ;
        
        mySize.y += 2 * m_macVerticalBorder ;
    }

    MacPreControlCreate( parent , id ,  "" , pos , mySize ,style, validator , name , &bounds , title ) ;

    if ( m_windowStyle & wxTE_MULTILINE )
    {
        wxASSERT_MSG( !(m_windowStyle & wxTE_PROCESS_ENTER),
                      wxT("wxTE_PROCESS_ENTER style is ignored for multiline text controls (they always process it)") );

        m_windowStyle |= wxTE_PROCESS_ENTER;
    }


    if ( !m_macUsesTXN )
    {
	    m_macControl = ::NewControl( (GrafPtr) parent->MacGetRootWindow() , &bounds , "\p" , true , 0 , 0 , 1, 
	  	    (style & wxTE_PASSWORD) ? kControlEditTextPasswordProc : kControlEditTextProc , (long) this ) ;
	  	long size ;
        ::GetControlData((ControlHandle)  m_macControl , 0, kControlEditTextTEHandleTag , sizeof( TEHandle ) , (char*) &((TEHandle) m_macTE) , &size ) ;

    }
	else
	{
        short featurSet;

        featurSet = kControlSupportsEmbedding | kControlSupportsFocus | kControlWantsIdle
                | kControlWantsActivate | kControlHandlesTracking | kControlHasSpecialBackground
                | kControlGetsFocusOnClick | kControlSupportsLiveFeedback;
            /* create the control */
        m_macControl = NewControl((GrafPtr) parent->MacGetRootWindow(), &bounds, "\p", true, featurSet, 0, featurSet, kControlUserPaneProc, 0);
            /* set up the mUP specific features and data */
    	mUPOpenControl((ControlHandle) m_macControl, m_windowStyle & wxTE_MULTILINE );
	}
    MacPostControlCreate() ;

    wxString value ;
    
	if( wxApp::s_macDefaultEncodingIsPC )
		value = wxMacMakeMacStringFromPC( st ) ;
	else
		value = st ;
		
	if ( !m_macUsesTXN )
	{
	    ::SetControlData( (ControlHandle) m_macControl, 0, ( m_windowStyle & wxTE_PASSWORD ) ? kControlEditTextPasswordTag : kControlEditTextTextTag , value.Length() , (char*) ((const char*)value) ) ;
    }
    else
    {
        STPTextPaneVars **tpvars;
        	/* set up locals */
        tpvars = (STPTextPaneVars **) GetControlReference((ControlHandle) m_macControl);
        	/* set the text in the record */
        TXNSetData( (**tpvars).fTXNRec, kTXNTextData,  (void*)value.c_str(), value.Length(),
          kTXNStartOffset, kTXNEndOffset);
        m_macTXN =  (**tpvars).fTXNRec ;
        m_macTXNvars = tpvars ;
        m_macUsesTXN = true ;
    }
  
  return TRUE;
}

wxString wxTextCtrl::GetValue() const
{
    Size actualsize;
     if ( !m_macUsesTXN )
     {
      ::GetControlData( (ControlHandle) m_macControl, 0, ( m_windowStyle & wxTE_PASSWORD ) ? kControlEditTextPasswordTag : kControlEditTextTextTag , 32767 , wxBuffer , &actualsize) ;
     }
     else
     {
     	Handle theText ;
     	OSStatus err = TXNGetDataEncoded( ((TXNObject) m_macTXN), kTXNStartOffset, kTXNEndOffset, &theText , kTXNTextData );
     		/* all done */
     	if ( err )
     	{
     	  actualsize = 0 ;
     	}
     	else
     	{
     	  actualsize = GetHandleSize( theText ) ;
     	  strncpy( wxBuffer , *theText , actualsize ) ;
     	  DisposeHandle( theText ) ;
     	}
     }
    wxBuffer[actualsize] = 0 ;
    if( wxApp::s_macDefaultEncodingIsPC )
        return wxMacMakePCStringFromMac( wxBuffer ) ;
    else
        return wxString(wxBuffer);
}

void wxTextCtrl::GetSelection(long* from, long* to) const
{
  if ( !m_macUsesTXN )
  {
    *from = (**((TEHandle) m_macTE)).selStart;
    *to = (**((TEHandle) m_macTE)).selEnd;
   }
   else
   {
        TXNGetSelection(  ((TXNObject) m_macTXN) , (TXNOffset*) from , (TXNOffset*) to ) ;
   }
}

void wxTextCtrl::SetValue(const wxString& st)
{
    wxString value ;
    
    if( wxApp::s_macDefaultEncodingIsPC )
        value = wxMacMakeMacStringFromPC( st ) ;
    else
        value = st ;
  if ( !m_macUsesTXN )
  {
	  ::SetControlData((ControlHandle)  m_macControl, 0, ( m_windowStyle & wxTE_PASSWORD ) ? kControlEditTextPasswordTag : kControlEditTextTextTag , value.Length() , (char*) ((const char*)value) ) ;
  }
  else
  {
  	TXNSetData( ((TXNObject) m_macTXN), kTXNTextData,  (void*)value.c_str(), value.Length(),
  	  kTXNStartOffset, kTXNEndOffset);
  }
    MacRedrawControl() ;
}

// Clipboard operations
void wxTextCtrl::Copy()
{
    if (CanCopy())
    {
      if ( !m_macUsesTXN )
      {
    		TECopy( ((TEHandle) m_macTE) ) ;
    		ClearCurrentScrap();
    		TEToScrap() ;
      		MacRedrawControl() ;
    	}
    	else
    	{
            ClearCurrentScrap();
            TXNCopy((TXNObject)m_macTXN); 
            TXNConvertToPublicScrap();
    	}
    }
}

void wxTextCtrl::Cut()
{
    if (CanCut())
    {
        if ( !m_macUsesTXN )
        {
    		TECut( ((TEHandle) m_macTE) ) ;
    		ClearCurrentScrap();
    		TEToScrap() ;
      		MacRedrawControl() ;
        }
    	else
    	{
            ClearCurrentScrap();
            TXNCut((TXNObject)m_macTXN); 
            TXNConvertToPublicScrap();
    	}
        wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, m_windowId);
        event.SetString( GetValue() ) ;
        event.SetEventObject( this );
        GetEventHandler()->ProcessEvent(event);
	  }
}

void wxTextCtrl::Paste()
{
    if (CanPaste())
    {
        if ( !m_macUsesTXN )
        {
            TEFromScrap() ;
            TEPaste( (TEHandle) m_macTE ) ;
            MacRedrawControl() ;
        }
       	else
       	{
            TXNConvertFromPublicScrap();
            TXNPaste((TXNObject)m_macTXN); 
       	}
        wxCommandEvent event(wxEVT_COMMAND_TEXT_UPDATED, m_windowId);
        event.SetString( GetValue() ) ;
        event.SetEventObject( this );
        GetEventHandler()->ProcessEvent(event);
    }
}

bool wxTextCtrl::CanCopy() const
{
    // Can copy if there's a selection
    long from, to;
    GetSelection(& from, & to);
    return (from != to);
}

bool wxTextCtrl::CanCut() const
{
    if ( !IsEditable() )
    {
        return false ;
    }
    // Can cut if there's a selection
    long from, to;
    GetSelection(& from, & to);
    return (from != to);
}

bool wxTextCtrl::CanPaste() const
{
    if (!IsEditable())
        return FALSE;

    long offset ;
#if TARGET_CARBON
    OSStatus err = noErr;
    ScrapRef scrapRef;
    
    err = GetCurrentScrap( &scrapRef );
    if ( err != noTypeErr && err != memFullErr )    
    {
		ScrapFlavorFlags	flavorFlags;
		Size				byteCount;
        
        if (( err = GetScrapFlavorFlags( scrapRef, 'TEXT', &flavorFlags )) == noErr)
        {
            if (( err = GetScrapFlavorSize( scrapRef, 'TEXT', &byteCount )) == noErr)
            {
                return TRUE ;
            }
        }
    }
    return FALSE;
    
#else
    if ( GetScrap( NULL , 'TEXT' , &offset ) > 0 )
    {
        return TRUE ;
    }
#endif
    return FALSE ;
}

void wxTextCtrl::SetEditable(bool editable)
{
    if ( editable != m_editable )
    {
        m_editable = editable ;
    if ( editable )
        	UMAActivateControl( (ControlHandle) m_macControl ) ;
        else
        	UMADeactivateControl((ControlHandle)  m_macControl ) ;
    }
}

void wxTextCtrl::SetInsertionPoint(long pos)
{
    SetSelection( pos , pos ) ;
}

void wxTextCtrl::SetInsertionPointEnd()
{
    long pos = GetLastPosition();
    SetInsertionPoint(pos);
}

long wxTextCtrl::GetInsertionPoint() const
{
  long begin,end ;
  GetSelection( &begin , &end ) ;
  return begin ;
}

long wxTextCtrl::GetLastPosition() const
{
    if ( !m_macUsesTXN )
  {
    return (**((TEHandle) m_macTE)).teLength ;
  }
  else
  {
    Handle theText ;
    long actualsize ;
    OSErr err = TXNGetDataEncoded( (TXNObject) m_macTXN, kTXNStartOffset, kTXNEndOffset, &theText , kTXNTextData );
        /* all done */
    if ( err )
    {
      actualsize = 0 ;
    }
    else
    {
      actualsize = GetHandleSize( theText ) ;
      DisposeHandle( theText ) ;
    }
    return actualsize ;
  }
}

void wxTextCtrl::Replace(long from, long to, const wxString& value)
{
  if ( !m_macUsesTXN )
  {
   	    ControlEditTextSelectionRec selection ;
   
   	    selection.selStart = from ;
   	    selection.selEnd = to ;
   	    ::SetControlData((ControlHandle)  m_macControl , 0, kControlEditTextSelectionTag , sizeof( selection ) , (char*) &selection ) ;
   	    TESetSelect( from , to  , ((TEHandle) m_macTE) ) ;
   	    TEDelete( ((TEHandle) m_macTE) ) ;
		TEInsert( value , value.Length() , ((TEHandle) m_macTE) ) ;
	}
	else
	{
	  TXNSetSelection( ((TXNObject) m_macTXN) , from , to ) ;
	  TXNClear( ((TXNObject) m_macTXN) ) ;
  	  TXNSetData( ((TXNObject) m_macTXN), kTXNTextData,  (void*)value.c_str(), value.Length(),
  	    kTXNUseCurrentSelection, kTXNUseCurrentSelection);
	}
    Refresh() ;
}

void wxTextCtrl::Remove(long from, long to)
{
  if ( !m_macUsesTXN )
  {
   	ControlEditTextSelectionRec selection ;
   
   	selection.selStart = from ;
   	selection.selEnd = to ;
   	::SetControlData( (ControlHandle) m_macControl , 0, kControlEditTextSelectionTag , sizeof( selection ) , (char*) &selection ) ;
   	TEDelete( ((TEHandle) m_macTE) ) ;
  }
  else
  {
    TXNSetSelection( ((TXNObject) m_macTXN) , from , to ) ; 
    TXNClear( ((TXNObject) m_macTXN) ) ; 
  }
    Refresh() ;
}

void wxTextCtrl::SetSelection(long from, long to)
{

  if ( !m_macUsesTXN )
  {
   ControlEditTextSelectionRec selection ;
   selection.selStart = from ;
   selection.selEnd = to ;
   
   TESetSelect( selection.selStart , selection.selEnd , ((TEHandle) m_macTE) ) ;
   ::SetControlData((ControlHandle)  m_macControl , 0, kControlEditTextSelectionTag , sizeof( selection ) , (char*) &selection ) ;
  }
  else
  {
  	STPTextPaneVars **tpvars;
  		/* set up our locals */
  	tpvars = (STPTextPaneVars **) GetControlReference((ControlHandle) m_macControl);
  		/* and our drawing environment as the operation
  		may force a redraw in the text area. */
  	SetPort((**tpvars).fDrawingEnvironment);
  		/* change the selection */
  	TXNSetSelection( (**tpvars).fTXNRec, from, to);
  }
}

bool wxTextCtrl::LoadFile(const wxString& file)
{
    if ( wxTextCtrlBase::LoadFile(file) )
    {
        return TRUE;
    }

    return FALSE;
}

void wxTextCtrl::WriteText(const wxString& text)
{
    wxString value ;
  	if( wxApp::s_macDefaultEncodingIsPC )
  		value = wxMacMakeMacStringFromPC( text ) ;
  	else
  		value = text ;
    if ( !m_macUsesTXN )
    {
  		TEInsert( value , value.Length() , ((TEHandle) m_macTE) ) ;
	}
	else
	{
    	TXNSetData( ((TXNObject) m_macTXN), kTXNTextData,  (const char*)value, value.Length(),
    	  kTXNUseCurrentSelection, kTXNUseCurrentSelection);
	}
	MacRedrawControl() ;
}

void wxTextCtrl::AppendText(const wxString& text)
{
    SetInsertionPointEnd();
    WriteText(text);
}

void wxTextCtrl::Clear()
{
    if ( !IsEditable() )
    {
        return ;
    }
  if ( !m_macUsesTXN )
  {
	::SetControlData((ControlHandle)  m_macControl, 0, ( m_windowStyle & wxTE_PASSWORD ) ? kControlEditTextPasswordTag : kControlEditTextTextTag , 0 , (char*) ((const char*)NULL) ) ;
  }
  else
  {
            ClearCurrentScrap();
            TXNClear((TXNObject)m_macTXN); 
  }
    Refresh() ;
}

bool wxTextCtrl::IsModified() const
{
    return TRUE;
}

bool wxTextCtrl::IsEditable() const
{
    return IsEnabled() && m_editable ;
}

bool wxTextCtrl::AcceptsFocus() const
{
    // we don't want focus if we can't be edited
    return /*IsEditable() && */ wxControl::AcceptsFocus();
}

wxSize wxTextCtrl::DoGetBestSize() const
{
    int wText = 100 ;
    
    int hText ;
        if ( UMAHasAppearance() )
            hText = 13 ;
        else
            hText = 24 ;
    hText += 2 * m_macHorizontalBorder ;
/*
    int cx, cy;
    wxGetCharSize(GetHWND(), &cx, &cy, &GetFont());

    int wText = DEFAULT_ITEM_WIDTH;

    int hText = EDIT_HEIGHT_FROM_CHAR_HEIGHT(cy);

    return wxSize(wText, hText);
*/
    if ( m_windowStyle & wxTE_MULTILINE )
    {
        hText *= wxMin(GetNumberOfLines(), 5);
    }
    //else: for single line control everything is ok
    return wxSize(wText, hText);
}

// ----------------------------------------------------------------------------
// Undo/redo
// ----------------------------------------------------------------------------

void wxTextCtrl::Undo()
{
    if (CanUndo())
    {
    }
}

void wxTextCtrl::Redo()
{
    if (CanRedo())
    {
    }
}

bool wxTextCtrl::CanUndo() const
{
    return FALSE ;
}

bool wxTextCtrl::CanRedo() const
{
    return FALSE ;
}

// Makes 'unmodified'
void wxTextCtrl::DiscardEdits()
{
    // TODO
}

int wxTextCtrl::GetNumberOfLines() const
{
  // TODO change this if possible to reflect real lines
  wxString content = GetValue() ;
    
    int count = 1;
	for (int i = 0; i < content.Length() ; i++)
	{
	    if (content[i] == '\r') count++;
    }
    
    return count;
}

long wxTextCtrl::XYToPosition(long x, long y) const
{
    // TODO
    return 0;
}

bool wxTextCtrl::PositionToXY(long pos, long *x, long *y) const
{
    return FALSE ;
}

void wxTextCtrl::ShowPosition(long pos)
{
    // TODO
}

int wxTextCtrl::GetLineLength(long lineNo) const
{
  // TODO change this if possible to reflect real lines
  wxString content = GetValue() ;
	
	// Find line first
	int count = 0;
	for (int i = 0; i < content.Length() ; i++)
    {
        if (count == lineNo)
        {
            // Count chars in line then
            count = 0;
	    	for (int j = i; j < content.Length(); j++)
            {
                count++;
	    	    if (content[j] == '\r') return count;
	    	}
	    	
	    	return count;
	    }
	    if (content[i] == '\r') count++;
	}
    return 0;
}

wxString wxTextCtrl::GetLineText(long lineNo) const
{
  // TODO change this if possible to reflect real lines
  wxString content = GetValue() ;

	// Find line first
	int count = 0;
	for (int i = 0; i < content.Length() ; i++)
    {
        if (count == lineNo)
        {
            // Add chars in line then
            wxString tmp("");
            
	    	for (int j = i; j < content.Length(); j++)
	    	{
	    	    if (content[j] == '\r')
	    	        return tmp;
	    	        
	    	    tmp += content[j];
	    	}
	    	
	    	return tmp;
	    }
	    if (content[i] == '\r') count++;
	}
}

/*
 * Text item
 */
 
void wxTextCtrl::Command(wxCommandEvent & event)
{
    SetValue (event.GetString());
    ProcessCommand (event);
}

void wxTextCtrl::OnDropFiles(wxDropFilesEvent& event)
{
    // By default, load the first file into the text window.
    if (event.GetNumberOfFiles() > 0)
    {
        LoadFile(event.GetFiles()[0]);
    }
}

void wxTextCtrl::OnChar(wxKeyEvent& event)
{
    int key = event.GetKeyCode() ;
    bool eat_key = false ;
    
    if ( !IsEditable() && key != WXK_LEFT && key != WXK_RIGHT && key != WXK_DOWN && key != WXK_UP && key != WXK_TAB && 
        !( key == WXK_RETURN && ( (m_windowStyle & wxPROCESS_ENTER) || (m_windowStyle & wxTE_MULTILINE) ) ) 
/*        && key != WXK_PRIOR && key != WXK_NEXT && key != WXK_HOME && key != WXK_END */
        )
    {
        // eat it
        return ;
    }
    switch ( key )
    {
        case WXK_RETURN:
            if (m_windowStyle & wxPROCESS_ENTER)
            {
                wxCommandEvent event(wxEVT_COMMAND_TEXT_ENTER, m_windowId);
                event.SetEventObject( this );
                event.SetString( GetValue() );
                if ( GetEventHandler()->ProcessEvent(event) )
                    return;
            } 
            if ( !(m_windowStyle & wxTE_MULTILINE) )
            {
                wxWindow *parent = GetParent();
                while( parent && !parent->IsTopLevel() && parent->GetDefaultItem() == NULL ) {
                  parent = parent->GetParent() ;
                }
                if ( parent && parent->GetDefaultItem() )
                {
                    wxButton *def = wxDynamicCast(parent->GetDefaultItem(),
                                                          wxButton);
                    if ( def && def->IsEnabled() )
                    {
                        wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, def->GetId() );
                        event.SetEventObject(def);
                        def->Command(event);
                        return ;
                   }
                }
               
                // this will make wxWindows eat the ENTER key so that
                // we actually prevent line wrapping in a single line
                // text control
                eat_key = TRUE;
            }

            break;

        case WXK_TAB:
            // always produce navigation event - even if we process TAB
            // ourselves the fact that we got here means that the user code
            // decided to skip processing of this TAB - probably to let it
            // do its default job.
            {
                wxNavigationKeyEvent eventNav;
                eventNav.SetDirection(!event.ShiftDown());
                eventNav.SetWindowChange(event.ControlDown());
                eventNav.SetEventObject(this);

                if ( GetParent()->GetEventHandler()->ProcessEvent(eventNav) )
                    return;

                event.Skip() ;
                return;
            }
            break;
    }
    
    EventRecord *ev = (EventRecord*) wxTheApp->MacGetCurrentEvent();
    short keychar = short(ev->message & charCodeMask);
    if (!eat_key)
    {
        short keycode = short(ev->message & keyCodeMask) >> 8 ;
        ::HandleControlKey( (ControlHandle) m_macControl , keycode , keychar , ev->modifiers );
    }
    if ( keychar >= 0x20 ||
         event.KeyCode() == WXK_RETURN ||
         event.KeyCode() == WXK_DELETE || 
         event.KeyCode() == WXK_BACK)
    {
        wxCommandEvent event1(wxEVT_COMMAND_TEXT_UPDATED, m_windowId);
        event1.SetString( GetValue() ) ;
        event1.SetEventObject( this );
        GetEventHandler()->ProcessEvent(event1);
    }
}

// ----------------------------------------------------------------------------
// standard handlers for standard edit menu events
// ----------------------------------------------------------------------------

void wxTextCtrl::OnCut(wxCommandEvent& event)
{
    Cut();
}

void wxTextCtrl::OnCopy(wxCommandEvent& event)
{
    Copy();
}

void wxTextCtrl::OnPaste(wxCommandEvent& event)
{
    Paste();
}

void wxTextCtrl::OnUndo(wxCommandEvent& event)
{
    Undo();
}

void wxTextCtrl::OnRedo(wxCommandEvent& event)
{
    Redo();
}

void wxTextCtrl::OnUpdateCut(wxUpdateUIEvent& event)
{
    event.Enable( CanCut() );
}

void wxTextCtrl::OnUpdateCopy(wxUpdateUIEvent& event)
{
    event.Enable( CanCopy() );
}

void wxTextCtrl::OnUpdatePaste(wxUpdateUIEvent& event)
{
    event.Enable( CanPaste() );
}

void wxTextCtrl::OnUpdateUndo(wxUpdateUIEvent& event)
{
    event.Enable( CanUndo() );
}

void wxTextCtrl::OnUpdateRedo(wxUpdateUIEvent& event)
{
    event.Enable( CanRedo() );
}



#endif
    // wxUSE_TEXTCTRL
