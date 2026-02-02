; Improved Inno Setup Script with VC++ Runtime and Error Handling
; Addresses RegSvr32 exit code 0x3 issue

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
; Ensure 64-bit installation on 64-bit systems
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

; Thumbnail Provider DLL - DO NOT use 'regserver' flag, we'll register manually
Source: "E:\dev\TTIIcon\files\x64\Release\TTIThumbnailProvider.dll"; DestDir: "{app}"; Flags: ignoreversion restartreplace; Components: thumbnails; Check: Is64BitInstallMode

; Visual C++ Redistributable (if not already installed)
; Download from: https://aka.ms/vs/17/release/vc_redist.x64.exe
; Place this file in your installer source directory
; NOTE: This line will be ignored if the file doesn't exist (skipifdoesntexist flag in [Run])
Source: "vc_redist.x64.exe"; DestDir: "{tmp}"; Flags: deleteafterinstall; Check: VCRedistNeedsInstall

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
; Note: We register the ShellEx key here, COM registration is done in [Code] section
Root: "HKCR"; Subkey: ".tti\ShellEx\{{E357FCCD-A995-4576-B01F-234630154E96}}"; ValueType: string; ValueData: "{{F8A7B9C2-1234-5678-9ABC-DEF012345678}}"; Flags: uninsdeletevalue; Components: thumbnails
Root: "HKCR"; Subkey: ".ep1\ShellEx\{{E357FCCD-A995-4576-B01F-234630154E96}}"; ValueType: string; ValueData: "{{F8A7B9C2-1234-5678-9ABC-DEF012345678}}"; Flags: uninsdeletevalue; Components: thumbnails

[Run]
; Install Visual C++ Runtime if needed (before DLL registration)
; Use /install and /passive for better user feedback instead of /quiet
Filename: "{tmp}\vc_redist.x64.exe"; Parameters: "/install /passive /norestart"; StatusMsg: "Installing Visual C++ Runtime (this may take a few minutes)..."; Flags: waituntilterminated skipifdoesntexist; Check: VCRedistNeedsInstall

; Launch wxTED after installation
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
var
  ThumbnailRegistrationFailed: Boolean;

// Check if Visual C++ Runtime needs to be installed
function VCRedistNeedsInstall: Boolean;
var
  Major: Cardinal;
  Minor: Cardinal;
  Bld: Cardinal;
  Rbld: Cardinal;
begin
  // Check for VC++ 2015-2022 Redistributable (version 14.x)
  // Try multiple registry locations as different versions use different keys
  Result := True; // Assume needs install
  
  // Check x64 runtime
  if RegQueryDWordValue(HKLM, 'SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\x64', 'Major', Major) then
  begin
    if Major >= 14 then
      Result := False; // Already installed
  end;
  
  // Also check WOW6432Node for 32-bit registry view
  if Result then
  begin
    if RegQueryDWordValue(HKLM, 'SOFTWARE\WOW6432Node\Microsoft\VisualStudio\14.0\VC\Runtimes\x64', 'Major', Major) then
    begin
      if Major >= 14 then
        Result := False; // Already installed
    end;
  end;
  
  if Result then
    Log('VC++ Runtime not found, will install')
  else
    Log('VC++ Runtime already installed, skipping');
end;

// Register the thumbnail provider DLL
function RegisterThumbnailProvider: Boolean;
var
  ResultCode: Integer;
  DllPath: String;
  RetryCount: Integer;
begin
  Result := False;
  DllPath := ExpandConstant('{app}\TTIThumbnailProvider.dll');
  
  if not FileExists(DllPath) then
  begin
    Log('ERROR: DLL not found at: ' + DllPath);
    Exit;
  end;
  
  Log('Attempting to register: ' + DllPath);
  
  // Try registration with retry logic
  RetryCount := 0;
  while (RetryCount < 3) and (not Result) do
  begin
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
        
        // Specific error messages for common codes
        case ResultCode of
          3: Log('ERROR: The system cannot find the path specified (missing dependencies?)');
          5: Log('ERROR: Access denied (run as administrator?)');
          else Log('ERROR: Unknown registration failure');
        end;
        
        // Wait a bit before retry
        Sleep(1000);
        RetryCount := RetryCount + 1;
      end;
    end
    else
    begin
      Log('ERROR: Failed to execute regsvr32.exe');
      Exit;
    end;
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
    
    if Exec('regsvr32.exe', '/u /s "' + DllPath + '"', '', SW_HIDE, ewWaitUntilTerminated, ResultCode) then
    begin
      if ResultCode = 0 then
        Log('DLL unregistered successfully')
      else
        Log('RegSvr32 unregister failed with code: ' + IntToStr(ResultCode));
    end;
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
    // Delete all thumbcache files
    DelTree(CachePath + '\thumbcache_*.db', False, True, True);
    Log('Thumbnail cache cleared');
  end;
