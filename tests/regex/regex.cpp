///////////////////////////////////////////////////////////////////////////////
// Name:        tests/regex/regex.cpp
// Purpose:     Test the built-in regex lib and wxRegEx
// Author:      Mike Wetherell
// RCS-ID:      $Id$
// Copyright:   (c) 2004 Mike Wetherell
// Licence:     wxWidgets licence
///////////////////////////////////////////////////////////////////////////////

//
// Notes:
//
// To run just one section, say wx_1, do this:
//  test regex.wx_1
//
// To run all the regex tests:
//  test regex
// 
// Some tests must be skipped since they use features which we do not make
// available through wxRegEx. To see the list of tests that have been skipped
// turn on verbose logging, e.g.:
//  test --verbose regex
// 
// The tests here are for the builtin library, tests for wxRegEx in general
// should go in another module.
//
// The tests are generated from Henry Spencer's reg.test, additional test
// can be added in wxreg.test. These test files are then turned into a C++
// include file 'regex.inc' (included below) using a script 'regex.pl'.
// 

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma implementation
    #pragma interface
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/regex.h"
#include "wx/cppunit.h"
#include <iomanip>
#include <stdexcept>

using namespace std;
using namespace CppUnit;

// many of the tests are specific to the builtin regex lib, so only attempts
// to do them when using the builtin regex lib.
//
#ifdef wxHAS_REGEX_ADVANCED


///////////////////////////////////////////////////////////////////////////////
// The test case - an instance represents a single test

class RegExTestCase : public TestCase
{
public:
    // constructor - create a single testcase
    RegExTestCase(
        const string& name,
        const char *mode,
        const char *id,
        const char *flags,
        const char *pattern,
        const char *data,
        const vector<const char *>& expected);

protected:
    // run this testcase
    void runTest();

private:
    // workers
    wxString Conv(const char *str);
    void parseFlags(const wxString& flags);
    void doTest(int flavor);
    static size_t matchCount(const wxString& expr, int flags);
    static wxString quote(const wxString& arg);
    const wxChar *convError() const { return _T("<cannot convert>"); }

    // assertions - adds some information about the test that failed
    void fail(const wxString& msg) const;
    void failIf(bool condition, const wxString& msg) const
        { if (condition) fail(msg); }

    // mode, id, flags, pattern, test data, expected results...
    int m_mode;
    wxString m_id;
    wxString m_flags;
    wxString m_pattern;
    wxString m_data;
    wxArrayString m_expected;

    // the flag decoded
    int m_compileFlags;
    int m_matchFlags;
    bool m_basic;
    bool m_extended;
    bool m_advanced;
};

// constructor - throws Exception on failure
//
RegExTestCase::RegExTestCase(
    const string& name,
    const char *mode,
    const char *id,
    const char *flags,
    const char *pattern,
    const char *data,
    const vector<const char *>& expected)
  :
    TestCase(name),
    m_mode(mode[0]),
    m_id(Conv(id)),
    m_flags(Conv(flags)),
    m_pattern(Conv(pattern)),
    m_data(Conv(data)),
    m_compileFlags(0),
    m_matchFlags(0),
    m_basic(false),
    m_extended(false),
    m_advanced(false)
{
    bool badconv = m_pattern == convError() || m_data == convError();
    vector<const char *>::const_iterator it;

    for (it = expected.begin(); it != expected.end(); ++it) {
        m_expected.push_back(Conv(*it));
        badconv = badconv || *m_expected.rbegin() == convError();
    }

    failIf(badconv, _T("cannot convert to default character encoding"));
    
    // the flags need further parsing...
    parseFlags(m_flags);

#ifndef wxHAS_REGEX_ADVANCED
    failIf(!m_basic && !m_extended, _T("advanced regexs not available"));
#endif
}

