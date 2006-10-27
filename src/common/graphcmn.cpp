/////////////////////////////////////////////////////////////////////////////
// Name:        src/common/graphcmn.cpp
// Purpose:     graphics context methods common to all platforms
// Author:      Stefan Csomor
// Modified by:
// Created:     
// RCS-ID:      $Id$
// Copyright:   (c) Stefan Csomor
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#if defined(__BORLANDC__)
    #pragma hdrstop
#endif

#if wxUSE_GRAPHICS_CONTEXT

#include "wx/graphics.h"

#ifndef WX_PRECOMP
    #include "wx/icon.h"
    #include "wx/bitmap.h"
    #include "wx/dcmemory.h"
    #include "wx/region.h"
    #include "wx/log.h"
#endif

#if !defined(wxMAC_USE_CORE_GRAPHICS_BLEND_MODES)
#define wxMAC_USE_CORE_GRAPHICS_BLEND_MODES 0
#endif

//-----------------------------------------------------------------------------
// constants
//-----------------------------------------------------------------------------

static const double RAD2DEG = 180.0 / M_PI;

//-----------------------------------------------------------------------------
// Local functions
//-----------------------------------------------------------------------------

static inline double DegToRad(double deg)
{
    return (deg * M_PI) / 180.0;
}

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// wxGraphicsObject
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxGraphicsObject, wxObject)

wxGraphicsObjectRefData::wxGraphicsObjectRefData( wxGraphicsRenderer* renderer )
{
    m_renderer = renderer;
}
wxGraphicsObjectRefData::wxGraphicsObjectRefData( const wxGraphicsObjectRefData* data )
{
    m_renderer = data->m_renderer;
}
wxGraphicsRenderer* wxGraphicsObjectRefData::GetRenderer() const 
{ 
    return m_renderer ; 
}

wxGraphicsObjectRefData* wxGraphicsObjectRefData::Clone() const 
{
    return new wxGraphicsObjectRefData(this);
}

wxGraphicsObject::wxGraphicsObject() 
{
}

wxGraphicsObject::wxGraphicsObject( wxGraphicsRenderer* renderer ) 
{
    SetRefData( new wxGraphicsObjectRefData(renderer));
}

wxGraphicsObject::~wxGraphicsObject() 
{
}

bool wxGraphicsObject::IsNull() const 
{ 
    return m_refData == NULL; 
}

wxGraphicsRenderer* wxGraphicsObject::GetRenderer() const 
{ 
    return ( IsNull() ? NULL : GetGraphicsData()->GetRenderer() ); 
}

wxGraphicsObjectRefData* wxGraphicsObject::GetGraphicsData() const 
{ 
    return (wxGraphicsObjectRefData*) m_refData; 
}

wxObjectRefData* wxGraphicsObject::CreateRefData() const
{
    wxLogDebug(wxT("A Null Object cannot be changed"));
    return NULL;
}

wxObjectRefData* wxGraphicsObject::CloneRefData(const wxObjectRefData* data) const
{
    const wxGraphicsObjectRefData* ptr = (const wxGraphicsObjectRefData*) data;
    return ptr->Clone();
}

//-----------------------------------------------------------------------------
// pens etc.
//-----------------------------------------------------------------------------

IMPLEMENT_DYNAMIC_CLASS(wxGraphicsPen, wxGraphicsObject)
IMPLEMENT_DYNAMIC_CLASS(wxGraphicsBrush, wxGraphicsObject)
IMPLEMENT_DYNAMIC_CLASS(wxGraphicsFont, wxGraphicsObject)
WXDLLIMPEXP_DATA_CORE(wxGraphicsPen) wxNullGraphicsPen;
WXDLLIMPEXP_DATA_CORE(wxGraphicsBrush) wxNullGraphicsBrush;
WXDLLIMPEXP_DATA_CORE(wxGraphicsFont) wxNullGraphicsFont;

IMPLEMENT_ABSTRACT_CLASS(wxGraphicsRenderer, wxObject)
IMPLEMENT_ABSTRACT_CLASS(wxGraphicsMatrix, wxGraphicsObject)
IMPLEMENT_ABSTRACT_CLASS(wxGraphicsPath, wxGraphicsObject)

