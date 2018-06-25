use v5.16.0;
use strict;
use warnings;
use integer;

BEGIN { unshift @INC, '.' }

require './regen/regen_lib.pl';
require './regen/charset_translations.pl';

# Generates the EBCDIC translation tables that were formerly hard-coded into
# utfebcdic.h

my $out_fh = open_new('ebcdic_tables.h', '>',
        {style => '*', by => $0, });

sub output_table ($$;$) {
    my $table_ref = shift;
    my $name = shift;

    # 0 => print in decimal
    # 1 => print in hex (translates code point to code point)
    # >= 2 => is a dfa table, like http://bjoern.hoehrmann.de/utf-8/decoder/dfa/
    #      The number is how many columns in the part after the code point
    #      portion.
    #
    # code point tables in hex areasier to debug, but don't fit into 80
    # columns
    my $type = shift // 1;

    my $print_in_hex = $type == 1;
    my $is_dfa = ($type >= 2) ? $type : 0;
    my $columns_after_256;

    die "Requres 256 entries in table $name, got @$table_ref"
                                if ! $is_dfa && @$table_ref != 256;
    if (! $is_dfa) {
        die "Requres 256 entries in table $name, got @$table_ref"
                                                        if @$table_ref != 256;
    }
    else {
        $columns_after_256 = $is_dfa;
    }

    my $TYPE = 'U8';
    $TYPE = 'U16' if grep { $_ > 255 } @$table_ref;
    my $declaration = "EXTCONST $TYPE $name\[\]";
    print $out_fh <<EOF;
#  ifndef DOINIT
#    $declaration;
#  else
#    $declaration = {
EOF

    my $column_numbers= "/*_0   _1   _2   _3   _4   _5   _6   _7   _8   _9   _A   _B   _C   _D   _E  _F*/\n";
    print $out_fh $column_numbers if $print_in_hex;
    my $count = @$table_ref;
    for my $i (0 .. $count - 1) {
        if ($print_in_hex) {
            # No row headings, so will fit in 80 cols.
            #printf $out_fh "/* %X_ */ ", $i / 16 if $i % 16 == 0;
            printf $out_fh "0x%02X", $table_ref->[$i];
        }
        else {
            printf $out_fh "%4d", $table_ref->[$i];
        }
        print $out_fh ",", if $i < $count -1;
        #print $out_fh ($i < $count -1) ? "," : " ";
        #printf $out_fh " /* %X_ */", $i / 16 if $print_in_hex && $i % 16 == 15;
        if ($is_dfa) {
            if ($i <= 255) {
                printf $out_fh " /*%02X-%02X*/\n", $i-15, $i if $i % 16 == 15;
            }
            elsif (($i - 256) % $columns_after_256 == $columns_after_256 - 1)
            {
                my $node = ($i - 256) / $columns_after_256;
                printf $out_fh " /*N%d=%d*/\n", $node, $i - 255 - $columns_after_256;
            }
        }
        else {
            print $out_fh "\n" if $i % 16 == 15;
        }
    }
    print $out_fh $column_numbers if $print_in_hex;
    print $out_fh "};\n#  endif\n\n";
}

print $out_fh <<END;

#ifndef PERL_EBCDIC_TABLES_H_   /* Guard against nested #includes */
#define PERL_EBCDIC_TABLES_H_   1

/* This file contains definitions for various tables used in EBCDIC handling.
 * More info is in utfebcdic.h */
END

