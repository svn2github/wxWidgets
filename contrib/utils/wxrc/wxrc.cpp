/////////////////////////////////////////////////////////////////////////////
// Name:        wxrc.cpp
// Purpose:     XML resource compiler
// Author:      Vaclav Slavik
// Created:     2000/03/05
// RCS-ID:      $Id$
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
    #pragma implementation
    #pragma interface
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWindows headers
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/cmdline.h"
#include "wx/xml/xml.h"
#include "wx/xml/xmlio.h"
#include "wx/ffile.h"
#include "wx/wfstream.h"





/*
#if wxUSE_GUI
#error "You must compile the resource compiler with wxBase!"
#endif
*/

class XmlResApp : public wxApp
{
public:

#if wxUSE_GUI
    bool OnInit();
#else
    virtual int OnRun();
#endif
    
private:
    
    void ParseParams(const wxCmdLineParser& cmdline);
    void CompileRes();
    wxArrayString PrepareTempFiles();
    void FindFilesInXML(wxXmlNode *node, wxArrayString& flist, const wxString& inputPath);

    void DeleteTempFiles(const wxArrayString& flist);
    void MakePackageZIP(const wxArrayString& flist);
    void MakePackageCPP(const wxArrayString& flist);
            
    bool flagVerbose, flagCPP, flagCompress;
    wxString parOutput, parFuncname, parOutputPath;
    wxArrayString parFiles;
    int retCode;
};

IMPLEMENT_APP(XmlResApp)

#if wxUSE_GUI
bool XmlResApp::OnInit()
#else
int XmlResApp::OnRun()
#endif
{
    static const wxCmdLineEntryDesc cmdLineDesc[] =
    {
        { wxCMD_LINE_SWITCH, "v", "verbose", "be verbose" },
        { wxCMD_LINE_SWITCH, "c", "cpp-code",  "output C++ source rather than .rsc file" },
        { wxCMD_LINE_SWITCH, "u", "uncompressed",  "do not compress .xml files (C++ only)" },
        { wxCMD_LINE_OPTION, "n", "function",  "C++ function name (with -c) [InitXmlResource]" },
        { wxCMD_LINE_OPTION, "o", "output",  "output file [resource.rsc/cpp]" },
        { wxCMD_LINE_OPTION, "l", "list-of-handlers",  "output list of neccessary handlers to this file" },

        { wxCMD_LINE_PARAM,  NULL, NULL, "input file",
            wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_MULTIPLE },

        { wxCMD_LINE_NONE }
    };

    wxXmlDocument::AddHandler(new wxXmlIOHandlerBinZ);

    wxCmdLineParser parser(cmdLineDesc, argc, argv);

    switch (parser.Parse())
    {
        case -1:
            return 0;
            break;

        case 0:
            retCode = 0;
            ParseParams(parser);
            CompileRes();
#if wxUSE_GUI
            return FALSE;
#else
            return retCode;
#endif
            break;

        default:
#if wxUSE_GUI
            return FALSE;
#else
            return 1;
#endif
            break;
    }
}




void XmlResApp::ParseParams(const wxCmdLineParser& cmdline)
{
    flagVerbose = cmdline.Found("v");
    flagCPP = cmdline.Found("c");
    flagCompress = flagCPP && !cmdline.Found("u");

    if (!cmdline.Found("o", &parOutput)) 
        parOutput = flagCPP ? "resource.cpp" : "resource.rsc";
    parOutputPath = wxPathOnly(parOutput);
    if (!parOutputPath) parOutputPath = ".";

    if (!cmdline.Found("n", &parFuncname)) 
        parFuncname = "InitXmlResource";

    for (size_t i = 0; i < cmdline.GetParamCount(); i++)
        parFiles.Add(cmdline.GetParam(i));
}




void XmlResApp::CompileRes()
{
    wxArrayString files = PrepareTempFiles();

    wxRemoveFile(parOutput);

    if (!retCode)
    {        
        if (flagCPP)
            MakePackageCPP(files);
        else
            MakePackageZIP(files);
    }
        
    DeleteTempFiles(files);
}



wxArrayString XmlResApp::PrepareTempFiles()
{
    wxArrayString flist;
    
    for (size_t i = 0; i < parFiles.Count(); i++)
    {
        if (flagVerbose) 
            wxPrintf("processing " + parFiles[i] +  "...\n");

        wxXmlDocument doc;
        
        if (!doc.Load(parFiles[i]))
        {
            wxLogError("Error parsing file " + parFiles[i]);
            retCode = 1;
            continue;
        }
        
        wxString name, ext, path;
        wxSplitPath(parFiles[i], &path, &name, &ext);

        FindFilesInXML(doc.GetRoot(), flist, path);

        doc.Save(parOutputPath + "/" + name + ".xmb", flagCompress ? wxXML_IO_BINZ : wxXML_IO_BIN);
        flist.Add(name + ".xmb");
    }
    
    return flist;
}



