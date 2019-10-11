
username=user
server_ip=ip_addr
server_ssh_port=port

ssh -XgtL 5901:localhost:5900 $username@$server_ip -p $server_ssh_port

