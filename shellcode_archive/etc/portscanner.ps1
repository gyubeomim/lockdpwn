# powershell ==> 해킹침투코드, 호스트의 포트를 스캐닝하는 코드 
                
# put our arguments into their respective variables
$device = $args[0]
$port  = $args[1]
$start = $args[2]
$stop = $args[3]


# function pingdevice
# ping the device to see if it is on te network
function pingdevice
{
    if(test-connection $device -erroraction silentlycontinue)
    {
        Write-Output "$device is up"
    }
    else
    {
        Write-Output "$device is down"
        exit
    }
}

# function checkports
# check to see if our ports ar open 
function checkports
{
    if ($port -match "multi")
    {
        #this branch check a port range
        for ($counter = $start; $counter -le $stop; $counter ++)
        {
            Write-Output "testing port $counter on $device"
            $porttest = New-Object Net.Sockets.TcpClient
            try{
                $connect = $porttest.connect($device,$counter)
                Write-Output "$counter is open"
                }catch{
                Write-Output "$counter is closed"
            }
        }
    }
    else
    { 
    #this branch checks a single port
    Write-Output "testing port $port on $device"
    $porttest = New-Object Net.Sockets.TcpClient
    try
    {
        $connect = $porttest.connect($device,$port)
        Write-Output "$port is open"
    }
    catch
    {
        Write-Output "$port is closed"
    }
  }
}

 #run our function
 pingdevice
 checkports
