#ifndef SPRINGLOBBY_HEADERGUARD_BATTLELISTCTRL_H
#define SPRINGLOBBY_HEADERGUARD_BATTLELISTCTRL_H

#include "battlelistfilter.h"
#include "battlelist.h"

#include "customlistctrl.h"

class wxMenu;
class Battle;
class wxListEvent;
class wxCommandEvent;
class Ui;


class BattleListCtrl : public customListCtrl
{
  public:
    BattleListCtrl( wxWindow* parent, Ui& ui );
    ~BattleListCtrl();


    int GetSelectedIndex();
    void SetSelectedIndex(const int newindex);
    int GetSelectedData();
    int GetIndexFromData( const int data );


    void Sort();

    void OnSelected( wxListEvent& event );
    void OnDeselected( wxListEvent& event );
    void OnListRightClick( wxListEvent& event );
    void OnDLMap( wxCommandEvent& event );
    void OnDLMod( wxCommandEvent& event );
    void OnMouseMotion(wxMouseEvent& event);
    void OnColClick( wxListEvent& event );
  protected:
    static int wxCALLBACK CompareStatusUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareStatusDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareCountryUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareCountryDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareRankUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareRankDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareDescriptionUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareDescriptionDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareMapUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareMapDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareModUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareModDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareHostUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareHostDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareSpectatorsUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareSpectatorsDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK ComparePlayerUP(long item1, long item2, long sortData);
    static int wxCALLBACK ComparePlayerDOWN(long item1, long item2, long sortData);
    static int wxCALLBACK CompareMaxPlayerUP(long item1, long item2, long sortData);
    static int wxCALLBACK CompareMaxPlayerDOWN(long item1, long item2, long sortData);


    struct {
      int col;
      bool direction;
    } m_sortorder[4];

    int m_selected;
    int m_selected_index;
    wxMenu* m_popup;
    Ui& m_ui;
    static Ui* m_ui_for_sort;


    DECLARE_EVENT_TABLE()
};

enum
{
    BLIST_LIST = wxID_HIGHEST,
    BLIST_DLMOD,
    BLIST_DLMAP
};

#endif // SPRINGLOBBY_HEADERGUARD_BATTLELISTCTRL_H