my @charsets = get_supported_code_pages();
shift @charsets;    # ASCII is the 0th, and we don't deal with that here.
foreach my $charset (@charsets) {
    # we process the whole array several times, make a copy
    my @a2e = @{get_a2n($charset)};

    print $out_fh "\n" . get_conditional_compile_line_start($charset);
    print $out_fh "\n";

    print $out_fh "/* Index is ASCII platform code point; value is $charset equivalent */\n";
    output_table(\@a2e, "PL_a2e");

    { # Construct the inverse
        my @e2a;
        for my $i (0 .. 255) {
            $e2a[$a2e[$i]] = $i;
        }
        print $out_fh "/* Index is $charset code point; value is ASCII platform equivalent */\n";
        output_table(\@e2a, "PL_e2a");
    }

    my @i82utf = @{get_I8_2_utf($charset)};
    print $out_fh <<END;
/* (Confusingly named) Index is $charset I8 byte; value is
 * $charset UTF-EBCDIC equivalent */
END
    output_table(\@i82utf, "PL_utf2e");

    { #Construct the inverse
        my @utf2i8;
        for my $i (0 .. 255) {
            $utf2i8[$i82utf[$i]] = $i;
        }
        print $out_fh <<END;
/* (Confusingly named) Index is $charset UTF-EBCDIC byte; value is
 * $charset I8 equivalent */
END
        output_table(\@utf2i8, "PL_e2utf");
    }

    {
        my @utf8skip;

        # These are invariants or continuation bytes.
        for my $i (0 .. 0xBF) {
            $utf8skip[$i82utf[$i]] = 1;
        }

        # These are start bytes;  The skip is the number of consecutive highest
        # order 1-bits (up to 7)
        for my $i (0xC0 .. 255) {
            my $count;
            if ($i == 0b11111111) {
                no warnings 'once';
                $count = $CHARSET_TRANSLATIONS::UTF_EBCDIC_MAXBYTES;
            }
            elsif (($i & 0b11111110) == 0b11111110) {
                $count= 7;
            }
            elsif (($i & 0b11111100) == 0b11111100) {
                $count= 6;
            }
            elsif (($i & 0b11111000) == 0b11111000) {
                $count= 5;
            }
            elsif (($i & 0b11110000) == 0b11110000) {
                $count= 4;
            }
            elsif (($i & 0b11100000) == 0b11100000) {
                $count= 3;
            }
            elsif (($i & 0b11000000) == 0b11000000) {
                $count= 2;
            }
            else {
                die "Something wrong for UTF8SKIP calculation for $i";
            }
            $utf8skip[$i82utf[$i]] = $count;
        }

        print $out_fh <<END;
/* Index is $charset UTF-EBCDIC byte; value is UTF8SKIP for start bytes
 * (including for overlongs); 1 for continuation.  Adapted from the shadow
 * flags table in tr16.  The entries marked 9 in tr16 are continuation bytes
 * and are marked as length 1 here so that we can recover. */
END
        output_table(\@utf8skip, "PL_utf8skip", 0);  # The 0 means don't print
                                                     # in hex
    }

    use feature 'unicode_strings';

    {
        my @lc;
        for my $i (0 .. 255) {
            $lc[$a2e[$i]] = $a2e[ord lc chr $i];
        }
        print $out_fh "/* Index is $charset code point; value is its lowercase equivalent */\n";
        output_table(\@lc, "PL_latin1_lc");
    }

    {
        my @uc;
        for my $i (0 .. 255) {
            my $uc = uc chr $i;
            if (length $uc > 1 || ord $uc > 255) {
                $uc = "\N{LATIN SMALL LETTER Y WITH DIAERESIS}";
            }
            $uc[$a2e[$i]] = $a2e[ord $uc];
        }
        print $out_fh <<END;
/* Index is $charset code point; value is its uppercase equivalent.
 * The 'mod' in the name means that codepoints whose uppercase is above 255 or
 * longer than 1 character map to LATIN SMALL LETTER Y WITH DIARESIS */
END
        output_table(\@uc, "PL_mod_latin1_uc");
    }

    { # PL_fold
        my @ascii_fold;
        for my $i (0 .. 255) {  # Initialise to identity map
            $ascii_fold[$i] = $i;
        }

        # Overwrite the entries that aren't identity
        for my $chr ('A' .. 'Z') {
            $ascii_fold[$a2e[ord $chr]] = $a2e[ord lc $chr];
        }
        for my $chr ('a' .. 'z') {
            $ascii_fold[$a2e[ord $chr]] = $a2e[ord uc $chr];
        }
        print $out_fh <<END;
/* Index is $charset code point; For A-Z, value is a-z; for a-z, value
 * is A-Z; all other code points map to themselves */
END
        output_table(\@ascii_fold, "PL_fold");
    }

    {
        my @latin1_fold;
        for my $i (0 .. 255) {
            my $char = chr $i;
            my $lc = lc $char;

            # lc and uc adequately proxy for fold-case pairs in this 0-255
            # range
            my $uc = uc $char;
            $uc = $char if length $uc > 1 || ord $uc > 255;
            if ($lc ne $char) {
                $latin1_fold[$a2e[$i]] = $a2e[ord $lc];
            }
            elsif ($uc ne $char) {
                $latin1_fold[$a2e[$i]] = $a2e[ord $uc];
            }
            else {
                $latin1_fold[$a2e[$i]] = $a2e[$i];
            }
        }
        print $out_fh <<END;
/* Index is $charset code point; value is its other fold-pair equivalent
 * (A => a; a => A, etc) in the 0-255 range.  If no such equivalent, value is
 * the code point itself */
END
        output_table(\@latin1_fold, "PL_fold_latin1");
    }

    {
      # This generates the dfa table for perl extended UTF-8, which accepts
      # surrogates, non-characters, and accepts start bytes up through FE.
      # The classes have been renumbered so that the patterns are more evident
      # in the table.  The class numbers for start bytes are constrained so
      # that they can be used as a shift count for masking off the leading one
      # bits
      #
      # The classes are
      #   00-9F           0
      #   A0-A1           7   Not legal immediately after start bytes F0 F8 FC
      #                       FE
      #   A2-A3           8   Not legal immediately after start bytes F0 F8 FC
      #   A4-A7           9   Not legal immediately after start bytes F0 F8
      #   A8-AF          10   Not legal immediately after start bytes F0
      #   B0-BF          11
      #   C0-C4           1
      #   C5-DF           2
      #   E0              1
      #   E1-EF           3
      #   F0             12
      #   F1-F7           4
      #   F8             13
      #   F9-FB           5
      #   FC             14
      #   FD              6
      #   FE             15
      #   FF              1
      #
      # The first part of the table maps bytes to character classes to reduce
      # the size of the transition table and create bitmasks.
      #
      # The second part is a transition table that maps a combination of a
      # state of the automaton and a character class to a new state.  The
      # numbering of the original nodes is retained, but some have been split
      # so that there are new nodes.  They mean:
      # N0     The initial state, and final accepting one.
      # N1     One continuation byte (A0-BF) left.  This is transitioned to
      #        immediately when the start byte indicates a two-byte sequence
      # N2     Two continuation bytes left.
      # N3     Three continuation bytes left.
      # N4     Four continuation bytes left.
      # N5     Five continuation bytes left.
      # N6     Start byte is F0.  Only a subset of continuation bytes is
      #        legal, causing transition to state N2
      # N7     Start byte is F8.  Only a subset of continuation bytes is
      #        legal, causing transition to state N3
      # N8     Start byte is FC.  Only a subset of continuation bytes is
      #        legal, causing transition to state N4
      # N9     Start byte is FE.  Only a subset of continuation bytes is
      #        legal, causing transition to state N5
      # 1      Reject.  All transitions not mentioned above (except the single
      #        byte ones (as they are always legal) are to this state.

        my $NUM_CLASSES = 16;
        my $N0 = 0;
        my $N1 =  $N0 + $NUM_CLASSES;
        my $N2 =  $N1 + $NUM_CLASSES;
        my $N3 =  $N2 + $NUM_CLASSES;
        my $N4 =  $N3 + $NUM_CLASSES;
        my $N5 =  $N4 + $NUM_CLASSES;
        my $N6 =  $N5 + $NUM_CLASSES;
        my $N7 =  $N6 + $NUM_CLASSES;
        my $N8 =  $N7 + $NUM_CLASSES;
        my $N9 =  $N8 + $NUM_CLASSES;
        my $N10 = $N9 + $NUM_CLASSES;

        my @perl_extended_utf8_dfa;
        my @i8 = (
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 00-0F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 10-1F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 20-2F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 30-3F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 40-4F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 50-5F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 60-6F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 70-7F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 80-8F
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, # 90-9F
                  7, 7, 8, 8, 9, 9, 9, 9,10,10,10,10,10,10,10,10, # A0-AF
                 11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11, # B0-BF
                  1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, # C0-CF
                  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, # D0-DF
                  1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, # E0-EF
                 12, 4, 4, 4, 4, 4, 4, 4,13, 5, 5, 5,14, 6,15, 1, # F0-FF
                );
        $perl_extended_utf8_dfa[$i82utf[$_]] = $i8[$_] for (0 .. 255);
        push @perl_extended_utf8_dfa, (
          # Class:
          # 0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15
            0,  1,$N1,$N2,$N3,$N4,$N5,  1,  1,  1,  1,  1,$N6,$N7,$N8,$N9, # N0
            1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  0,  0,  1,  1,  1,  1, # N1
            1,  1,  1,  1,  1,  1,  1,$N1,$N1,$N1,$N1,$N1,  1,  1,  1,  1, # N2
            1,  1,  1,  1,  1,  1,  1,$N2,$N2,$N2,$N2,$N2,  1,  1,  1,  1, # N3
            1,  1,  1,  1,  1,  1,  1,$N3,$N3,$N3,$N3,$N3,  1,  1,  1,  1, # N4
            1,  1,  1,  1,  1,  1,  1,$N4,$N4,$N4,$N4,$N4,  1,  1,  1,  1, # N5

            1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,$N2,  1,  1,  1,  1, # N6
            1,  1,  1,  1,  1,  1,  1,  1,  1,  1,$N3,$N3,  1,  1,  1,  1, # N7
            1,  1,  1,  1,  1,  1,  1,  1,  1,$N4,$N4,$N4,  1,  1,  1,  1, # N8
            1,  1,  1,  1,  1,  1,  1,  1,$N5,$N5,$N5,$N5,  1,  1,  1,  1, # N9
        );
        output_table(\@perl_extended_utf8_dfa, "perl_extended_utf8_dfa_tab",
                                                                   $NUM_CLASSES);
    }

    print $out_fh get_conditional_compile_line_end();
}

print $out_fh "\n#endif /* PERL_EBCDIC_TABLES_H_ */\n";

read_only_bottom_close_and_rename($out_fh);
