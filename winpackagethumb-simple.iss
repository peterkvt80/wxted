; Simplified Inno Setup Script - Without Automatic VC++ Installation
; This version is faster and asks users to install VC++ manually if needed

#define MyAppName "wxTED"
#define MyAppVersion "1.65"
#define MyAppPublisher "Peter Kwan"
#define MyAppURL "github.com/peterkvt80/wxted"
#define MyAppExeName "wxTED.exe"

[Setup]
AppId={{BF8D5847-6816-45D9-AB36-99F50155DCE4}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName=wxTED Teletext Editor
AllowNoIcons=yes
OutputDir=E:\dev\wxTED-GitHub\wxted\bin\Release
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
VersionInfoVersion=1.65
ChangesAssociations=yes
PrivilegesRequired=admin
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Components]
Name: "wxTED"; Description: "wxTED Editor (Required)"; Types: full compact custom; Flags: fixed
Name: "thumbnails"; Description: "TTI Thumbnail Provider (Show previews in Explorer)"; Types: full

[Files]
; wxTED application files
Source: "E:\dev\wxTED-GitHub\wxted\bin\Release\wxTED.exe"; DestDir: "{app}"; Flags: ignoreversion; Components: wxTED
Source: "E:\dev\wxTED-GitHub\wxted\bin\Release\BBC100.tti"; DestDir: "{app}"; Flags: ignoreversion; Components: wxTED
Source: "E:\dev\wxTED-GitHub\wxted\bin\Release\wxtedsplash.tti"; DestDir: "{app}"; Flags: ignoreversion; Components: wxTED
Source: "E:\dev\wxTED-GitHub\wxted\bin\Release\manual.pdf"; DestDir: "{app}"; Flags: ignoreversion; Components: wxTED
Source: "E:\dev\wxTED-GitHub\wxted\bin\Release\sample pages\*"; DestDir: "{app}\samples"; Flags: ignoreversion recursesubdirs createallsubdirs; Components: wxTED
Source: "E:\dev\wxTED-GitHub\wxted\bin\Release\Templates\*.tti"; DestDir: "{app}\Templates"; Flags: ignoreversion; Components: wxTED

; Fonts - install system-wide
Source: "E:\dev\wxTED-GitHub\wxted\bin\Release\teletext2.ttf"; DestDir: "{fonts}"; FontInstall: "Teletext2"; Flags: onlyifdoesntexist uninsneveruninstall; Components: wxTED
Source: "E:\dev\TTIIcon\teletext4.ttf"; DestDir: "{fonts}"; FontInstall: "Teletext4"; Flags: onlyifdoesntexist uninsneveruninstall; Components: thumbnails

; Thumbnail Provider DLL
Source: "E:\dev\TTIIcon\files\x64\Release\TTIThumbnailProvider.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace; Components: thumbnails; Check: Is64BitInstallMode

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{group}\Manual"; Filename: "{app}\manual.pdf"

[Registry]
; File associations for wxTED
Root: "HKCR"; Subkey: ".tti"; ValueType: string; ValueData: "{#MyAppName}"; Flags: uninsdeletevalue; Components: wxTED
Root: "HKCR"; Subkey: ".ttix"; ValueType: string; ValueData: "{#MyAppName}"; Flags: uninsdeletevalue; Components: wxTED
Root: "HKCR"; Subkey: ".ep1"; ValueType: string; ValueData: "{#MyAppName}"; Flags: uninsdeletevalue; Components: wxTED
Root: "HKCR"; Subkey: "{#MyAppName}"; ValueType: string; ValueData: "Program {#MyAppName}"; Flags: uninsdeletevalue; ValueName: ""
Root: "HKCR"; Subkey: "{#MyAppName}\DefaultIcon"; ValueType: string; ValueData: "{app}\{#MyAppExeName},0"; ValueName: ""
Root: "HKCR"; Subkey: "{#MyAppName}\shell\open\command"; ValueType: string; ValueData: """{app}\{#MyAppExeName}"" ""%1"""; ValueName: ""

; Thumbnail Provider Shell Extension registration
Root: "HKCR"; Subkey: ".tti\ShellEx\{{E357FCCD-A995-4576-B01F-234630154E96}}"; ValueType: string; ValueData: "{{F8A7B9C2-1234-5678-9ABC-DEF012345678}}"; Flags: uninsdeletevalue; Components: thumbnails
Root: "HKCR"; Subkey: ".ep1\ShellEx\{{E357FCCD-A995-4576-B01F-234630154E96}}"; ValueType: string; ValueData: "{{F8A7B9C2-1234-5678-9ABC-DEF012345678}}"; Flags: uninsdeletevalue; Components: thumbnails

[Run]
; Launch wxTED after installation
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
var
  ThumbnailRegistrationFailed: Boolean;
  VCRuntimeMissing: Boolean;

// Check if Visual C++ Runtime is installed
function IsVCRuntimeInstalled: Boolean;
var
  Major: Cardinal;
begin
  Result := False;
  
  // Check for VC++ 2015-2022 Redistributable (version 14.x)
  if RegQueryDWordValue(HKLM, 'SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x64', 'Major', Major) then
  begin
    if Major >= 14 then
      Result := True;
  end;
  
  // Also check WOW6432Node
  if not Result then
  begin
    if RegQueryDWordValue(HKLM, 'SOFTWARE\WOW6432Node\Microsoft\VisualStudio\14.0\VC\Runtimes\x64', 'Major', Major) then
    begin
      if Major >= 14 then
        Result := True;
    end;
  end;
end;

// Show VC++ Runtime warning if needed
function InitializeSetup(): Boolean;
var
  ResultCode: Integer;
