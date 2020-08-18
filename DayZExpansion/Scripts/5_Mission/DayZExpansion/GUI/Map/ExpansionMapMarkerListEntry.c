/**
 * ExpansionMapMarkerListEntry.c
 *
 * DayZ Expansion Mod
 * www.dayzexpansion.com
 * © 2020 DayZ Expansion Mod Team
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/.
 *
*/

class ExpansionMapMarkerListEntry extends ScriptedWidgetEventHandler
{
	private Widget m_Root;
	
	private Widget m_ListPanel;
	private ImageWidget m_Icon;
	private TextWidget m_Name;
	private ButtonWidget m_3DToggle;
	private ImageWidget m_3DToggleIcon;
	private ButtonWidget m_2DToggle;	
	private ImageWidget m_2DToggleIcon;
	
	private ExpansionMapMenu m_MapMenu;
	private ExpansionMapMarker m_Marker;
	private ExpansionMarkerData m_MarkerData;
	private ExpansionMarkerModule m_MarkerModule;
	
	private static int COLOR_NOFOCUS = ARGB(140,35,35,35);
	private static int COLOR_FOCUS = ARGB(140,255,255,255);
	
	private bool m_MouseHover = false;
	
	private ref ExpansionUITooltip m_InfoTooltip;
	
	// ------------------------------------------------------------
	// ExpansionMapMarkerListEntry Constructor
	// ------------------------------------------------------------	
	void ExpansionMapMarkerListEntry( ref ExpansionMapMenu map_menu, Widget list_category_parent, ref ExpansionMapMarker marker )
	{
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::ExpansionMapMarkerListEntry - Start");
		#endif
		
		m_Root = GetGame().GetWorkspace().CreateWidgets( "DayZExpansion/GUI/layouts/map/expansion_markerlist_entry.layout", list_category_parent );
	
		m_ListPanel = Widget.Cast(m_Root.FindAnyWidget("MarkerListEntryPanel"));
		m_Icon = ImageWidget.Cast(m_Root.FindAnyWidget("MarkerListEntryIcon"));
		m_Name = TextWidget.Cast(m_Root.FindAnyWidget("MarkerListEntryName"));

		m_2DToggle = ButtonWidget.Cast(m_Root.FindAnyWidget("visibility_marker_option_entry_2d"));
		m_2DToggleIcon = ImageWidget.Cast(m_Root.FindAnyWidget("visibility_marker_option_entry_2d_icon"));

		m_3DToggle = ButtonWidget.Cast(m_Root.FindAnyWidget("visibility_marker_option_entry_3d"));
		m_3DToggleIcon = ImageWidget.Cast(m_Root.FindAnyWidget("visibility_marker_option_entry_3d_icon"));
		
		m_Root.SetHandler(this);
		
		m_MapMenu = map_menu;
		m_Marker = marker;
		m_MarkerData = m_Marker.GetMarkerData();
		m_MarkerModule = ExpansionMarkerModule.Cast( GetModuleManager().GetModule( ExpansionMarkerModule ) );
		
		m_InfoTooltip = new ExpansionUITooltip("<p>" + "X:" + m_Marker.GetMarkerData().GetPosition()[0] + " Y:" + m_Marker.GetMarkerData().GetPosition()[1] + " Z:" + m_Marker.GetMarkerData().GetPosition()[2] + "</p>");
		m_InfoTooltip.SetTextPos("center");
		SetEntry();
		
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::ExpansionMapMarkerListEntry - End");
		#endif
	}
	
