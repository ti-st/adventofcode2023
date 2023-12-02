      * day1_1
       identification division.
           program-id. trebuchet_calibration_value.
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


           01 i pic 9(9).
           01 ws-f-first pic 9(1).

           01 ws-eof pic a(1).

       procedure division.

           open input f-input.
           perform until ws-eof = 'Y'
               read f-input into cal_input_line at
               end move 'Y' to ws-eof
               not at end

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

           perform until i = 200
               if cal_input_line(i:1) is numeric then
                   if ws-f-first = 0 then
                       move function
                       numval(cal_input_line(i:1)) to ws-first
                       move ws-first to ws-last
                       move 1 to ws-f-first
                   else
                       move function
                       numval(cal_input_line(i:1)) to ws-last
                   end-if
               end-if
               add 1 to i
           end-perform.

           compute ws-curr = ws-first * 10 + ws-last.
           add ws-curr to ws-sum.