wxPoint2DDouble wxGraphicsPath::GetCurrentPoint()
{
    wxDouble x,y;
    GetCurrentPoint(x,y);
    return wxPoint2DDouble(x,y);
}

void wxGraphicsPath::MoveToPoint( const wxPoint2DDouble& p)
{
    MoveToPoint( p.m_x , p.m_y);
}

void wxGraphicsPath::AddLineToPoint( const wxPoint2DDouble& p)
{
    AddLineToPoint( p.m_x , p.m_y);
}

void wxGraphicsPath::AddCurveToPoint( const wxPoint2DDouble& c1, const wxPoint2DDouble& c2, const wxPoint2DDouble& e)
{
    AddCurveToPoint(c1.m_x, c1.m_y, c2.m_x, c2.m_y, e.m_x, e.m_y);
}

void wxGraphicsPath::AddArc( const wxPoint2DDouble& c, wxDouble r, wxDouble startAngle, wxDouble endAngle, bool clockwise)
{
    AddArc(c.m_x, c.m_y, r, startAngle, endAngle, clockwise);
}

wxRect2DDouble wxGraphicsPath::GetBox()
{
	wxDouble x,y,w,h;
	GetBox(&x,&y,&w,&h);
	return wxRect2DDouble( x,y,w,h );
}

//
// Emulations
//

void wxGraphicsPath::AddQuadCurveToPoint( wxDouble cx, wxDouble cy, wxDouble x, wxDouble y )
{
    // calculate using degree elevation to a cubic bezier
    wxPoint2DDouble c1;
    wxPoint2DDouble c2;

    wxPoint2DDouble start = GetCurrentPoint();
    wxPoint2DDouble end(x,y);
    wxPoint2DDouble c(cx,cy);
    c1 = wxDouble(1/3.0) * start + wxDouble(2/3.0) * c;
    c2 = wxDouble(2/3.0) * c + wxDouble(1/3.0) * end;
    AddCurveToPoint(c1.m_x,c1.m_y,c2.m_x,c2.m_y,x,y);
}

void wxGraphicsPath::AddRectangle( wxDouble x, wxDouble y, wxDouble w, wxDouble h )
{
    MoveToPoint(x,y);
    AddLineToPoint(x,y+h);
    AddLineToPoint(x+w,y+h);
    AddLineToPoint(x+w,y);
    CloseSubpath();
}

void wxGraphicsPath::AddCircle( wxDouble x, wxDouble y, wxDouble r )
{
    MoveToPoint(x+r,y);
    AddArc( x,y,r,0,2*M_PI,false);
    CloseSubpath();
}

void wxGraphicsPath::AddEllipse( wxDouble x, wxDouble y, wxDouble w, wxDouble h)
{
    wxDouble rw = w/2;
    wxDouble rh = h/2;
    wxDouble xc = x + rw;
    wxDouble yc = y + rh;
    wxGraphicsMatrix* m = GetRenderer()->CreateMatrix();
    m->Translate(xc,yc);
    m->Scale(rw/rh,1.0);
    wxGraphicsPath* p = GetRenderer()->CreatePath();
    p->AddCircle(0,0,rh);
    p->Transform(m);
    AddPath(p);
    delete p;
    delete m;
}

void wxGraphicsPath::AddRoundedRectangle( wxDouble x, wxDouble y, wxDouble w, wxDouble h, wxDouble radius)
{
    if ( radius == 0 )
        AddRectangle(x,y,w,h);
    else
    {
        MoveToPoint( x + w, y + h / 2);
        AddArcToPoint(x + w, y + h, x + w / 2, y + h, radius);
        AddArcToPoint(x, y + h, x, y + h / 2, radius);
        AddArcToPoint(x, y , x + w / 2, y, radius);
        AddArcToPoint(x + w, y, x + w, y + h / 2, radius);
        CloseSubpath();
    }
}

