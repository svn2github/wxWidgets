/////////////////////////////////////////////////////////////////////////////
// Name:        cursor.h
// Purpose:     wxCursor class
// Author:      Julian Smart
// Modified by:
// Created:     01/02/97
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:   	wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __CURSORH__
#define __CURSORH__

#ifdef __GNUG__
#pragma interface "cursor.h"
#endif

#include "wx/bitmap.h"

class WXDLLEXPORT wxCursorRefData: public wxBitmapRefData
{
    friend class WXDLLEXPORT wxBitmap;
    friend class WXDLLEXPORT wxCursor;
public:
    wxCursorRefData(void);
    ~wxCursorRefData(void);

protected:
  WXHCURSOR m_hCursor;
  bool m_destroyCursor;
};

#define M_CURSORDATA ((wxCursorRefData *)m_refData)
#define M_CURSORHANDLERDATA ((wxCursorRefData *)bitmap->m_refData)

// Cursor
class WXDLLEXPORT wxCursor: public wxBitmap
{
  DECLARE_DYNAMIC_CLASS(wxCursor)

public:
  wxCursor(void);

  // Copy constructors
  inline wxCursor(const wxCursor& cursor) { Ref(cursor); }
  inline wxCursor(const wxCursor* cursor) { /* UnRef(); */ if (cursor) Ref(*cursor); }

  wxCursor(const char bits[], const int width, const int height, const int hotSpotX = -1, const int hotSpotY = -1,
    const char maskBits[] = NULL);
  wxCursor(const wxString& name, const long flags = wxBITMAP_TYPE_CUR_RESOURCE,
   const int hotSpotX = 0, const int hotSpotY = 0);
  wxCursor(const int cursor_type);
  ~wxCursor(void);

  virtual bool Ok(void) const { return (m_refData != NULL && M_CURSORDATA->m_hCursor) ; }

  inline wxCursor& operator = (const wxCursor& cursor) { if (*this == cursor) return (*this); Ref(cursor); return *this; }
  inline bool operator == (const wxCursor& cursor) { return m_refData == cursor.m_refData; }
  inline bool operator != (const wxCursor& cursor) { return m_refData != cursor.m_refData; }

  void SetHCURSOR(WXHCURSOR cursor);
  inline WXHCURSOR GetHCURSOR(void) const { return (M_CURSORDATA ? M_CURSORDATA->m_hCursor : 0); }

  bool FreeResource(bool force = FALSE);
};

#endif
    // __CURSORH__
