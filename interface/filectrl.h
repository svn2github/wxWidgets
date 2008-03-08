/////////////////////////////////////////////////////////////////////////////
// Name:        filectrl.h
// Purpose:     documentation for wxFileCtrl class
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxFileCtrl
    @wxheader{filectrl.h}
    
    This control allows the user to select a file. two implemetations exist, one
    for Gtk and another generic one for anything other than Gtk.
    It is only available if @c wxUSE_FILECTRL is set to 1.
    
    @beginStyleTable
    @style{wxFC_DEFAULT_STYLE}:
           The default style: wxFC_OPEN
    @style{wxFC_OPEN}:
           Creates an file control suitable for opening files. Cannot be
           combined with wxFC_SAVE.
    @style{wxFC_SAVE}:
           Creates an file control suitable for saving files. Cannot be
           combined with wxFC_OPEN.
    @style{wxFC_MULTIPLE}:
           For open control only, Allows selecting multiple files. Cannot be
           combined with wxFC_SAVE
    @style{wxFC_NOSHOWHIDDEN}:
           Hides the "Show Hidden Files" checkbox (Generic only)
    @endStyleTable
    
    @library{wxbase}
    @category{FIXME}
    
    @seealso
    wxGenericDirCtrl
*/
class wxFileCtrl : public wxWindow
{
public:
    //@{
    /**
        @param parent 
        Parent window, must not be non-@NULL.
        
        @param id 
        The identifier for the control.
        
        @param defaultDirectory 
        The initial directory shown in the control. Must be
        a valid path to a directory or the empty string.
        In case it is the empty string, the current working directory is used.
        
        @param defaultFilename 
        The default filename, or the empty string.
        
        @param wildcard 
        A wildcard specifying which files can be selected,
        such as "*.*" or "BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif".
        
        @param style 
        The window style, see wxFC_* flags.
        
        @param pos 
        Initial position.
        
        @param size 
        Initial size.
        
        @param name 
        Control name.
        
        @returns @true if the control was successfully created or @false if
                   creation failed.
    */
    wxFileCtrl();
        wxFileCtrl(wxWindow * parent, wxWindowID id,
                   const wxString& defaultDirectory = wxEmptyString,
                   const wxString& defaultFilename = wxEmptyString,
                   const wxPoint& wildCard = wxFileSelectorDefaultWildcardStr,
                   long style = wxFC_DEFAULT_STYLE,
                   const wxPoint& pos = wxDefaultPosition,
                   const wxSize& size = wxDefaultSize,
                   const wxString& name = "filectrl");
    //@}

    /**
        Create function for two-step construction. See wxFileCtrl() for details.
    */
    bool Create(wxWindow * parent, wxWindowID id,
                const wxString& defaultDirectory = wxEmptyString,
                const wxString& defaultFilename = wxEmptyString,
                const wxPoint& wildCard = wxFileSelectorDefaultWildcardStr,
                long style = wxFC_DEFAULT_STYLE,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                const wxString& name = "filectrl");

    /**
        Returns the current directory of the file control (i.e. the directory shown by
        it).
    */
    wxString GetDirectory();

    /**
        Returns the currently selected filename.
        For the controls having the @c wxFC_MULTIPLE style, use GetFilenames()
        instead
    */
    wxString GetFilename();

    /**
        Fills the array @e filenames with the filenames only of selected items. This
        function should only be used with the controls having the @c wxFC_MULTIPLE
        style,
        use GetFilename() for the others.
        
        @remarks filenames is emptied first.
    */
    void GetFilenames(wxArrayString& filenames);

    /**
        Returns the zero-based index of the currently selected filter.
    */
    int GetFilterIndex();

    /**
        Returns the full path (directory and filename) of the currently selected file.
        For the controls having the @c wxFC_MULTIPLE style, use GetPaths()
        instead
    */
    wxString GetPath();

    /**
        Fills the array @e paths with the full paths of the files chosen. This
        function should be used with the controls having the @c wxFC_MULTIPLE style,
        use GetPath() otherwise.
        
        @remarks paths is emptied first.
    */
    void GetPaths(wxArrayString& paths);

    /**
        Returns the current wildcard.
    */
    wxString GetWildcard();

    /**
        Sets(changes) the current directory displayed in the control.
        
        @returns Returns @true on success, @false otherwise.
    */
    bool SetDirectory(const wxString& directory);

    /**
        Selects a certain file.
        
        @returns Returns @true on success, @false otherwise
    */
    bool SetFilename(const wxString& filename);

    /**
        Sets the current filter index, starting from zero.
    */
    void SetFilterIndex(int filterIndex);

    /**
        Sets the wildcard, which can contain multiple file types, for example:
        
        "BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif"
    */
    void SetWildcard(const wxString& wildCard);

    /**
        Sets whether hidden files and folders are shown or not.
    */
    void ShowHidden(const bool show);
};


/**
    @class wxFileCtrlEvent
    @wxheader{filectrl.h}
    
    A file control event holds information about events associated with
    wxFileCtrl objects.
    
    @library{wxbase}
    @category{FIXME}
*/
class wxFileCtrlEvent : public wxCommandEvent
{
public:
    /**
        Constructor.
    */
    wxFileCtrlEvent(wxEventType type, wxObject evtObject, int id);

    /**
        Returns the current directory.
        In case of a @b EVT_FILECTRL_FOLDERCHANGED, this method returns the new
        directory.
    */
    wxString GetDirectory();

    /**
        Returns the file selected(assuming it is only one file).
    */
    wxString GetFile();

    /**
        Returns the files selected.
        In case of a @b EVT_FILECTRL_SELECTIONCHANGED, this method returns the
        files selected after the event.
    */
    wxArrayString GetFiles();

    /**
        Sets the files changed by this event.
    */
     wxFileCtrlEvent::SetFiles(const wxArrayString files);
};