// draws a an arc to two tangents connecting (current) to (x1,y1) and (x1,y1) to (x2,y2), also a straight line from (current) to (x1,y1)
void wxGraphicsPath::AddArcToPoint( wxDouble x1, wxDouble y1 , wxDouble x2, wxDouble y2, wxDouble r )
{   
    wxPoint2DDouble current = GetCurrentPoint();
    wxPoint2DDouble p1(x1,y1);
    wxPoint2DDouble p2(x2,y2);

    wxPoint2DDouble v1 = current - p1;
    v1.Normalize();
    wxPoint2DDouble v2 = p2 - p1;
    v2.Normalize();

    wxDouble alpha = v1.GetVectorAngle() - v2.GetVectorAngle();

    if ( alpha < 0 )
        alpha = 360 + alpha;
    // TODO obtuse angles

    alpha = DegToRad(alpha);

    wxDouble dist = r / sin(alpha/2) * cos(alpha/2);
    // calculate tangential points
    wxPoint2DDouble t1 = dist*v1 + p1;
    wxPoint2DDouble t2 = dist*v2 + p1;

    wxPoint2DDouble nv1 = v1;
    nv1.SetVectorAngle(v1.GetVectorAngle()-90);
    wxPoint2DDouble c = t1 + r*nv1;

    wxDouble a1 = v1.GetVectorAngle()+90;
    wxDouble a2 = v2.GetVectorAngle()-90;

    AddLineToPoint(t1);
    AddArc(c.m_x,c.m_y,r,DegToRad(a1),DegToRad(a2),true);
    AddLineToPoint(p2);
}

//-----------------------------------------------------------------------------
// wxGraphicsContext Convenience Methods
//-----------------------------------------------------------------------------

IMPLEMENT_ABSTRACT_CLASS(wxGraphicsContext, wxObject)


wxGraphicsContext::wxGraphicsContext(wxGraphicsRenderer* renderer) : wxGraphicsObject(renderer) 
{
}

wxGraphicsContext::~wxGraphicsContext() 
{
}

// sets the pen
void wxGraphicsContext::SetPen( const wxGraphicsPen& pen ) 
{
    m_pen = pen;
}

void wxGraphicsContext::SetPen( const wxPen& pen )
{
    if ( pen.GetStyle() == wxTRANSPARENT )
        SetPen( wxNullGraphicsPen );
    else
        SetPen( CreatePen( pen ) );
}
    
// sets the brush for filling
void wxGraphicsContext::SetBrush( const wxGraphicsBrush& brush ) 
{
    m_brush = brush;
}

void wxGraphicsContext::SetBrush( const wxBrush& brush )
{
    if ( brush.GetStyle() == wxTRANSPARENT )
        SetBrush( wxNullGraphicsBrush );
    else
        SetBrush( CreateBrush( brush ) );
}

// sets the brush for filling
void wxGraphicsContext::SetFont( const wxGraphicsFont& font ) 
{
    m_font = font;
}

void wxGraphicsContext::SetFont( const wxFont& font, const wxColour& colour )
{
    if ( font.Ok() )
        SetFont( CreateFont( font, colour ) );
    else
        SetFont( wxNullGraphicsFont );
}

void wxGraphicsContext::DrawPath( const wxGraphicsPath *path, int fillStyle )
{
    FillPath( path , fillStyle );
    StrokePath( path );
}

void wxGraphicsContext::DrawText( const wxString &str, wxDouble x, wxDouble y, wxDouble angle )
{
    Translate(x,y);
    Rotate( -angle );
    DrawText( str , 0, 0 );
    Rotate( angle );
    Translate(-x,-y);
}

void wxGraphicsContext::StrokeLine( wxDouble x1, wxDouble y1, wxDouble x2, wxDouble y2)
{
    wxGraphicsPath* path = CreatePath();
    path->MoveToPoint(x1, y1);
    path->AddLineToPoint( x2, y2 );
    StrokePath( path );
    delete path;
}

void wxGraphicsContext::DrawRectangle( wxDouble x, wxDouble y, wxDouble w, wxDouble h)
{
    wxGraphicsPath* path = CreatePath();
    path->AddRectangle( x , y , w , h );
    DrawPath( path );
    delete path;
}

void wxGraphicsContext::DrawEllipse( wxDouble x, wxDouble y, wxDouble w, wxDouble h)
{
    wxGraphicsPath* path = CreatePath();
    path->AddEllipse(x,y,w,h);
    DrawPath(path);
    delete path;
}

void wxGraphicsContext::DrawRoundedRectangle( wxDouble x, wxDouble y, wxDouble w, wxDouble h, wxDouble radius)
{
    wxGraphicsPath* path = CreatePath();
    path->AddRoundedRectangle(x,y,w,h,radius);
    DrawPath(path);
    delete path;
}