begin
  Result := True;
  VCRuntimeMissing := not IsVCRuntimeInstalled;
  
  if VCRuntimeMissing then
  begin
    if MsgBox('Microsoft Visual C++ Runtime is required for thumbnail previews.' + #13#10 + #13#10 +
              'The runtime is not currently installed on your system.' + #13#10 + #13#10 +
              'Installation will continue, but thumbnail previews may not work.' + #13#10 + #13#10 +
              'Would you like to download and install the VC++ Runtime now?' + #13#10 +
              '(This will open a browser window)',
              mbConfirmation, MB_YESNO) = IDYES then
    begin
      ShellExec('open', 'https://aka.ms/vs/17/release/vc_redist.x64.exe', '', '', SW_SHOWNORMAL, ewNoWait, ResultCode);
      
      MsgBox('Please complete the VC++ Runtime installation, then click OK to continue with wxTED installation.',
             mbInformation, MB_OK);
    end;
  end;
end;

// Register the thumbnail provider DLL
function RegisterThumbnailProvider: Boolean;
var
  ResultCode: Integer;
  DllPath: String;
begin
  Result := False;
  DllPath := ExpandConstant('{app}\TTIThumbnailProvider.dll');
  
  if not FileExists(DllPath) then
  begin
    Log('ERROR: DLL not found at: ' + DllPath);
    Exit;
  end;
  
  Log('Registering: ' + DllPath);
  
  if Exec('regsvr32.exe', '/s "' + DllPath + '"', '', SW_HIDE, ewWaitUntilTerminated, ResultCode) then
  begin
    if ResultCode = 0 then
    begin
      Log('DLL registered successfully');
      Result := True;
    end
    else
    begin
      Log('RegSvr32 failed with exit code: ' + IntToStr(ResultCode));
      
      case ResultCode of
        3: Log('ERROR: Missing dependencies (likely VC++ Runtime)');
        5: Log('ERROR: Access denied');
        else Log('ERROR: Unknown registration failure');
      end;
    end;
  end
  else
  begin
    Log('ERROR: Failed to execute regsvr32.exe');
  end;
end;

// Unregister the thumbnail provider DLL
procedure UnregisterThumbnailProvider;
var
  ResultCode: Integer;
  DllPath: String;
begin
  DllPath := ExpandConstant('{app}\TTIThumbnailProvider.dll');
  
  if FileExists(DllPath) then
  begin
    Log('Unregistering: ' + DllPath);
    Exec('regsvr32.exe', '/u /s "' + DllPath + '"', '', SW_HIDE, ewWaitUntilTerminated, ResultCode);
  end;
end;

// Clear Windows thumbnail cache
procedure ClearThumbnailCache;
var
  CachePath: String;
begin
  Log('Clearing thumbnail cache...');
  CachePath := ExpandConstant('{localappdata}\Microsoft\Windows\Explorer');
  
  if DirExists(CachePath) then
  begin
    DelTree(CachePath + '\thumbcache_*.db', False, True, True);
    Log('Thumbnail cache cleared');
  end;
end;

// Called after installation completes
procedure CurStepChanged(CurStep: TSetupStep);
var
  ErrorMsg: String;
begin
  if CurStep = ssPostInstall then
  begin
    if IsComponentSelected('thumbnails') then
    begin
      Log('Registering thumbnail provider...');
      
      if not RegisterThumbnailProvider then
      begin
        ThumbnailRegistrationFailed := True;
        
        // Build error message
        ErrorMsg := 'The thumbnail provider could not be registered.' + #13#10 + #13#10;
        
        if VCRuntimeMissing then
        begin
          ErrorMsg := ErrorMsg + 'This is likely because the Visual C++ Runtime is not installed.' + #13#10 + #13#10 +
                      'To fix this:' + #13#10 +
                      '1. Download VC++ Runtime from: https://aka.ms/vs/17/release/vc_redist.x64.exe' + #13#10 +
                      '2. Install it' + #13#10 +
                      '3. Re-run this installer' + #13#10 + #13#10;
        end
        else
        begin
          ErrorMsg := ErrorMsg + 'You can try manual registration:' + #13#10 +
                      '  Open Command Prompt as Administrator and run:' + #13#10 +
                      '  regsvr32 "' + ExpandConstant('{app}') + '\TTIThumbnailProvider.dll"' + #13#10 + #13#10;
        end;
        
        ErrorMsg := ErrorMsg + 'wxTED will work normally, but thumbnail previews will not appear.';
        
        MsgBox(ErrorMsg, mbError, MB_OK);
      end
      else
      begin
        ClearThumbnailCache;
        Log('Thumbnail provider registered successfully');
      end;
    end;
  end;
end;

// Called when setup is finished
procedure DeinitializeSetup();
var
  Response: Integer;
  ResultCode: Integer;
begin
  // Ask to restart Explorer only if registration succeeded
  if IsComponentSelected('thumbnails') and not ThumbnailRegistrationFailed then
  begin
    Response := MsgBox('To enable thumbnail previews, Windows Explorer should be restarted.' + #13#10 + #13#10 +
                       'Restart Windows Explorer now?' + #13#10 +
                       '(All Explorer windows will close briefly)',
                       mbConfirmation, MB_YESNO or MB_DEFBUTTON2);
    
    if Response = IDYES then
    begin
      Exec('taskkill', '/f /im explorer.exe', '', SW_HIDE, ewNoWait, ResultCode);
      Sleep(1500);
      ShellExec('', ExpandConstant('{win}\explorer.exe'), '', '', SW_SHOWNORMAL, ewNoWait, ResultCode);
    end
    else
    begin
      MsgBox('Thumbnail previews will be available after restarting Windows Explorer or rebooting.', 
             mbInformation, MB_OK);
    end;
  end;
end;

// Called during uninstallation
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usUninstall then
  begin
    UnregisterThumbnailProvider;
  end;
end;
