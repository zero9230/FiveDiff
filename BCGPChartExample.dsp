# Microsoft Developer Studio Project File - Name="BCGPChartExample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BCGPChartExample - Win32 DebugGL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BCGPChartExample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BCGPChartExample.mak" CFG="BCGPChartExample - Win32 DebugGL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BCGPChartExample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BCGPChartExample - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BCGPChartExample - Win32 ReleaseStatic" (based on "Win32 (x86) Application")
!MESSAGE "BCGPChartExample - Win32 DebugGL" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BCGPChartExample - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BCGPChartExample - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPChartExampleD.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "BCGPChartExample - Win32 ReleaseStatic"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BCGPChartExample___Win32_ReleaseStatic"
# PROP BASE Intermediate_Dir "BCGPChartExample___Win32_ReleaseStatic"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\BinStatic"
# PROP Intermediate_Dir "ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_BCGCBPRO_STATIC_" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /i "..\..\BCGCBPro\Styles" /d "NDEBUG" /d "_AFXDLL" /d "_BCGCBPRO_STATIC_"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "BCGPChartExample - Win32 DebugGL"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BCGPChartExample___Win32_DebugGL"
# PROP BASE Intermediate_Dir "BCGPChartExample___Win32_DebugGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Bin"
# PROP Intermediate_Dir "DebugGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "USE_OPENGL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPChartExampleD.exe" /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"..\..\Bin/BCGPChartExampleDGL.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "BCGPChartExample - Win32 Release"
# Name "BCGPChartExample - Win32 Debug"
# Name "BCGPChartExample - Win32 ReleaseStatic"
# Name "BCGPChartExample - Win32 DebugGL"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BCGPChartExample.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPChartExample.rc
# End Source File
# Begin Source File

SOURCE=.\BCGPChartExampleDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BCGPChartExampleView.cpp
# End Source File
# Begin Source File

SOURCE=.\CChartAreaView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartAdvancedLegendView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartArea3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartAreaHistoricalView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartBar3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartBarView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartBubbleView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCombined3D.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCombinedView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartContainerView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartCustomAxisView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartDataTableView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartElementsView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartFormulaTrendView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartFormulaView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartFunnelView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartGridView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartHistoricalView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartHugeAverageDataView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartHugeDataView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartInteractiveView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartLegendView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartLine3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartLineView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartLogarithmicAxisView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartObjectsView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartPieGroupSmallerSlicesView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartPieView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartPointView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartPolarView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartPyramidView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartRangeBarView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartRealTimeView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartScaleBreaksView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSecondaryAxisView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSmartLabelsView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartStepLineView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartStockRTView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartStockView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSurfaceAdvancedView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartSurfaceView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartTernaryView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartThumbnailsView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartVirtualSeriesView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartVirtualView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintChartView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BCGPChartExample.h
# End Source File
# Begin Source File

SOURCE=.\BCGPChartExampleDoc.h
# End Source File
# Begin Source File

SOURCE=.\BCGPChartExampleView.h
# End Source File
# Begin Source File

SOURCE=.\CChartAreaView.h
# End Source File
# Begin Source File

SOURCE=.\ChartAdvancedLegendView.h
# End Source File
# Begin Source File

SOURCE=.\ChartArea3DView.h
# End Source File
# Begin Source File

SOURCE=.\ChartAreaHistoricalView.h
# End Source File
# Begin Source File

SOURCE=.\ChartBar3DView.h
# End Source File
# Begin Source File

SOURCE=.\ChartBarView.h
# End Source File
# Begin Source File

SOURCE=.\ChartBubbleView.h
# End Source File
# Begin Source File

SOURCE=.\ChartCombined3D.h
# End Source File
# Begin Source File

SOURCE=.\ChartCombinedView.h
# End Source File
# Begin Source File

SOURCE=.\ChartContainerView.h
# End Source File
# Begin Source File

