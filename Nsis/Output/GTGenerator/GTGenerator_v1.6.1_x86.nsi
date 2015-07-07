############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.19.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "GTGenerator_v1.6.1_x86"
!define COMP_NAME "GPRS"
#!define WEB_SITE "http://gta.manizales.unal.edu.co/signal/index.php"
!define VERSION "00.00.01.00"
!define COPYRIGHT "GPRS © 2015"
!define DESCRIPTION "Ground Truth Generator"
!define INSTALLER_NAME "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Nsis\Output\GTGenerator\setup_GTGenerator_v1.6.1_x86.exe"
!define MAIN_APP_EXE "GTGenerator.exe"
!define INSTALL_TYPE "SetShellVarContext current"
!define REG_ROOT "HKCU"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

######################################################################

VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${VERSION}"

######################################################################

SetCompressor LZMA
Name "${APP_NAME}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\${APP_NAME}"

######################################################################

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING

!define MUI_ICON "gt_icon.ico"
!define MUI_UNICON "gt_icon.ico"

!insertmacro MUI_PAGE_WELCOME
!define MUI_WELCOMEPAGE_TITLE "${APP_NAME} Installer"

!ifdef LICENSE_TXT
!insertmacro MUI_PAGE_LICENSE "${LICENSE_TXT}"
!endif

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "GTGenerator_v1.6.1_x86"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN "$INSTDIR\${MAIN_APP_EXE}"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM

!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

######################################################################

Section -MainProgram
${INSTALL_TYPE}
SetOverwrite ifnewer
CreateDirectory "$INSTDIR\Xml"
SetOutPath "$INSTDIR\Xml"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\GTGenerator\Resources\Xml\rois.xsd"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\GTGenerator\Resources\Xml\labels.xsd"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\GTGenerator\Resources\Xml\gtp.xsd"
SetOutPath "$INSTDIR"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Win32\Release\GTGenerator.exe"
File "gt_icon.ico"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\libeay32.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\libmysql.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\libpq.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\msvcp100.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\msvcr100.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\msvcr120.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_calib3d2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_contrib2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_core2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_features2d2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_flann2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_gpu2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_highgui2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_imgproc2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_legacy2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_ml2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_nonfree2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_objdetect2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_ocl2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_photo2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_stitching2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_superres2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_video2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\opencv_videostab2410.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\phonon4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\Qt3Support4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtCLucene4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtCore4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtDeclarative4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtDesigner4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtDesignerComponents4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtGui4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtHelp4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtMultimedia4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtNetwork4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtOpenGL4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtScript4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtScriptTools4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtSql4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtSvg4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtTest4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtWebKit4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtXml4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\QtXmlPatterns4.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\ssleay32.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\Xalan-C_1_11.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\XalanMessages_1_11.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\xerces-c_3_1.dll"
File "G:\data\sebastianvilla139\work\qt\last_v19\GTGenerator\Runtime\x86\xqilla23.dll"
SectionEnd

######################################################################

Section -Icons_Reg
SetShellVarContext all
SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"

!ifdef REG_START_MENU
#!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
#CreateDirectory "$SMPROGRAMS\$SM_Folder"
#CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
#CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "" "$INSTDIR\gt_icon.ico"
#CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "" "$INSTDIR\gt_icon.ico"
#CreateShortCut "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
#WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
#CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
#!insertmacro MUI_STARTMENU_WRITE_END
!endif

#!ifndef REG_START_MENU
CreateDirectory "$SMPROGRAMS\GTGenerator_v1.6.1_x86"
CreateShortCut "$SMPROGRAMS\GTGenerator_v1.6.1_x86\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "" "$INSTDIR\gt_icon.ico"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}" "" "$INSTDIR\gt_icon.ico"
CreateShortCut "$SMPROGRAMS\GTGenerator_v1.6.1_x86\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

#!ifdef WEB_SITE
#WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
#CreateShortCut "$SMPROGRAMS\GTGenerator_v1.6.1_x86\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
#!endif
#!endif

WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

!ifdef WEB_SITE
#WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
!endif
SectionEnd

######################################################################

