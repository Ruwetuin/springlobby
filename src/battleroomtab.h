//
// Class: BattleRoomTab
//

#ifndef _BATTLEROOMTAB_H_
#define _BATTLEROOMTAB_H_

#include <wx/panel.h>
#include <wx/splitter.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/combobox.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/statline.h>
#include <wx/checkbox.h>

#include "battle.h"
#include "battleroomlistctrl.h"
#include "chatpanel.h"

class Ui;

const wxString team_choices[] = { _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("8"), _("9"), _("10"), _("11"), _("12"), _("13"), _("14"), _("15"), _("16") };


class BattleRoomTab : public wxPanel
{
  public:
    BattleRoomTab( wxWindow* parent, Ui& ui, Battle& battle );
     ~BattleRoomTab();
  
    // BattleRoomTab interface
   BattleroomListCtrl& GetPlayersListCtrl() { assert( m_players != NULL); return *m_players; }
   
   Battle& GetBattle() { return m_battle; }
   ChatPanel& GetChatPanel() { return *m_chat; }
   
   void OnLeave( wxCommandEvent& event );
   void OnImReady( wxCommandEvent& event );
   void OnTeamSel( wxCommandEvent& event );
   void OnAllySel( wxCommandEvent& event );
   
   void OnUserJoined( User& user );
   void OnUserLeft( User& user );
   
  protected:
    // BattleRoomTab variables
  
    Ui& m_ui;
    Battle& m_battle;
  
    wxBoxSizer* m_players_sizer;
    wxBoxSizer* m_player_sett_sizer;
    wxBoxSizer* m_info_sizer;
    wxBoxSizer* m_top_sizer;
    wxBoxSizer* m_buttons_sizer;
    wxBoxSizer* m_main_sizer;
  
    wxComboBox* m_team_sel;
    wxComboBox* m_ally_sel;
    wxComboBox* m_color_sel;
    wxComboBox* m_side_sel;
  
    wxStaticText* m_team_lbl;
    wxStaticText* m_ally_lbl;
    wxStaticText* m_color_lbl;
    wxStaticText* m_side_lbl;
    wxStaticText* m_map_lbl;
  
    wxPanel* m_player_panel;
  
    BattleroomListCtrl* m_players;
    ChatPanel* m_chat;
    wxSplitterWindow* m_splitter;
  
    wxStaticLine* m_command_line;
  
    wxButton* m_leave_btn;
    wxButton* m_start_btn;
  
    wxCheckBox* m_ready_chk;
  
    DECLARE_EVENT_TABLE()
};

enum
{
    BROOM_LEAVE = wxID_HIGHEST,
    BROOM_IMREADY,
    BROOM_TEAMSEL,
    BROOM_ALLYSEL
};

#endif  //_BATTLEROOMTAB_H_

