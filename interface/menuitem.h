/////////////////////////////////////////////////////////////////////////////
// Name:        menuitem.h
// Purpose:     documentation for wxMenuItem class
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxMenuItem
    @wxheader{menuitem.h}

    A menu item represents an item in a menu. Note that you usually don't have to
    deal with it directly as wxMenu methods usually construct an
    object of this class for you.

    Also please note that the methods related to fonts and bitmaps are currently
    only implemented for Windows and GTK+.

    @library{wxcore}
    @category{menus}

    @seealso
    wxMenuBar, wxMenu
*/
class wxMenuItem : public wxObject
{
public:
    /**
        Constructs a wxMenuItem object.
        
        Menu items can be standard, or "stock menu items'', or custom. For the
        standard menu items (such as commands to open a file, exit the program and so
        on, see @ref overview_stockitems "stock items" for the full list) it is enough
        to
        specify just the stock ID and leave @e text and @e helpString empty. In
        fact, leaving at least @e text empty for the stock menu items is strongly
        recommended as they will have appearance and keyboard interface (including
        standard accelerators) familiar to the user.
        
        For the custom (non-stock) menu items, @e text must be specified and while
        @e helpString may be left empty, it's recommended to pass the item
        description (which is automatically shown by the library in the status bar when
        the menu item is selected) in this parameter.
        
        Finally note that you can e.g. use a stock menu label without using its stock
        help string:
        that is, stock properties are set independently one from the other.
        
        @param parentMenu
        Menu that the menu item belongs to.
        
        @param id
        Identifier for this menu item, or wxID_SEPARATOR to indicate a separator.
        
        @param text
        Text for the menu item, as shown on the menu. An accelerator
        key can be specified using the ampersand '' character. In order to embed an
        ampersand character in the menu item text, the ampersand must be doubled.
        
        @param helpString
        Optional help string that will be shown on the status bar.
        
        @param kind
        May be wxITEM_SEPARATOR, wxITEM_NORMAL,
        wxITEM_CHECK or wxITEM_RADIO
        
        @param subMenu
        If non-@NULL, indicates that the menu item is a submenu.
    */
    wxMenuItem(wxMenu* parentMenu = @NULL, int id = wxID_SEPARATOR,
               const wxString& text = "",
               const wxString& helpString = "",
               wxItemKind kind = wxITEM_NORMAL,
               wxMenu* subMenu = @NULL);

    /**
        Destructor.
    */
    ~wxMenuItem();

    /**
        Checks or unchecks the menu item.
        
        Note that this only works when the item is already appended to a menu.
    */
    void Check(bool check = @true);

    /**
        Enables or disables the menu item.
    */
    void Enable(bool enable = @true);

    /**
        Returns the background colour associated with the menu item (Windows only).
    */
    wxColour GetBackgroundColour();

    /**
        Returns the checked or unchecked bitmap (Windows only).
    */
    wxBitmap GetBitmap(bool checked = @true);

    /**
        Returns the font associated with the menu item (Windows only).
    */
    wxFont GetFont();

    /**
        Returns the help string associated with the menu item.
    */
    wxString GetHelp();

    /**
        Returns the menu item identifier.
    */
    int GetId();

    /**
        Returns the text associated with the menu item including any accelerator
        characters that were passed to the constructor or SetItemLabel.
        
        @sa GetItemLabelText(), GetLabelText()
    */
    wxString GetItemLabel();

    /**
        Returns the text associated with the menu item, without any accelerator
        characters.
        
        @sa GetItemLabel(), GetLabelText()
    */
    wxString GetItemLabelText();

    /**
        Returns the item kind, one of @c wxITEM_SEPARATOR, @c wxITEM_NORMAL,
        @c wxITEM_CHECK or @c wxITEM_RADIO.
    */
    wxItemKind GetKind();

    /**
        Returns the text associated with the menu item without any accelerator
        characters it might contain.
        
        This function is deprecated in favour of GetItemLabelText().
        
        @sa GetText(), GetLabelFromText()
    */
    wxString GetLabel();

    /**
        Strips all accelerator characters and mnemonics from the given @e text.
        For example,
        will return just @c "Hello".
        
        This function is deprecated; please use GetLabelText() instead.
        
        @sa GetText(), GetLabel()
    */
    static wxString GetLabelFromText(const wxString& text);

    /**
        Strips all accelerator characters and mnemonics from the given @e text.
        For example,
        will return just @c "Hello".
        
        @sa GetItemLabelText(), GetItemLabel()
    */
    static wxString GetLabelText(const wxString& text);

    /**
        Gets the width of the menu item checkmark bitmap (Windows only).
    */
    int GetMarginWidth();

    /**
        Returns the menu this menu item is in, or @NULL if this menu item is not
        attached.
    */
    wxMenu* GetMenu();

    /**
        Returns the text associated with the menu item.
        
        @b NB: this function is deprecated, please use
        GetItemLabel() or GetItemLabelText()
        instead.
    */
    wxString GetName();

    /**
        Returns the submenu associated with the menu item, or @NULL if there isn't one.
    */
    wxMenu* GetSubMenu();

    /**
        Returns the text associated with the menu item, such as it was passed to the
        wxMenuItem constructor, i.e. with any accelerator characters it may contain.
        
        This function is deprecated in favour of GetItemLabel().
        
        @sa GetLabel(), GetLabelFromText()
    */
    wxString GetText();

    /**
        Returns the text colour associated with the menu item (Windows only).
    */
    wxColour GetTextColour();

    /**
        Returns @true if the item is checkable.
    */
    bool IsCheckable();

    /**
        Returns @true if the item is checked.
    */
    bool IsChecked();

    /**
        Returns @true if the item is enabled.
    */
    bool IsEnabled();

    /**
        Returns @true if the item is a separator.
    */
    bool IsSeparator();

    /**
        Returns @true if the item is a submenu.
    */
    bool IsSubMenu();

    /**
        Sets the background colour associated with the menu item (Windows only).
    */
    void SetBackgroundColour(const wxColour& colour);

    /**
        Sets the bitmap for the menu item (Windows and GTK+ only). It is
        equivalent to wxMenuItem::SetBitmaps(bmp, wxNullBitmap).
    */
    void SetBitmap(const wxBitmap& bmp);

    /**
        Sets the checked/unchecked bitmaps for the menu item (Windows only). The first
        bitmap
        is also used as the single bitmap for uncheckable menu items.
    */
    void SetBitmaps(const wxBitmap& checked,
                    const wxBitmap& unchecked = wxNullBitmap);

    /**
        Sets the font associated with the menu item (Windows only).
    */
    void SetFont(const wxFont& font);

    /**
        Sets the help string.
    */
    void SetHelp(const wxString& helpString);

    /**
        Sets the label associated with the menu item.
    */
    void SetItemLabel(const wxString& label);

    /**
        Sets the width of the menu item checkmark bitmap (Windows only).
    */
    void SetMarginWidth(int width);

    /**
        Sets the parent menu which will contain this menu item.
    */
    void SetMenu(const wxMenu* menu);

    /**
        Sets the submenu of this menu item.
    */
    void SetSubMenu(const wxMenu* menu);

    /**
        Sets the text associated with the menu item.
        
        This function is deprecated in favour of SetItemLabel().
    */
    void SetText(const wxString& text);

    /**
        Sets the text colour associated with the menu item (Windows only).
    */
    void SetTextColour(const wxColour& colour);
};
