$wifi = $(netsh.exe wlan show profiles)
 
if ($wifi -match "There is no wireless interface on the system."){
    Write-Output $wifi
    exit 
}

 
$ListOfSSID = ($wifi | 
                Select-string -pattern "\w*All User Profile.*: (.*)" -allmatches).Matches | 
                ForEach-Object {$_.Groups[1].Value}
$NumberOfWifi = $ListOfSSID.count
#Write-Warning "[$(Get-Date)] I've found $NumberOfWifi Wi-Fi Connection settings stored in your system $($env:computername) : "


if($args.count -eq 1){ $Input = $args[0] }
else { $Input = $null }


if(!$Input){
    foreach ($SSID in $ListOfSSID){
        try {
            $passphrase = ($(netsh.exe wlan show profiles name=`"$SSID`" key=clear) |
                        Select-String -pattern ".*Key Content.*:(.*)" -allmatches).Matches |
                            ForEach-Object {$_.Groups[1].Value}
        }
        catch {
            $passphrase = "N/A"
        }
        Write-Output "$SSID : $passphrase"
    }
}
else{
        $SSID = $Input
        try {
            $passphrase = ($(netsh.exe wlan show profiles name=`"$SSID`" key=clear) |
                        Select-String -pattern ".*Key Content.*:(.*)" -allmatches).Matches |
                            ForEach-Object {$_.Groups[1].Value}
        }
        catch {
            $passphrase = "N/A"
        }
        Write-Output "$SSID : $passphrase"
}