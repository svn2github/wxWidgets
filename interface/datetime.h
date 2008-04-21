/////////////////////////////////////////////////////////////////////////////
// Name:        datetime.h
// Purpose:     interface of wxDateTime
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxDateTime
    @wxheader{datetime.h}

    wxDateTime class represents an absolute moment in the time.

    The type @c wxDateTime_t is typedefed as <tt>unsigned short</tt> and is
    used to contain the number of years, hours, minutes, seconds and
    milliseconds.


    @section datetime_constants Constants

    Global constant wxDefaultDateTime and synonym for it wxInvalidDateTime are
    defined. This constant will be different from any valid wxDateTime object.

    All the following constants are defined inside wxDateTime class (i.e., to
    refer to them you should prepend their names with "wxDateTime::").

    Time zone symbolic names:

    @code
    enum TZ
    {
        // the time in the current time zone
        Local,

        // zones from GMT (= Greenwhich Mean Time): they're guaranteed to be
        // consequent numbers, so writing something like `GMT0 + offset' is
        // safe if abs(offset) <= 12

        // underscore stands for minus
        GMT_12, GMT_11, GMT_10, GMT_9, GMT_8, GMT_7,
        GMT_6, GMT_5, GMT_4, GMT_3, GMT_2, GMT_1,
        GMT0,
        GMT1, GMT2, GMT3, GMT4, GMT5, GMT6,
        GMT7, GMT8, GMT9, GMT10, GMT11, GMT12, GMT13,
        // Note that GMT12 and GMT_12 are not the same: there is a difference
        // of exactly one day between them

        // some symbolic names for TZ

        // Europe
        WET = GMT0,         // Western Europe Time
        WEST = GMT1,        // Western Europe Summer Time
        CET = GMT1,         // Central Europe Time
        CEST = GMT2,        // Central Europe Summer Time
        EET = GMT2,         // Eastern Europe Time
        EEST = GMT3,        // Eastern Europe Summer Time
        MSK = GMT3,         // Moscow Time
        MSD = GMT4,         // Moscow Summer Time

        // US and Canada
        AST = GMT_4,        // Atlantic Standard Time
        ADT = GMT_3,        // Atlantic Daylight Time
        EST = GMT_5,        // Eastern Standard Time
        EDT = GMT_4,        // Eastern Daylight Saving Time
        CST = GMT_6,        // Central Standard Time
        CDT = GMT_5,        // Central Daylight Saving Time
        MST = GMT_7,        // Mountain Standard Time
        MDT = GMT_6,        // Mountain Daylight Saving Time
        PST = GMT_8,        // Pacific Standard Time
        PDT = GMT_7,        // Pacific Daylight Saving Time
        HST = GMT_10,       // Hawaiian Standard Time
        AKST = GMT_9,       // Alaska Standard Time
        AKDT = GMT_8,       // Alaska Daylight Saving Time

        // Australia

        A_WST = GMT8,       // Western Standard Time
        A_CST = GMT13 + 1,  // Central Standard Time (+9.5)
        A_EST = GMT10,      // Eastern Standard Time
        A_ESST = GMT11,     // Eastern Summer Time

        // New Zealand
        NZST = GMT12,       // Standard Time
        NZDT = GMT13,       // Daylight Saving Time

        // Universal Coordinated Time = the new and politically correct name
        // for GMT
        UTC = GMT0
    };
    @endcode

    Month names: Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec and
    Inv_Month for an invalid month are the values of @c wxDateTime::Month enum.

    Likewise, Sun, Mon, Tue, Wed, Thu, Fri, Sat, and Inv_WeekDay are the values
    in @c wxDateTime::WeekDay enum.

    Finally, Inv_Year is defined to be an invalid value for year parameter.

    GetMonthName() and GetWeekDayName() functions use the following flags:

    @code
    enum NameFlags
    {
        Name_Full = 0x01,       // return full name
        Name_Abbr = 0x02        // return abbreviated name
    };
    @endcode

    Several functions accept an extra parameter specifying the calendar to use
    (although most of them only support now the Gregorian calendar). This
    parameters is one of the following values:

    @code
    enum Calendar
    {
        Gregorian,  // calendar currently in use in Western countries
        Julian      // calendar in use since -45 until the 1582 (or later)
    };
    @endcode

    Date calculations often depend on the country and wxDateTime allows to set
    the country whose conventions should be used using SetCountry(). It takes
    one of the following values as parameter:

    @code
    enum Country
    {
        Country_Unknown, // no special information for this country
        Country_Default, // set the default country with SetCountry() method
                         // or use the default country with any other

        Country_WesternEurope_Start,
        Country_EEC = Country_WesternEurope_Start,
        France,
        Germany,
        UK,
        Country_WesternEurope_End = UK,

        Russia,

        USA
    };
    @endcode

    Different parts of the world use different conventions for the week start.
    In some countries, the week starts on Sunday, while in others -- on Monday.
    The ISO standard doesn't address this issue, so we support both conventions
    in the functions whose result depends on it (GetWeekOfYear() and
    GetWeekOfMonth()).

    The desired behvaiour may be specified by giving one of the following
    constants as argument to these functions:

    @code
    enum WeekFlags
    {
        Default_First,   // Sunday_First for US, Monday_First for the rest
        Monday_First,    // week starts with a Monday
        Sunday_First     // week starts with a Sunday
    };
    @endcode


    @section datetime_static Static Functions

    All static functions either set or return the static variables of
    wxDateSpan (the country), return the current moment, year, month or number
    of days in it, or do some general calendar-related actions.

    Please note that although several function accept an extra Calendar
    parameter, it is currently ignored as only the Gregorian calendar is
    supported. Future versions will support other calendars.

    @beginWxPythonOnly
    These methods are standalone functions named
    "wxDateTime_<StaticMethodName>" in wxPython.
    @endWxPythonOnly


    @section datetime_formatting Date Formatting and Parsing

    The date formatting and parsing functions convert wxDateTime objects to and
    from text. The conversions to text are mostly trivial: you can either do it
    using the default date and time representations for the current locale
    (FormatDate() and FormatTime()), using the international standard
    representation defined by ISO 8601 (FormatISODate(), FormatISOTime() and
    FormatISOCombined()) or by specifying any format at all and using Format()
    directly.

    The conversions from text are more interesting, as there are much more
    possibilities to care about. The simplest cases can be taken care of with
    ParseFormat() which can parse any date in the given (rigid) format.
    ParseRfc822Date() is another function for parsing dates in predefined
    format -- the one of RFC 822 which (still...) defines the format of email
    messages on the Internet. This format can not be described with
    @c strptime(3)-like format strings used by Format(), hence the need for a
    separate function.

    But the most interesting functions are ParseTime(), ParseDate() and
    ParseDateTime(). They try to parse the date and time (or only one of them)
    in 'free' format, i.e. allow them to be specified in any of possible ways.
    These functions will usually be used to parse the (interactive) user input
    which is not bound to be in any predefined format. As an example,
    ParseDateTime() can parse the strings such as "tomorrow", "March first" and
    even "next Sunday".

    Finally notice that each of the parsing functions is available in several
    overloads: if the input string is a narrow (@c char *) string, then a
    narrow pointer is returned. If the input string is a wide string, a wide
    char pointer is returned. Finally, if the input parameter is a wxString, a
    narrow char pointer is also returned for backwards compatibility but there
    is also an additional argument of wxString::const_iterator type in which,
    if it is not @NULL, an iterator pointing to the end of the scanned string
    part is returned.


    @library{wxbase}
    @category{data}

    @stdobjects
    - ::wxDefaultDateTime

    @see @ref overview_datetime, wxTimeSpan, wxDateSpan, wxCalendarCtrl
