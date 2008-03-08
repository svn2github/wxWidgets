/////////////////////////////////////////////////////////////////////////////
// Name:        checkbox.h
// Purpose:     documentation for wxCheckBox class
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxCheckBox
    @wxheader{checkbox.h}

    A checkbox is a labelled box which by default is either on (checkmark is
    visible) or off (no checkmark). Optionally (when the wxCHK_3STATE style flag
    is set) it can have a third state, called the mixed or undetermined state.
    Often this is used as a "Does Not Apply" state.

    @beginStyleTable
    @style{wxCHK_2STATE}:
           Create a 2-state checkbox. This is the default.
    @style{wxCHK_3STATE}:
           Create a 3-state checkbox. Not implemented in wxMGL, wxOS2 and
           wxGTK built against GTK+ 1.2.
    @style{wxCHK_ALLOW_3RD_STATE_FOR_USER}:
           By default a user can't set a 3-state checkbox to the third state.
           It can only be done from code. Using this flags allows the user to
           set the checkbox to the third state by clicking.
    @style{wxALIGN_RIGHT}:
           Makes the text appear on the left of the checkbox.
    @endStyleTable

    @beginEventTable
    @event{EVT_CHECKBOX(id\, func)}:
           Process a wxEVT_COMMAND_CHECKBOX_CLICKED event, when the checkbox
           is clicked.
    @endEventTable

    @library{wxcore}
    @category{ctrl}
    @appearance{checkbox.png}

    @seealso
    wxRadioButton, wxCommandEvent
*/
class wxCheckBox : public wxControl
{
public:
    //@{
    /**
        Constructor, creating and showing a checkbox.
        
        @param parent
        Parent window. Must not be @NULL.
        
        @param id
        Checkbox identifier. The value wxID_ANY indicates a default value.
        
        @param label
        Text to be displayed next to the checkbox.
        
        @param pos
        Checkbox position. If wxDefaultPosition is specified then a default
        position is chosen.
        
        @param size
        Checkbox size. If wxDefaultSize is specified then a default size is
        chosen.
        
        @param style
        Window style. See wxCheckBox.
        
        @param validator
        Window validator.
        
        @param name
        Window name.
        
        @sa Create(), wxValidator
    */
    wxCheckBox();
    wxCheckBox(wxWindow* parent, wxWindowID id,
               const wxString& label,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize,
               long style = 0,
               const wxValidator& val,
               const wxString& name = "checkBox");
    //@}

    /**
        Destructor, destroying the checkbox.
    */
    ~wxCheckBox();

    /**
        Creates the checkbox for two-step construction. See wxCheckBox()
        for details.
    */
    bool Create(wxWindow* parent, wxWindowID id,
                const wxString& label,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = 0,
                const wxValidator& val,
                const wxString& name = "checkBox");

    /**
        Gets the state of a 3-state checkbox.
        
        @returns Returns wxCHK_UNCHECKED when the checkbox is unchecked,
                   wxCHK_CHECKED  when it is checked and
                   wxCHK_UNDETERMINED when it's in the undetermined
                   state. Asserts when the function is used with a
                   2-state checkbox.
    */
    wxCheckBoxState Get3StateValue();

    /**
        Gets the state of a 2-state checkbox.
        
        @returns Returns @true if it is checked, @false otherwise.
    */
    bool GetValue();

    /**
        Returns whether or not the checkbox is a 3-state checkbox.
        
        @returns Returns @true if this checkbox is a 3-state checkbox, @false if
                   it's a 2-state checkbox.
    */
    bool Is3State();

    /**
        Returns whether or not the user can set the checkbox to the third state.
        
        @returns Returns @true if the user can set the third state of this
                   checkbox, @false if it can only be set
                   programmatically or if it's a 2-state checkbox.
    */
    bool Is3rdStateAllowedForUser();

    /**
        This is just a maybe more readable synonym for
        GetValue(): just as the latter, it returns
        @true if the checkbox is checked and @false otherwise.
    */
    bool IsChecked();

    /**
        Sets the checkbox to the given state. This does not cause a
        wxEVT_COMMAND_CHECKBOX_CLICKED event to get emitted.
        
        @param state
        If @true, the check is on, otherwise it is off.
    */
    void SetValue(bool state);
};
