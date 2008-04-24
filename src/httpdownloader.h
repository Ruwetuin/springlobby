#ifndef SPRINGLOBBY_HEADERGUARD_HTTPDOWNLOADER
#define SPRINGLOBBY_HEADERGUARD_HTTPDOWNLOADER

class wxProgressDialog;
class UpdateProgressbar;
class HttpDownloader;

class UpdateProgressbar : public wxThread
{
  public:
    UpdateProgressbar( HttpDownloader& CallingClass, const wxString& FileUrl, const wxString& DestPath );
    ~UpdateProgressbar();
    void Init();
    void* Entry();
    void CloseThread();
    bool TestDestroy();
  private:
    HttpDownloader& m_calling_class;
    bool m_destroy;

    wxString m_destpath;
    wxString m_fileurl;
};

class HttpDownloader
{
  public:
    HttpDownloader( const wxString& FileUrl, const wxString& DestPath );
    ~HttpDownloader();
    void OnComplete(wxCommandEvent& event);

  protected:
    UpdateProgressbar m_thread_updater;



};



#endif // SPRINGLOBBY_HEADERGUARD_HTTPDOWNLOADER