*/
class wxDateTime
{
public:
    /**
        @name Constructors, Assignment Operators and Setters

        Constructors and various Set() methods are collected here. If you
        construct a date object from separate values for day, month and year,
        you should use IsValid() method to check that the values were correct
        as constructors can not return an error code.
    */
    //@{

    /**
        Default constructor. Use one of the Set() functions to initialize the
        object later.
    */
    wxDateTime();
    /**
        Same as Set().

        @beginWxPythonOnly
        This constructor is named "wxDateTimeFromTimeT" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& wxDateTime(time_t timet);
    /**
        Same as Set().

        @beginWxPythonOnly Unsupported. @endWxPythonOnly
    */
    wxDateTime& wxDateTime(const struct tm& tm);
    /**
        Same as Set().

        @beginWxPythonOnly
        This constructor is named "wxDateTimeFromJDN" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& wxDateTime(double jdn);
    /**
        Same as Set().

        @beginWxPythonOnly
        This constructor is named "wxDateTimeFromHMS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& wxDateTime(wxDateTime_t hour, wxDateTime_t minute = 0,
                           wxDateTime_t second = 0, wxDateTime_t millisec = 0);
    /**
        Same as Set().

        @beginWxPythonOnly
        This constructor is named "wxDateTimeFromDMY" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime(wxDateTime_t day, Month month = Inv_Month,
               int year = Inv_Year, wxDateTime_t hour = 0,
               wxDateTime_t minute = 0, wxDateTime_t second = 0,
               wxDateTime_t millisec = 0);

    /**
        Reset time to midnight (00:00:00) without changing the date.
    */
    wxDateTime& ResetTime();

    /**
        Constructs the object from @a timet value holding the number of seconds
        since Jan 1, 1970.

        @beginWxPythonOnly
        This method is named "SetTimeT" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& Set(time_t timet);
    /**
        Sets the date and time from the broken down representation in the
        standard @a tm structure.

        @beginWxPythonOnly Unsupported. @endWxPythonOnly
    */
    wxDateTime& Set(const struct tm& tm);
    /**
        Sets the date from the so-called Julian Day Number.

        By definition, the Julian Day Number, usually abbreviated as JDN, of a
        particular instant is the fractional number of days since 12 hours
        Universal Coordinated Time (Greenwich mean noon) on January 1 of the
        year -4712 in the Julian proleptic calendar.

        @beginWxPythonOnly
        This method is named "SetJDN" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& Set(double jdn);
    /**
        Sets the date to be equal to Today() and the time from supplied
        parameters.

        @beginWxPythonOnly
        This method is named "SetHMS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& Set(wxDateTime_t hour, wxDateTime_t minute = 0,
                    wxDateTime_t second = 0, wxDateTime_t millisec = 0);
    /**
        Sets the date and time from the parameters.
    */
    wxDateTime& Set(wxDateTime_t day, Month month = Inv_Month,
                    int year = Inv_Year, wxDateTime_t hour = 0,
                    wxDateTime_t minute = 0, wxDateTime_t second = 0,
                    wxDateTime_t millisec = 0);

    /**
        Sets the day without changing other date components.
    */
    wxDateTime& SetDay(short unsigned int);

    /**
        Sets the date from the date and time in DOS format.
    */
    wxDateTime& SetFromDOS(unsigned long ddt);

    /**
        Sets the hour without changing other date components.
    */
    wxDateTime& SetHour(short unsigned int);

    /**
        Sets the millisecond without changing other date components.
    */
    wxDateTime& SetMillisecond(short unsigned int);

    /**
        Sets the minute without changing other date components.
    */
    wxDateTime& SetMinute(short unsigned int);

    /**
        Sets the month without changing other date components.
    */
    wxDateTime& SetMonth(Month month);

    /**
        Sets the second without changing other date components.
    */
    wxDateTime& SetSecond(short unsigned int);

    /**
        Sets the date and time of to the current values. Same as assigning the
        result of Now() to this object.
    */
    wxDateTime& SetToCurrent();

    /**
        Sets the year without changing other date components.
    */
    wxDateTime& SetYear(int year);

    /**
        Same as Set().
    */
    wxDateTime& operator=(time_t timet);
    /**
        Same as Set().
    */
    wxDateTime& operator=(const struct tm& tm);

    //@}



    /**
        @name Accessors

        Here are the trivial accessors. Other functions, which might have to
        perform some more complicated calculations to find the answer are under
        the "Date Arithmetics" section.
    */
    //@{

    /**
        Returns the date and time in DOS format.
    */
    long unsigned int GetAsDOS() const;

    /**
        Returns the century of this date.
    */
    int GetCentury(const TimeZone& tz = Local) const;

    /**
        Returns the object having the same date component as this one but time
        of 00:00:00.

        @since 2.8.2

        @see ResetTime()
    */
    wxDateTime GetDateOnly() const;

    /**
        Returns the day in the given timezone (local one by default).
    */
    short unsigned int GetDay(const TimeZone& tz = Local) const;

    /**
        Returns the day of the year (in 1-366 range) in the given timezone
        (local one by default).
    */
    short unsigned int GetDayOfYear(const TimeZone& tz = Local) const;

    /**
        Returns the hour in the given timezone (local one by default).
    */
    short unsigned int GetHour(const TimeZone& tz = Local) const;

    /**
        Returns the milliseconds in the given timezone (local one by default).
    */
    short unsigned int GetMillisecond(const TimeZone& tz = Local) const;

    /**
        Returns the minute in the given timezone (local one by default).
    */
    short unsigned int GetMinute(const TimeZone& tz = Local) const;

    /**
        Returns the month in the given timezone (local one by default).
    */
    Month GetMonth(const TimeZone& tz = Local) const;

    /**
        Returns the seconds in the given timezone (local one by default).
    */
    short unsigned int GetSecond(const TimeZone& tz = Local) const;

    /**
        Returns the number of seconds since Jan 1, 1970. An assert failure will
        occur if the date is not in the range covered by @c time_t type.
    */
    time_t GetTicks() const;

    /**
        Returns broken down representation of the date and time.
    */
    Tm GetTm(const TimeZone& tz = Local) const;