// find all files mentioned in structure, e.g. <bitmap>filename</bitmap>
void XmlResApp::FindFilesInXML(wxXmlNode *node, wxArrayString& flist, const wxString& inputPath)
{
    wxXmlNode *n = node;
    if (n == NULL) return;
    n = n->GetChildren();
    
    while (n)
    {
        if ((node->GetType() == wxXML_ELEMENT_NODE) &&
            // parent is an element, i.e. has subnodes...
            (n->GetType() == wxXML_TEXT_NODE || 
            n->GetType() == wxXML_CDATA_SECTION_NODE) &&
            // ...it is textnode...
            (node/*not n!*/->GetName() == "bitmap"))
            // ...and known to contain filename
        {
            wxString fullname;
            wxString filename = n->GetContent();
            if (wxIsAbsolutePath(n->GetContent())) fullname = n->GetContent();
            else fullname = inputPath + "/" + n->GetContent();
            
            filename.Replace("/", "_");
            filename.Replace("\\", "_");
            filename.Replace("*", "_");
            filename.Replace("?", "_");
            n->SetContent(filename);
            
            if (flagVerbose) 
                wxPrintf("adding " + filename +  "...\n");

            flist.Add(filename);

            wxFileInputStream sin(fullname);
            wxFileOutputStream sout(parOutputPath + "/" + filename);
            sin.Read(sout); // copy the stream
        }
        
        // subnodes:
        if (n->GetType() == wxXML_ELEMENT_NODE)
            FindFilesInXML(n, flist, inputPath);
        
        n = n->GetNext();
    }
}



void XmlResApp::DeleteTempFiles(const wxArrayString& flist)
{
    for (size_t i = 0; i < flist.Count(); i++)
        wxRemoveFile(parOutputPath + "/" + flist[i]);
}



void XmlResApp::MakePackageZIP(const wxArrayString& flist)
{
    wxString files;
    
    for (size_t i = 0; i < flist.Count(); i++)
        files += flist[i] + " ";
    files.RemoveLast();
    
    if (flagVerbose) 
        wxPrintf("compressing " + parOutput +  "...\n");

    if (wxExecute("zip -9 -j " + wxString(flagVerbose ? "" : "-q ") + 
                  parOutput + " " + files, TRUE) == -1)
    {
        wxLogError("Unable to execute zip program. Make sure it is in the path.");
        wxLogError("You can download it at http://www.cdrom.com/pub/infozip/");
        retCode = 1;
        return;
    }
}




static wxString FileToCppArray(wxString filename, int num)
{
    wxString output;
    wxString tmp;
    wxString snum;
    wxFFile file(filename, "rb");
    size_t lng = file.Length();
    int linelng;
    
    snum.Printf("%i", num);
    output.Printf("static size_t xml_res_size_" + snum + " = %i;\n", lng);
    output += "static unsigned char xml_res_file_" + snum + "[] = \"\\\n";
    
    unsigned char *buffer = new unsigned char[lng];
    file.Read(buffer, lng);
    
    for (size_t i = 0, linelng = 0; i < lng; i++)
    {
        if (linelng > 70) 
        {
            linelng = 0;
            output += "\\\n";
        }
        if (buffer[i] < 32 || buffer[i] == '"' || buffer[i] == '\\')
        {
            tmp.Printf("\\%03o", buffer[i]);
            output += tmp;
            linelng += 4;
        }
        else
        {
            output << (wxChar)buffer[i];
            linelng++;
        }
    }
    
    delete[] buffer;
    
    output += "\"\n;\n\n";
    
    return output;
}


void XmlResApp::MakePackageCPP(const wxArrayString& flist)
{
    wxFFile file(parOutput, "wt");
    size_t i;

    if (flagVerbose) 
        wxPrintf("creating C++ source file " + parOutput +  "...\n");
    
    file.Write("\
#include \"wx/wxprec.h\"\n\
\n\
#ifdef __BORLANDC__\n\
    #pragma hdrstop\n\
#endif\n\
\n\
#ifndef WX_PRECOMP\n\
    #include \"wx/wx.h\"\n\
#endif\n\
\
#include \"wx/filesys.h\"\n\
#include \"wx/fs_mem.h\"\n\
#include \"wx/xml/xmlres.h\"\n\
#include \"wx/xml/xh_all.h\"\n\
\n");

    for (i = 0; i < flist.Count(); i++)
        file.Write(FileToCppArray(flist[i], i));
    
    file.Write("\
void " + parFuncname + "()\n\
{\n\
\n\
    // Check for memory FS. If not present, load the handler:\n\
    {\n\
        wxMemoryFSHandler::AddFile(\"xml_resource/dummy_file\", \"dummy one\");\n\
        wxFileSystem fsys;\n\
        wxFSFile *f = fsys.OpenFile(\"memory:xml_resource/dummy_file\");\n\
        wxMemoryFSHandler::RemoveFile(\"xml_resource/dummy_file\");\n\
        if (f) delete f;\n\
        else wxFileSystem::AddHandler(new wxMemoryFSHandler);\n\
    }\n\
\n");

    for (i = 0; i < flist.Count(); i++)
    {
        wxString s;
        s.Printf("    wxMemoryFSHandler::AddFile(\"xml_resource/" + flist[i] +
                 "\", xml_res_file_%i, xml_res_size_%i);\n", i, i);
        file.Write(s);
    }

    for (i = 0; i < parFiles.Count(); i++)
    {
        wxString name, ext, path;
        wxSplitPath(parFiles[i], &path, &name, &ext);
        file.Write("    wxTheXmlResource->Load(\"memory:xml_resource/" + 
                   name + ".xmb" + "\");\n");
    }
    
    file.Write("\n}\n");


}
