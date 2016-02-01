#
# @(#) $Id: //bas/BIN/src/maketools/u16lit.pl#21 $ SAP
#
#  Copyright (C) 2001, SAP AG, Neurottstrasse 16, 69190 Walldorf, 
#  GERMANY.
#
# This script converts C/C++ source code on platforms where the type 
# 'unsigned short' is used for Unicode characters and literals for
# this type are not supported.
#
# Literals that are preceeded by _U16_LIT_iU are converted to array
# initializers.  Literals that are preceeded by _U16_LIT_cU are
# converted to pointers to a constant unsigned short array (unless it
# is "obvious" that they are array initializers).  A special handling
# is necessary if the literal is the argument of a sizeof.
#
# This script is called after the C/C++ preprocessor and before the
# native compiler.
# Invocation:
#   perl u16lit.pl [-cpp] [-le|-be] <source>.ii
# This will produce a file <source>.i, which can be compiled by the
# native compiler.
# Options:
#   -cpp : C++ coding.
#   -le  : The platform is little endian (auto-detected).
#   -be  : The platform is big endian (auto-detected).
#
# Known restrictions:
# - Initializers with optional braces are not supported, e.g.
#   SAP_UC s[8] = { iU("ABC") };
# - char s[3] = "ABC";  is correct in C, but an error in C++. We follow
#   C++ and do not support 
#   SAP_UC s[3] = iU("ABC");
# - This script cannot detect if you use string literals as C++ template
#   arguments.

use strict;

########################################################################
# Global variables
########################################################################
use vars qw($buf_size $buf_idx $litp_idx @buf $cur_pos @lit_ar $mod_line);
use vars qw($iu_flag $char_flag $pre_pos);
use vars qw($infile $cpp_flag $le_flag $asciistring_flag $debug_flag);

########################################################################
# check if any options are set
########################################################################

# C++ 
$cpp_flag = 0;
# endianess (autodetect)
if ( pack("s",1) eq "\1\0" ) {
	$le_flag = 1;	# little-endian
} else {
	$le_flag = 0;	# big-endian
}
# normal ASCII strings or wchar style strings
$asciistring_flag = 0;
# insert debugging stuff
$debug_flag = 0;

while( $ARGV[0] =~ /^-/ )
  {
    if( $ARGV[0] eq "-cpp" ) 
      {
	$cpp_flag = 1;
	shift @ARGV;
      } 
    if( $ARGV[0] eq "-le" ) 
      {
        if ( $le_flag eq 0 ) {
		print "WARNING (u16lit.pl): Overriding autodetected big-endian mode !\n";
	}
	$le_flag = 1;
	shift @ARGV;
      } 
    if( $ARGV[0] eq "-be" ) 
      {
        if ( $le_flag eq 1 ) {
		print "WARNING (u16lit.pl): Overriding autodetected little-endian mode !\n";
	}
	$le_flag = 0;
	shift @ARGV;
      } 
    if( $ARGV[0] eq "-asciistring" ) 
      {
	$asciistring_flag = 1;
	shift @ARGV;
      } 
    if( $ARGV[0] eq "-wcharstring" ) 
      {
	$asciistring_flag = 0;
	shift @ARGV;
      } 
    if( $ARGV[0] eq "-debug" ) 
      {
	$debug_flag = 1;
	shift @ARGV;
      } 
    if( $ARGV[0] eq "-sp" ) 
      {
	# Ignore this (obsolete) flag.
	shift @ARGV;
      } 
  }

########################################################################
# Initialize global variables
########################################################################
# number of lines to be buffered
$buf_size = 40;         
$buf_idx = -1;

# current position in current line $_; all what is before $cur_pos has already
# been written to $mod_line (perhaps after modification).
$cur_pos = 0;

# integer array to hold literals
@lit_ar = ( );

# modified line to be written to OUTF
$mod_line = "";

########################################################################
# Open input and output files.
########################################################################
$_ = $ARGV[0];
$infile = $_ ;
open( INF, $_ ) || error_die("open $_ failed");
s/\.ii/.i/ ;
open( OUTF, ">$_" ) || error_die ("open $_ failed");