    /**
        Returns the week day in the given timezone (local one by default).
    */
    WeekDay GetWeekDay(const TimeZone& tz = Local) const;

    /**
        Returns the ordinal number of the week in the month (in 1-5 range).

        As GetWeekOfYear(), this function supports both conventions for the
        week start. See the description of these @c WeekFlags in the
        @ref datetime_constants section.
    */
    wxDateTime_t GetWeekOfMonth(WeekFlags flags = Monday_First,
                                const TimeZone& tz = Local) const;

    /**
        Returns the number of the week of the year this date is in. The first
        week of the year is, according to international standards, the one
        containing Jan 4 or, equivalently, the first week which has Thursday in
        this year. Both of these definitions are the same as saying that the
        first week of the year must contain more than half of its days in this
        year. Accordingly, the week number will always be in 1-53 range (52 for
        non-leap years).

        The function depends on the @ref datetime_constants "week start"
        convention specified by the @a flags argument but its results for
        @c Sunday_First are not well-defined as the ISO definition quoted above
        applies to the weeks starting on Monday only.
    */
    wxDateTime_t GetWeekOfYear(WeekFlags flags = Monday_First,
                               const TimeZone& tz = Local) const;

    /**
        Returns the year in the given timezone (local one by default).
    */
    int GetYear(const TimeZone& tz = Local) const;

    /**
        Returns @true if the given date is later than the date of adoption of
        the Gregorian calendar in the given country (and hence the Gregorian
        calendar calculations make sense for it).
    */
    bool IsGregorianDate(GregorianAdoption country = Gr_Standard) const;

    /**
        Returns @true if the object represents a valid time moment.
    */
    bool IsValid() const;

    /**
        Returns @true is this day is not a holiday in the given country.
    */
    bool IsWorkDay(Country country = Country_Default) const;

    //@}



    /**
        @name Date Comparison

        There are several functions to allow date comparison. To supplement
        them, a few global operators, etc taking wxDateTime are defined.
    */
    //@{

    /**
        Returns @true if this date precedes the given one.
    */
    bool IsEarlierThan(const wxDateTime& datetime) const;

    /**
        Returns @true if the two dates are strictly identical.
    */
    bool IsEqualTo(const wxDateTime& datetime) const;

    /**
        Returns @true if the date is equal to another one up to the given time
        interval, i.e. if the absolute difference between the two dates is less
        than this interval.
    */
    bool IsEqualUpTo(const wxDateTime& dt, const wxTimeSpan& ts) const;

    /**
        Returns @true if this date is later than the given one.
    */
    bool IsLaterThan(const wxDateTime& datetime) const;

    /**
        Returns @true if the date is the same without comparing the time parts.
    */
    bool IsSameDate(const wxDateTime& dt) const;

    /**
        Returns @true if the time is the same (although dates may differ).
    */
    bool IsSameTime(const wxDateTime& dt) const;

    /**
        Returns @true if this date lies strictly between the two given dates.

        @see IsBetween()
    */
    bool IsStrictlyBetween(const wxDateTime& t1,
                            const wxDateTime& t2) const;

    /**
        Returns @true if IsStrictlyBetween() is @true or if the date is equal
        to one of the limit values.

        @see IsStrictlyBetween()
    */
    bool IsBetween(const wxDateTime& t1, const wxDateTime& t2) const;

    //@}



    /**
        @name Date Arithmetics

        These functions carry out
        @ref overview_datetime_arithmetics "arithmetics" on the wxDateTime
        objects. As explained in the overview, either wxTimeSpan or wxDateSpan
        may be added to wxDateTime, hence all functions are overloaded to
        accept both arguments.

        Also, both Add() and Subtract() have both const and non-const version.
        The first one returns a new object which represents the sum/difference
        of the original one with the argument while the second form modifies
        the object to which it is applied. The operators "-=" and "+=" are
        defined to be equivalent to the second forms of these functions.
    */
    //@{

    /**
        Adds the given date span to this object.

        @beginWxPythonOnly
        This method is named "AddDS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime Add(const wxDateSpan& diff) const;
    /**
        Adds the given date span to this object.

        @beginWxPythonOnly
        This method is named "AddDS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime Add(const wxDateSpan& diff);
    /**
        Adds the given time span to this object.

        @beginWxPythonOnly
        This method is named "AddTS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime Add(const wxTimeSpan& diff) const;
    /**
        Adds the given time span to this object.

        @beginWxPythonOnly
        This method is named "AddTS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& Add(const wxTimeSpan& diff);

    /**
        Subtracts the given time span from this object.

        @beginWxPythonOnly
        This method is named "SubtractTS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime Subtract(const wxTimeSpan& diff) const;
    /**
        Subtracts the given time span from this object.

        @beginWxPythonOnly
        This method is named "SubtractTS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& Subtract(const wxTimeSpan& diff);
    /**
        Subtracts the given date span from this object.

        @beginWxPythonOnly
        This method is named "SubtractDS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime Subtract(const wxDateSpan& diff) const;
    /**
        Subtracts the given date span from this object.

        @beginWxPythonOnly
        This method is named "SubtractDS" in wxPython.
        @endWxPythonOnly
    */
    wxDateTime& Subtract(const wxDateSpan& diff);
    /**
        Subtracts another date from this one and returns the difference between
        them as a wxTimeSpan.
    */
    wxTimeSpan Subtract(const wxDateTime& dt) const;

    /**
        Adds the given date span to this object.
    */
    wxDateTime operator+=(const wxDateSpan& diff);
    /**
        Subtracts the given date span from this object.
    */
    wxDateTime& operator-=(const wxDateSpan& diff);
    /**
        Adds the given time span to this object.
    */
    wxDateTime& operator+=(const wxTimeSpan& diff);
    /**
        Subtracts the given time span from this object.
    */
    wxDateTime& operator-=(const wxTimeSpan& diff);

    //@}



    /**
        @name Date Formatting and Parsing

        See @ref datetime_formatting
    */
    //@{

    /**
        This function does the same as the standard ANSI C @c strftime(3)
        function. Please see its description for the meaning of @a format
        parameter.

        It also accepts a few wxWidgets-specific extensions: you can optionally
        specify the width of the field to follow using @c printf(3)-like syntax
        and the format specification @c "%l" can be used to get the number of
        milliseconds.

        @see ParseFormat()
    */
    wxString Format(const wxChar* format = wxDefaultDateTimeFormat,
                    const TimeZone& tz = Local) const;

    /**
        Identical to calling Format() with @c "%x" argument (which means
        "preferred date representation for the current locale").
    */
    wxString FormatDate() const;

    /**
        Returns the combined date-time representation in the ISO 8601 format
        @c "YYYY-MM-DDTHH:MM:SS". The @a sep parameter default value produces
        the result exactly corresponding to the ISO standard, but it can also
        be useful to use a space as seprator if a more human-readable combined
        date-time representation is needed.

        @see FormatISODate(), FormatISOTime(), ParseISOCombined()
    */
    wxString FormatISOCombined(char sep = 'T') const;