SOURCE=.\ChartCustomAxisView.h
# End Source File
# Begin Source File

SOURCE=.\ChartDataTableView.h
# End Source File
# Begin Source File

SOURCE=.\ChartElementsView.h
# End Source File
# Begin Source File

SOURCE=.\ChartFormulaTrendView.h
# End Source File
# Begin Source File

SOURCE=.\ChartFormulaView.h
# End Source File
# Begin Source File

SOURCE=.\ChartFunnelView.h
# End Source File
# Begin Source File

SOURCE=.\ChartGridView.h
# End Source File
# Begin Source File

SOURCE=.\ChartHistoricalView.h
# End Source File
# Begin Source File

SOURCE=.\ChartHugeAverageDataView.h
# End Source File
# Begin Source File

SOURCE=.\ChartHugeDataView.h
# End Source File
# Begin Source File

SOURCE=.\ChartInteractiveView.h
# End Source File
# Begin Source File

SOURCE=.\ChartLegendView.h
# End Source File
# Begin Source File

SOURCE=.\ChartLine3DView.h
# End Source File
# Begin Source File

SOURCE=.\ChartLineView.h
# End Source File
# Begin Source File

SOURCE=.\ChartLogarithmicAxisView.h
# End Source File
# Begin Source File

SOURCE=.\ChartObjectsView.h
# End Source File
# Begin Source File

SOURCE=.\ChartPieGroupSmallerSlicesView.h
# End Source File
# Begin Source File

SOURCE=.\ChartPieView.h
# End Source File
# Begin Source File

SOURCE=.\ChartPointView.h
# End Source File
# Begin Source File

SOURCE=.\ChartPolarView.h
# End Source File
# Begin Source File

SOURCE=.\ChartPyramidView.h
# End Source File
# Begin Source File

SOURCE=.\ChartRangeBarView.h
# End Source File
# Begin Source File

SOURCE=.\ChartRealTimeView.h
# End Source File
# Begin Source File

SOURCE=.\ChartScaleBreaksView.h
# End Source File
# Begin Source File

SOURCE=.\ChartSecondaryAxisView.h
# End Source File
# Begin Source File

SOURCE=.\ChartSmartLabelsView.h
# End Source File
# Begin Source File

SOURCE=.\ChartStepLineView.h
# End Source File
# Begin Source File

SOURCE=.\ChartStockRTView.h
# End Source File
# Begin Source File

SOURCE=.\ChartStockView.h
# End Source File
# Begin Source File

SOURCE=.\ChartSurfaceAdvancedView.h
# End Source File
# Begin Source File

SOURCE=.\ChartSurfaceView.h
# End Source File
# Begin Source File

SOURCE=.\ChartTernaryView.h
# End Source File
# Begin Source File

SOURCE=.\ChartThumbnailsView.h
# End Source File
# Begin Source File

SOURCE=.\ChartVirtualSeriesView.h
# End Source File
# Begin Source File

SOURCE=.\ChartVirtualView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PrintChartView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WorkspaceBar.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\background.png
# End Source File
# Begin Source File

SOURCE=.\res\BCGPChartExample.ico
# End Source File
# Begin Source File

SOURCE=.\res\BCGPChartExample.rc2
# End Source File
# Begin Source File

SOURCE=.\res\BCGPChartExampleDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\texture1.png
# End Source File
# Begin Source File

SOURCE=.\res\texture2.png
# End Source File
# Begin Source File

SOURCE=.\res\texture3.png
# End Source File
# Begin Source File

SOURCE=.\res\texture4.png
# End Source File
# Begin Source File

SOURCE=.\res\texture5.png
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar_hc.png
# End Source File
# Begin Source File

SOURCE=.\res\toolbartree.bmp
# End Source File
# Begin Source File

SOURCE=.\res\wall.png
# End Source File
# Begin Source File

SOURCE=.\res\workspace.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\xptheme.xml
# End Source File
# End Target
# End Project