// convert a string from UTF8 to the internal encoding
//
wxString RegExTestCase::Conv(const char *str)
{
    const wxWCharBuffer wstr = wxConvUTF8.cMB2WC(str);
    const wxWC2WXbuf buf = wxConvCurrent->cWC2WX(wstr);

    if (!buf || wcscmp(wxConvCurrent->cWX2WC(buf), wstr) != 0)
        return convError();
    else
        return buf;
}

// Parse flags
//
void RegExTestCase::parseFlags(const wxString& flags)
{
    for (const wxChar *p = flags; *p; p++) {
        switch (*p) {
            // noop
            case '-': break;

            // we don't fully support these flags, but they don't stop us
            // checking for success of failure of the match, so treat as noop
            case 'A': case 'B': case 'E': case 'H':
            case 'I': case 'L': case 'M': case 'N':
            case 'P': case 'Q': case 'R': case 'S':
            case 'T': case 'U': case '%':
                break;

            // match options
            case '^': m_matchFlags |= wxRE_NOTBOL; break;
            case '$': m_matchFlags |= wxRE_NOTEOL; break;
#if wxUSE_UNICODE
            case '*': break;
#endif
            // compile options
            case '&': m_advanced = m_basic = true; break;
            case 'b': m_basic = true; break;
            case 'e': m_extended = true; break;
            case 'i': m_compileFlags |= wxRE_ICASE; break;
            case 'o': m_compileFlags |= wxRE_NOSUB; break;
            case 'n': m_compileFlags |= wxRE_NEWLINE; break;
            case 't': if (strchr("ep", m_mode)) break; // else fall through...

            // anything else we must skip the test
            default:
                fail(wxString::Format(
                     _T("requires unsupported flag '%c'"), *p));
        }
    }
}

// Try test for all flavours of expression specified
//
void RegExTestCase::runTest()
{
    if (m_basic)
        doTest(wxRE_BASIC);
    if (m_extended)
        doTest(wxRE_EXTENDED);
#ifdef wxHAS_REGEX_ADVANCED
    if (m_advanced || (!m_basic && !m_extended))
        doTest(wxRE_ADVANCED);
#endif
}
    
// Try the test for a single flavour of expression
//
void RegExTestCase::doTest(int flavor)
{
    wxRegEx re(m_pattern, m_compileFlags | flavor);

    // 'e' - test that the pattern fails to compile
    if (m_mode == 'e')
        return failIf(re.IsValid(), _T("compile suceeded (should fail)"));
    failIf(!re.IsValid(), _T("compile failed"));

    bool matches = re.Matches(m_data, m_matchFlags);

    // 'f' or 'p' - test that the pattern does not match
    if (m_mode == 'f' || m_mode == 'p')
        return failIf(matches, _T("match suceeded (should fail)"));

    // otherwise 'm' or 'i' - test the pattern does match
    failIf(!matches, _T("match failed"));

    // Check that wxRegEx is going to allocate a large enough array for the
    // results we are supposed to get
    failIf(m_expected.size() > matchCount(m_pattern, m_compileFlags | flavor),
           _T("wxRegEx has not allocated a large enough array for the ")
           _T("number of results expected"));

    wxString result;
    size_t start, len;

    for (size_t i = 0; i < m_expected.size(); i++) {
        failIf(!re.GetMatch(&start, &len, i), wxString::Format(
                _T("wxRegEx::GetMatch failed for match %d"), i));

        // m - check the match returns the strings given
        if (m_mode == 'm')
            if (start < INT_MAX)
                result = m_data.substr(start, len);
            else
                result = _T("");

        // i - check the match returns the offsets given
        else if (m_mode == 'i')
            if (start < INT_MAX)
                result = wxString::Format(_T("%d %d"), start, start + len - 1);
            else
                result = _T("-1 -1");

        failIf(result != m_expected[i], wxString::Format(
                _T("match(%d) == %s, expected == %s"), i,
                quote(result).c_str(), quote(m_expected[i]).c_str()));
    }
}