    /**
        This function returns the date representation in the ISO 8601 format
        @c "YYYY-MM-DD".
    */
    wxString FormatISODate() const;

    /**
        This function returns the time representation in the ISO 8601 format
        @c "HH:MM:SS".
    */
    wxString FormatISOTime() const;

    /**
        Identical to calling Format() with @c "%X" argument (which means
        "preferred time representation for the current locale").
    */
    wxString FormatTime() const;

    /**
        This function is like ParseDateTime(), but it only allows the date to
        be specified. It is thus less flexible then ParseDateTime(), but also
        has less chances to misinterpret the user input.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseDate(const wxString& date,
                           wxString::const_iterator* end = NULL);
    /**
        This function is like ParseDateTime(), but it only allows the date to
        be specified. It is thus less flexible then ParseDateTime(), but also
        has less chances to misinterpret the user input.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseDate(const char* date);
    /**
        This function is like ParseDateTime(), but it only allows the date to
        be specified. It is thus less flexible then ParseDateTime(), but also
        has less chances to misinterpret the user input.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const wchar_t* ParseDate(const wchar_t* date);

    /**
        Parses the string @a datetime containing the date and time in free
        format. This function tries as hard as it can to interpret the given
        string as date and time. Unlike ParseRfc822Date(), it will accept
        anything that may be accepted and will only reject strings which can
        not be parsed in any way at all.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseDateTime(const wxString& datetime,
                              wxString::const_iterator* end = NULL);
    /**
        Parses the string @a datetime containing the date and time in free
        format. This function tries as hard as it can to interpret the given
        string as date and time. Unlike ParseRfc822Date(), it will accept
        anything that may be accepted and will only reject strings which can
        not be parsed in any way at all.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseDateTime(const char* datetime);
    /**
        Parses the string @a datetime containing the date and time in free
        format. This function tries as hard as it can to interpret the given
        string as date and time. Unlike ParseRfc822Date(), it will accept
        anything that may be accepted and will only reject strings which can
        not be parsed in any way at all.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const wchar_t* ParseDateTime(const wchar_t* datetime);

    /**
        This function parses the string @a date according to the given
        @e format. The system @c strptime(3) function is used whenever
        available, but even if it is not, this function is still implemented,
        although support for locale-dependent format specifiers such as
        @c "%c", @c "%x" or @c "%X" may not be perfect and GNU extensions such
        as @c "%z" and @c "%Z" are not implemented. This function does handle
        the month and weekday names in the current locale on all platforms,
        however.

        Please see the description of the ANSI C function @c strftime(3) for
        the syntax of the format string.

        The @a dateDef parameter is used to fill in the fields which could not
        be determined from the format string. For example, if the format is
        @c "%d" (the day of the month), the month and the year are taken from
        @a dateDef. If it is not specified, Today() is used as the default
        date.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseFormat(const wxString& date,
                             const wxString& format = wxDefaultDateTimeFormat,
                             const wxDateTime& dateDef = wxDefaultDateTime,
                             wxString::const_iterator* end = NULL);
    /**
        This function parses the string @a date according to the given
        @e format. The system @c strptime(3) function is used whenever
        available, but even if it is not, this function is still implemented,
        although support for locale-dependent format specifiers such as
        @c "%c", @c "%x" or @c "%X" may not be perfect and GNU extensions such
        as @c "%z" and @c "%Z" are not implemented. This function does handle
        the month and weekday names in the current locale on all platforms,
        however.

        Please see the description of the ANSI C function @c strftime(3) for
        the syntax of the format string.

        The @a dateDef parameter is used to fill in the fields which could not
        be determined from the format string. For example, if the format is
        @c "%d" (the day of the month), the month and the year are taken from
        @a dateDef. If it is not specified, Today() is used as the default
        date.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseFormat(const char* date,
                              const wxString& format = wxDefaultDateTimeFormat,
                              const wxDateTime& dateDef = wxDefaultDateTime);
    /**
        This function parses the string @a date according to the given
        @e format. The system @c strptime(3) function is used whenever
        available, but even if it is not, this function is still implemented,
        although support for locale-dependent format specifiers such as
        @c "%c", @c "%x" or @c "%X" may not be perfect and GNU extensions such
        as @c "%z" and @c "%Z" are not implemented. This function does handle
        the month and weekday names in the current locale on all platforms,
        however.

        Please see the description of the ANSI C function @c strftime(3) for
        the syntax of the format string.

        The @a dateDef parameter is used to fill in the fields which could not
        be determined from the format string. For example, if the format is
        @c "%d" (the day of the month), the month and the year are taken from
        @a dateDef. If it is not specified, Today() is used as the default
        date.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const wchar_t* ParseFormat(const wchar_t* date,
                                 const wxString& format = wxDefaultDateTimeFormat,
                                 const wxDateTime& dateDef = wxDefaultDateTime);

    /**
        This function parses the string containing the date and time in ISO
        8601 combined format @c "YYYY-MM-DDTHH:MM:SS". The separator between
        the date and time parts must be equal to @a sep for the function to
        succeed.

        @returns @true if the entire string was parsed successfully, @false
                 otherwise.
    */
    bool ParseISOCombined(const wxString& date, char sep = 'T');

    /**
        This function parses the date in ISO 8601 format @c "YYYY-MM-DD".

        @returns @true if the entire string was parsed successfully, @false
                 otherwise.
    */
    bool ParseISODate(const wxString& date);

    /**
        This function parses the time in ISO 8601 format @c "HH:MM:SS".

        @returns @true if the entire string was parsed successfully, @false
                 otherwise.
    */
    bool ParseISOTime(const wxString& date);

    /**
        Parses the string @a date looking for a date formatted according to the
        RFC 822 in it. The exact description of this format may, of course, be
        found in the RFC (section 5), but, briefly, this is the format used in
        the headers of Internet email messages and one of the most common
        strings expressing date in this format may be something like
        @c "Sat, 18 Dec 1999 00:48:30 +0100".

        Returns @NULL if the conversion failed, otherwise return the pointer to
        the character immediately following the part of the string which could
        be parsed. If the entire string contains only the date in RFC 822
        format, the returned pointer will be pointing to a @c NUL character.

        This function is intentionally strict, it will return an error for any
        string which is not RFC 822 compliant. If you need to parse date
        formatted in more free ways, you should use ParseDateTime() or
        ParseDate() instead.
    */
    const char* ParseRfc822Date(const wxString& date,
                                  wxString::const_iterator* end = NULL);
    /**
        Parses the string @a date looking for a date formatted according to the
        RFC 822 in it. The exact description of this format may, of course, be
        found in the RFC (section 5), but, briefly, this is the format used in
        the headers of Internet email messages and one of the most common
        strings expressing date in this format may be something like
        @c "Sat, 18 Dec 1999 00:48:30 +0100".

        Returns @NULL if the conversion failed, otherwise return the pointer to
        the character immediately following the part of the string which could
        be parsed. If the entire string contains only the date in RFC 822
        format, the returned pointer will be pointing to a @c NUL character.

        This function is intentionally strict, it will return an error for any
        string which is not RFC 822 compliant. If you need to parse date
        formatted in more free ways, you should use ParseDateTime() or
        ParseDate() instead.
    */
    const char* ParseRfc822Date(const char* date);
    /**
        Parses the string @a date looking for a date formatted according to the
        RFC 822 in it. The exact description of this format may, of course, be
        found in the RFC (section 5), but, briefly, this is the format used in
        the headers of Internet email messages and one of the most common
        strings expressing date in this format may be something like
        @c "Sat, 18 Dec 1999 00:48:30 +0100".

        Returns @NULL if the conversion failed, otherwise return the pointer to
        the character immediately following the part of the string which could
        be parsed. If the entire string contains only the date in RFC 822
        format, the returned pointer will be pointing to a @c NUL character.

        This function is intentionally strict, it will return an error for any
        string which is not RFC 822 compliant. If you need to parse date
        formatted in more free ways, you should use ParseDateTime() or
        ParseDate() instead.
    */
    const wchar_t* ParseRfc822Date(const wchar_t* date);

