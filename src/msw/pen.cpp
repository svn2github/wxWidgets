/////////////////////////////////////////////////////////////////////////////
// Name:        msw/pen.cpp
// Purpose:     wxPen
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart and Markus Holzem
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "pen.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <stdio.h>
#include "wx/setup.h"
#include "wx/list.h"
#include "wx/utils.h"
#include "wx/app.h"
#include "wx/pen.h"
#endif

#include "wx/msw/private.h"
#include "assert.h"

IMPLEMENT_DYNAMIC_CLASS(wxPen, wxGDIObject)

wxPenRefData::wxPenRefData()
{
  m_style = wxSOLID;
  m_width = 1;
  m_join = wxJOIN_ROUND ;
  m_cap = wxCAP_ROUND ;
  m_nbDash = 0 ;
  m_dash = (wxMSWDash*)NULL;
  m_hPen = 0;
}

wxPenRefData::wxPenRefData(const wxPenRefData& data)
{
    m_style = data.m_style;
    m_width = data.m_width;
    m_join = data.m_join;
    m_cap = data.m_cap;
    m_nbDash = data.m_nbDash;
    m_dash = data.m_dash;
    m_colour = data.m_colour;
    m_hPen = 0;
}

wxPenRefData::~wxPenRefData()
{
        if ( m_hPen )
                ::DeleteObject((HPEN) m_hPen);
}

// Pens

wxPen::wxPen()
{
  if (wxThePenList)
    wxThePenList->AddPen(this);
}

wxPen::~wxPen()
{
    if (wxThePenList)
        wxThePenList->RemovePen(this);
}

// Should implement Create
wxPen::wxPen(const wxColour& col, int Width, int Style)
{
  m_refData = new wxPenRefData;

  M_PENDATA->m_colour = col;
//  M_PENDATA->m_stipple = NULL;
  M_PENDATA->m_width = Width;
  M_PENDATA->m_style = Style;
  M_PENDATA->m_join = wxJOIN_ROUND ;
  M_PENDATA->m_cap = wxCAP_ROUND ;
  M_PENDATA->m_nbDash = 0 ;
  M_PENDATA->m_dash = (wxMSWDash*)NULL;
  M_PENDATA->m_hPen = 0 ;

#ifndef __WIN32__
  // In Windows, only a pen of width = 1 can be dotted or dashed!
  if ((Style == wxDOT) || (Style == wxLONG_DASH) ||
      (Style == wxSHORT_DASH) || (Style == wxDOT_DASH) ||
      (Style == wxUSER_DASH))
    M_PENDATA->m_width = 1;
#else
/***
  DWORD vers = GetVersion() ;
  WORD  high = HIWORD(vers) ; // high bit=0 for NT, 1 for Win32s
  // Win32s doesn't support wide dashed pens

  if ((high&0x8000)!=0)
***/
  if (wxGetOsVersion()==wxWIN32S)
  {
    // In Windows, only a pen of width = 1 can be dotted or dashed!
    if ((Style == wxDOT) || (Style == wxLONG_DASH) ||
        (Style == wxSHORT_DASH) || (Style == wxDOT_DASH) ||
        (Style == wxUSER_DASH))
      M_PENDATA->m_width = 1;
  }
#endif
  RealizeResource();

  if ( wxThePenList )
    wxThePenList->AddPen(this);
}

wxPen::wxPen(const wxBitmap& stipple, int Width)
{
    m_refData = new wxPenRefData;

//  M_PENDATA->m_colour = col;
    M_PENDATA->m_stipple = stipple;
    M_PENDATA->m_width = Width;
    M_PENDATA->m_style = wxSTIPPLE;
    M_PENDATA->m_join = wxJOIN_ROUND ;
    M_PENDATA->m_cap = wxCAP_ROUND ;
    M_PENDATA->m_nbDash = 0 ;
    M_PENDATA->m_dash = (wxMSWDash*)NULL;
    M_PENDATA->m_hPen = 0 ;

    RealizeResource();

    if (wxThePenList)
       wxThePenList->AddPen(this);
}

