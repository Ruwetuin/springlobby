//
// Class: BattleroomListCtrl
//

#include "battleroomlistctrl.h"
#include "iconimagelist.h"

BattleroomListCtrl::BattleroomListCtrl( wxWindow* parent ) : wxListCtrl(parent, -1, 
  wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER | wxLC_REPORT | wxLC_SINGLE_SEL )
{
  SetImageList( &icons(), wxIMAGE_LIST_NORMAL );
  SetImageList( &icons(), wxIMAGE_LIST_SMALL );
  SetImageList( &icons(), wxIMAGE_LIST_STATE );
  
  wxListItem col;
  
  col.SetText( _("r") );
  col.SetImage( -1 );
  InsertColumn( 0, col );

  col.SetText( _("s") );
  col.SetImage( -1 );
  InsertColumn( 1, col );
  
  col.SetText( _("c") );
  col.SetImage( -1 );
  InsertColumn( 2, col );

  col.SetText( _("f") );
  col.SetImage( -1 );
  InsertColumn( 3, col );
  
  col.SetText( _("r") );
  col.SetImage( -1 );
  InsertColumn( 4, col );
  
  col.SetText( _T("Nickname") );
  col.SetImage( -1 );
  InsertColumn( 5, col );
  
  col.SetText( _T("t") );
  col.SetImage( -1 );
  InsertColumn( 6, col );

  col.SetText( _T("a") );
  col.SetImage( -1 );
  InsertColumn( 7, col );

  col.SetText( _T("cpu") );
  col.SetImage( -1 );
  InsertColumn( 8, col );

  col.SetText( _T("Handicap") );
  col.SetImage( -1 );
  InsertColumn( 9, col );

#ifdef __WXMSW__
  SetColumnWidth( 0, 45 );
#else
  SetColumnWidth( 0, 20 );
#endif
  SetColumnWidth( 1, 20 );
  SetColumnWidth( 2, 20 );
  SetColumnWidth( 3, 20 );
  SetColumnWidth( 4, 20 );
  SetColumnWidth( 5, 170 );
  SetColumnWidth( 6, 26 );
  SetColumnWidth( 7, 26 );
  SetColumnWidth( 8, 80 );
  SetColumnWidth( 9, 60 );
}


BattleroomListCtrl::~BattleroomListCtrl()
{
  
}


void BattleroomListCtrl::UpdateList()
{
  
}


void BattleroomListCtrl::AddUser( User& user )
{
  int index = InsertItem( 0, ICON_NREADY );
  assert( index != -1 );
  SetItemData(index, (wxUIntPtr)&user );

  UpdateUser( index );
}


void BattleroomListCtrl::RemoveUser( User& user )
{
  DeleteItem( GetUserIndex( user ) );
}


void BattleroomListCtrl::UpdateUser( User& user )
{
  UpdateUser( GetUserIndex( user ) );
}


void BattleroomListCtrl::UpdateUser( const int& index )
{
  assert( index != -1 );
  
  wxListItem item;
  item.SetId( index );
   
  if (!GetItem( item )) assert(false);
    
  User& user = *((User*)GetItemData( index ));
  
  icons().SetColourIcon( user.GetBattleStatus().team, wxColour( user.GetBattleStatus().color_r, user.GetBattleStatus().color_g, user.GetBattleStatus().color_b ) );

  SetItemImage( index, (user.GetBattleStatus().spectator)?ICON_SPECTATOR:IconImageList::GetReadyIcon( user.GetBattleStatus().ready ) );
  SetItemColumnImage( index, 1, IconImageList::GetSideIcon( user.GetBattleStatus().side ) );
  SetItemColumnImage( index, 2, IconImageList::GetColourIcon( user.GetBattleStatus().team ) );
  SetItemColumnImage( index, 3, IconImageList::GetFlagIcon( user.GetCountry() ) );
  SetItemColumnImage( index, 4, IconImageList::GetRankIcon( user.GetStatus().rank ) );
  SetItem( index, 5, WX_STRING( user.GetNick() ) );
  if ( !user.GetBattleStatus().spectator ) {
    SetItem( index, 6, wxString::Format( _("%d"), user.GetBattleStatus().team + 1 ) );
    SetItem( index, 7, wxString::Format( _("%d"), user.GetBattleStatus().ally + 1 ) );
    SetItem( index, 9, wxString::Format( _("%d%%"), user.GetBattleStatus().handicap ) );
  } else {
    SetItem( index, 6, _("") );
    SetItem( index, 7, _("") );
    SetItem( index, 9, _("") );
  }
  SetItem( index, 8, wxString::Format( _("%.1f GHz"), user.GetCpu() / 1000.0 ) );
}


int BattleroomListCtrl::GetUserIndex( User& user )
{
  for (int i = 0; i < GetItemCount() ; i++ ) {
    if ( (unsigned long)&user == GetItemData( i ) ) return i;
  }
  debug_error( "didn't find the battle." );
	return -1;
}


