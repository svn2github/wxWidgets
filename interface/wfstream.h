/////////////////////////////////////////////////////////////////////////////
// Name:        wfstream.h
// Purpose:     documentation for wxTempFileOutputStream class
// Author:      wxWidgets team
// RCS-ID:      $Id$
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

/**
    @class wxTempFileOutputStream
    @wxheader{wfstream.h}

    wxTempFileOutputStream is an output stream based on wxTempFile. It
    provides a relatively safe way to replace the contents of the
    existing file.

    @library{wxbase}
    @category{streams}

    @seealso
    wxTempFile
*/
class wxTempFileOutputStream : public wxOutputStream
{
public:
    /**
        Associates wxTempFileOutputStream with the file to be replaced and opens it.
        You should use
        wxStreamBase::IsOk to verify if the constructor succeeded.
        
        Call Commit() or wxOutputStream::Close to
        replace the old file and close this one. Calling Discard()
        (or allowing the destructor to do it) will discard the changes.
    */
    wxTempFileOutputStream(const wxString& fileName);

    /**
        Validate changes: deletes the old file of the given name and renames the new
        file to the old name. Returns @true if both actions succeeded. If @false is
        returned it may unfortunately mean two quite different things: either that
        either the old file couldn't be deleted or that the new file couldn't be renamed
        to the old name.
    */
    bool Commit();

    /**
        Discard changes: the old file contents are not changed, the temporary file is
        deleted.
    */
    void Discard();
};


/**
    @class wxFFileOutputStream
    @wxheader{wfstream.h}

    This class represents data written to a file. There are actually
    two such groups of classes: this one is based on wxFFile
    whereas wxFileInputStream is based in
    the wxFile class.

    Note that wxOutputStream::SeekO
    can seek beyond the end of the stream (file) and will thus not return
    @e wxInvalidOffset for that.

    @library{wxbase}
    @category{streams}

    @seealso
    wxBufferedOutputStream, wxFFileInputStream, wxFileInputStream
*/
class wxFFileOutputStream : public wxOutputStream
{
public:
    //@{
    /**
        Initializes a file stream in write-only mode using the file descriptor @e fp.
    */
    wxFFileOutputStream(const wxString& filename,
                        const wxString& mode="w+b");
    wxFFileOutputStream(wxFFile& file);
    wxFFileOutputStream(FILE * fp);
    //@}

    /**
        Destructor.
    */
    ~wxFFileOutputStream();

    /**
        Returns @true if the stream is initialized and ready.
    */
#define bool IsOk()     /* implementation is private */
};


/**
    @class wxFileOutputStream
    @wxheader{wfstream.h}

    This class represents data written to a file. There are actually
    two such groups of classes: this one is based on wxFile
    whereas wxFFileInputStream is based in
    the wxFFile class.

    Note that wxOutputStream::SeekO
    can seek beyond the end of the stream (file) and will thus not return
    @e wxInvalidOffset for that.

    @library{wxbase}
    @category{streams}

    @seealso
    wxBufferedOutputStream, wxFileInputStream, wxFFileInputStream
*/
class wxFileOutputStream : public wxOutputStream
{
public:
    //@{
    /**
        Initializes a file stream in write-only mode using the file descriptor @e fd.
    */
    wxFileOutputStream(const wxString& ofileName);
    wxFileOutputStream(wxFile& file);
    wxFileOutputStream(int fd);
    //@}

    /**
        Destructor.
    */
    ~wxFileOutputStream();

    /**
        Returns @true if the stream is initialized and ready.
    */
#define bool IsOk()     /* implementation is private */
};


/**
    @class wxFileInputStream
    @wxheader{wfstream.h}

    This class represents data read in from a file. There are actually
    two such groups of classes: this one is based on wxFile
    whereas wxFFileInputStream is based in
    the wxFFile class.

    Note that wxInputStream::SeekI
    can seek beyond the end of the stream (file) and will thus not return
    @e wxInvalidOffset for that.

    @library{wxbase}
    @category{streams}

    @seealso
    wxBufferedInputStream, wxFileOutputStream, wxFFileOutputStream
*/
class wxFileInputStream : public wxInputStream
{
public:
    //@{
    /**
        Initializes a file stream in read-only mode using the specified file descriptor.
    */
    wxFileInputStream(const wxString& ifileName);
    wxFileInputStream(wxFile& file);
    wxFileInputStream(int fd);
    //@}

    /**
        Destructor.
    */
    ~wxFileInputStream();

    /**
        Returns @true if the stream is initialized and ready.
    */
#define bool IsOk()     /* implementation is private */
};


/**
    @class wxFFileInputStream
    @wxheader{wfstream.h}

    This class represents data read in from a file. There are actually
    two such groups of classes: this one is based on wxFFile
    whereas wxFileInputStream is based in
    the wxFile class.

    Note that wxInputStream::SeekI
    can seek beyond the end of the stream (file) and will thus not return
    @e wxInvalidOffset for that.

    @library{wxbase}
    @category{streams}

    @seealso
    wxBufferedInputStream, wxFFileOutputStream, wxFileOutputStream
*/
class wxFFileInputStream : public wxInputStream
{
public:
    //@{
    /**
        Initializes a file stream in read-only mode using the specified file pointer @e
        fp.
    */
    wxFFileInputStream(const wxString& filename,
                       const wxString& mode = "rb");
    wxFFileInputStream(wxFFile& file);
    wxFFileInputStream(FILE * fp);
    //@}

    /**
        Destructor.
    */
    ~wxFFileInputStream();

    /**
        Returns @true if the stream is initialized and ready.
    */
#define bool IsOk()     /* implementation is private */
};


/**
    @class wxFFileStream
    @wxheader{wfstream.h}


    @library{wxbase}
    @category{FIXME}

    @seealso
    wxStreamBuffer
*/
class wxFFileStream : public wxFFileOutputStream
{
public:
    /**
        Initializes a new file stream in read-write mode using the specified
        @e iofilename name.
    */
    wxFFileStream(const wxString& iofileName);
};


/**
    @class wxFileStream
    @wxheader{wfstream.h}


    @library{wxbase}
    @category{FIXME}

    @seealso
    wxStreamBuffer
*/
class wxFileStream : public wxFileOutputStream
{
public:
    /**
        Initializes a new file stream in read-write mode using the specified
        @e iofilename name.
    */
    wxFileStream(const wxString& iofileName);
};
