#include <wx/wx.h>
#include <wx/url.h>
#include <wx/xml/xml.h>

#include <stdio.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  wxString theUrl(wxT("http://sbp.enterprisedb.com/applications.xml"));
  wxURL url(theUrl);
//tryDownload:
tryDownload:
{
  url = theUrl;
    url.SetProxy(wxT("proxy.sios.com:8080"));
  {
    wxHTTP *http = (wxHTTP *)&url.GetProtocol();
      http->SetHeader(wxT("Host"), url.GetServer());
      //http->SetHeader(wxT("Accept"), wxT("*/*"));
  }
    fprintf(stderr, "cp %s\n", (char *) theUrl.char_str());
    //wxLogError(wxString::Format(wxT("cp1: %s"), theUrl.c_str(), wxT("hoge")));
    wxURLError err = url.GetError();
    if (err != wxURL_NOERR)
    {
        wxString msg;
        switch (err)
        {
            case wxURL_SNTXERR:
                msg = _("Could not parse the URL.");
                break;
            case wxURL_NOPROTO:
                msg = _("Unsupported protocol specified.");
                break;
            case wxURL_NOHOST:
                msg = _("No hostname specified in URL.");
                break;
            case wxURL_NOPATH:
                msg = _("No path specified in URL.");
                break;
            case wxURL_CONNERR:
                msg = _("A connection error occurred.");
                break;
            case wxURL_PROTOERR:
                wxProtocolError perr = url.GetProtocol().GetError();
                switch(perr)    
                {               
                    case wxPROTO_NETERR:
                        msg = _("A network error occured.");
                        break;                  
                    case wxPROTO_PROTERR:
                        msg = _("An error occured during negotiation.");
                        break;                  
                    case wxPROTO_CONNERR:
                        msg = _("A connection to the server could not be established.");
                        break;                  
                    case wxPROTO_NOFILE:
                        msg = _("The file does not exist.");
                        break;                  
                    default:            
                        msg = _("An unknown error occured.");
                        break;                  
                }
                break;
        }
        wxLogError(wxString::Format(_("Failed to open the application list: %s\n\nError: %s"), theUrl.c_str(), msg.c_str()));
        return false;
    }
  wxInputStream * ip = url.GetInputStream();
    // Handle http redirects if required
fprintf(stderr, "cp1\n");
    if (url.GetScheme() == wxT("http"))
    {
      wxHTTP *http = (wxHTTP *)&url.GetProtocol();
      if (http->GetResponse() == 301 || http->GetResponse() == 302)
      {
        theUrl = http->GetHeader(wxT("Location"));
        // Try again
        goto tryDownload;
        //continue;
      }
    }
                                                                                     
    if (! ip || ! ip->IsOk()) {
        wxLogError(wxT("Failed 0"));
        return (false);
    }
    //{
    //  char sz[512];
    //    ip->Read(sz, sizeof (sz));
    //    fprintf(stderr, "%s\n", sz);
    //}
    wxXmlDocument xml;
    if (! xml.Load(* ip)) {
        wxLogError(wxT("Failed 1"));
        return (false);
    }
} while (0);
fprintf(stderr, "cp done\n");
    return (true);
}