    /**
        This functions is like ParseDateTime(), but only allows the time to be
        specified in the input string.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseTime(const wxString& time,
                           wxString::const_iterator* end = NULL);
    /**
        This functions is like ParseDateTime(), but only allows the time to be
        specified in the input string.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const char* ParseTime(const char* time);
    /**
        This functions is like ParseDateTime(), but only allows the time to be
        specified in the input string.

        @returns @NULL if the conversion failed, otherwise return the pointer
                 to the character which stopped the scan.
    */
    const wchar_t* ParseTime(const wchar_t* time);

    //@}



    /**
        @name Calendar Calculations

        The functions in this section perform the basic calendar calculations,
        mostly related to the week days. They allow to find the given week day
        in the week with given number (either in the month or in the year) and
        so on.

        None of the functions in this section modify the time part of the
        wxDateTime, they only work with the date part of it.
    */
    //@{

    /**
        Returns the copy of this object to which SetToLastMonthDay() was
        applied.
    */
    wxDateTime GetLastMonthDay(Month month = Inv_Month,
                               int year = Inv_Year) const;

    /**
        Returns the copy of this object to which SetToLastWeekDay() was
        applied.
    */
    wxDateTime GetLastWeekDay(WeekDay weekday, Month month = Inv_Month,
                              int year = Inv_Year);

    /**
        Returns the copy of this object to which SetToNextWeekDay() was
        applied.
    */
    wxDateTime GetNextWeekDay(WeekDay weekday) const;

    /**
        Returns the copy of this object to which SetToPrevWeekDay() was
        applied.
    */
    wxDateTime GetPrevWeekDay(WeekDay weekday) const;

    /**
        Returns the copy of this object to which SetToWeekDay() was applied.
    */
    wxDateTime GetWeekDay(WeekDay weekday, int n = 1, Month month = Inv_Month,
                          int year = Inv_Year) const;

    /**
        Returns the copy of this object to which SetToWeekDayInSameWeek() was
        applied.
    */
    wxDateTime GetWeekDayInSameWeek(WeekDay weekday,
                                    WeekFlags flags = Monday_First) const;

    /**
        Returns the copy of this object to which SetToYearDay() was applied.
    */
    wxDateTime GetYearDay(wxDateTime_t yday) const;

    /**
        Sets the date to the last day in the specified month (the current one
        by default).

        @returns The reference to the modified object itself.
    */
    wxDateTime SetToLastMonthDay(Month month = Inv_Month,
                                 int year = Inv_Year);

    /**
        The effect of calling this function is the same as of calling
        @c SetToWeekDay(-1, weekday, month, year). The date will be set to the
        last @a weekday in the given month and year (the current ones by
        default). Always returns @true.
    */
    bool SetToLastWeekDay(WeekDay weekday, Month month = Inv_Month,
                          int year = Inv_Year);

    /**
        Sets the date so that it will be the first @a weekday following the
        current date.

        @returns The reference to the modified object itself.
    */
    wxDateTime& SetToNextWeekDay(WeekDay weekday);

    /**
        Sets the date so that it will be the last @a weekday before the current
        date.

        @returns The reference to the modified object itself.
    */
    wxDateTime& SetToPrevWeekDay(WeekDay weekday);

    /**
        Sets the date to the @e n-th @a weekday in the given month of the given
        year (the current month and year are used by default). The parameter
        @a n may be either positive (counting from the beginning of the month)
        or negative (counting from the end of it).

        For example, SetToWeekDay(2, wxDateTime::Wed) will set the date to the
        second Wednesday in the current month and
        SetToWeekDay(-1, wxDateTime::Sun) will set the date to the last Sunday
        in the current month.

        @returns @true if the date was modified successfully, @false otherwise
                 meaning that the specified date doesn't exist.
    */
    bool SetToWeekDay(WeekDay weekday, int n = 1,
                       Month month = Inv_Month, int year = Inv_Year);

    /**
        Adjusts the date so that it will still lie in the same week as before,
        but its week day will be the given one.

        @returns The reference to the modified object itself.
    */
    wxDateTime SetToWeekDayInSameWeek(WeekDay weekday,
                                      WeekFlags flags = Monday_First);

    /**
        Sets the date to the day number @a yday in the same year (i.e., unlike
        the other functions, this one does not use the current year). The day
        number should be in the range 1-366 for the leap years and 1-365 for
        the other ones.

        @returns The reference to the modified object itself.
    */
    wxDateTime& SetToYearDay(wxDateTime_t yday);

    //@}



    /**
        @name Astronomical/Historical Functions

        Some degree of support for the date units used in astronomy and/or
        history is provided. You can construct a wxDateTime object from a
        JDN and you may also get its JDN, MJD or Rata Die number from it.

        Related functions in other groups: wxDateTime(double), Set(double)
    */
    //@{

    /**
        Synonym for GetJulianDayNumber().
    */
    double GetJDN() const;

    /**
        Returns the JDN corresponding to this date. Beware of rounding errors!

        @see GetModifiedJulianDayNumber()
    */
    double GetJulianDayNumber() const;

    /**
        Synonym for GetModifiedJulianDayNumber().
    */
    double GetMJD() const;

    /**
        Returns the @e "Modified Julian Day Number" (MJD) which is, by
        definition, is equal to JDN - 2400000.5. The MJDs are simpler to work
        with as the integral MJDs correspond to midnights of the dates in the
        Gregorian calendar and not the noons like JDN. The MJD 0 represents
        Nov 17, 1858.
    */
    double GetModifiedJulianDayNumber() const;

    /**
        Return the @e Rata Die number of this date.

        By definition, the Rata Die number is a date specified as the number of
        days relative to a base date of December 31 of the year 0. Thus January
        1 of the year 1 is Rata Die day 1.
    */
    double GetRataDie() const;