	// ------------------------------------------------------------
	// Set
	// ------------------------------------------------------------	
	void SetEntry()
	{
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::Set - Start");
		#endif
		
		if (m_Marker && m_Marker.GetMarkerData())
		{
			m_Icon.LoadImageFile(0, ExpansionIcons.GetPath(m_Marker.GetMarkerData().GetIconName()));
			m_Icon.SetImage(0);
			m_Icon.SetColor(m_Marker.GetMarkerData().GetColor());
			m_Name.SetText(m_Marker.GetMarkerData().GetName());
			m_Name.SetColor(m_Marker.GetMarkerData().GetColor());
			
			m_3DToggleIcon.LoadImageFile(0, EXPANSION_NOTIFICATION_ICON_3D_OFF);
			m_3DToggleIcon.LoadImageFile(1, EXPANSION_NOTIFICATION_ICON_3D_ON);
			
			m_2DToggleIcon.LoadImageFile(0, EXPANSION_NOTIFICATION_ICON_2D_OFF);
			m_2DToggleIcon.LoadImageFile(1, EXPANSION_NOTIFICATION_ICON_2D_ON);
			
			TextWidget button_lable = TextWidget.Cast( m_Root.FindAnyWidget( "MarkerListEntry3DButtonLable" ) );
			if ( !m_Marker.GetMarkerData().Is3D() )
			{
				m_3DToggleIcon.Show( false );
				m_3DToggle.SetFlags( WidgetFlags.IGNOREPOINTER | WidgetFlags.NOFOCUS );
			} else
			{
				m_3DToggleIcon.Show( true );
				m_3DToggle.ClearFlags( WidgetFlags.IGNOREPOINTER | WidgetFlags.NOFOCUS );
			}

			m_2DToggleIcon.SetImage( m_MarkerData.IsMapVisible() );
			m_3DToggleIcon.SetImage( m_MarkerData.IsWorldVisible() );
			
			m_InfoTooltip.SetText("<p>" + "X:" + m_Marker.GetMarkerData().GetPosition()[0] + " Y:" + m_Marker.GetMarkerData().GetPosition()[1] + " Z:" + m_Marker.GetMarkerData().GetPosition()[2] + "</p>");
		}
		
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::Set - End");
		#endif
	}
	
	// ------------------------------------------------------------
	// UpdateEntry
	// ------------------------------------------------------------	
	private void UpdateEntry()
	{
		m_Icon.LoadImageFile(0, ExpansionIcons.GetPath(m_Marker.GetMarkerData().GetIconName()));
		m_Icon.SetImage(0);
		m_Icon.SetColor(m_Marker.GetMarkerData().GetColor());
		m_Name.SetText(m_Marker.GetMarkerData().GetName());
		m_Name.SetColor(m_Marker.GetMarkerData().GetColor());
		
		if ( !m_Marker.GetMarkerData().Is3D() )
		{
			m_3DToggleIcon.Show( false );
			m_3DToggle.SetFlags( WidgetFlags.IGNOREPOINTER | WidgetFlags.NOFOCUS );
		} else
		{
			m_3DToggleIcon.Show( true );
			m_3DToggle.ClearFlags( WidgetFlags.IGNOREPOINTER | WidgetFlags.NOFOCUS );
		}
		
		m_InfoTooltip.SetText("<p>" + "X:" + m_Marker.GetMarkerData().GetPosition()[0] + " Y:" + m_Marker.GetMarkerData().GetPosition()[1] + " Z:" + m_Marker.GetMarkerData().GetPosition()[2] + "</p>");
	}
		
	// ------------------------------------------------------------
	// Override OnClick
	// ------------------------------------------------------------
	override bool OnClick( Widget w, int x, int y, int button )
	{
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::OnClick");
		#endif
		
		if ( w && w == m_3DToggle )
		{
			if ( m_MarkerData.IsWorldVisible() )
			{
				m_MarkerModule.RemoveVisibility( m_MarkerData, EXPANSION_MARKER_VIS_WORLD );

				if ( m_Marker.IsEditting() )
					m_Marker.CloseEditPanel();
			} else
			{
				m_MarkerModule.SetVisibility( m_MarkerData, EXPANSION_MARKER_VIS_WORLD );
			}
			
			m_MarkerModule.Refresh();

			UpdateToggleStates();
		} else if ( w && w == m_2DToggle )
		{
			if ( m_MarkerData.IsMapVisible() )
			{
				m_MarkerModule.RemoveVisibility( m_MarkerData, EXPANSION_MARKER_VIS_MAP );

				if ( m_Marker.IsEditting() )
					m_Marker.CloseEditPanel();
			} else
			{
				m_MarkerModule.SetVisibility( m_MarkerData, EXPANSION_MARKER_VIS_MAP );
			}
			
			m_MarkerModule.Refresh();

			UpdateToggleStates();
		}

		return false;
	}
	