bool wxPen::RealizeResource()
{
   if (M_PENDATA && (M_PENDATA->m_hPen == 0))
   {
       if (M_PENDATA->m_style==wxTRANSPARENT)
       {
           M_PENDATA->m_hPen = (WXHPEN) ::GetStockObject(NULL_PEN);
           return TRUE;
       }

       COLORREF ms_colour = 0;
       ms_colour = M_PENDATA->m_colour.GetPixel();

       // Join style, Cap style, Pen Stippling only on Win32.
       // Currently no time to find equivalent on Win3.1, sorry
       // [if such equiv exist!!]
#if defined(__WIN32__) && !defined(__WXMICROWIN__)
       if (M_PENDATA->m_join==wxJOIN_ROUND        &&
           M_PENDATA->m_cap==wxCAP_ROUND          &&
           M_PENDATA->m_style!=wxUSER_DASH        &&
           M_PENDATA->m_style!=wxSTIPPLE          &&
           M_PENDATA->m_width <= 1)
       {
           M_PENDATA->m_hPen =
             (WXHPEN) CreatePen( wx2msPenStyle(M_PENDATA->m_style),
                                 M_PENDATA->m_width,
                                 ms_colour );
       }
       else
       {
           DWORD ms_style = PS_GEOMETRIC | wx2msPenStyle(M_PENDATA->m_style);

           switch(M_PENDATA->m_join)
           {
               case wxJOIN_BEVEL: ms_style |= PS_JOIN_BEVEL; break;
               case wxJOIN_MITER: ms_style |= PS_JOIN_MITER; break;
               default:
               case wxJOIN_ROUND: ms_style |= PS_JOIN_ROUND; break;
           }

           switch(M_PENDATA->m_cap)
           {
               case wxCAP_PROJECTING: ms_style |= PS_ENDCAP_SQUARE;  break;
               case wxCAP_BUTT:       ms_style |= PS_ENDCAP_FLAT;    break;
               default:
               case wxCAP_ROUND:      ms_style |= PS_ENDCAP_ROUND;   break;
           }

           LOGBRUSH logb;

           switch(M_PENDATA->m_style)
           {
               case wxSTIPPLE:
                   logb.lbStyle = BS_PATTERN ;
                   if (M_PENDATA->m_stipple.Ok())
                       logb.lbHatch = (LONG)M_PENDATA->m_stipple.GetHBITMAP();
                   else
                       logb.lbHatch = (LONG)0;
                   break;
               case wxBDIAGONAL_HATCH:
                   logb.lbStyle = BS_HATCHED;
                   logb.lbHatch = HS_BDIAGONAL;
                   break;
               case wxCROSSDIAG_HATCH:
                   logb.lbStyle = BS_HATCHED;
                   logb.lbHatch = HS_DIAGCROSS;
                   break;
               case wxFDIAGONAL_HATCH:
                   logb.lbStyle = BS_HATCHED;
                   logb.lbHatch = HS_FDIAGONAL;
                   break;
               case wxCROSS_HATCH:
                   logb.lbStyle = BS_HATCHED;
                   logb.lbHatch = HS_CROSS;
                   break;
               case wxHORIZONTAL_HATCH:
                   logb.lbStyle = BS_HATCHED;
                   logb.lbHatch = HS_HORIZONTAL;
                   break;
               case wxVERTICAL_HATCH:
                   logb.lbStyle = BS_HATCHED;
                   logb.lbHatch = HS_VERTICAL;
                   break;
               default:
                   logb.lbStyle = BS_SOLID;
#ifdef __WXDEBUG__
                   // this should be unnecessary (it's unused) but suppresses the Purigy
                   // messages about uninitialized memory read
                   logb.lbHatch = 0;
#endif
                   break;
           }

           logb.lbColor = ms_colour;

           wxMSWDash *real_dash;
           if (M_PENDATA->m_style==wxUSER_DASH && M_PENDATA->m_nbDash && M_PENDATA->m_dash)
           {
               real_dash = new wxMSWDash[M_PENDATA->m_nbDash];
               int i;
               for (i=0; i<M_PENDATA->m_nbDash; i++)
                   real_dash[i] = M_PENDATA->m_dash[i] * M_PENDATA->m_width;
           }
           else
           {
               real_dash = (wxMSWDash*)NULL;
           }

           // Win32s doesn't have ExtCreatePen function...
           if (wxGetOsVersion()==wxWINDOWS_NT || wxGetOsVersion()==wxWIN95)
           {
               M_PENDATA->m_hPen =
                 (WXHPEN) ExtCreatePen( ms_style,
                                        M_PENDATA->m_width,
                                        &logb,
                                        M_PENDATA->m_style == wxUSER_DASH
                                          ? M_PENDATA->m_nbDash
                                          : 0,
                                        (LPDWORD)real_dash );
           }
           else
           {
               M_PENDATA->m_hPen =
                  (WXHPEN) CreatePen( wx2msPenStyle(M_PENDATA->m_style),
                                      M_PENDATA->m_width,
                                      ms_colour );
           }

           if (real_dash)
               delete [] real_dash;
       }
#else
       M_PENDATA->m_hPen =
         (WXHPEN) CreatePen( wx2msPenStyle(M_PENDATA->m_style),
                             M_PENDATA->m_width,
                             ms_colour );
#endif
#ifdef WXDEBUG_CREATE
       if (M_PENDATA->m_hPen==0)
           wxError("Cannot create pen","Internal error") ;
#endif
       return TRUE;
    }
    return FALSE;
}