    //@}



    /**
        @name Time Zone and DST Support

        Please see the @ref overview_datetime_timezones "time zone overview"
        for more information about time zones. Normally, these functions should
        be rarely used.

        Related functions in other groups: GetBeginDST(), GetEndDST()
    */
    //@{

    /**
        Transform the date from the given time zone to the local one. If
        @a noDST is @true, no DST adjustments will be made.

        @returns The date in the local time zone.
    */
    wxDateTime FromTimezone(const TimeZone& tz, bool noDST = false) const;

    /**
        Returns @true if the DST is applied for this date in the given country.

        @see GetBeginDST(), GetEndDST()
    */
    int IsDST(Country country = Country_Default) const;

    /**
        Same as FromTimezone() but modifies the object in place.
    */
    wxDateTime MakeFromTimezone(const TimeZone& tz, bool noDST = false);

    /**
        Modifies the object in place to represent the date in another time
        zone. If @a noDST is @true, no DST adjustments will be made.
    */
    wxDateTime MakeTimezone(const TimeZone& tz, bool noDST = false);

    /**
        This is the same as calling MakeTimezone() with the argument @c GMT0.
    */
    wxDateTime& MakeUTC(bool noDST = false);

    /**
        Transform the date to the given time zone. If @a noDST is @true, no DST
        adjustments will be made.

        @returns The date in the new time zone.
    */
    wxDateTime ToTimezone(const TimeZone& tz, bool noDST = false) const;

    /**
        This is the same as calling ToTimezone() with the argument @c GMT0.
    */
    wxDateTime ToUTC(bool noDST = false) const;

    //@}





    /**
        Converts the year in absolute notation (i.e. a number which can be
        negative, positive or zero) to the year in BC/AD notation. For the
        positive years, nothing is done, but the year 0 is year 1 BC and so for
        other years there is a difference of 1.

        This function should be used like this:

        @code
        wxDateTime dt(...);
        int y = dt.GetYear();
        printf("The year is %d%s", wxDateTime::ConvertYearToBC(y), y > 0 ? "AD" : "BC");
        @endcode
    */
    static int ConvertYearToBC(int year);

    /**
        Returns the translations of the strings @c AM and @c PM used for time
        formatting for the current locale. Either of the pointers may be @NULL
        if the corresponding value is not needed.
    */
    static void GetAmPmStrings(wxString* am, wxString* pm);

    /**
        Get the beginning of DST for the given country in the given year
        (current one by default). This function suffers from limitations
        described in the @ref overview_datetime_dst "DST overview".

        @see GetEndDST()
    */
    static wxDateTime GetBeginDST(int year = Inv_Year,
                                   Country country = Country_Default);

    /**
        Returns the end of DST for the given country in the given year (current
        one by default).

        @see GetBeginDST()
    */
    static wxDateTime GetEndDST(int year = Inv_Year,
                                 Country country = Country_Default);

    /**
        Get the current century, i.e. first two digits of the year, in given
        calendar (only Gregorian is currently supported).
    */
    static int GetCentury(int year);

    /**
        Returns the current default country. The default country is used for
        DST calculations, for example.

        @see SetCountry()
    */
    static Country GetCountry();

    /**
        Get the current month in given calendar (only Gregorian is currently
        supported).
    */
    static Month GetCurrentMonth(Calendar cal = Gregorian);

    /**
        Get the current year in given calendar (only Gregorian is currently
        supported).
    */
    static int GetCurrentYear(Calendar cal = Gregorian);

    /**
        Gets the full (default) or abbreviated (specify @c Name_Abbr name of
        the given month.

        @see GetWeekDayName()
    */
    static wxString GetMonthName(Month month, NameFlags flags = Name_Full);

    /**
        Returns the number of days in the given year. The only supported value
        for @a cal currently is @c Gregorian.

        @beginWxPythonOnly
        This method is named "GetNumberOfDaysInYear" in wxPython.
        @endWxPythonOnly
    */
    static wxDateTime_t GetNumberOfDays(int year, Calendar cal = Gregorian);

    /**
        Returns the number of days in the given month of the given year. The
        only supported value for @a cal currently is @c Gregorian.

        @beginWxPythonOnly
        This method is named "GetNumberOfDaysInMonth" in wxPython.
        @endWxPythonOnly
    */
    static wxDateTime_t GetNumberOfDays(Month month, int year = Inv_Year,
                                        Calendar cal = Gregorian);

    /**
        Returns the current time.
    */
    static time_t GetTimeNow();

    /**
        Returns the current time broken down using the buffer whose adress is
        passed to the function with @a tm to store the result.
    */
    static struct tm* GetTmNow(struct tm *tm);

    /**
        Returns the current time broken down. Note that this function returns a
        pointer to a static buffer that's reused by calls to this function and
        certain C library functions (e.g. localtime). If there is any chance
        your code might be used in a multi-threaded application, you really
        should use GetTmNow(struct tm *) instead.
    */
    static struct tm* GetTmNow();

    /**
        Gets the full (default) or abbreviated (specify @c Name_Abbr) name of
        the given week day.

        @see GetMonthName()
    */
    static wxString GetWeekDayName(WeekDay weekday,
                                    NameFlags flags = Name_Full);

    /**
        Returns @true if DST was used n the given year (the current one by
        default) in the given country.
    */
    static bool IsDSTApplicable(int year = Inv_Year,
                                  Country country = Country_Default);

    /**
        Returns @true if the @a year is a leap one in the specified calendar.
        This functions supports Gregorian and Julian calendars.
    */
    static bool IsLeapYear(int year = Inv_Year, Calendar cal = Gregorian);

    /**
        This function returns @true if the specified (or default) country is
        one of Western European ones. It is used internally by wxDateTime to
        determine the DST convention and date and time formatting rules.
    */
    static bool IsWestEuropeanCountry(Country country = Country_Default);

    /**
        Returns the object corresponding to the current time.

        Example:

        @code
        wxDateTime now = wxDateTime::Now();
        printf("Current time in Paris:\t%s\n", now.Format("%c", wxDateTime::CET).c_str());
        @endcode

        @note This function is accurate up to seconds. UNow() should be used
              for better precision, but it is less efficient and might not be
              available on all platforms.

        @see Today()
    */
    static wxDateTime Now();

    /**
        Sets the country to use by default. This setting influences the DST
        calculations, date formatting and other things.

        The possible values for @a country parameter are enumerated in the
        @ref datetime_constants section.

        @see GetCountry()
    */
    static void SetCountry(Country country);

    /**
        Set the date to the given @a weekday in the week number @a numWeek of
        the given @a year . The number should be in range 1-53.

        Note that the returned date may be in a different year than the one
        passed to this function because both the week 1 and week 52 or 53 (for
        leap years) contain days from different years. See GetWeekOfYear() for
        the explanation of how the year weeks are counted.
    */
    static wxDateTime SetToWeekOfYear(int year, wxDateTime_t numWeek,
                                       WeekDay weekday = Mon);

