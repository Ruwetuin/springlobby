//
// Class: MainWindow
//

#include <wx/frame.h>
#include <wx/intl.h>
#include <wx/textdlg.h>
#include <wx/imaglist.h>
#include <wx/icon.h>
#include "mainwindow.h"
#include "settings.h"
#include "ui.h"
#include "images/bot.xpm"

#include "images/chat_icon.xpm"
#include "images/join_icon.xpm"
#include "images/options_icon.xpm"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)

  EVT_MENU( MENU_JOIN, MainWindow::OnMenuJoin )
  EVT_MENU( MENU_CHAT, MainWindow::OnMenuChat )
  EVT_MENU( MENU_CONNECT, MainWindow::OnMenuConnect )
  EVT_MENU( MENU_DISCONNECT, MainWindow::OnMenuDisconnect )
  EVT_MENU( MENU_QUIT, MainWindow::OnMenuQuit )
  EVT_MENU( MENU_USYNC, MainWindow::OnUnitsyncReload )
  EVT_MENU( MENU_TRAC, MainWindow::OnReportBug )
  EVT_MENU( MENU_DOC, MainWindow::OnShowDocs )

END_EVENT_TABLE()


MainWindow::MainWindow( Ui& ui ) : wxFrame((wxFrame *)NULL, -1, _T("Spring Lobby"),
                               wxPoint(50, 50), wxSize(450, 340)), m_ui(ui)
{
  SetIcon( wxIcon(bot_xpm) );
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(MENU_CONNECT, _T("&Connect..."));
  menuFile->Append(MENU_DISCONNECT, _T("&Disconnect"));
  menuFile->AppendSeparator();
  menuFile->Append(MENU_QUIT, _T("&Quit"));

  wxMenu *menuEdit = new wxMenu;

  wxMenu *menuTools = new wxMenu;
  menuTools->Append(MENU_JOIN, _T("&Join channel..."));
  menuTools->Append(MENU_CHAT, _T("Open &chat..."));
  menuTools->AppendSeparator();
  menuTools->Append(MENU_USYNC, _T("&Reload unitsync"));

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(MENU_ABOUT, _T("&About"));
  menuHelp->Append(MENU_TRAC, _T("&Report a bug..."));
  menuHelp->Append(MENU_DOC, _T("&Documentation"));

  wxMenuBar *menubar = new wxMenuBar;
  menubar->Append(menuFile, _T("&File"));
  menubar->Append(menuEdit, _T("&Edit"));
  menubar->Append(menuTools, _T("&Tools"));
  menubar->Append(menuHelp, _T("&Help"));
  SetMenuBar(menubar);

  m_main_sizer = new wxBoxSizer( wxHORIZONTAL );
  m_func_tabs = new wxListbook( this, -1, wxDefaultPosition, wxDefaultSize, wxLB_LEFT );

  m_func_tab_images = new wxImageList( 64, 64 );
  m_func_tab_images->Add( wxIcon(chat_icon_xpm) );
  m_func_tab_images->Add( wxIcon(join_icon_xpm) );
  m_func_tab_images->Add( wxIcon(options_icon_xpm) );

  m_func_tabs->AssignImageList( m_func_tab_images );
  m_chat_tab = new MainChatTab( m_func_tabs, m_ui );
  m_join_tab = new MainJoinBattleTab( m_func_tabs, m_ui );
  m_opts_tab = new MainOptionsTab( m_func_tabs, m_ui );

  m_func_tabs->AddPage( m_chat_tab, _(""), true, 0 );
  m_func_tabs->AddPage( m_join_tab, _(""), false, 1 );
  m_func_tabs->AddPage( m_opts_tab, _(""), false, 2 );

  m_main_sizer->Add( m_func_tabs, 1, wxEXPAND | wxALL, 2 );

  SetSizer( m_main_sizer );

  SetSize( sett().GetMainWindowLeft(), sett().GetMainWindowTop(), sett().GetMainWindowWidth(), sett().GetMainWindowHeight() );
  Layout();
}


MainWindow::~MainWindow()
{
  int x, y, w, h;
  GetSize( &w, &h );
  sett().SetMainWindowHeight( h );
  sett().SetMainWindowWidth( w );
  GetPosition( &x, &y );
  sett().SetMainWindowTop( y );
  sett().SetMainWindowLeft( x );
  sett().SaveSettings();
  m_ui.m_main_win = NULL;
}

/*
//! @brief Get the ChatPanel dedicated to server output and input
ChatPanel& servwin()
{
  return m_ui.mw().GetChatTab().ServerChat();
}
*/

//! @brief Returns the curent MainChatTab object
MainChatTab& MainWindow::GetChatTab()
{
  assert( m_chat_tab != NULL );
  return *m_chat_tab;
}


//! @brief Open a new chat tab with a channel chat
//!
//! @param channel The channel name
//! @note This does NOT join the chatt.
//! @sa Server::JoinChannel OpenPrivateChat
void MainWindow::OpenChannelChat( Channel& channel )
{
  assert( m_chat_tab != NULL );
  m_chat_tab->AddChatPannel( channel );
}


//! @brief Open a new chat tab with a private chat
//!
//! @param nick The user to whom the chatwindow should be opened to
void MainWindow::OpenPrivateChat( User& user )
{
  assert( m_chat_tab != NULL );
  m_chat_tab->AddChatPannel( user );
}


//! @brief Close all chat tabs, both private and channel
//!
//! @todo Implement
void MainWindow::CloseAllChats()
{
}


//! @brief Displays the lobby configuration.
void MainWindow::ShowConfigure()
{
  m_func_tabs->SetSelection( 2 );
}


//! @brief Called when join channel menuitem is clicked
void MainWindow::OnMenuJoin( wxCommandEvent& event )
{

  if ( !m_ui.IsConnected() ) return;
  wxString answer;
  if ( Ui::AskText( _T("Join channel..."), _T("Name of channel to join"), answer ) ) {
    m_ui.JoinChannel( answer, _("") );
  }

}


void MainWindow::OnMenuChat( wxCommandEvent& event )
{

  if ( !m_ui.IsConnected() ) return;
  wxString answer;
  if ( Ui::AskText( _T("Open Private Chat..."), _T("Name of user"), answer ) ) {
    if (m_ui.GetServer().UserExists( STL_STRING(answer) ) ) {
      OpenPrivateChat( m_ui.GetServer().GetUser( STL_STRING(answer) ) );
    }
  }

}


void MainWindow::OnMenuConnect( wxCommandEvent& event )
{
  m_ui.ShowConnectWindow();
}


void MainWindow::OnMenuDisconnect( wxCommandEvent& event )
{
  m_ui.Disconnect();
}


void MainWindow::OnMenuQuit( wxCommandEvent& event )
{
  m_ui.Quit();
}

void MainWindow::OnUnitsyncReload( wxCommandEvent& event )
{
  usync().FreeUnitsyncLib();
  usync().LoadUnitsyncLib();
  m_join_tab->GetBattleListTab().UpdateList();
}


void MainWindow::OnReportBug( wxCommandEvent& event )
{
  wxLaunchDefaultBrowser( _("http://tc.serveftp.net/trac/newticket") );
}


void MainWindow::OnShowDocs( wxCommandEvent& event )
{
  wxLaunchDefaultBrowser( _("http://tc.serveftp.net/trac") );
}