WXHANDLE wxPen::GetResourceHandle()
{
        if ( !M_PENDATA )
                return 0;
        else
                return (WXHANDLE)M_PENDATA->m_hPen;
}

bool wxPen::FreeResource(bool WXUNUSED(force))
{
  if (M_PENDATA && (M_PENDATA->m_hPen != 0))
  {
    DeleteObject((HPEN) M_PENDATA->m_hPen);
    M_PENDATA->m_hPen = 0;
    return TRUE;
  }
  else return FALSE;
}

bool wxPen::IsFree() const
{
  return (M_PENDATA && M_PENDATA->m_hPen == 0);
}

void wxPen::Unshare()
{
        // Don't change shared data
        if (!m_refData)
    {
                m_refData = new wxPenRefData();
        }
    else
    {
                wxPenRefData* ref = new wxPenRefData(*(wxPenRefData*)m_refData);
                UnRef();
                m_refData = ref;
        }
}

void wxPen::SetColour(const wxColour& col)
{
    Unshare();

    M_PENDATA->m_colour = col;

    RealizeResource();
}

void wxPen::SetColour(unsigned char r, unsigned char g, unsigned char b)
{
    Unshare();

    M_PENDATA->m_colour.Set(r, g, b);

    RealizeResource();
}

void wxPen::SetWidth(int Width)
{
    Unshare();

    M_PENDATA->m_width = Width;

    RealizeResource();
}

void wxPen::SetStyle(int Style)
{
    Unshare();

    M_PENDATA->m_style = Style;

    RealizeResource();
}

void wxPen::SetStipple(const wxBitmap& Stipple)
{
    Unshare();

    M_PENDATA->m_stipple = Stipple;
    M_PENDATA->m_style = wxSTIPPLE;

    RealizeResource();
}

void wxPen::SetDashes(int nb_dashes, const wxDash *Dash)
{
    Unshare();

    M_PENDATA->m_nbDash = nb_dashes;
    M_PENDATA->m_dash = (wxMSWDash *)Dash;

    RealizeResource();
}

void wxPen::SetJoin(int Join)
{
    Unshare();

    M_PENDATA->m_join = Join;

    RealizeResource();
}

void wxPen::SetCap(int Cap)
{
    Unshare();

    M_PENDATA->m_cap = Cap;

    RealizeResource();
}

int wx2msPenStyle(int wx_style)
{
    int cstyle;
    switch (wx_style)
    {
#if !defined(__WXMICROWIN__)
       case wxDOT:
           cstyle = PS_DOT;
           break;

       case wxDOT_DASH:
           cstyle = PS_DASHDOT;
           break;

       case wxSHORT_DASH:
       case wxLONG_DASH:
           cstyle = PS_DASH;
           break;

       case wxTRANSPARENT:
           cstyle = PS_NULL;
           break;
#endif

       case wxUSER_DASH:
#if !defined(__WXMICROWIN__)
#ifdef __WIN32__
           // Win32s doesn't have PS_USERSTYLE
           if (wxGetOsVersion()==wxWINDOWS_NT || wxGetOsVersion()==wxWIN95)
               cstyle = PS_USERSTYLE;
           else
               cstyle = PS_DOT; // We must make a choice... This is mine!
#else
           cstyle = PS_DASH;
#endif
#endif
           break;
       case wxSOLID:
       default:
           cstyle = PS_SOLID;
           break;
   }
   return cstyle;
}