void wxGraphicsContext::StrokeLines( size_t n, const wxPoint2DDouble *points)
{
    wxASSERT(n > 1);
    wxGraphicsPath* path = CreatePath();
    path->MoveToPoint(points[0].m_x, points[0].m_y);
    for ( size_t i = 1; i < n; ++i)
        path->AddLineToPoint( points[i].m_x, points[i].m_y );
    StrokePath( path );
    delete path;
}

void wxGraphicsContext::DrawLines( size_t n, const wxPoint2DDouble *points, int fillStyle)
{
    wxASSERT(n > 1);
    wxGraphicsPath* path = CreatePath();
    path->MoveToPoint(points[0].m_x, points[0].m_y);
    for ( size_t i = 1; i < n; ++i)
        path->AddLineToPoint( points[i].m_x, points[i].m_y );
    DrawPath( path , fillStyle);
    delete path;
}

void wxGraphicsContext::StrokeLines( size_t n, const wxPoint2DDouble *beginPoints, const wxPoint2DDouble *endPoints)
{
    wxASSERT(n > 0);
    wxGraphicsPath* path = CreatePath();
    for ( size_t i = 0; i < n; ++i)
    {
        path->MoveToPoint(beginPoints[i].m_x, beginPoints[i].m_y);
        path->AddLineToPoint( endPoints[i].m_x, endPoints[i].m_y );
    }
    StrokePath( path );
    delete path;
}

// create a 'native' matrix corresponding to these values
wxGraphicsMatrix* wxGraphicsContext::CreateMatrix( wxDouble a, wxDouble b, wxDouble c, wxDouble d, 
    wxDouble tx, wxDouble ty)
{
    return GetRenderer()->CreateMatrix(a,b,c,d,tx,ty);
}

wxGraphicsPath * wxGraphicsContext::CreatePath()
{
    return GetRenderer()->CreatePath();
}

wxGraphicsPen wxGraphicsContext::CreatePen(const wxPen& pen)
{
    return GetRenderer()->CreatePen(pen);
}

wxGraphicsBrush wxGraphicsContext::CreateBrush(const wxBrush& brush )
{
    return GetRenderer()->CreateBrush(brush);
}

// sets the brush to a linear gradient, starting at (x1,y1) with color c1 to (x2,y2) with color c2
wxGraphicsBrush wxGraphicsContext::CreateLinearGradientBrush( wxDouble x1, wxDouble y1, wxDouble x2, wxDouble y2, 
                                                   const wxColour&c1, const wxColour&c2)
{
    return GetRenderer()->CreateLinearGradientBrush(x1,y1,x2,y2,c1,c2);
}

// sets the brush to a radial gradient originating at (xo,yc) with color oColor and ends on a circle around (xc,yc) 
// with radius r and color cColor
wxGraphicsBrush wxGraphicsContext::CreateRadialGradientBrush( wxDouble xo, wxDouble yo, wxDouble xc, wxDouble yc, wxDouble radius,
                                                   const wxColour &oColor, const wxColour &cColor)
{
    return GetRenderer()->CreateRadialGradientBrush(xo,yo,xc,yc,radius,oColor,cColor);
}

// sets the font
wxGraphicsFont wxGraphicsContext::CreateFont( const wxFont &font , const wxColour &col )
{
    return GetRenderer()->CreateFont(font,col);
}

wxGraphicsContext* wxGraphicsContext::Create( const wxWindowDC& dc) 
{
    return wxGraphicsRenderer::GetDefaultRenderer()->CreateContext(dc);
}

wxGraphicsContext* wxGraphicsContext::CreateFromNative( void * context )
{
    return wxGraphicsRenderer::GetDefaultRenderer()->CreateContextFromNativeContext(context);
}

wxGraphicsContext* wxGraphicsContext::CreateFromNativeWindow( void * window )
{
    return wxGraphicsRenderer::GetDefaultRenderer()->CreateContextFromNativeWindow(window);
}

wxGraphicsContext* wxGraphicsContext::Create( wxWindow* window )
{
    return wxGraphicsRenderer::GetDefaultRenderer()->CreateContext(window);
}

#endif // wxUSE_GRAPHICS_CONTEXT