Section Uninstall
SetShellVarContext all
${INSTALL_TYPE}
Delete "$INSTDIR\${MAIN_APP_EXE}"
Delete "$INSTDIR\libeay32.dll"
Delete "$INSTDIR\libintl-8.dll"
Delete "$INSTDIR\libmysql.dll"
Delete "$INSTDIR\libpq.dll"
Delete "$INSTDIR\msvcp100.dll"
Delete "$INSTDIR\msvcr100.dll"
Delete "$INSTDIR\msvcr120.dll"
Delete "$INSTDIR\opencv_calib3d2410.dll"
Delete "$INSTDIR\opencv_contrib2410.dll"
Delete "$INSTDIR\opencv_core2410.dll"
Delete "$INSTDIR\opencv_features2d2410.dll"
Delete "$INSTDIR\opencv_ffmpeg2410_64.dll"
Delete "$INSTDIR\opencv_flann2410.dll"
Delete "$INSTDIR\opencv_gpu2410.dll"
Delete "$INSTDIR\opencv_highgui2410.dll"
Delete "$INSTDIR\opencv_imgproc2410.dll"
Delete "$INSTDIR\opencv_legacy2410.dll"
Delete "$INSTDIR\opencv_ml2410.dll"
Delete "$INSTDIR\opencv_nonfree2410.dll"
Delete "$INSTDIR\opencv_objdetect2410.dll"
Delete "$INSTDIR\opencv_ocl2410.dll"
Delete "$INSTDIR\opencv_photo2410.dll"
Delete "$INSTDIR\opencv_stitching2410.dll"
Delete "$INSTDIR\opencv_superres2410.dll"
Delete "$INSTDIR\opencv_video2410.dll"
Delete "$INSTDIR\opencv_videostab2410.dll"
Delete "$INSTDIR\phonon4.dll"
Delete "$INSTDIR\Qt3Support4.dll"
Delete "$INSTDIR\QtCLucene4.dll"
Delete "$INSTDIR\QtCore4.dll"
Delete "$INSTDIR\QtDeclarative4.dll"
Delete "$INSTDIR\QtDesigner4.dll"
Delete "$INSTDIR\QtDesignerComponents4.dll"
Delete "$INSTDIR\QtGui4.dll"
Delete "$INSTDIR\QtHelp4.dll"
Delete "$INSTDIR\QtMultimedia4.dll"
Delete "$INSTDIR\QtNetwork4.dll"
Delete "$INSTDIR\QtOpenGL4.dll"
Delete "$INSTDIR\QtScript4.dll"
Delete "$INSTDIR\QtScriptTools4.dll"
Delete "$INSTDIR\QtSql4.dll"
Delete "$INSTDIR\QtSvg4.dll"
Delete "$INSTDIR\QtTest4.dll"
Delete "$INSTDIR\QtWebKit4.dll"
Delete "$INSTDIR\QtXml4.dll"
Delete "$INSTDIR\QtXmlPatterns4.dll"
Delete "$INSTDIR\ssleay32.dll"
Delete "$INSTDIR\Xalan-C_1_11.dll"
Delete "$INSTDIR\XalanMessages_1_11.dll"
Delete "$INSTDIR\xerces-c_3_1.dll"
Delete "$INSTDIR\xqilla23.dll"
Delete "$INSTDIR\gt_icon.ico"
Delete "$INSTDIR\uninstall.exe"
Delete "$INSTDIR\settings.ini"
Delete "$INSTDIR\Xml\rois.xsd"
Delete "$INSTDIR\Xml\labels.xsd"
Delete "$INSTDIR\Xml\gtp.xsd"
!ifdef WEB_SITE
#Delete "$INSTDIR\${APP_NAME} website.url"
!endif

RmDir "$INSTDIR\Xml"
RmDir "$INSTDIR"

!ifdef REG_START_MENU
#!insertmacro MUI_STARTMENU_GETFOLDER "Application" $SM_Folder
#Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk"
#Delete "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
#Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk"
!endif
#Delete "$DESKTOP\${APP_NAME}.lnk"

#RmDir "$SMPROGRAMS\$SM_Folder"
!endif

#!ifndef REG_START_MENU
Delete "$SMPROGRAMS\GTGenerator_v1.6.1_x86\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\GTGenerator_v1.6.1_x86\Uninstall ${APP_NAME}.lnk"
#!ifdef WEB_SITE
#Delete "$SMPROGRAMS\GTGenerator_v1.6.1_x86\${APP_NAME} Website.lnk"
#!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\GTGenerator_v1.6.1_x86"
#!endif

DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