    /**
        Returns the object corresponding to the midnight of the current day
        (i.e. the same as Now(), but the time part is set to 0).

        @see Now()
    */
    static wxDateTime Today();

    /**
        Returns the object corresponding to the current time including the
        milliseconds if a function to get time with such precision is available
        on the current platform (supported under most Unices and Win32).

        @see Now()
    */
    static wxDateTime UNow();
};

/**
    Global instance of an empty wxDateTime object.

    @todo Would it be better to rename this wxNullDateTime so it's consistent
          with the rest of the "empty/invalid/null" global objects?
*/
const wxDateTime wxDefaultDateTime;



/**
    @class wxDateTimeWorkDays
    @wxheader{datetime.h}

    @todo Write wxDateTimeWorkDays documentation.

    @library{wxbase}
    @category{data}
*/
class wxDateTimeWorkDays
{
public:

};



/**
    @class wxDateSpan
    @wxheader{datetime.h}

    This class is a "logical time span" and is useful for implementing program
    logic for such things as "add one month to the date" which, in general,
    doesn't mean to add 60*60*24*31 seconds to it, but to take the same date
    the next month (to understand that this is indeed different consider adding
    one month to Feb, 15 -- we want to get Mar, 15, of course).

    When adding a month to the date, all lesser components (days, hours, ...)
    won't be changed unless the resulting date would be invalid: for example,
    Jan 31 + 1 month will be Feb 28, not (non-existing) Feb 31.

    Because of this feature, adding and subtracting back again the same
    wxDateSpan will @b not, in general, give back the original date: Feb 28 - 1
    month will be Jan 28, not Jan 31!

    wxDateSpan objects can be either positive or negative. They may be
    multiplied by scalars which multiply all deltas by the scalar: i.e.
    2*(1  month and  1  day) is 2 months and 2 days. They can be added together
    with wxDateTime or wxTimeSpan, but the type of result is different for each
    case.

    @warning If you specify both weeks and days, the total number of days added
             will be 7*weeks + days! See also GetTotalDays().

    Equality operators are defined for wxDateSpans. Two wxDateSpans are equal
    if and only if they both give the same target date when added to @b every
    source date. Thus wxDateSpan::Months(1) is not equal to
    wxDateSpan::Days(30), because they don't give the same date when added to
    Feb 1st. But wxDateSpan::Days(14) is equal to wxDateSpan::Weeks(2).

    Finally, notice that for adding hours, minutes and so on you don't need
    this class at all: wxTimeSpan will do the job because there are no
    subtleties associated with those (we don't support leap seconds).

    @library{wxbase}
    @category{data}

    @see @ref overview_datetime, wxDateTime
*/
class wxDateSpan
{
public:
    /**
        Constructs the date span object for the given number of years, months,
        weeks and days. Note that the weeks and days add together if both are
        given.
    */
    wxDateSpan(int years = 0, int months = 0, int weeks = 0, int days = 0);

    /**
        Returns the sum of two date spans.

        @returns A new wxDateSpan object with the result.
    */
    wxDateSpan Add(const wxDateSpan& other) const;
    /**
        Adds the given wxDateSpan to this wxDateSpan and returns a reference
        to itself.
    */
    wxDateSpan& Add(const wxDateSpan& other);

    /**
        Returns a date span object corresponding to one day.

        @see Days()
    */
    static wxDateSpan Day();

    /**
        Returns a date span object corresponding to the given number of days.

        @see Day()
    */
    static wxDateSpan Days(int days);

    /**
        Returns the number of days (not counting the weeks component) in this
        date span.

        @see GetTotalDays()
    */
    int GetDays() const;

    /**
        Returns the number of the months (not counting the years) in this date
        span.
    */
    int GetMonths() const;

    /**
        Returns the combined number of days in this date span, counting both
        weeks and days. This doesn't take months or years into account.

        @see GetWeeks(), GetDays()
    */
    int GetTotalDays() const;

    /**
        Returns the number of weeks in this date span.

        @see GetTotalDays()
    */
    int GetWeeks() const;

    /**
        Returns the number of years in this date span.
    */
    int GetYears() const;

    /**
        Returns a date span object corresponding to one month.

        @see Months()
    */
    static wxDateSpan Month();

    /**
        Returns a date span object corresponding to the given number of months.

        @see Month()
    */
    static wxDateSpan Months(int mon);

    /**
        Returns the product of the date span by the specified @a factor. The
        product is computed by multiplying each of the components by the
        @a factor.

        @returns A new wxDateSpan object with the result.
    */
    wxDateSpan Multiply(int factor) const;
    /**
        Multiplies this date span by the specified @a factor. The product is
        computed by multiplying each of the components by the @a factor.

        @returns A reference to this wxDateSpan object modified in place.
    */
    wxDateSpan& Multiply(int factor);

    /**
        Changes the sign of this date span.

        @see Negate()
    */
    wxDateSpan& Neg();

    /**
        Returns a date span with the opposite sign.

        @see Neg()
    */
    wxDateSpan Negate() const;

    /**
        Sets the number of days (without modifying any other components) in
        this date span.
    */
    wxDateSpan& SetDays(int n);

    /**
        Sets the number of months (without modifying any other components) in
        this date span.
    */
    wxDateSpan& SetMonths(int n);

    /**
        Sets the number of weeks (without modifying any other components) in
        this date span.
    */
    wxDateSpan& SetWeeks(int n);

    /**
        Sets the number of years (without modifying any other components) in
        this date span.
    */
    wxDateSpan& SetYears(int n);

    /**
        Returns the difference of two date spans.

        @returns A new wxDateSpan object with the result.
    */
    wxDateSpan Subtract(const wxDateSpan& other) const;
    /**
        Subtracts the given wxDateSpan to this wxDateSpan and returns a
        reference to itself.
    */
    wxDateSpan& Subtract(const wxDateSpan& other);

    /**
        Returns a date span object corresponding to one week.

        @see Weeks()
    */
    static wxDateSpan Week();

    /**
        Returns a date span object corresponding to the given number of weeks.

        @see Week()
    */
    static wxDateSpan Weeks(int weeks);

    /**
        Returns a date span object corresponding to one year.

        @see Years()
    */
    static wxDateSpan Year();

    /**
        Returns a date span object corresponding to the given number of years.

        @see Year()
    */
    static wxDateSpan Years(int years);

    /**
        Adds the given wxDateSpan to this wxDateSpan and returns the result.
    */
    wxDateSpan& operator+=(const wxDateSpan& other);

    /**
        Subtracts the given wxDateSpan to this wxDateSpan and returns the
        result.
    */
    wxDateSpan& operator-=(const wxDateSpan& other);

    /**
        Changes the sign of this date span.

        @see Negate()
    */
    wxDateSpan& operator-();