	// ------------------------------------------------------------
	// Override OnMouseButtonDown
	// ------------------------------------------------------------
	override bool OnMouseButtonDown(Widget w, int x, int y, int button)
	{
		if ( button == 0 && w == m_ListPanel )
		{
			m_Marker.FocusOnMarker( true );
		}
		
		return false;
	}
	
	// ------------------------------------------------------------
	// GetMarker
	// ------------------------------------------------------------
	ref ExpansionMapMarker GetMarker()
	{
		return m_Marker;
	}

	ref ExpansionMarkerData GetData()
	{
		return m_MarkerData;
	}
	
	// ------------------------------------------------------------
	// Update
	// ------------------------------------------------------------
	void Update()
	{
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::Update - Start");
		#endif
		
		if (GetGame().GetInput().LocalPress("UAExpansionMapDeleteMarker", false))
		{
			RemoveMarker();
			return;
		}
		
	   	UpdateEntry();
		
		#ifdef EXPANSIONEXLOGPRINT
	   	EXLogPrint("ExpansionMapMarkerListEntry::Update - End");
		#endif
	}
	
	// ------------------------------------------------------------
	// Expansion RemoveMarker
	// Events when remove marker with delete key
	// ------------------------------------------------------------	
	void RemoveMarker()
	{
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::RemoveMarker - Start");
		#endif
		
		if (IsMouseHovering())
		{
			m_MapMenu.DeleteMarker(m_Marker);

			return;
		}
		
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::RemoveMarker - End");
		#endif
	}
	
	// ------------------------------------------------------------
	// Override OnMouseEnter
	// ------------------------------------------------------------
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::OnMouseEnter");
		#endif
		
		if (w == m_ListPanel)
		{
			m_ListPanel.SetColor(COLOR_FOCUS);
			m_MouseHover = true;
			m_InfoTooltip.ShowTooltip();
		}

		if ( w.GetName().IndexOf( "visibility_marker_option_entry_" ) == 0 )
		{
			w.GetChildren().SetColor( ARGB( 255, 150, 150, 150 ) );
		}

		return false;
	}
	
	// ------------------------------------------------------------
	// Override OnMouseLeave
	// ------------------------------------------------------------	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{	
		#ifdef EXPANSIONEXLOGPRINT
		EXLogPrint("ExpansionMapMarkerListEntry::OnMouseLeave");
		#endif

		if (w == m_ListPanel)
		{
			m_ListPanel.SetColor(COLOR_NOFOCUS);
			m_MouseHover = false;
			m_InfoTooltip.HideTooltip();
		}

		if ( w.GetName().IndexOf( "visibility_marker_option_entry_" ) == 0 )
		{
			w.GetChildren().SetColor( ARGB( 255, 255, 255, 255 ) );
			return true;
		}
		
		return false;
	}
	
	// ------------------------------------------------------------
	// IsMouseHovering
	// ------------------------------------------------------------	
	bool IsMouseHovering()
	{
		return m_MouseHover;
	}
	
	// ------------------------------------------------------------
	// UpdateToggleStates
	// ------------------------------------------------------------	
	void UpdateToggleStates()
	{
		m_2DToggleIcon.SetImage(m_MarkerData.IsMapVisible());
		m_3DToggleIcon.SetImage(m_MarkerData.IsWorldVisible());
	}
	
	// ------------------------------------------------------------
	// GetTooltip
	// ------------------------------------------------------------	
	ref ExpansionUITooltip GetTooltip()
	{
		return m_InfoTooltip;
	}
}