########################################################################
# Loop over input lines
########################################################################
while(1 == get_line( ) )
  {
    my $parsing_line = 1;
    while ($parsing_line == 1)
      {
	# Does the rest of the cur. line have a _U16_LIT_ ?
	$pre_pos = index( $_, "_U16_LIT_", $cur_pos ) ;
	if ($pre_pos == -1)
	  {
	    # No literal. Write the rest of the current line.
	    if ($cur_pos < length )
	      {
		$mod_line .= substr( $_, $cur_pos );
	      }
	    # Exit the loop
	    $parsing_line = 0;
	  }
	else
	  {
	    # Write what comes before the literal
	    $mod_line .= substr( $_, $cur_pos, $pre_pos - $cur_pos );

	    $cur_pos = $pre_pos;
	    $litp_idx = $buf_idx;
	    if ( search_quote( ) == 0 ) 
	      {
		# No literal.
		error_die( "No cU/iU literal after _U16_LIT_" );
	      }
	    if ($char_flag == 1)
	      {
		single_quote( );
	      }
	    elsif ($char_flag == 0)
	      {
		double_quote( );
	      }
	  }
      }
    print OUTF "$mod_line" ;
  }

exit 0;
#### end of the main program ###########################################

########################################################################
# Search for the beginning of a literal.
#   - Start search at $cur_pos in $_.
#   - Set $char_flag.
#   - Set $iu_flag.
#   - Set $cur_pos to position of (single or double) quote.
#   - Return 0 if there is no literal. Else return 1.
########################################################################
sub search_quote
  {
    my $t_str = substr( $_, $cur_pos );
    if ( $t_str =~ /^\s*_U16_LIT_cU/ )
      {
	$cur_pos = index( $_, "_U16_LIT_cU", $cur_pos ) 
	  + length("_U16_LIT_cU");
	$iu_flag = 0;
      }
    elsif ( $t_str =~ /^\s*_U16_LIT_iU/ )
      {
	$cur_pos = index( $_, "_U16_LIT_iU", $cur_pos ) 
	  + length("_U16_LIT_iU");
	$iu_flag = 1;
      }
    elsif ( $t_str =~ /^\s*$/ )
      {
	# We have to look at the next line.
	# First, finish the current line.
	print OUTF "$mod_line\n" ;
	if ( 0 == get_line( ) )
	  {
	    error_die( "Unexpected end of file" );
	  }
	if ( /^\s*_U16_LIT_cU/ )
	  {
	    $cur_pos = index( $_, "_U16_LIT_cU" ) 
	      + length("_U16_LIT_cU");
	    $iu_flag = 0;
	  }
	elsif ( /^\s*_U16_LIT_iU/ )
	  {
	    $cur_pos = index( $_, "_U16_LIT_iU" ) 
	      + length("_U16_LIT_iU");
	    $iu_flag = 1;
	  }
	else
	  {
	    return 0;
	  }
      }
    else
      {
	return 0;
      }
    # Find the single or double quote
    $t_str = substr( $_, $cur_pos );
    if ( $t_str =~ /^\s*\"/ )
      {
	$cur_pos = index( $_, "\"", $cur_pos );
	$char_flag = 0;
      }
    elsif ( $t_str =~ /^\s*\'/ )
      {
	$cur_pos = index( $_, "'", $cur_pos );
	$char_flag = 1;
      }
    elsif ( $t_str =~ /^\s*$/ )
      {
	# We have to look at the next line.
	# First, finish the current line.
	print OUTF "$mod_line\n" ;
	if ( 0 == get_line( ) )
	  {
	    error_die( "Unexpected end of file" );
	  }
	if ( /^\s*\"/ )
	  {
	    $cur_pos = index( $_, "\"" );
	    $char_flag = 0;
	  }
	elsif ( /^\s*\'/ )
	  {
	    $cur_pos = index( $_, "'" );
	    $char_flag = 1;
	  }
	else
	  {
	    error_die( "No literal after _U16_LIT_..." );
	  }
      }
    elsif ( $t_str =~ /^ *\\\"/ )
      {
        # set char_flag=-1 -> ignore this literal since we are inside a string (e.g. in assert()),
        # changed d040425 December 4th 2002
       $char_flag = -1;
      }
    else
      {
       error_die( "No literal after _U16_LIT_...(".$t_str.")" );
      }
    return 1;
  }


########################################################################
# Deal with a single quote in $_ at position $cur_pos
#   - Append to $mod_line
#   - Increment $cur_pos
########################################################################
sub single_quote
  {
    # Find closing ' ; first consider special case '\''.
    # $cont_pos is the position after the closing '
    my $cont_pos;
    if ( "'\\''" eq substr( $_, $cur_pos, 4 ) )
      {
	$cont_pos = $cur_pos + 4;
      }
    else
      {
	$cont_pos = 1 + index( $_, "'", $cur_pos + 1 );
	if ($cont_pos == 0)
	  {
	    error_die("Can't find closing \"'\" ");
	  }
      }
    if ( $cpp_flag == 1 )
      {
	# For C++, insert a cast
	$mod_line .= "(SAP_UTF16)";
      }
    # Write '...'
    $mod_line .= substr( $_, $cur_pos, $cont_pos - $cur_pos );
    $cur_pos = $cont_pos;
  }

########################################################################
# Deal with a double quote in $_ at position $cur_pos
#   - Check whether the literal is the argument of a sizeof
#   - Append to $mod_line
#   - Increment $cur_pos
########################################################################
sub double_quote
  {
    # Is the string literal the argument of a sizeof or a simple
    # array initializer?
    my $ar_sizeof_flag = search_ar_sizeof( );

    # Parse till the end of the literal and increment $cur_pos. 
    parse_string_lit( );

    if ( $ar_sizeof_flag == 1 )
      {
	write_sizeof_arg( );
      }
    elsif ( $iu_flag == 1 || $ar_sizeof_flag == 2 )
      {
	write_ini_array( );
      }
    else
      {
	write_ptr_lit( );
      }
  }

########################################################################
# Search backwards to see whether the string literal is 
#     (1) the argument of a sizeof or
#     (2) the initializer of a "simple" array.
#   - Start search at $pre_pos - 1 .
#   - Return 1 in case (1), 2 in case (2), else 0.
########################################################################
sub search_ar_sizeof
  {
    # Line where the _U16_LIT_ occurred.
    my $back_idx = $litp_idx;

    my $z_str = "";
    if ( $pre_pos > 0 )
      {
	$z_str = substr( $buf[$back_idx], 0, $pre_pos - 1 );
      }

    # state has following values:
    # 1 if '(' was consumed;
    # 2 if '=' was consumed.
    my $state = 0;

    while (1 == 1)
      {
	if ( $z_str =~ /sizeof(\s*\()*\s*$/ )
	  {
	    # We have ... sizeof ( ... ( <literal>
	    if ( $state == 2 )
	      {
		error_die( "Unexpected '='" );
	      }
	    return 1;
	  }
	elsif ( $z_str =~ /^\s*$/ )
	  {
	    # Only whitespace.
	    # Don't change state.
	  }
	elsif ( $state != 2 && ( $z_str =~ /^(\s*\()+\s*$/ ) )
	  {
	    # We have ... ( ... ( <literal>
	    $state = 1;
	  }
	elsif ( $state != 1 && ( $z_str =~ /^\s*=\s*$/ ) )
	  {
	    # We have ... = <literal>
	    $state = 2;
	  }
	elsif ( ( $state == 2 &&
		  $z_str =~ /\WSAP_CHAR\s+\w+\s*\[\s*[0-9]*\s*\]\s*$/ ) ||
		( $state == 2 &&
		  $z_str =~   /\WSAP_UC\s+\w+\s*\[\s*[0-9]*\s*\]\s*$/ ) ||
		( $state == 0 &&
		  $z_str =~ /\WSAP_CHAR\s+\w+\s*\[\s*[0-9]*\s*\]\s*=\s*$/ ) ||
		( $state == 0 &&
		  $z_str =~   /\WSAP_UC\s+\w+\s*\[\s*[0-9]*\s*\]\s*=\s*$/ )
	      )
	  {
	    # Simple array initialization
	    return 2;
	  }
	else
	  {
	    return 0;
	  }
	# We must look at the previous line
	$back_idx = ( $back_idx - 1 ) % $buf_size;
	if ( $back_idx == $buf_idx )
	  {
	    # @buf is exhausted.
	    error_die( "Statement exceeds $buf_size lines" );
	  }
	$z_str = $buf[$back_idx] ;
      }
  }

########################################################################
# Parse string literal till closing '"'.
#   - Opening '"' is in $_ at position $cur_pos.
#   - The position after the closing '"' will be returned.
#   - The literal is stored in @lit_ar as an array of integers.
########################################################################
sub parse_string_lit
  {
    @lit_ar = ( );
    my $num_str;

    # index in array @lit_ar
    my $c_idx = 0;

    # position in $_
    $cur_pos += 1;

    while (1 == 1)
      {
	if ( $cur_pos > length )
	  {
	    error_die( "Unexpected end of line" );
	  }

	my $s_str = substr( $_, $cur_pos );
	if ( $s_str =~ /^\\[\'\"\?\\]/ )
	  {
	    # escaped ' " ? \ 
 	    $lit_ar[$c_idx++] = ord( substr( $s_str, 1 ) );
	    $cur_pos += 2;
	  }
	elsif ( $s_str =~ /^\\a/ )
	  {
	    $lit_ar[$c_idx++] = 0x7;
	    $cur_pos += 2;
	  }
	elsif ( $s_str =~ /^\\b/ )
	  {
	    $lit_ar[$c_idx++] = 0x8;
	    $cur_pos += 2;
	  }
	elsif ( $s_str =~ /^\\f/ )
	  {
	    $lit_ar[$c_idx++] = 0xc;
	    $cur_pos += 2;
	  }
	elsif ( $s_str =~ /^\\n/ )
	  {
	    $lit_ar[$c_idx++] = 0xa;
	    $cur_pos += 2;
	  }
	elsif ( $s_str =~ /^\\r/ )
	  {
	    $lit_ar[$c_idx++] = 0xd;
	    $cur_pos += 2;
	  }
	elsif ( $s_str =~ /^\\t/ )
	  {
	    $lit_ar[$c_idx++] = 0x9;
	    $cur_pos += 2;
	  }
	elsif ( $s_str =~ /^\\v/ )
	  {
	    $lit_ar[$c_idx++] = 0xb;
	    $cur_pos += 2;
	  }
	elsif ( ($num_str) = ( $s_str =~ /^\\([0-7]+)/ ) )
	  {
	    # octal number, at most 3 digits
	    $num_str = substr( $num_str, 0, 3 );
	    $lit_ar[$c_idx++] = oct( $num_str );
	    $cur_pos += length( $num_str ) + 1;
	  }
	elsif ( ($num_str) = ( $s_str =~ /^\\x([0-9a-fA-F]+)/ ) )
	  {
	    # hexadecimal number, no limit on number of digits
	    $lit_ar[$c_idx++] = hex( $num_str );
	    $cur_pos += length( $num_str ) + 2;
	  }
	elsif ( ($num_str) = ( $s_str =~ /^\\u([0-9a-fA-F]+)/ ) )
	  {
	    # universal character name, at most 4 digits
	    # (Standard says: exactly 4 digits)
	    $num_str = substr( $num_str, 0, 4 );
	    $lit_ar[$c_idx++] = hex( $num_str );
	    $cur_pos += length( $num_str ) + 2;
	  }
	elsif ( ($num_str) = ( $s_str =~ /^\\U([0-9a-fA-F]+)/ ) )
	  {
	    # universal character name, at most 8 digits
	    # (Standard says: exactly 8 digits)
	    # TODO: convert from UTF-32 to UTF-16
	    $num_str = substr( $num_str, 0, 8 );
	    $lit_ar[$c_idx++] = hex( $num_str );
	    $cur_pos += length( $num_str ) + 2;
	  }
	elsif ( $s_str =~ /^\\/ )
	  {
	    error_die( "String literal contains undefined escape sequence" );
	  }
	elsif ( $s_str =~ /^\"/ )
	  {
	    # Closing '"'
	    $cur_pos += 1;

	    # Check if another string literal follows
	    if ( search_quote( ) == 0 )
	      {
		last;
	      }
	    else
	      {
		# Another string literal follows
		if ($char_flag == 1)
		  {
		    error_die( "Syntax error" );
		  }
		$cur_pos += 1;
	      }
	  }
	else
	  {
	    # Ordinary character
 	    $lit_ar[$c_idx++] = ord( $s_str );
	    $cur_pos += 1;
	  }
      } # End of while loop
  }

########################################################################
# Read lines until there is a line that is not whitespace and does not
# start with '#'.
#   - initialize $mod_line
#   - save line in @buf
#   - initialize $cur_pos
########################################################################
sub get_line
  {
    while(<INF>)
      {
	$mod_line = "";
	# Only whitespace in cur. line?
	if ( /^\s*$/ )         
	  { 
	    $mod_line = $_;
	    next; 
	  }
	# Does line start with '#' ? ('\#' because of Emacs indentation) 
	if ( /^\#/ )
	  { 
	    $mod_line = $_;
	    next; 
	  }
	$buf_idx = ( $buf_idx + 1 ) % $buf_size ;
	$buf[$buf_idx] = $_ ; 	 
	
	# current position in current line
	$cur_pos = 0;
	return 1;
      } continue
      { 
	print OUTF "$mod_line" ;   
      }
    return 0;
  }

########################################################################
# Format the contents of @lit_ar as
#   {0x41,0x42,0}     (for instance)
#   - Append to $mod_line.
########################################################################
sub write_ini_array
  {
    $mod_line .= "{";
    my $c_int;
    foreach $c_int (@lit_ar)
      {
	$mod_line .= sprintf("0x%x,", $c_int );
      }
    $mod_line .= "0}";
  }

########################################################################
# Process the contents of @lit_ar to get
#   "+++++"     (5 '+' if there are 2 characters in @lit_ar).
#   - Append to $mod_line.
#
# Further remark:
# sizeof(SAP_UC[3]) would also work, but
# sizeof SAP_UC[3]  and sizeof((SAP_UC[3])) would be syntax errors.
########################################################################
sub write_sizeof_arg
  {
    # $#lit_ar is the index of the last element in @lit_ar.
    # One terminating zero-byte is appended anyway.
    my $cnt = $#lit_ar * 2 + 3;
    $mod_line .= "\"" . ( "+" x $cnt ) . "\"" ;
  }

########################################################################
# Format the contents of @lit_ar. Example:
#   @lit_ar = ( 0x41, 0x42, 0x43, 0x44, 0x45 );
# On a big endian machine, this gives:
#   ((SAP_UTF16 *)L"\x410042\x430044\x450000")
# On a little endian machine:
#   ((SAP_UTF16 *)L"\x420041\x440043\x000045")
#
#   - Append to $mod_line.
#
# Further remarks:
#
# We do not write (const SAP_UTF16 *) because that results in too many
# warnings.
#
# The C Standard ISO 9899:1999 allows "compound literals", see Section
# 6.5.2.5: 
#   memcpy( s1, (unsigned short []){ 'A', 'B', 0 }, 6 ) ; 
# With gcc version 2.95.2 and egcs-2.91.66 on Linux, this works
# (in C and C++).
# On HP-UX 11 and Digital Unix 4.0, this gives a syntax error. 
#
# On HP-UX 11, (unsigned short *)"\000A\000B\000" gives the message:
# "Casting from loose to strict alignment: Resulting pointer may be misaligned."
# And in fact we need the correct alignment for SAP_UTF16* .
# Alternatives: 
# a) Initialize a static variable (with a generated name) at the 
#    beginning of the file.
# b) Generate xU("\000A\000B\000\000A\000B\000"). Here our string occurs
#    twice with different alignment, and xU() is a function that selects
#    the correctly aligned array at run time.
# c) Misuse L"..."
#
########################################################################
sub write_ptr_lit_wcharstring
  {
    $mod_line .= "((SAP_UTF16*)L\"";
    my $ar_len = $#lit_ar + 1;
    # length of @lit_ar might be odd, but we want to read an even number
    # of characters. So append a '\0'.
    $lit_ar[$ar_len] = 0;
    my $cur_c = 0;
    my $x_str;
    
    while ( $cur_c < $ar_len )
      {
	if ( $le_flag == 1 )
	  {
	    # Little endian
	    $x_str = sprintf("\\x%04x%04x", $lit_ar[$cur_c + 1], 
			                    $lit_ar[$cur_c]);
	  }
	else
	  {
	    # Big endian
	    $x_str = sprintf("\\x%04x%04x", $lit_ar[$cur_c], 
			                    $lit_ar[$cur_c + 1]);
	  }
	$cur_c += 2;
	$mod_line .= $x_str;
      }
    $mod_line .= "\")";
  }


#############################################################################
# Format the contents of @lit_ar in style of standard ASCII strings. Example:
#   @lit_ar = ( 0x61, 0x62, 0x63 );
# On a big endian machine, this gives:
#   ((SAP_UTF16 *) "\0A\0B\0C\0";
# On a little endian machine:
#   ((SAP_UTF16 *) "A\0B\0C\0")
#
#   - Append to $mod_line.
#
# NOTES:
#
# - currently we use this function for AIX 5.1 only.
# - at the end we add an \0 byte. The other needed one will be added by the compiler.
#
#############################################################################
sub write_ptr_lit_asciistring
  {
    if ( $debug_flag ) {
       $mod_line .= "dbgAlignCheckStringU16(\"";
    } else {
       $mod_line .= "((SAP_UTF16*) \"";
    }
    my $ar_len = $#lit_ar;
    my $cur_c = 0;
    my $x_str;
    my $a;
    
    while ( $cur_c <= $ar_len )
      {
	$a = $lit_ar[$cur_c];
	
	if ( chr($a) =~ /[a-zA-Z !&\/\?\(\);:,\-]/ ) {
	 # it's a printable ascii character...
	 # (except digits, which could be interpreted as octals)
	 if ( $le_flag == 1 ) {
		$x_str = sprintf("%c\\0", $a ); # Little endian
	 } else {
		$x_str = sprintf("\\0%c", $a ); # Big endian
	 }
	 
	} else {
	
	 # we need to print the hex notation
	 if ( $le_flag == 1 ) {
		# Little endian
		if ( $a < 256 ) {  # shorten the string if possible.
			$x_str = sprintf("\\x%02x\\0", $a );
		} else {
			$x_str = sprintf("\\x%02x\\x%02x", $a % 256, $a / 256 );
		}
	 } else {
		# Big endian
		if ( $a < 256 ) {  # shorten the string if possible.
			$x_str = sprintf("\\0\\x%02x", $a );
		} else {
			$x_str = sprintf("\\x%02x\\x%02x", $a / 256, $a % 256 );
		}
	 }
	 
	}

	$cur_c += 1;
	$mod_line .= $x_str;
      }

    # add the trailing 0-byte, another one will be added by the compiler.
    $mod_line .= "\\0";
    $mod_line .= "\")";
  }


sub write_ptr_lit()
  {
    if ($asciistring_flag ne 0) {
    	write_ptr_lit_asciistring( );
    } else {
    	write_ptr_lit_wcharstring( );
    }
  }


########################################################################
# Output compiler-like message and die
########################################################################
sub error_die
  {
    my $txt = $_[0];
    # $. is the line number in the input file <INF> .
    print STDERR "$infile:$.: $txt --";
    die "dying";
  }