end;

// Restart Windows Explorer to reload shell extensions
// NOTE: This is now called at the very end via DeinitializeSetup
procedure RestartExplorer;
var
  ResultCode: Integer;
  ExplorerPath: String;
begin
  Log('Preparing to restart Windows Explorer...');
  
  // Use full path to explorer.exe
  ExplorerPath := ExpandConstant('{win}\explorer.exe');
  
  // Kill explorer (don't wait - let it happen asynchronously)
  if Exec('taskkill', '/f /im explorer.exe', '', SW_HIDE, ewNoWait, ResultCode) then
    Log('Sent kill signal to explorer.exe')
  else
    Log('Could not send kill signal to explorer.exe');
  
  // Wait a moment
  Sleep(1500);
  
  // Start explorer using ShellExecute-style approach
  if ShellExec('', ExplorerPath, '', '', SW_SHOWNORMAL, ewNoWait, ResultCode) then
    Log('Started explorer.exe')
  else
    Log('WARNING: Failed to start explorer.exe');
end;

// Called after installation completes
procedure CurStepChanged(CurStep: TSetupStep);
begin
  if CurStep = ssPostInstall then
  begin
    Log('Post-install step started');
    
    // Only if thumbnail component was selected
    if IsComponentSelected('thumbnails') then
    begin
      Log('Thumbnail component selected, proceeding with registration');
      
      // Register the DLL
      if not RegisterThumbnailProvider then
      begin
        ThumbnailRegistrationFailed := True;
        Log('WARNING: Thumbnail provider registration failed');
        
        // Show user-friendly error message
        MsgBox('The thumbnail provider could not be registered.' + #13#10 + #13#10 +
               'Possible causes:' + #13#10 +
               '  - Missing Visual C++ Runtime (should have been installed)' + #13#10 +
               '  - Antivirus blocking registration' + #13#10 +
               '  - Insufficient permissions' + #13#10 + #13#10 +
               'You can try manual registration later:' + #13#10 +
               '  1. Open Command Prompt as Administrator' + #13#10 +
               '  2. Run: regsvr32 "' + ExpandConstant('{app}') + '\TTIThumbnailProvider.dll"' + #13#10 + #13#10 +
               'wxTED will work normally, but thumbnail previews may not appear.',
               mbError, MB_OK);
      end
      else
      begin
        // Success - clear cache only
        ClearThumbnailCache;
        Log('Registration successful, cache cleared');
      end;
    end;
    
    Log('Post-install step completed');
  end;
end;

// Called when setup is completely finished and about to close
procedure DeinitializeSetup();
var
  Response: Integer;
begin
  Log('DeinitializeSetup called');
  
  // Only restart Explorer if thumbnails were successfully registered
  if IsComponentSelected('thumbnails') and not ThumbnailRegistrationFailed then
  begin
    // Ask user if they want to restart Explorer now
    Response := MsgBox('Windows Explorer needs to be restarted to enable thumbnail previews.' + #13#10 + #13#10 +
                       'Restart Windows Explorer now?' + #13#10 + #13#10 +
                       'Note: All Explorer windows will close temporarily.',
                       mbConfirmation, MB_YESNO);
    
    if Response = IDYES then
    begin
      RestartExplorer;
      Log('User chose to restart Explorer');
    end
    else
    begin
      Log('User chose not to restart Explorer');
      MsgBox('Thumbnail previews will be available after you restart Windows Explorer or reboot your computer.', 
             mbInformation, MB_OK);
    end;
  end;
end;

// Called during uninstallation
procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  if CurUninstallStep = usUninstall then
  begin
    Log('Uninstall: Unregistering thumbnail provider');
    UnregisterThumbnailProvider;
  end;
end;

// Show final page with status
procedure CurPageChanged(CurPageID: Integer);
begin
  if CurPageID = wpFinished then
  begin
    if ThumbnailRegistrationFailed then
    begin
      WizardForm.FinishedLabel.Caption := 
        WizardForm.FinishedLabel.Caption + #13#10 + #13#10 +
        'Note: Thumbnail previews may not work due to registration failure. ' +
        'See the error message for details.';
    end;
  end;
end;
