/////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/button.h
// Purpose:     wxButton class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_BUTTON_H_
#define _WX_BUTTON_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "button.h"
#endif

// ----------------------------------------------------------------------------
// Pushbutton
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxButton : public wxButtonBase
{
public:
    wxButton() { }
    wxButton(wxWindow *parent,
             wxWindowID id,
             const wxString& label,
             const wxPoint& pos = wxDefaultPosition,
             const wxSize& size = wxDefaultSize,
             long style = 0,
             const wxValidator& validator = wxDefaultValidator,
             const wxString& name = wxButtonNameStr)
    {
        Create(parent, id, label, pos, size, style, validator, name);
    }
    
    wxButton(wxWindow *parent, wxWindowID id, wxStockItemID stock,
           const wxString& descriptiveLabel = wxEmptyString,
           const wxPoint& pos = wxDefaultPosition,
           long style = 0,
           const wxValidator& validator = wxDefaultValidator,
           const wxString& name = wxButtonNameStr)
    {
        Create(parent, id, stock, descriptiveLabel, pos, style, validator, name);
    }
  
    bool Create(wxWindow *parent, wxWindowID id, wxStockItemID stock,
           const wxString& descriptiveLabel = wxEmptyString,
           const wxPoint& pos = wxDefaultPosition,
           long style = 0,
           const wxValidator& validator = wxDefaultValidator,
           const wxString& name = wxButtonNameStr)
    {
        return CreateStock(parent, id, stock, descriptiveLabel,
                           pos, style, validator, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxString& label,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& validator = wxDefaultValidator,
                const wxString& name = wxButtonNameStr);

    virtual ~wxButton();

    virtual void SetDefault();

    // implementation from now on
    virtual void Command(wxCommandEvent& event);
    virtual WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam);
    virtual bool MSWCommand(WXUINT param, WXWORD id);

    virtual void ApplyParentThemeBackground(const wxColour& bg)
    {
        // avoide switching into owner-drawn mode
        wxControl::SetBackgroundColour(bg);
    }
    
#ifdef __WIN32__
    // coloured buttons support
    virtual bool SetBackgroundColour(const wxColour &colour);
    virtual bool SetForegroundColour(const wxColour &colour);

    virtual bool MSWOnDraw(WXDRAWITEMSTRUCT *item);

private:
    void MakeOwnerDrawn();
#endif // __WIN32__

protected:
    // send a notification event, return TRUE if processed
    bool SendClickEvent();

    // default button handling
    void SetTmpDefault();
    void UnsetTmpDefault();

    // set or unset BS_DEFPUSHBUTTON style
    static void SetDefaultStyle(wxButton *btn, bool on);

    // usually overridden base class virtuals
    virtual wxSize DoGetBestSize() const;
    virtual WXDWORD MSWGetStyle(long style, WXDWORD *exstyle) const ;

private:
    DECLARE_DYNAMIC_CLASS_NO_COPY(wxButton)
};

#endif
    // _WX_BUTTON_H_