// assertion - adds some information about the test that failed
//
void RegExTestCase::fail(const wxString& msg) const
{
    wxString str;
    wxArrayString::const_iterator it;

    str << (wxChar)m_mode << _T(" ") << m_id << _T(" ") << m_flags << _T(" ")
        << quote(m_pattern) << _T(" ") << quote(m_data);

    for (it = m_expected.begin(); it != m_expected.end(); ++it)
        str << _T(" ") << quote(*it);
    
    if (str.length() > 77)
        str = str.substr(0, 74) + _T("...");

    str << _T("\n ") << msg;

    // no lossy convs so using utf8
    CPPUNIT_FAIL(string(str.mb_str(wxConvUTF8)));
}

// quote a string so that it can be displayed (static)
//
wxString RegExTestCase::quote(const wxString& arg)
{
    const wxChar *needEscape = _T("\a\b\t\n\v\f\r\"\\");
    const wxChar *escapes = _T("abtnvfr\"\\");
    wxString str;

    for (size_t i = 0; i < arg.length(); i++) {
        wxUChar ch = arg[i];
        const wxChar *p = wxStrchr(needEscape, ch);
        
        if (p)
            str += wxString::Format(_T("\\%c"), escapes[p - needEscape]);
        else if (wxIscntrl(ch))
            str += wxString::Format(_T("\\%03o"), ch);
        else
            str += ch;
    }

    return str.length() == arg.length() && str.find(' ') == wxString::npos ?
        str : _T("\"") + str + _T("\"");
}

// Count the number of subexpressions (taken from wxRegExImpl::Compile)
//
size_t RegExTestCase::matchCount(const wxString& expr, int flags)
{
    // there is always one for the whole expression
    size_t nMatches = 1;

    // and some more for bracketed subexperessions
    for ( const wxChar *cptr = expr; *cptr; cptr++ )
    {
        if ( *cptr == _T('\\') )
        {
            // in basic RE syntax groups are inside \(...\)
            if ( *++cptr == _T('(') && (flags & wxRE_BASIC) )
            {
                nMatches++;
            }
        }
        else if ( *cptr == _T('(') && !(flags & wxRE_BASIC) )
        {
            // we know that the previous character is not an unquoted
            // backslash because it would have been eaten above, so we
            // have a bar '(' and this indicates a group start for the
            // extended syntax
            nMatches++;
        }
    }

    return nMatches;
}


///////////////////////////////////////////////////////////////////////////////
// Test suite
//
// In a non-unicode build the regex is affected by the current locale, so
// this derived TestSuite is used. It sets the locale in it's run() method
// for the duration of the regex tests.

class RegExTestSuite : public TestSuite
{
public:
    RegExTestSuite(string name);
    void run(TestResult *result);
    void add(const char *mode, const char *id, const char *flags,
             const char *pattern, const char *data, const char *expected, ...);
};

// constructor, sets the locale so that it is set when the tests are added
//
RegExTestSuite::RegExTestSuite(string name) : TestSuite(name)
{
    setlocale(LC_ALL, "");
}

// run the test suite, sets the locale again since it may have been changed
// by another test since this suite was crated
//
void RegExTestSuite::run(TestResult *result)
{
    setlocale(LC_ALL, "");
    TestSuite::run(result);
}

// Add a testcase to the suite
//
void RegExTestSuite::add(
    const char *mode,
    const char *id,
    const char *flags,
    const char *pattern,
    const char *data,
    const char *expected, ...)
{
    string name = getName() + "." + id;

    vector<const char *> expected_results;
    va_list ap;

    for (va_start(ap, expected); expected; expected = va_arg(ap, const char *))
        expected_results.push_back(expected);

    va_end(ap);
        
    try {
        addTest(new RegExTestCase(
            name, mode, id, flags, pattern, data, expected_results));
    }
    catch (Exception& e) {
        wxLogInfo(wxString::Format(_T("skipping: %s\n %s\n"),
            wxString(name.c_str(), wxConvUTF8).c_str(),
            wxString(e.what(), wxConvUTF8).c_str()));
    }
}


// Include the generated tests
//
#include "regex.inc"


#endif // wxHAS_REGEX_ADVANCED
