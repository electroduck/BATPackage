SetCompressor /SOLID lzma
Outfile "BATPackageInstall.exe"
Name "BATPackage"

InstallDir $PROGRAMFILES\BATPackage
RequestExecutionLevel admin

LicenseData LICENSE.txt

Page license
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section
	SetOutPath $INSTDIR
	File exefrombat.exe
	File loader.exe
	File pad.exe
	File GUI\Release\BATPackage.exe
	WriteUninstaller $INSTDIR\Uninstall.exe
	
	CreateDirectory $SMPROGRAMS\BATPackage
	CreateShortCut "$SMPROGRAMS\BATPackage\BATPackage.lnk" "$INSTDIR\BATPackage.exe"
	CreateShortCut "$SMPROGRAMS\BATPackage\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
SectionEnd

Section "un.Uninstall"
	RMDir /r $INSTDIR
	RMDir /r "$SMPROGRAMS\BATPackage"
SectionEnd