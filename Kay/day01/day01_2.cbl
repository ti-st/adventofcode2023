      * day1_2
       identification division.
           program-id. trebuchet_calibration_value_ext.
           author. kayms.
      *
       environment division.
           input-output section.
           file-control.
           select f-input assign to "../input.txt"
           organization is line sequential.

       data division.
           file section.

           fd f-input.
           01 cal_input_line pic x(200).

           working-storage section.

           01 ws-sum pic 9(9).
           01 ws-curr pic 9(9).
           01 ws-first pic 9(1).
           01 ws-last pic 9(1).

           01 ws-char_i pic 9(9).
           01 ws-curr_num pic 9(1).

           01 i pic 9(9).
           01 ws-f-first pic 9(1).

           01 ws-eof pic a(1).

       procedure division.

           open input f-input.
           perform until ws-eof = 'Y'
               read f-input into cal_input_line at
               end move 'Y' to ws-eof
               not at end

               move function lower-case(cal_input_line)
                   to cal_input_line
               perform search_numbers

           end-perform.
           display "sum " ws-sum
           close f-input.
           stop run.

       search_numbers.
           move 1 to i.
           move 0 to ws-f-first.
           move 0 to ws-first.
           move 0 to ws-last.
           move 0 to ws-char_i.
           move 0 to ws-curr_num.

           perform until i >= 200
               if cal_input_line(i:1) is numeric then
                   move function
                   numval(cal_input_line(i:1)) to ws-curr_num
               else
                   move i to ws-char_i
                   perform text_to_num
      *             move ws-char_i to i
               end-if

               if ws-curr_num > 0 then
                   if ws-f-first = 0 then
                       move ws-curr_num to ws-first
                       move ws-curr_num to ws-last
                       move 1 to ws-f-first
                   else
                       move ws-curr_num to ws-last
                   end-if
               end-if

               add 1 to i
           end-perform.

           compute ws-curr = ws-first * 10 + ws-last.
           add ws-curr to ws-sum.


       text_to_num.
           move 0 to ws-curr_num.

           if cal_input_line(ws-char_i:3) = "one"
               move 1 to ws-curr_num
               add 2 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:3) = "two"
               move 2 to ws-curr_num
               add 2 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:5) = "three"
               move 3 to ws-curr_num
               add 4 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:4) = "four"
               move 4 to ws-curr_num
               add 3 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:4) = "five"
               move 5 to ws-curr_num
               add 3 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:3) = "six"
               move 6 to ws-curr_num
               add 2 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:5) = "seven"
               move 7 to ws-curr_num
               add 4 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:5) = "eight"
               move 8 to ws-curr_num
               add 4 to ws-char_i
               exit paragraph
           end-if.

           if cal_input_line(ws-char_i:4) = "nine"
               move 9 to ws-curr_num
               add 3 to ws-char_i
               exit paragraph
           end-if.
