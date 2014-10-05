//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: GDJS.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef GDJS_BASE_CLASSES_H
#define GDJS_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/webview.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/statbmp.h>
#include <wx/hyperlink.h>
#include <wx/button.h>
#include <wx/choicebk.h>
#include <wx/panel.h>
#include <wx/imaglist.h>
#include <wx/statbox.h>
#include <wx/checkbox.h>

class BaseUploadOnlineDialog : public wxDialog
{
protected:
    wxStaticText* m_staticText15;
    wxWebView* webView;
    wxStaticText* m_staticText151;
    wxTextCtrl* packageLocationEdit;
    wxStaticLine* m_staticLine25;
    wxStaticBitmap* m_staticBitmap31;
    wxHyperlinkCtrl* m_hyperLink29;
    wxButton* m_button6;

protected:
    virtual void OnCloseBtClicked(wxCommandEvent& event) { event.Skip(); }

public:
    BaseUploadOnlineDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Upload to GameDevShare.com"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800,750), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER);
    virtual ~BaseUploadOnlineDialog();
};


class BaseProjectExportDialog : public wxDialog
{
protected:
    wxStaticText* m_staticText59;
    wxChoicebook* exportChoice;
    wxPanel* m_panel63;
    wxPanel* gdsharelogoPanel;
    wxStaticBitmap* m_staticBitmap57;
    wxStaticText* m_staticText65;
    wxStaticText* m_staticText67;
    wxPanel* m_panel61;
    wxStaticText* ID_STATICTEXT4;
    wxTextCtrl* exportFolderEdit;
    wxButton* browseBt;
    wxCheckBox* minifyCheck;
    wxHyperlinkCtrl* nodejsLink;
    wxStaticText* ID_STATICTEXT2;
    wxStaticText* ID_STATICTEXT1;
    wxStaticText* ID_STATICTEXT3;
    wxHyperlinkCtrl* ID_HYPERLINKCTRL2;
    wxPanel* m_panel118;
    wxPanel* cocoonjslogoPanel22;
    wxStaticBitmap* m_staticBitmap5744;
    wxStaticText* m_staticText6555;
    wxStaticText* m_staticText6768;
    wxPanel* m_panel71;
    wxPanel* cocoonjslogoPanel2;
    wxStaticBitmap* m_staticBitmap574;
    wxStaticText* m_staticText655;
    wxStaticText* m_staticText676;
    wxStaticBitmap* ID_STATICBITMAP2;
    wxHyperlinkCtrl* ID_HYPERLINKCTRL1;
    wxButton* closeBt;
    wxButton* exportBt;

protected:
    virtual void OnBrowseBtClick(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCloseBtClicked(wxCommandEvent& event) { event.Skip(); }
    virtual void OnExportBtClicked(wxCommandEvent& event) { event.Skip(); }

public:
    BaseProjectExportDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Export the project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1,-1), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~BaseProjectExportDialog();
};


class BaseCocoonJSUploadDialog : public wxDialog
{
protected:
    wxPanel* cocoonjslogoPanel27;
    wxStaticBitmap* m_staticBitmap5749;
    wxStaticText* m_staticText101;
    wxHyperlinkCtrl* m_hyperLink104;
    wxStaticText* m_staticText15111;
    wxTextCtrl* packageLocationEdit;
    wxStaticText* m_staticText106;
    wxButton* m_button108;

protected:
    virtual void OnCloseBtClicked(wxCommandEvent& event) { event.Skip(); }

public:
    BaseCocoonJSUploadDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Upload the packaged game to CocoonJS cloud compiler"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~BaseCocoonJSUploadDialog();
};


class BaseIntelXDKPackageDialog : public wxDialog
{
protected:
    wxPanel* cocoonjslogoPanel274;
    wxStaticBitmap* m_staticBitmap57496;
    wxStaticText* m_staticText1017;
    wxHyperlinkCtrl* m_hyperLink1048;
    wxStaticText* m_staticText1511110;
    wxTextCtrl* packageLocationEdit;
    wxStaticText* m_staticText10611;
    wxStaticBitmap* ID_STATICBITMAP216;
    wxHyperlinkCtrl* ID_HYPERLINKCTRL117;
    wxButton* m_button10812;

protected:
    virtual void OnCloseClicked(wxCommandEvent& event) { event.Skip(); }

public:
    BaseIntelXDKPackageDialog(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Package the game with Intel XDK"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,300), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~BaseIntelXDKPackageDialog();
};

#endif
