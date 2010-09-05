///////////////////////////////////////////////////////////////////////////////
// Name:        tests/controls/bitmaptogglebuttontest.cpp
// Purpose:     wxBitmapToggleButton unit test
// Author:      Steven Lamerton
// Created:     2010-07-17
// RCS-ID:      $Id$
// Copyright:   (c) 2010 Steven Lamerton
///////////////////////////////////////////////////////////////////////////////

#include "testprec.h"

#if wxUSE_TOGGLEBTN

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/app.h"
#endif // WX_PRECOMP

#include "testableframe.h"
#include "wx/uiaction.h"
#include "wx/artprov.h"
#include "wx/tglbtn.h"

class BitmapToggleButtonTestCase : public CppUnit::TestCase
{
public:
    BitmapToggleButtonTestCase() { }

    void setUp();
    void tearDown();

private:
    CPPUNIT_TEST_SUITE( BitmapToggleButtonTestCase );
        WXUISIM_TEST( Click );
        CPPUNIT_TEST( Value );
    CPPUNIT_TEST_SUITE_END();

    void Click();
    void Value();

    wxBitmapToggleButton* m_button;

    DECLARE_NO_COPY_CLASS(BitmapToggleButtonTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( BitmapToggleButtonTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( BitmapToggleButtonTestCase,
                                      "BitmapToggleButtonTestCase" );

void BitmapToggleButtonTestCase::setUp()
{
    m_button = new wxBitmapToggleButton(wxTheApp->GetTopWindow(), wxID_ANY,
                                        wxArtProvider::GetIcon(wxART_INFORMATION,
                                                               wxART_OTHER,
                                                               wxSize(32, 32)));
    m_button->Update();
    m_button->Refresh();
}

void BitmapToggleButtonTestCase::tearDown()
{
    wxDELETE(m_button);
}

void BitmapToggleButtonTestCase::Click()
{
#if wxUSE_UIACTIONSIMULATOR
    wxTestableFrame* frame = wxStaticCast(wxTheApp->GetTopWindow(),
                                          wxTestableFrame);

    EventCounter count(m_button, wxEVT_COMMAND_TOGGLEBUTTON_CLICKED);

    wxUIActionSimulator sim;

    //We move in slightly to account for window decorations
    sim.MouseMove(m_button->GetScreenPosition() + wxPoint(10, 10));
    wxYield();

    sim.MouseClick();
    wxYield();

    CPPUNIT_ASSERT_EQUAL(1, frame->GetEventCount());
    CPPUNIT_ASSERT(m_button->GetValue());

    wxMilliSleep(1000);

    sim.MouseClick();
    wxYield();

    CPPUNIT_ASSERT_EQUAL(1, frame->GetEventCount());
    CPPUNIT_ASSERT(!m_button->GetValue());
#endif // wxUSE_UIACTIONSIMULATOR
}

void BitmapToggleButtonTestCase::Value()
{
    wxTestableFrame* frame = wxStaticCast(wxTheApp->GetTopWindow(),
                                          wxTestableFrame);

    EventCounter count(m_button, wxEVT_COMMAND_BUTTON_CLICKED);

    m_button->SetValue(true);

    CPPUNIT_ASSERT(m_button->GetValue());

    m_button->SetValue(false);

    CPPUNIT_ASSERT(!m_button->GetValue());

    CPPUNIT_ASSERT_EQUAL( 0, frame->GetEventCount() );
}

#endif