    /**
        Multiplies this date span by the specified @a factor. The product is
        computed by multiplying each of the components by the @a factor.

        @returns A reference to this wxDateSpan object modified in place.
    */
    wxDateSpan& operator*=(int factor);

    /**
        Returns @true if this date span is different from the other one.
    */
    bool operator!=(const wxDateSpan&) const;

    /**
        Returns @true if this date span is equal to the other one. Two date
        spans are considered equal if and only if they have the same number of
        years and months and the same total number of days (counting both days
        and weeks).
    */
    bool operator==(const wxDateSpan&) const;
};



/**
    @class wxTimeSpan
    @wxheader{datetime.h}

    wxTimeSpan class represents a time interval.

    @library{wxbase}
    @category{data}

    @see @ref overview_datetime, wxDateTime
*/
class wxTimeSpan
{
public:
    /**
        Default constructor, constructs a zero timespan.
    */
    wxTimeSpan();
    /**
        Constructs timespan from separate values for each component, with the
        date set to 0. Hours are not restricted to 0-24 range, neither are
        minutes, seconds or milliseconds.
    */
    wxTimeSpan(long hours, long min, long sec, long msec);

    /**
        Returns the absolute value of the timespan: does not modify the object.
    */
    wxTimeSpan Abs() const;

    /**
        Returns the sum of two time spans.

        @returns A new wxDateSpan object with the result.
    */
    wxTimeSpan Add(const wxTimeSpan& diff) const;
    /**
        Adds the given wxTimeSpan to this wxTimeSpan and returns a reference
        to itself.
    */
    wxTimeSpan& Add(const wxTimeSpan& diff);

    /**
        Returns the timespan for one day.
    */
    static wxTimespan Day();

    /**
        Returns the timespan for the given number of days.
    */
    static wxTimespan Days(long days);

    /**
        Returns the string containing the formatted representation of the time
        span. The following format specifiers are allowed after %:

        - @c H - Number of Hours
        - @c M - Number of Minutes
        - @c S - Number of Seconds
        - @c l - Number of Milliseconds
        - @c D - Number of Days
        - @c E - Number of Weeks
        - @c % - The percent character

        Note that, for example, the number of hours in the description above is
        not well defined: it can be either the total number of hours (for
        example, for a time span of 50 hours this would be 50) or just the hour
        part of the time span, which would be 2 in this case as 50 hours is
        equal to 2 days and 2 hours.

        wxTimeSpan resolves this ambiguity in the following way: if there had
        been, indeed, the @c %D format specified preceding the @c %H, then it
        is interpreted as 2. Otherwise, it is 50.

        The same applies to all other format specifiers: if they follow a
        specifier of larger unit, only the rest part is taken, otherwise the
        full value is used.
    */
    wxString Format(const wxString& = wxDefaultTimeSpanFormat) const;

    /**
        Returns the difference in number of days.
    */
    int GetDays() const;

    /**
        Returns the difference in number of hours.
    */
    int GetHours() const;

    /**
        Returns the difference in number of milliseconds.
    */
    wxLongLong GetMilliseconds() const;

    /**
        Returns the difference in number of minutes.
    */
    int GetMinutes() const;

    /**
        Returns the difference in number of seconds.
    */
    wxLongLong GetSeconds() const;

    /**
        Returns the internal representation of timespan.
    */
    wxLongLong GetValue() const;

    /**
        Returns the difference in number of weeks.
    */
    int GetWeeks() const;

    /**
        Returns the timespan for one hour.
    */
    static wxTimespan Hour();

    /**
        Returns the timespan for the given number of hours.
    */
    static wxTimespan Hours(long hours);

    /**
        Returns @true if two timespans are equal.
    */
    bool IsEqualTo(const wxTimeSpan& ts) const;

    /**
        Compares two timespans: works with the absolute values, i.e. -2 hours
        is longer than 1 hour. Also, it will return @false if the timespans are
        equal in absolute value.
    */
    bool IsLongerThan(const wxTimeSpan& ts) const;

    /**
        Returns @true if the timespan is negative.
    */
    bool IsNegative() const;

    /**
        Returns @true if the timespan is empty.
    */
    bool IsNull() const;

    /**
        Returns @true if the timespan is positive.
    */
    bool IsPositive() const;

    /**
        Compares two timespans: works with the absolute values, i.e. 1 hour is
        shorter than -2 hours. Also, it will return @false if the timespans are
        equal in absolute value.
    */
    bool IsShorterThan(const wxTimeSpan& ts) const;

    /**
        Returns the timespan for one millisecond.
    */
    static wxTimespan Millisecond();

    /**
        Returns the timespan for the given number of milliseconds.
    */
    static wxTimespan Milliseconds(long ms);

    /**
        Returns the timespan for one minute.
    */
    static wxTimespan Minute();

    /**
        Returns the timespan for the given number of minutes.
    */
    static wxTimespan Minutes(long min);

    /**
        Returns the product of this time span by @a n.

        @returns A new wxTimeSpan object with the result.
    */
    wxTimeSpan Multiply(int n) const;
    /**
        Multiplies this time span by @a n.

        @returns A reference to this wxTimeSpan object modified in place.
    */
    wxTimeSpan& Multiply(int n);

    /**
        Negate the value of the timespan.

        @see Negate()
    */
    wxTimeSpan& Neg();

    /**
        Returns timespan with inverted sign.

        @see Neg()
    */
    wxTimeSpan Negate() const;

    /**
        Returns the timespan for one second.
    */
    static wxTimespan Second();

    /**
        Returns the timespan for the given number of seconds.
    */
    static wxTimespan Seconds(long sec);

    /**
        Returns the difference of two time spans.

        @returns A new wxDateSpan object with the result.
    */
    wxTimeSpan Subtract(const wxTimeSpan& diff) const;
    /**
        Subtracts the given wxTimeSpan to this wxTimeSpan and returns a
        reference to itself.
    */
    wxTimeSpan& Subtract(const wxTimeSpan& diff);

    /**
        Returns the timespan for one week.
    */
    static wxTimespan Week();

    /**
        Returns the timespan for the given number of weeks.
    */
    static wxTimespan Weeks(long weeks);

    /**
        Adds the given wxTimeSpan to this wxTimeSpan and returns the result.
    */
    wxTimeSpan& operator+=(const wxTimeSpan& diff);

    /**
        Multiplies this time span by @a n.

        @returns A reference to this wxTimeSpan object modified in place.
    */
    wxTimeSpan& operator*=(int n);

    /**
        Negate the value of the timespan.

        @see Negate()
    */
    wxTimeSpan& operator-();

    /**
        Subtracts the given wxTimeSpan to this wxTimeSpan and returns the
        result.
    */
    wxTimeSpan& operator-=(const wxTimeSpan& diff);
};



/**
    @class wxDateTimeHolidayAuthority
    @wxheader{datetime.h}

    @todo Write wxDateTimeHolidayAuthority documentation.

    @library{wxbase}
    @category{misc}
*/
class wxDateTimeHolidayAuthority
{
public:

};

